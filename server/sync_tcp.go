package server

import (
	"bufio"
	"encoding/json"
	"fmt"
	"io"
	"net"
	"strconv"
	"strings"

	"github.com/ChandanKhamitkar/BranchDB/config"
	"github.com/ChandanKhamitkar/BranchDB/core"
	"github.com/ChandanKhamitkar/BranchDB/models"
)

func readCommand(c net.Conn) (*models.Command, error) {
	reader := bufio.NewReader(c)
	input, err := reader.ReadString('\n')
	if err != nil {
		return nil, err
	}

	input = strings.TrimSpace(input)
	return core.ParseCommand(input)
}

func respond(cmd string, c net.Conn) error {
	// convert the cmd of type string to byte while sending back to client
	// as network expects data in byte slices
	// _ represents no of bytes done, so no need here
	// if error occurs return err, else return nil in case of success
	if _, err := c.Write([]byte(cmd)); err != nil {
		return err
	}
	return nil
}

func RunSyncTCPServer() {
	fmt.Println("Starting the Synchronous TCP server on : ", config.Host, config.Port)

	var con_clients int = 0

	// listen to configured host & port
	listner, err := net.Listen("tcp", config.Host+":"+strconv.Itoa(config.Port))
	if err != nil {
		panic(err)
	}

	for {
		// Accept the client connection request
		con, err := listner.Accept()
		if err != nil {
			fmt.Println("Failed to accept connection:", err)
			continue
		}

		// Increment the no.of connected clients
		con_clients += 1
		fmt.Println("Client connected with address : ", con.RemoteAddr(), " Concurrent Clients : ", con_clients)

		//Handle Clients in Seperate Go routines
		go func(conn net.Conn) {
			defer conn.Close()
			defer func() {
				con_clients -= 1
				fmt.Println("Client disconnected:", conn.RemoteAddr(), "Concurrent Clients:", con_clients)
			}()

			for {
				// on the connected socket, continuously read the command and print it out
				cmd, err := readCommand(con)
				fmt.Println("cmd = ", cmd)
				if err != nil {
					if err == io.EOF {
						return
					}
					fmt.Println("Read Error : ", err)
					return
				}

				fmt.Println("Command Read : ", cmd)
				responseBytes, _ := json.Marshal(cmd)

				// after reading data, respond back to client
				if err = respond(string(responseBytes), con); err != nil {
					fmt.Println("Write Error: ", err)
					return
				}
			}
		}(con)
	}

}

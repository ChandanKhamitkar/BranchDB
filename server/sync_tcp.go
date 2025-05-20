package server

import (
	"bufio"
	"encoding/json"
	"io"
	"log"
	"net"
	"strconv"
	"strings"
	"time"

	"github.com/ChandanKhamitkar/BranchDB/config"
	"github.com/ChandanKhamitkar/BranchDB/core"
	"github.com/ChandanKhamitkar/BranchDB/models"
)

// Initializing Store
var store = core.NewStore()

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
	log.Println("Starting the Synchronous TCP server on : ", config.Host, config.Port)

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
			log.Println("Failed to accept connection:", err)
			continue
		}

		// Increment the no.of connected clients
		con_clients += 1
		log.Println("Client connected with address : ", con.RemoteAddr(), " Concurrent Clients : ", con_clients)

		//Handle Clients in Seperate Go routines
		go func(conn net.Conn) {
			time.Sleep(100 * time.Millisecond)
			defer conn.Close()
			defer func() {
				con_clients -= 1
				log.Println("Client disconnected:", conn.RemoteAddr(), "Concurrent Clients:", con_clients)
			}()

			for {
				// on the connected socket, continuously read the command and print it out
				cmd, err := readCommand(con)
				log.Println("cmd = ", cmd)
				if err != nil {
					if err == io.EOF {
						return
					}
					log.Println("Read Error : ", err)
					return
				}

				// Execute Command 📍
				resp := core.ExecuteCommand(cmd, store)
				responseBytes, _ := json.Marshal(resp)

				// after reading data, respond back to client
				if err = respond(string(responseBytes)+"\n", con); err != nil {
					log.Println("Write Error: ", err)
					return
				}
			}
		}(con)
	}

}

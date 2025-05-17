package server

import (
	"fmt"
	"io"
	"net"
	"strconv"

	"github.com/ChandanKhamitkar/BranchDB/config"
)

func readCommand(c net.Conn) (string, error) {
	var buf []byte = make([]byte, 512)
	n, err := c.Read(buf[:])
	if err != nil {
		return "", err
	}
	return string(buf[:n]), nil
}

func respond(cmd string, c net.Conn) error {
	// convert the cmd of type string to byte while sending back to client
	// as network expects data in byte slices
	// _ represents no of bytes done, so no need here
	// if error occurs return err, else return nil in case of success
	if _,err := c.Write([]byte(cmd)); err != nil { 
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
			panic(err)
		}

		// Increment the no.of connected clients
		con_clients += 1
		fmt.Println("Client connected with address : ", con.RemoteAddr(), " Concurrent Clients : ", con_clients)
		
		for {
			// on the connected socket, continuously read the command and print it out
			cmd, err := readCommand(con)
			if err != nil {
				con.Close()
				con_clients -= 1
				fmt.Println("Client Disconnected : ", con.RemoteAddr(), " Concurrent Clients : ", con_clients)

				// if no more data ot read, if reached end of data
				if err == io.EOF {
					break
				}
				fmt.Println("err : ", err)
			}

			fmt.Println("Command Read : ", cmd)

			// after reading data, respond back to client
			if err = respond(cmd, con); err != nil {
				fmt.Println("Error in write: ", err)
			}
		}
	}
	
}
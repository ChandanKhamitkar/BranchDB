package main

import (
	"flag"
	"log"

	"github.com/ChandanKhamitkar/BranchDB/config"
	"github.com/ChandanKhamitkar/BranchDB/server"
)

func setUpFlags() {
	flag.StringVar(&config.Host, "host", "0.0.0.0", "Host for the Branch Server")
	flag.IntVar(&config.Port, "port", 9379, "Port for the Branch Server")
	flag.Parse()
}

func main() {
	setUpFlags()
	log.Println("Growing the Branch Data 🌿")
	server.RunSyncTCPServer()
}
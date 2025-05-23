package core

import (
	"log"
	"strings"

	"github.com/ChandanKhamitkar/BranchDB/models"
)

func ExecuteCommand(cmd *models.Command, store *Store) *models.Response {
	log.Println("Command TYPE: ", cmd.Cmd)
	if cmd.Cmd == "SET" {
		log.Println("Value received to executable : ", cmd.Data.Value)
	}

	switch cmd.Cmd {
	case "SET":
		// if no value then send
		if strings.TrimSpace(cmd.Data.Value) == "" {
			return &models.Response{Status: "ERR", Result: "SET command expects value"}
		}
		store.SET(cmd.Key, cmd.Data.Value, cmd.Data.ExpiresAt)
		return &models.Response{Status: "OK", Result: "store"}

	case "GET":
		val, ok := store.GET(cmd.Key)
		if !ok {
			return &models.Response{Status: "ERR", Result: "key not found"}
		}
		return &models.Response{Status: "OK", Result: val}

	case "DELETE":
		ok := store.DELETE(cmd.Key)
		if !ok {
			return &models.Response{Status: "ERR", Result: "key not found"}
		}
		return &models.Response{Status: "OK", Result: "deleted"}

	case "PING":
		return &models.Response{Status: "OK", Result: "PONG"}

	default:
		return &models.Response{Status: "ERR", Result: "unknown command"}
	}
}

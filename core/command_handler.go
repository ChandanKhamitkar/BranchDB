package core

import "github.com/ChandanKhamitkar/BranchDB/models"

func ExecuteCommand(cmd *models.Command, store *Store) *models.Response {
	switch cmd.Cmd {
	case "SET":
		store.SET(cmd.Key, cmd.Value)
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

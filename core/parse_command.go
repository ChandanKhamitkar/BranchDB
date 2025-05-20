package core

import (
	"encoding/json"
	"errors"
	"log"
	"strings"

	"github.com/ChandanKhamitkar/BranchDB/models"
)

func ParseCommand(input string) (*models.Command, error) {
	log.Println("input recevied for parsing : ", input)
	
	// find the length of parts in string
	parts := strings.Fields(input)

	if len(parts) == 0 {
		return nil, errors.New("empty command")
	}

	cmdType := strings.ToUpper(parts[0])
	cmd := &models.Command{
		Cmd: cmdType,
	}

	// supports commands like `PING`
	if len(parts) == 1 {
		return cmd, nil
	}

	// Key also been passed
	cmd.Key = parts[1]

	// if `value` to passed ( Must be JSON format )
	if len(parts) > 2 {
		valuePart := strings.Join(parts[2:], " ")

		// validate JSON
		if json.Valid([]byte(valuePart)) {
			cmd.Value = valuePart
		} else {
			// throw error and terminate connection
			return nil, errors.New("value passed is not a valid JSON")
		}
	}

	return cmd, nil
}

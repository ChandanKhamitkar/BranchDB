package core

import (
	"encoding/json"
	"errors"
	"fmt"
	"strings"

	"github.com/ChandanKhamitkar/BranchDB/models"
)

func ParseCommand(input string) (*models.Command, error) {
	fmt.Println("input got : ", input)
	// find the length of parts in string
	parts := strings.Fields(input)

	if len(parts) < 2 {
		return nil, errors.New("invalid command")
	}

	// Only two parts ( cmd type, key )
	cmd := &models.Command{
		Cmd: strings.ToUpper(parts[0]),
		Key: parts[1],
	}

	// if `value` to passed ( Must be JSON format )
	if len(parts) > 2 {
		valuePart := strings.Join(parts[2:], " ")

		// validate JSON
		if json.Valid([]byte(valuePart)) {
			cmd.Value = valuePart
		} else {
			// throw error and terminate connection
			return nil, errors.New("value passed is not a json type")
		}
	}

	return cmd, nil
}

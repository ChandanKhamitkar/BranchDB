package core

import (
	"encoding/json"
	"errors"
	"log"
	"strconv"
	"strings"
	"time"

	"github.com/ChandanKhamitkar/BranchDB/models"
)

func ParseCommand(input string) (*models.Command, error) {
	log.Println("input recevied for parsing : ", input)
	input = strings.TrimSpace(input)

	if input == "" {
		return nil, errors.New("empty command")
	}

	// Tokenize basic command type
	parts := strings.SplitN(input, " ", 3)
	log.Println("parts length = ", len(parts))
	if len(parts) < 1 {
		return nil, errors.New("invalid command")
	}

	cmd := &models.Command{
		Cmd: strings.ToUpper(parts[0]),
	}

	// supports commands like `PING`
	if len(parts) == 1 {
		return cmd, nil
	}

	// Key also been passed
	cmd.Key = parts[1]

	// GET, DELETE
	if len(parts) == 2 && (cmd.Key == "GET" || cmd.Key == "DELETE") {
		return cmd, nil
	}

	if cmd.Cmd == "SET" {
		// process value + optional EX
		valueSection := parts[2]
		exIndex := strings.LastIndex(strings.ToUpper(valueSection), "EX ")
		expiresAt := time.Time{}

		var valuePart string
		if exIndex != -1 {
			valuePart = strings.TrimSpace(valueSection[:exIndex])
			ttlStr := strings.TrimSpace(valueSection[exIndex+3:])
			ttl, err := strconv.Atoi(ttlStr)
			if err != nil {
				return nil, errors.New("invalid TTL value")
			}
			expiresAt = time.Now().Add(time.Duration(ttl) * time.Second)
		} else {
			valuePart = strings.TrimSpace(valueSection)
		}

		if json.Valid([]byte(valuePart)) {
			cmd.Data = models.Data{
				Value:     valuePart,
				ExpiresAt: expiresAt,
			}
		} else {
			return nil, errors.New("value passed is not a valid JSON")
		}
	}
	return cmd, nil
}

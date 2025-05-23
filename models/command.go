package models

import "time"

type Command struct {
	Cmd  string `json:"cmd"`
	Key  string `json:"key,omitempty"`
	Data Data   `json:"data"`
}

type Data struct {
	Value     string    `json:"value,omitempty"`
	ExpiresAt time.Time `json:"expires_at,omitzero"`
}

type Response struct {
	Status string `json:"status"`
	Result string `json:"result,omitempty"`
	Error  string `json:"error,omitempty"`
}

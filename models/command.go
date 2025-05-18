package models

type Command struct {
	Cmd   string `json:"cmd"`
	Key   string `json:"key"`
	Value string `json:"value,omitempty"`
}

type Response struct {
	Status string `json:"status"`
	Result string `json:"result,omitempty"`
	Error  string `json:"error,omitempty"`
}

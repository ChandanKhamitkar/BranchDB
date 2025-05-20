package core

import "sync"

type Store struct {
	mu sync.RWMutex
	data map[string]string // both key value is of type string
}

// Initialize NewStore
func NewStore() *Store {
	return &Store{
		data: make(map[string]string),
	}
}

// SET method 
// First `Lock` before Writing value
// (s *Store) -> assuming `s` as instance name for store in this func
// and any modification made here will reflect in actual store as well
func (s *Store) SET(key, value string) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.data[key] = value
}

// GET method
// First `Read Lock`
func (s *Store) GET(key string) (string, bool) {
	s.mu.RLock()
	defer s.mu.RUnlock()
	val, ok := s.data[key]
	return val, ok
}

// DELETE method
// First `Lock`
func (s *Store) DELETE(key string) (bool) {
	s.mu.Lock()
	defer s.mu.Unlock()
	
	// check if `key` exists
	_, exists := s.data[key]
	if exists {
		delete(s.data, key)
		return true
	}
	
	return false
}
package core

import (
	"sync"
	"time"

	"github.com/ChandanKhamitkar/BranchDB/models"
)

type Store struct {
	mu sync.RWMutex
	data map[string]models.Data // both key value is of type string
}

// Initialize NewStore
func NewStore() *Store {
	return &Store{
		data: make(map[string]models.Data),
	}
}

// SET method 
// First `Lock` before Writing value
// (s *Store) -> assuming `s` as instance name for store in this func
// and any modification made here will reflect in actual store as well
func (s *Store) SET(key, value string, ttl time.Time) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.data[key] = models.Data{
		Value: value,
		ExpiresAt : ttl,
	}
}

// GET method
// First `Read Lock`
func (s *Store) GET(key string) (string, bool) {
	s.mu.RLock()
	val, ok := s.data[key]

	// Check TTL while retriving
	if !val.ExpiresAt.IsZero() && time.Now().After(val.ExpiresAt) {
		// expired
		s.mu.RUnlock()
		s.mu.Lock()
		delete(s.data, key)
		s.mu.Unlock()
		return "", false;
	}

	s.mu.RUnlock()
	return val.Value, ok
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

// --- TTL ---
// Periodically Deletes expired keys
func (s *Store) TTL_Reaper(interval time.Duration) {
	go func () {
		for {
			time.Sleep(interval)
			now := time.Now()

			s.mu.Lock()
			for key, ttl := range s.data {
				if !ttl.ExpiresAt.IsZero() && now.After(ttl.ExpiresAt) {
					delete(s.data, key)
				}
			}
			s.mu.Unlock()
		}
	}()
}
# Branch DB

**Branch DB** is a lightweight, high-performance, and simple key-value database built in Go. It offers in-memory and on-disk persistence for storing and retrieving data efficiently. This project aims to provide a basic yet powerful storage engine to experiment with low-level database concepts.

## Features

- **Key-Value Store:** Simple and efficient key-value pair storage
- **Persistence:** Supports on-disk storage with append-only logs for durability
- **Serialization:** Efficient binary format for encoding and decoding data
- **Concurrency:** Reader-Writer locks for thread-safe operations
- **Indexing:** In-memory indexing using a B-tree (or other structures) for fast lookups
- **API/CLI Support:** Basic command-line interface for interacting with the database


### ✅ In Scope:
- Basic key-value data storage engine
- On-disk persistence via append-only logs
- In-memory indexing for fast key lookups
- Data serialization/deserialization logic
- Safe concurrent access (read/write locks)
- Simple CLI interface for basic operations
- Unit, integration, and benchmark testing
- Clear documentation and open-source release


## 🎯 Project Goals  
### 🎯 Primary Goals:
- Build a functional, performant key-value store in Go
- Learn low-level storage and database design concepts
- Implement both in-memory and on-disk storage strategies
- Ensure safe concurrent access using Go’s concurrency primitives
- Create a simple CLI for interacting with the database
- Document all components with a clear, beginner-friendly explanation
- Open-source the project under an MIT license with a clean GitHub repo

## Architecture

Branch DB is designed with a minimalistic architecture to focus on core database principles like storage, indexing, and concurrency. The system consists of the following components:

1. **Storage Engine** – Manages in-memory and on-disk data storage.
2. **Indexing System** – Uses B-trees (or other methods) to index data for faster retrieval.
3. **Concurrency Layer** – Implements thread-safety with read-write locks.
4. **Persistence Layer** – Ensures durability by writing data to disk via log files.


## Run Code
```
go run main.go
```
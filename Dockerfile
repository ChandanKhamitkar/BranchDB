FROM gcc:12 AS builder

WORKDIR /app

RUN apt-get update && \
    apt-get install -y --no-install-recommends cmake make libboost-all-dev && \
    rm -rf /var/lib/apt/lists/*

COPY . .

RUN mkdir -p build && cd build && \
    cmake .. && \
    cmake --build .

FROM debian:bookworm-slim

WORKDIR /app

EXPOSE 1981

COPY --from=builder /app/build/BranchDB ./BranchDB

CMD ["./BranchDB"]
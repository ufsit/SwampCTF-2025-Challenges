FROM rust:latest AS builder

WORKDIR /usr/src/app

COPY . .

RUN cargo build --release

FROM rust:latest

WORKDIR /usr/src/app

COPY --from=builder /usr/src/app/target/release/server .
COPY ./data /usr/src/app/data

RUN chmod +x server

CMD ["./server", "/usr/src/app/data"]

HEALTHCHECK --interval=30s --timeout=10s --start-period=10s CMD pgrep server || exit 1

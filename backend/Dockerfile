# Build stage
FROM alpine:3.18 AS build

# Install build dependencies
RUN apk add --no-cache \
    build-base \
    cmake \
    git \
    openssl-dev \
    sqlite-dev \
    asio-dev

WORKDIR /app

# Copy source files
COPY . .

# Build the C++ project
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --target api

# Runner stage
FROM alpine:3.18

RUN apk add --no-cache \
    libstdc++ \
    openssl \
    sqlite-libs

WORKDIR /app

# Copy binary and database directory from build stage
COPY --from=build /app/build/api /app/api
COPY --from=build /app/core /app/core

EXPOSE 18080

# Run API server
CMD ["./api"]

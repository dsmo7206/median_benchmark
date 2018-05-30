#!/usr/bin/env bash

set -e

echo "Building C++..."
cd cpp
make
cd ..

echo "Building Go..."
cd go
go build
cd ..

echo "Building Rust..."
cd rust
cargo build --release
cd ..

echo "All done!"

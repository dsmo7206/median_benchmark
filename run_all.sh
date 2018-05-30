#!/usr/bin/env bash

set -e

SIZE=5000000

echo ""
echo "Running C++..."
./cpp/median $SIZE

echo ""
echo "Running Go..."
./go/go $SIZE

echo ""
echo "Running Python..."
./py/median.py $SIZE

echo ""
echo "Running Rust..."
./rust/target/release/median $SIZE

echo ""
echo "All done!"

#!/bin/bash

# 确保从项目根目录执行
cd "$(dirname "$0")/.." || exit 1
if [ ! -d "APP" ]; then
    echo "Error: Please run from algorithm_packet root directory"
    exit 1
fi

PROJECTS=(
    "binary_indexed_tree"
    "graph_dijkstra_floyd" 
    "hash_table"
    "union_find_sets"
)

for proj in "${PROJECTS[@]}"; do
    echo "===================================="
    echo "Building $proj..."
    echo "===================================="
    
    cd "APP/$proj/build" || {
        echo "Error: Failed to enter $proj build directory"
        exit 1
    }
    
    ./build.sh --no-remote || {
        echo "Error: $proj build failed"
        exit 1
    }
    
    cd ../../.. || exit 1
    echo "$proj build completed"
    echo
done

echo "All projects built successfully"

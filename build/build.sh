#!/bin/bash

# 确保从项目根目录执行
cd "$(dirname "$0")/.." || exit 1
if [ ! -d "APP" ]; then
    echo "Error: Please run from algorithm_packet root directory"
    exit 1
fi

# 自动检测APP目录下的模块
modules=()
while IFS= read -r -d '' dir; do
    if [ -f "$dir/CMakeLists.txt" ]; then
        modules+=("$(basename "$dir")")
    fi
done < <(find APP -maxdepth 1 -mindepth 1 -type d -print0)

if [ ${#modules[@]} -eq 0 ]; then
    echo "Error: No valid modules found in APP directory"
    exit 1
fi

# 排序模块名称
IFS=$'\n' modules=($(sort <<<"${modules[*]}"))
unset IFS

show_menu() {
    clear
    echo "==================================="
    echo "   Algorithm Packet Build System   "
    echo "==================================="
    echo
    echo "Available modules in APP directory:"
    
    local i=1
    for module in "${modules[@]}"; do
        echo "[$i] $module"
        ((i++))
    done
    
    local all_option=$i
    ((i++))
    local clear_option=$i
    ((i++))
    local exit_option=$i
    
    echo "[$all_option] ALL - Build all modules"
    echo "[$clear_option] CLEAR - Clean build directories"
    echo "[$exit_option] Exit"
    echo
    read -p "Please select an option (1-$exit_option): " choice
    
    # 验证输入
    if [[ ! "$choice" =~ ^[0-9]+$ ]] || [ "$choice" -lt 1 ] || [ "$choice" -gt "$exit_option" ]; then
        echo "Invalid choice! Please try again."
        read -n 1 -s -r -p "Press any key to continue..."
        return 1
    fi
    
    if [ "$choice" -eq "$all_option" ]; then
        build_all
    elif [ "$choice" -eq "$clear_option" ]; then
        clean_all
    elif [ "$choice" -eq "$exit_option" ]; then
        exit_program
    else
        local selected_index=$((choice - 1))
        if [ "$selected_index" -lt "${#modules[@]}" ]; then
            build_module "${modules[$selected_index]}"
        else
            echo "Invalid module selection!"
            read -n 1 -s -r -p "Press any key to continue..."
        fi
    fi
}

build_module() {
    local module="$1"
    echo
    echo "==================================="
    echo "Building $module..."
    echo "==================================="
    
    if [ ! -d "APP/$module" ]; then
        echo "Error: Project directory APP/$module does not exist"
        read -n 1 -s -r -p "Press any key to continue..."
        return 1
    fi
    
    # 检查是否是有效的算法模块
    if [ ! -f "APP/$module/CMakeLists.txt" ]; then
        echo "Warning: APP/$module does not contain CMakeLists.txt, skipping..."
        read -n 1 -s -r -p "Press any key to continue..."
        return 0
    fi
    
    # 进入项目目录
    cd "APP/$module" || {
        echo "Error: Failed to enter $module directory"
        read -n 1 -s -r -p "Press any key to continue..."
        return 1
    }
    
    # 创建build目录（如果不存在）
    if [ ! -d "build" ]; then
        mkdir -p build || {
            echo "Error: Failed to create build directory for $module"
            read -n 1 -s -r -p "Press any key to continue..."
            return 1
        }
    fi
    
    # 进入build目录
    cd build || {
        echo "Error: Failed to enter build directory for $module"
        read -n 1 -s -r -p "Press any key to continue..."
        return 1
    }
    
    # 使用Conan构建
    echo "Running Conan install..."
    conan install .. --build=missing --no-remote || {
        echo "Error: Conan install failed for $module"
        read -n 1 -s -r -p "Press any key to continue..."
        return 1
    }
    
    # 运行CMake配置
    echo "Running CMake configure..."
    cmake .. -DCMAKE_BUILD_TYPE=Release || {
        echo "Error: CMake configure failed for $module"
        read -n 1 -s -r -p "Press any key to continue..."
        return 1
    }
    
    # 运行CMake构建
    echo "Running CMake build..."
    cmake --build . --config Release || {
        echo "Error: CMake build failed for $module"
        read -n 1 -s -r -p "Press any key to continue..."
        return 1
    }
    
    # 返回项目根目录
    cd ../../.. || {
        echo "Error: Failed to return to project root directory"
        read -n 1 -s -r -p "Press any key to continue..."
        return 1
    }
    
    echo "$module build completed successfully!"
    echo "Output files are in APP/$module/bin/ directory"
    echo
    read -n 1 -s -r -p "Press any key to continue..."
}

build_all() {
    for module in "${modules[@]}"; do
        build_module "$module"
    done
}

clean_module() {
    local module="$1"
    echo
    echo "==================================="
    echo "Cleaning $module..."
    echo "==================================="
    
    # 清理构建目录（包含CMake缓存和临时文件）
    if [ -d "APP/$module/build" ]; then
        echo "Removing build directory for $module..."
        rm -rf "APP/$module/build"
        echo "Build directory removed."
    else
        echo "No build directory found for $module."
    fi
    
    # 清理可执行文件目录
    if [ -d "APP/$module/bin" ]; then
        echo "Removing bin directory for $module..."
        rm -rf "APP/$module/bin"
        echo "Bin directory removed."
    else
        echo "No bin directory found for $module."
    fi
    
    # 清理库文件目录
    if [ -d "APP/$module/lib" ]; then
        echo "Removing lib directory for $module..."
        rm -rf "APP/$module/lib"
        echo "Lib directory removed."
    else
        echo "No lib directory found for $module."
    fi
    
    echo "$module cleanup completed!"
    echo
}

clean_all() {
    for module in "${modules[@]}"; do
        clean_module "$module"
    done
    read -n 1 -s -r -p "Press any key to continue..."
}

exit_program() {
    echo
    echo "Thank you for using Algorithm Packet Build System!"
    echo
    exit 0
}

# 主循环
while true; do
    show_menu
done

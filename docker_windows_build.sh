#!/bin/bash

# Docker跨平台Windows构建脚本（实验性）

echo "🐳 Docker Windows构建方案"
echo "=========================="

cat << 'DOCKERFILE' > Dockerfile.windows
# 使用Wine运行Windows程序的Ubuntu环境
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# 安装基础工具
RUN apt-get update && apt-get install -y \
    wget \
    unzip \
    git \
    build-essential \
    cmake \
    software-properties-common \
    && rm -rf /var/lib/apt/lists/*

# 安装Wine
RUN dpkg --add-architecture i386 && \
    wget -nc https://dl.winehq.org/wine-builds/winehq.key && \
    apt-key add winehq.key && \
    add-apt-repository 'deb https://dl.winehq.org/wine-builds/ubuntu/ focal main' && \
    apt-get update && \
    apt-get install -y winehq-stable && \
    rm -rf /var/lib/apt/lists/*

# 配置Wine
RUN wine --version

WORKDIR /workspace

# 复制构建脚本
COPY . .

# 构建命令（需要在容器内配置Qt和Visual Studio）
CMD ["echo", "Docker Windows构建环境已准备就绪"]
DOCKERFILE

echo "📝 Dockerfile已创建"
echo ""
echo "⚠️ 注意：Docker Windows构建比较复杂，建议使用GitHub Actions"
echo ""
echo "如需使用Docker构建："
echo "1. docker build -f Dockerfile.windows -t gobang-windows ."
echo "2. docker run -v \$(pwd):/workspace gobang-windows"
echo ""
echo "更简单的方案："
echo "1. 使用 ./trigger_windows_build.sh 触发GitHub构建"
echo "2. 在Windows机器上运行 build_windows.bat"

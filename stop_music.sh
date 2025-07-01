#!/bin/bash
# 五子棋游戏背景音乐清理脚本

echo "正在停止五子棋背景音乐..."

# 停止相关进程
pkill -f "while true.*afplay" 2>/dev/null
killall afplay 2>/dev/null
pkill -f "nohup sh.*afplay" 2>/dev/null

echo "背景音乐已停止"

# 检查是否还有残留进程
REMAINING=$(ps aux | grep afplay | grep -v grep | wc -l)
if [ $REMAINING -eq 0 ]; then
    echo "✅ 所有音乐进程已清理完毕"
else
    echo "⚠️  仍有 $REMAINING 个相关进程在运行"
    ps aux | grep afplay | grep -v grep
fi 
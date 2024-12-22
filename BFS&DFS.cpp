/*
10 10
1 1 1 1 1 0 0 0 0 0
1 0 0 1 1 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 0 0 
1 1 0 1 1 0 0 0 1 1 
0 0 0 0 0 0 0 1 0 1 
1 1 1 0 1 1 1 0 0 0 
0 0 0 0 0 0 0 0 0 0
*/
#include <graphics.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <stack>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

const int CELL_SIZE = 30;  // 每个格子的大小
const int MARGIN = 50;     // 边距
const int BTN_WIDTH = 150; // 按钮宽度
const int BTN_HEIGHT = 50; // 按钮高度
const int GAP = 100;       // DFS 和 BFS 图之间的间隙
const int WINDOW_WIDTH = 800;  // 固定窗口宽度
const int WINDOW_HEIGHT = 600; // 固定窗口高度
const int MAX_N = 20;      // 最大地图大小

// 地图和访问标记
vector<vector<int>> grid;
vector<vector<bool>> visited_dfs, visited_bfs;
int rows, cols; // 地图行列数

// DFS 和 BFS 状态
stack<pair<int, int>> dfs_stack; // DFS 栈
queue<pair<int, int>> bfs_queue; // BFS 队列

// 当前染色块的颜色
int dfs_color = RGB(255, 100, 100); // DFS 使用红色
int bfs_color = RGB(100, 100, 255); // BFS 使用蓝色

// 方向数组
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

// 绘制单元格
void drawCell(int x, int y, int color, int offsetX) {
    setfillcolor(color);
    fillrectangle(offsetX + x * CELL_SIZE, MARGIN + y * CELL_SIZE,
        offsetX + (x + 1) * CELL_SIZE, MARGIN + (y + 1) * CELL_SIZE);
}

// 绘制地图
void drawGrid(const vector<vector<bool>>& visited, int offsetX, int color) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                if (visited[i][j]) {
                    drawCell(j, i, color, offsetX); // 已访问的格子
                }
                else {
                    drawCell(j, i, RGB(200, 200, 200), offsetX); // 未访问的格子
                }
            }
            else {
                drawCell(j, i, RGB(50, 50, 50), offsetX); // 空白格子
            }
        }
    }
}

// 绘制按钮
void drawButtons() {
    // 左侧按钮 (DFS)
    int dfsBtnX = MARGIN;
    int dfsBtnY = rows * CELL_SIZE + MARGIN * 2 + 20;
    setfillcolor(RGB(100, 200, 100));
    fillrectangle(dfsBtnX, dfsBtnY, dfsBtnX + BTN_WIDTH, dfsBtnY + BTN_HEIGHT);
    settextstyle(20, 0, _T("微软雅黑"));
    settextcolor(WHITE);
    outtextxy(dfsBtnX + 20, dfsBtnY + 10, _T("DFS 下一步"));

    // 右侧按钮 (BFS)
    int bfsBtnX = WINDOW_WIDTH - MARGIN - BTN_WIDTH;
    int bfsBtnY = dfsBtnY;
    setfillcolor(RGB(100, 200, 100));
    fillrectangle(bfsBtnX, bfsBtnY, bfsBtnX + BTN_WIDTH, bfsBtnY + BTN_HEIGHT);
    outtextxy(bfsBtnX + 20, bfsBtnY + 10, _T("BFS 下一步"));
}

// 初始化 DFS 和 BFS
void initSearch() {
    visited_dfs.assign(rows, vector<bool>(cols, false));
    visited_bfs.assign(rows, vector<bool>(cols, false));
}

// DFS 单步执行
bool dfsStep() {
    if (dfs_stack.empty()) {
        // 如果栈为空，寻找下一块未访问的连通块
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1 && !visited_dfs[i][j]) {
                    dfs_stack.push(make_pair(i, j));
                    return true; // 找到新的连通块
                }
            }
        }
        return false; // 没有更多连通块
    }

    pair<int, int> current = dfs_stack.top(); // 获取栈顶元素
    dfs_stack.pop();

    int x = current.first;
    int y = current.second;

    if (visited_dfs[x][y]) return true;
    visited_dfs[x][y] = true;

    // 将相邻节点压入栈
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
            grid[nx][ny] == 1 && !visited_dfs[nx][ny]) {
            dfs_stack.push(make_pair(nx, ny));
        }
    }
    return true;
}

// BFS 单步执行
bool bfsStep() {
    if (bfs_queue.empty()) {
        // 如果队列为空，寻找下一块未访问的连通块
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1 && !visited_bfs[i][j]) {
                    bfs_queue.push(make_pair(i, j));
                    visited_bfs[i][j] = true;
                    return true; // 找到新的连通块
                }
            }
        }
        return false; // 没有更多连通块
    }

    pair<int, int> current = bfs_queue.front(); // 获取队首元素
    bfs_queue.pop();

    int x = current.first;
    int y = current.second;

    visited_bfs[x][y] = true;

    // 将相邻节点加入队列
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
            grid[nx][ny] == 1 && !visited_bfs[nx][ny]) {
            bfs_queue.push(make_pair(nx, ny));
            visited_bfs[nx][ny] = true;
        }
    }
    return true;
}

// 主程序
int main() {
    // 设置控制台为 Unicode 模式
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    // 控制台输入地图数据
    wcout << L"请输入地图的行数和列数（最大20x20）: ";
    wcin >> rows >> cols;

    // 检查行列数是否有效
    if (rows <= 0 || cols <= 0 || rows > MAX_N || cols > MAX_N) {
        wcout << L"输入的行列数无效！必须在 1 到 " << MAX_N << L" 之间。" << endl;
        return 1;
    }

    grid.assign(rows, vector<int>(cols));

    wcout << L"请输入地图数据（每行输入0和1，用空格分隔）:" << endl;
    for (int i = 0; i < rows; i++) {
        wcout << L"第 " << i + 1 << L" 行: ";
        for (int j = 0; j < cols; j++) {
            wcin >> grid[i][j];
            if (grid[i][j] != 0 && grid[i][j] != 1) {
                wcout << L"输入的地图数据无效！只能是 0 或 1。" << endl;
                return 1;
            }
        }
    }

    // 初始化图形窗口
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    setbkcolor(RGB(50, 50, 50));
    cleardevice();

    // 初始化搜索
    initSearch();

    // 绘制初始界面
    drawGrid(visited_dfs, MARGIN, dfs_color);
    drawGrid(visited_bfs, WINDOW_WIDTH / 2 + GAP / 2, bfs_color);
    drawButtons();

    // 等待用户点击按钮
    while (true) {
        ExMessage msg = getmessage(EM_MOUSE);
        if (msg.message == WM_LBUTTONDOWN) {
            int dfsBtnX = MARGIN;
            int dfsBtnY = rows * CELL_SIZE + MARGIN * 2 + 20;
            int bfsBtnX = WINDOW_WIDTH - MARGIN - BTN_WIDTH;
            int bfsBtnY = dfsBtnY;

            // 判断点击的是哪个按钮
            if (msg.x >= dfsBtnX && msg.x <= dfsBtnX + BTN_WIDTH &&
                msg.y >= dfsBtnY && msg.y <= dfsBtnY + BTN_HEIGHT) {
                if (!dfsStep()) {
                    wcout << L"DFS 已完成所有连通块的染色！" << endl;
                }
            }
            else if (msg.x >= bfsBtnX && msg.x <= bfsBtnX + BTN_WIDTH &&
                msg.y >= bfsBtnY && msg.y <= bfsBtnY + BTN_HEIGHT) {
                if (!bfsStep()) {
                    wcout << L"BFS 已完成所有连通块的染色！" << endl;
                }
            }

            // 更新界面
            drawGrid(visited_dfs, MARGIN, dfs_color);
            drawGrid(visited_bfs, WINDOW_WIDTH / 2 + GAP / 2, bfs_color);
            drawButtons();
        }
    }

    // 关闭窗口
    closegraph();
    return 0;
}


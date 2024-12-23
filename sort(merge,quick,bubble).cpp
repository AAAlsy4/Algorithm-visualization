#include <graphics.h>  
#include <vector>  
#include <algorithm>  
#include <thread>  
#include <functional>  
#include <string>  

using namespace std;

// 全局变量  
vector<int> arr; // 排序数据  
bool backToMenu = false; // 是否返回主菜单  

// 窗口宽高  
const int WIDTH = 800;
const int HEIGHT = 600;

// 数据条数  
const int NUM_BARS = 50;

// 每条柱子的宽度  
const int BAR_WIDTH = WIDTH / NUM_BARS;

// 初始化随机数据  
void initData() {
    arr.clear();
    for (int i = 0; i < NUM_BARS; ++i) {
        arr.push_back(rand() % (HEIGHT - 100) + 50); // 保证柱子高度在 50 到 HEIGHT-100 之间  
    }
}

// 绘制柱状图（使用双缓冲）  
void drawBars(const vector<int>& arr, int highlight1 = -1, int highlight2 = -1) {
    BeginBatchDraw(); // 开始双缓冲  
    cleardevice();

    // 绘制背景  
    setfillcolor(RGB(30, 30, 30));
    bar(0, 0, WIDTH, HEIGHT);

    // 绘制柱状图  
    for (int i = 0; i < arr.size(); ++i) {
        setfillcolor(i == highlight1 || i == highlight2 ? RGB(255, 69, 0) : RGB(100, 149, 237));
        bar(i * BAR_WIDTH, HEIGHT - arr[i], (i + 1) * BAR_WIDTH - 2, HEIGHT);
    }

    // 绘制提示文字  
    settextstyle(20, 0, _T("Consolas"));
    settextcolor(WHITE);
    outtextxy(10, 10, _T("按 ESC 返回主菜单"));

    EndBatchDraw(); // 结束双缓冲  
    Sleep(50); // 控制动画速度  
}

// 检测是否按下 ESC 键  
void checkForEscapeKey() {
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // 检测 ESC 键是否被按下  
        backToMenu = true;
    }
}

// 冒泡排序  
void bubbleSort() {
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            checkForEscapeKey(); // 检测 ESC 键  
            if (backToMenu) return; // 检测是否返回主菜单  
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
            drawBars(arr, j, j + 1);
        }
    }
}

// 快速排序  
void quickSort(int left, int right) {
    checkForEscapeKey(); // 检测 ESC 键  
    if (backToMenu) return; // 检测是否返回主菜单  
    if (left >= right) return;
    int pivot = arr[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && arr[j] >= pivot) --j;
        arr[i] = arr[j];
        drawBars(arr, i, j);
        checkForEscapeKey(); // 检测 ESC 键  
        if (backToMenu) return;
        while (i < j && arr[i] <= pivot) ++i;
        arr[j] = arr[i];
        drawBars(arr, i, j);
        checkForEscapeKey(); // 检测 ESC 键  
        if (backToMenu) return;
    }
    arr[i] = pivot;
    drawBars(arr, i);
    quickSort(left, i - 1);
    quickSort(i + 1, right);
}

// 归并排序  
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        checkForEscapeKey(); // 检测 ESC 键  
        if (backToMenu) return; // 检测是否返回主菜单  
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
        drawBars(arr, i, j);
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
        drawBars(arr, i);
        checkForEscapeKey(); // 检测 ESC 键  
        if (backToMenu) return;
    }
    while (j <= right) {
        temp[k++] = arr[j++];
        drawBars(arr, j);
        checkForEscapeKey(); // 检测 ESC 键  
        if (backToMenu) return;
    }
    for (int p = 0; p < temp.size(); ++p) {
        arr[left + p] = temp[p];
        drawBars(arr, left + p);
        checkForEscapeKey(); // 检测 ESC 键  
        if (backToMenu) return;
    }
}

void mergeSort(int left, int right) {
    checkForEscapeKey(); // 检测 ESC 键  
    if (backToMenu) return; // 检测是否返回主菜单  
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    merge(arr, left, mid, right);
}

// 主菜单界面  
void drawMenu() {
    cleardevice();

    // 绘制背景  
    setfillcolor(RGB(50, 50, 50));
    bar(0, 0, WIDTH, HEIGHT);

    // 绘制标题  
    settextstyle(40, 0, _T("Consolas"));
    settextcolor(WHITE);
    outtextxy(WIDTH / 2 - 150, HEIGHT / 4, _T("排序算法可视化"));

    // 绘制按钮  
    setfillcolor(RGB(70, 130, 180));
    bar(WIDTH / 2 - 100, HEIGHT / 2 - 60, WIDTH / 2 + 100, HEIGHT / 2 - 20);
    bar(WIDTH / 2 - 100, HEIGHT / 2, WIDTH / 2 + 100, HEIGHT / 2 + 40);
    bar(WIDTH / 2 - 100, HEIGHT / 2 + 60, WIDTH / 2 + 100, HEIGHT / 2 + 100);

    // 绘制按钮文字  
    settextstyle(20, 0, _T("Consolas"));
    settextcolor(WHITE);
    outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 50, _T("冒泡排序"));
    outtextxy(WIDTH / 2 - 50, HEIGHT / 2 + 10, _T("快速排序"));
    outtextxy(WIDTH / 2 - 50, HEIGHT / 2 + 70, _T("归并排序"));
}

// 排序界面  
void runSort(function<void()> sortFunc) {
    initData();
    while (!backToMenu) {
        drawBars(arr);
        sortFunc();
    }
    backToMenu = false;
}

// 主程序  
int main() {
    initgraph(WIDTH, HEIGHT);
    while (true) {
        drawMenu();
        while (true) {
            if (MouseHit()) {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    if (msg.x >= WIDTH / 2 - 100 && msg.x <= WIDTH / 2 + 100) {
                        if (msg.y >= HEIGHT / 2 - 60 && msg.y <= HEIGHT / 2 - 20) {
                            runSort(bubbleSort);
                            break;
                        }
                        else if (msg.y >= HEIGHT / 2 && msg.y <= HEIGHT / 2 + 40) {
                            runSort([]() { quickSort(0, arr.size() - 1); });
                            break;
                        }
                        else if (msg.y >= HEIGHT / 2 + 60 && msg.y <= HEIGHT / 2 + 100) {
                            runSort([]() { mergeSort(0, arr.size() - 1); });
                            break;
                        }
                    }
                }
            }
        }
    }
    closegraph();
    return 0;
}

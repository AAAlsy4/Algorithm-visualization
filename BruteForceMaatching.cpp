#define _CRT_SECURE_NO_WARNINGS  
#include <graphics.h>  
#include <conio.h>  
#include <string>  
#include <thread>  
#include <chrono>  
#include <iostream>  
using namespace std;  

// 将 std::string 转换为 TCHAR*  
TCHAR* stringToTCHAR(const string& str) {  
    static TCHAR buffer[256]; // 定义一个静态缓冲区  
    mbstowcs(buffer, str.c_str(), str.size() + 1); // 将多字节字符串转换为宽字符  
    return buffer;  
}  

// 绘制主串  
void drawMainString(const string& mainStr) {  
    settextstyle(30, 0, _T("Consolas"));  
    outtextxy(100, 100, _T("主串:"));  
    for (int i = 0; i < mainStr.size(); i++) {  
        setfillcolor(WHITE);  
        solidrectangle(200 + i * 40, 100, 240 + i * 40, 140);  
        setbkmode(TRANSPARENT);  
        settextcolor(BLUE);  
        outtextxy(210 + i * 40, 105, stringToTCHAR(string(1, mainStr[i]))); // 转换字符后显示  
    }  
}  

// 绘制模式串  
void drawPatternString(const string& pattern, int matchIndex, int currentIndex, bool isMatch, bool isFail = false) {  
    settextstyle(30, 0, _T("Consolas"));  
    outtextxy(100, 300, _T("模式串:"));  
    for (int i = 0; i < pattern.size(); i++) {  
        if (i == currentIndex && isFail) {  
            setfillcolor(RED); // 当前比较失败字符高亮  
        } else if (i == currentIndex) {  
            setfillcolor(LIGHTBLUE); // 当前比较字符高亮  
        } else if (isMatch && i < currentIndex) {  
            setfillcolor(GREEN); // 已匹配成功的部分高亮  
        } else {  
            setfillcolor(WHITE);  
        }  
        solidrectangle(200 + (matchIndex + i) * 40, 300, 240 + (matchIndex + i) * 40, 340);  
        setbkmode(TRANSPARENT);  
        settextcolor(BLACK);  
        outtextxy(210 + (matchIndex + i) * 40, 305, stringToTCHAR(string(1, pattern[i]))); // 转换字符后显示  
    }  
}  

// 暴力匹配算法的可视化  
void visualizeMatching(const string& mainStr, const string& pattern) {  
    int n = mainStr.size();  
    int m = pattern.size();  

    // 绘制主串（常驻显示）  
    drawMainString(mainStr);  

    for (int i = 0; i <= n - m; i++) { // 遍历主串的每个起始位置  
        int j = 0;  
        for (; j < m; j++) { // 遍历模式串  
            drawPatternString(pattern, i, j, false); // 绘制当前匹配状态  
            flushmessage(); // 刷新图形  
            this_thread::sleep_for(chrono::milliseconds(800)); // 延迟 800ms  

            if (mainStr[i + j] != pattern[j]) { // 如果字符不匹配  
                drawPatternString(pattern, i, j, false, true); // 显示匹配失败状态  
                flushmessage();  
                this_thread::sleep_for(chrono::milliseconds(800)); // 延迟 800ms  
                break; // 跳出当前匹配  
            }  
        }  

        if (j == m) { // 如果模式串完全匹配  
            drawPatternString(pattern, i, j, true); // 高亮显示匹配成功部分  
            flushmessage();  
            settextcolor(GREEN);  
            string successMessage = "匹配成功！起始位置: " + to_string(i);
            outtextxy(100, 400, stringToTCHAR(successMessage)); // 转换后显示
           
            return;  
        }  
    }  

    // 匹配失败  
    settextcolor(RED);  
    outtextxy(100, 400, _T("匹配失败！"));  
    flushmessage();  
}  

int main() {  
    // 初始化图形窗口  
    initgraph(1200, 600);  
    setbkcolor(WHITE);  
    cleardevice();  

    // 输入主串和模式串  
    string mainStr, pattern;  
    cout << "请输入主串: ";  
    cin >> mainStr;  
    cout << "请输入模式串: ";  
    cin >> pattern;  

    // 可视化匹配过程  
    visualizeMatching(mainStr, pattern);  

    // 等待用户按键退出  
    _getch();  
    getchar();
  
    return 0;  
}

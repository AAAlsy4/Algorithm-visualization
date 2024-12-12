/*
6 8
1 2
2 5
2 4
3 1
4 1
4 3
4 6
6 5
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>
#include<windows.h>
#include <graphics.h>
#include <conio.h>
using namespace std;
int px[9] = { 200,400,400,550,650,800,800,1000,1000 };
int py[9] = { 400,300,500,300,500,200,600,200,600 };
struct node 
{
    int v, next;
}edge[1001];
int DFN[1001], LOW[1001];
int stack[1001], heads[1001], visit[1001], cnt, tot, index;
void add(int x, int y)
{
    edge[++cnt].next = heads[x];
    edge[cnt].v = y;
    heads[x] = cnt;
    return;
}
void tarjan(int x)//代表第几个点在处理。递归的是点。
{
    DFN[x] = LOW[x] = ++tot;// 新进点的初始化
    char Dfn = DFN[x] + '0';
    char Low = LOW[x] + '0';
    char newlow;
    settextcolor(LIGHTBLUE);
    outtextxy(px[x - 1] + 20, py[x - 1] - 20, Low);
    settextcolor(RED);
    outtextxy(px[x - 1] - 20, py[x - 1] - 20, Dfn);
    _getch();
    stack[++index] = x;//进栈
    visit[x] = 1;//表示在栈里
    for (int i = heads[x]; i != -1; i = edge[i].next)
    {
        if (!DFN[edge[i].v])
        {
            //如果没访问过
            tarjan(edge[i].v);//往下进行延伸，开始递归
            LOW[x] = min(LOW[x], LOW[edge[i].v]);//递归出来，比较谁是谁的儿子／父亲，就是树的对应关系，涉及到强连通分量子树最小根的事情。
            settextcolor(LIGHTBLUE);
            newlow = LOW[x] + '0';
            outtextxy(px[x - 1] + 20, py[x - 1] - 20, newlow);
            _getch();
        }
        else if (visit[edge[i].v]) 
        {  
            //如果访问过，并且还在栈里。
            LOW[x] = min(LOW[x], DFN[edge[i].v]);//比较谁是谁的儿子／父亲。就是链接对应关系
            settextcolor(LIGHTBLUE);
            newlow = LOW[x] + '0';
            outtextxy(px[x - 1] + 20, py[x - 1] - 20, newlow);
            _getch();
        }
    }
    if (LOW[x] == DFN[x]) //发现是整个强连通分量子树里的最小根。
    {
        printf("栈内:");
        for (int i = 1; i <= index; i++)
        {
            printf("%d", stack[i]);
        }
        printf("\n");
        _getch();
        do 
        {
            printf("%d ", stack[index]);
            setfillcolor(BROWN);
            solidcircle(px[stack[index] - 1], py[stack[index] - 1], 20);
            _getch();
            visit[stack[index]] = 0;
            index--;
        } while (x != stack[index + 1]);//出栈，并且输出。
        printf("\n");
    }
    return;
}
int main()
{
    initgraph(1200, 800, 1);
    memset(heads, -1, sizeof(heads));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        circle(px[i], py[i], 20);
        char str = i + '1';
        outtextxy(px[i], py[i], str);
    }
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        line(px[x - 1], py[x - 1], px[y - 1], py[y - 1]);
        // 计算箭头头部两条边的方向向量
        double dx = (px[x - 1] + px[y - 1]) / 2 - px[x - 1];
        double dy = (py[x - 1] + py[y - 1]) / 2 - py[x - 1];
        double length = sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;
        // 计算箭头头部两条边的终点坐标
        int arrowTipX1 = (px[x - 1] + px[y - 1]) / 2 + (int)(10 * (dy - dx));
        int arrowTipY1 = (py[x - 1] + py[y - 1]) / 2 - (int)(10 * (dx + dy));
        int arrowTipX2 = (px[x - 1] + px[y - 1]) / 2 - (int)(10 * (dy + dx));
        int arrowTipY2 = (py[x - 1] + py[y - 1]) / 2 - (int)(10 * (-dx + dy));
        // 绘制箭头头部
        line((px[x - 1] + px[y - 1]) / 2, (py[x - 1] + py[y - 1]) / 2, arrowTipX1, arrowTipY1);
        line((px[x - 1] + px[y - 1]) / 2, (py[x - 1] + py[y - 1]) / 2, arrowTipX2, arrowTipY2);
        add(x, y);
    }
    _getch();
    for (int i = 1; i <= n; i++)
        if (!DFN[i])  
            tarjan(i);//当这个点没有访问过，就从此点开始。防止图没走完
    _getch();
    closegraph();
    return 0;
}
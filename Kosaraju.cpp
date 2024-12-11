/*
8 18
1 2
2 3
3 7
1 3
2 7
1 4
4 1
4 2
4 5
2 5
5 2
5 6
6 3
6 8
8 6
3 8
6 7
8 7
*/
/*#include <iostream>
#include <cstring>
#include <vector>
#include<cstdio>
#include<cmath>
#include<windows.h>
#include <graphics.h>
#include <conio.h>
using namespace std;
int px[9] = { 200,400,400,550,650,800,800,1000,1000 };
int pya[9] = { 200,150,250,150,250,100,300,100,300 };
int pyb[9] = { 600,650,550,650,550,700,500,700,500 };
const int N = 100010;
vector<int> G[N], rG[N];
vector<int> S;  // 存第一次dfs1()的结果，即标记点的先后顺序，优先级小的点先进
int vis[N];    // vis[i]标记第一次dfs1()点i是否访问过
int sccno[N];  // sccno[i]标记点i属于第几个强连通分量，同时记录dfs2()过程中点i是否访问过
int cnt;    //cnt表示强连通分量的个数
char Clock1 = '1';
void dfs1(int u) 
{
    if (vis[u])  
        return;
    vis[u] = 1;
    for (int i = 0; i < G[u].size(); i++)
    {
        dfs1(G[u][i]);
    }
    settextcolor(LIGHTBLUE);
    outtextxy(px[u-1]+20, pya[u-1]+20, Clock1);
    _getch();
    Clock1++;
    S.push_back(u); //记录点的先后顺序，按照拓扑排序，优先级大的放在S的后面
}
void dfs2(int u) 
{
    settextcolor(RED);
    outtextxy(px[u-1]+20, pyb[u-1]+20, '-');
    if (sccno[u])    
        return;
    sccno[u] = cnt;
    for (int i = 0; i < rG[u].size(); i++)
    {
        dfs2(rG[u][i]);
    }
}
void Kosaraju(int n) 
{
    cnt = 0;
    S.clear();
    memset(vis, 0, sizeof(vis));
    memset(sccno, 0, sizeof(sccno));
    for (int i = 1; i <= n; i++) //搜索所有点
        dfs1(i);
    for (int i = n - 1; i >= 0; i--)
    {
        if (!sccno[S[i]]) 
        {
            setfillcolor(BROWN);
            solidcircle(px[S[i]-1], pyb[S[i]-1], 20);
            _getch();
            cnt++;
            dfs2(S[i]);
            _getch();
        }
    }
}
int main() 
{
    initgraph(1200, 800, 1);
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        circle(px[i], pya[i], 20);
        circle(px[i], pyb[i], 20);
        char str = i + '1';
        outtextxy(px[i], pya[i], str);
        outtextxy(px[i], pyb[i], str);
    }
    for (int i = 0; i < n; i++) 
    {
        G[i].clear();
        rG[i].clear();
    }
    for (int i = 0; i < m; i++) 
    {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);  // 原图
        rG[v].push_back(u); // 反图
        line(px[u - 1], pya[u - 1], px[v - 1], pya[v - 1]);
        // 计算箭头头部两条边的方向向量
        double dx = (px[u - 1] + px[v - 1]) / 2 - px[u - 1];
        double dy = (pya[u - 1] + pya[v - 1]) / 2 - pya[u - 1];
        double length = sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;
        // 计算箭头头部两条边的终点坐标
        int arrowTipX1 = (px[u - 1] + px[v - 1]) / 2 + (int)(10 * (dy - dx));
        int arrowTipY1 = (pya[u - 1] + pya[v - 1]) / 2 - (int)(10 * (dx + dy));
        int arrowTipX2 = (px[u - 1] + px[v - 1]) / 2 - (int)(10 * (dy + dx));
        int arrowTipY2 = (pya[u - 1] + pya[v - 1]) / 2 - (int)(10 * (-dx + dy));
        // 绘制箭头头部
        line((px[u - 1] + px[v - 1]) / 2, (pya[u - 1] + pya[v - 1]) / 2, arrowTipX1, arrowTipY1);
        line((px[u - 1] + px[v - 1]) / 2, (pya[u - 1] + pya[v - 1]) / 2, arrowTipX2, arrowTipY2);
        line(px[v - 1],pyb[v - 1], px[u - 1], pyb[u - 1]);
        // 计算箭头头部两条边的方向向量
        double dx1 = (px[v - 1] + px[u - 1]) / 2 - px[v - 1];
        double dy1 = (pyb[v - 1] + pyb[u - 1]) / 2 - pyb[v - 1];
        double length1 = sqrt(dx1 * dx1 + dy1 * dy1);
        dx1 /= length1;
        dy1 /= length1;
        // 计算箭头头部两条边的终点坐标
        int arrowTipX11 = (px[v - 1] + px[u - 1]) / 2 + (int)(10 * (dy1 - dx1));
        int arrowTipY11 = (pyb[v - 1] + pyb[u - 1]) / 2 - (int)(10 * (dx1 + dy1));
        int arrowTipX21 = (px[v - 1] + px[u - 1]) / 2 - (int)(10 * (dy1 + dx1));
        int arrowTipY21 = (pyb[v - 1] + pyb[u - 1]) / 2 - (int)(10 * (-dx1 + dy1));
        // 绘制箭头头部
        line((px[v - 1] + px[u - 1]) / 2, (pyb[v - 1] + pyb[u - 1]) / 2, arrowTipX11, arrowTipY11);
        line((px[v - 1] + px[u - 1]) / 2, (pyb[v - 1] + pyb[u - 1]) / 2, arrowTipX21, arrowTipY21);
    }
    _getch();
    Kosaraju(n);
    printf("%d", cnt);
    _getch();
    closegraph();
    return 0;
}*/
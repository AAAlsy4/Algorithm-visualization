#include <iostream>
#include <cmath>
#include <graphics.h>
#include <conio.h>
using namespace std;

const int INF = 99999999;
const int MAXN = 10;
int px[MAXN] = { 200, 400, 400, 550, 650, 800, 800, 1000, 1000 };
int py[MAXN] = { 400, 300, 500, 300, 500, 200, 600, 200, 600 };

void drawNode(int x, int y, int id, int color = WHITE) {
    setfillcolor(color);
    solidcircle(x, y, 20);
    char str[2] = { char(id + '0'), '\0' };
    settextcolor(BLUE);
    setbkmode(TRANSPARENT);
    outtextxy(x - 5, y - 10, str);
}

void drawArrow(int x1, int y1, int x2, int y2, int weight, int color = WHITE) {
  
    double dx = x2 - x1;
    double dy = y2 - y1;
    double length = sqrt(dx * dx + dy * dy);
    dx /= length;
    dy /= length;

    int startX = x1 + int(20 * dx);
    int startY = y1 + int(20 * dy);
    int endX = x2 - int(20 * dx);
    int endY = y2 - int(20 * dy);

    setlinecolor(color);
    line(startX, startY, endX, endY);


    int arrowBaseX = startX + int(length * 0.25 * dx);
    int arrowBaseY = startY + int(length * 0.25 * dy);

    int arrowTipX1 = arrowBaseX - int(10 * (dx + dy));
    int arrowTipY1 = arrowBaseY - int(10 * (dy - dx));
    int arrowTipX2 = arrowBaseX - int(10 * (dx - dy));
    int arrowTipY2 = arrowBaseY - int(10 * (dy + dx));

    line(arrowBaseX, arrowBaseY, arrowTipX1, arrowTipY1);
    line(arrowBaseX, arrowBaseY, arrowTipX2, arrowTipY2);

    
    char str[10];
    sprintf(str, "%d", weight);
    setbkmode(TRANSPARENT);
    settextcolor(YELLOW);
    outtextxy((startX + arrowBaseX) / 2, (startY + arrowBaseY) / 2 - 10, str);
}

void printMatrix(int n, int e[MAXN][MAXN]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (e[i][j] == INF) printf("%10s", "INF");
            else printf("%10d", e[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    initgraph(1200, 800);

    int e[MAXN][MAXN], n, m, t1, t2, t3;
    int book[MAXN][MAXN] = { 0 };

   
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            e[i][j] = (i == j) ? 0 : INF;
        }
    }


    for (int i = 0; i < n; i++) {
        drawNode(px[i], py[i], i + 1);
    }

   
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &t1, &t2, &t3);
        e[t1][t2] = t3;
        book[t1][t2] = 1;

        
        drawArrow(px[t1 - 1], py[t1 - 1], px[t2 - 1], py[t2 - 1], t3);

        
        printMatrix(n, e);
       
    }

   

    for (int k = 1; k <= n; k++) {
        drawNode(px[k - 1], py[k - 1], k, RED); 
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (e[i][k] != INF && e[k][j] != INF && e[i][j] > e[i][k] + e[k][j]) {
                    e[i][j] = e[i][k] + e[k][j];

                    
                    if (book[i][j]) {
                        drawArrow(px[i - 1], py[i - 1], px[j - 1], py[j - 1], e[i][j], RED);
                    }
                }
            }
        }
        cout<<"以"<<k<<"号节点为中间节点后得到的最短路程为" << endl;
        printMatrix(n, e);
        _getch();
        drawNode(px[k - 1], py[k - 1], k); 
    }

   
    system("cls");
    cout<<"最终的邻接矩阵为" << endl;
    printMatrix(n, e);
    _getch();

    closegraph();
    return 0;
}

#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <dos.h>

// Function to implement DDA Line Drawing Algorithm
void drawDDA(int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1, y = y1;
    
    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), color);
        x += xInc;
        y += yInc;
    }
}

// Function to implement Bresenham's Circle Algorithm
void drawCircle(int xc, int yc, int r, int color) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);
        putpixel(xc + y, yc + x, color);
        putpixel(xc - y, yc + x, color);
        putpixel(xc + y, yc - x, color);
        putpixel(xc - y, yc - x, color);
        
        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Function to implement Boundary Fill Algorithm
void boundaryFill(int x, int y, int fillColor, int boundaryColor) {
    int current = getpixel(x, y);
    if (current != fillColor && current != boundaryColor) {
        putpixel(x, y, fillColor);
        boundaryFill(x + 1, y, fillColor, boundaryColor);
        boundaryFill(x - 1, y, fillColor, boundaryColor);
        boundaryFill(x, y + 1, fillColor, boundaryColor);
        boundaryFill(x, y - 1, fillColor, boundaryColor);
    }
}

void drawScene() {
    // Sky
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, getmaxx(), getmaxy());
    
    // Clouds using Bresenham's Circle Algorithm
    drawCircle(150, 60, 30, WHITE);
    drawCircle(190, 60, 40, WHITE);
    drawCircle(230, 60, 30, WHITE);
    
    drawCircle(400, 60, 30, WHITE);
    drawCircle(440, 60, 40, WHITE);
    drawCircle(480, 60, 30, WHITE);
    
    // Ground
    setfillstyle(SOLID_FILL, BROWN);
    bar(0, 400, getmaxx(), getmaxy());
    
    // Tree using Bresenham's Circle Algorithm
    setcolor(BROWN);
    rectangle(100, 300, 130, 400);
    setfillstyle(SOLID_FILL, BROWN);
    floodfill(110, 350, BROWN);
    
    setcolor(GREEN);
    drawCircle(115, 250, 50, GREEN);
    drawCircle(85, 270, 40, GREEN);
    drawCircle(145, 270, 40, GREEN);
    boundaryFill(115, 250, GREEN, GREEN);
    
    // House
    drawDDA(300, 300, 500, 300, YELLOW);
    drawDDA(300, 500, 500, 500, YELLOW);
    drawDDA(300, 300, 300, 500, YELLOW);
    drawDDA(500, 300, 500, 500, YELLOW);
    boundaryFill(310, 310, YELLOW, YELLOW);
    
    // Roof
    drawDDA(280, 300, 520, 300, RED);
    drawDDA(280, 300, 400, 220, RED);
    drawDDA(520, 300, 400, 220, RED);
    boundaryFill(400, 250, RED, RED);
    
    // Door
    drawDDA(370, 400, 430, 400, BROWN);
    drawDDA(370, 500, 430, 500, BROWN);
    drawDDA(370, 400, 370, 500, BROWN);
    drawDDA(430, 400, 430, 500, BROWN);
    boundaryFill(380, 410, BROWN, BROWN);
}

void drawRain() {
    for (int i = 0; i < 100; i++) {
        int x = rand() % getmaxx();
        int y = rand() % getmaxy();
        drawDDA(x, y, x, y + 10, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    srand(time(NULL));
    
    while (!kbhit()) {
        cleardevice();
        drawScene();
        drawRain();
        delay(50);
    }
    
    getch();
    closegraph();
    return 0;
}


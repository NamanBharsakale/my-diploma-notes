#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

// Function to implement DDA Algorithm for drawing a line
void drawDDALine(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;
    
    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), WHITE);
        x += xIncrement;
        y += yIncrement;
    }
}

// Function to implement Bresenham’s Circle Algorithm
void drawBresenhamCircle(int xc, int yc, int r, int color) {
    int x = 0, y = r;
    int d = 3 - (2 * r);
    
    while (x <= y) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);
        putpixel(xc + y, yc + x, color);
        putpixel(xc - y, yc + x, color);
        putpixel(xc + y, yc - x, color);
        putpixel(xc - y, yc - x, color);

        if (d < 0)
            d = d + (4 * x) + 6;
        else {
            d = d + (4 * (x - y)) + 10;
            y--;
        }
        x++;
    }
}

// Function to implement Boundary Fill Algorithm
void boundaryFill(int x, int y, int fill_color, int boundary_color) {
    int current = getpixel(x, y);
    if (current != boundary_color && current != fill_color) {
        putpixel(x, y, fill_color);
        boundaryFill(x + 1, y, fill_color, boundary_color);
        boundaryFill(x - 1, y, fill_color, boundary_color);
        boundaryFill(x, y + 1, fill_color, boundary_color);
        boundaryFill(x, y - 1, fill_color, boundary_color);
    }
}

// Function to draw the background scene
void drawScene() {
    // Sky background
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, getmaxx(), getmaxy());

    // Sun using Bresenham’s Circle Algorithm
    drawBresenhamCircle(80, 80, 40, YELLOW);

    // Ground
    setcolor(BROWN);
    rectangle(0, 400, getmaxx(), getmaxy());
    boundaryFill(10, 450, BROWN, BROWN);

    // House
    setcolor(RED);
    rectangle(500, 300, 700, 500);
    boundaryFill(550, 350, YELLOW, RED);

    // Roof
    setcolor(RED);
    line(500, 300, 600, 200);
    line(700, 300, 600, 200);
    line(500, 300, 700, 300);
    boundaryFill(600, 250, RED, RED);

    // Door
    setcolor(BLACK);
    rectangle(570, 400, 630, 500);
    boundaryFill(580, 420, BROWN, BLACK);

    // Window
    setcolor(BLACK);
    rectangle(620, 330, 720, 420);
    line(670, 330, 670, 420);
    line(620, 375, 720, 375);
    boundaryFill(630, 340, WHITE, BLACK);

    // Tree Trunk
    setcolor(BROWN);
    rectangle(200, 300, 230, 500);
    boundaryFill(210, 350, BROWN, BROWN);

    // Tree Leaves using Bresenham’s Circle Algorithm
    drawBresenhamCircle(215, 250, 50, GREEN);
    drawBresenhamCircle(190, 270, 50, GREEN);
    drawBresenhamCircle(240, 270, 50, GREEN);
    boundaryFill(215, 250, GREEN, GREEN);
}

// Function to generate rainfall using DDA Line Algorithm
void drawRain() {
    for (int i = 0; i < 100; i++) {
        int x = rand() % getmaxx();
        int y = rand() % getmaxy();
        drawDDALine(x, y, x, y + 10);
    }
}

// Main function
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


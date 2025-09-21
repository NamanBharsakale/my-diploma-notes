#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <conio.h>
void drawScene() {
    // Sky background
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, getmaxx(), getmaxy());

    // Clouds (moved higher)
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(150, 40, 70, 40);
    fillellipse(220, 40, 80, 50);
    fillellipse(300, 40, 70, 40);

    fillellipse(500, 40, 80, 50);
    fillellipse(600, 40, 70, 40);
    fillellipse(700, 40, 80, 50);

    // Ground
    setfillstyle(SOLID_FILL, BROWN);
    bar(0, 400, getmaxx(), getmaxy());

    // Tree
    setcolor(BROWN);
    rectangle(200, 300, 230, 500);
    setfillstyle(SOLID_FILL, BROWN);
    floodfill(215, 350, BROWN);

    setcolor(GREEN);
    ellipse(215, 250, 0, 360, 80, 100);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(215, 250, GREEN);

    // House with bigger window
    setfillstyle(SOLID_FILL, YELLOW);
    bar(500, 300, 700, 500);
    setfillstyle(SOLID_FILL, RED);
    bar(450, 200, 750, 300);
    line(450, 300, 600, 150);
    line(600, 150, 750, 300);

    // Door
    setfillstyle(SOLID_FILL, BROWN);
    bar(570, 400, 630, 500);

    // Big Window
    setfillstyle(SOLID_FILL, WHITE);
    bar(620, 330, 720, 420);
    setcolor(BLACK);
    line(620, 375, 720, 375);
    line(670, 330, 670, 420);
}

void drawRain() {
    for (int i = 0; i < 100; i++) {
        int x = rand() % getmaxx();
        int y = rand() % getmaxy();
        setcolor(WHITE);
        line(x, y, x, y + 10);
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


#ifndef MAZEDRAWER_H
#define MAZEDRAWER_H

#include "qdebug.h"
#include "qimage.h"
#include "qpixmap.h"
#include <vector>
#include <queue>
#include "../maze/mazesolver.h"
class MazeDrawer {

    private:
         QImage myImage;
         int mazeDimension;

         // colors
         QRgb backgroundColor;
         QRgb wallColor;
         QRgb pointColor;
         QRgb pathColor;

         int wallWidth;
         MyPoint firstPoint;
         MyPoint lastPoint;
         bool isInit;

         std::vector<int> horizontalWalls;
         std::vector<int> verticalWalls;
         std::vector<int> solution;
    public:
         MazeDrawer(int n, QRgb bColor, QRgb wColor, QRgb pColor, QRgb pthColor);
         MazeDrawer() = delete;
         MyPoint identifyPoint(int i, int j);
         void onMazeClicked(int i, int j);
         void drawPoint(MyPoint p);
         void clearPoint(MyPoint p);
         QPixmap getPixmap();
         void drawMaze(const std::vector<int> &hWalls, const std::vector<int> &vWalls);
         void drawVerticalWall(int hCoord, int vCoord);
         void drawHorizontalWall(int hCoord, int vCoord);
         void drawConnector(int a, int b, QRgb color);
         void eraseSolution();
         void drawSolution();
};
#endif // MAZEDRAWER_H

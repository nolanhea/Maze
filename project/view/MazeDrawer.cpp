#include "MazeDrawer.h"

MazeDrawer::MazeDrawer(int n, QRgb bColor, QRgb wColor, QRgb pColor, QRgb pthColor): myImage(QImage(500, 500, QImage::Format_RGB32)), mazeDimension(n),
    backgroundColor(bColor), wallColor(wColor), pointColor(pColor), pathColor(pthColor), firstPoint(-1, -1), lastPoint(-1, -1){
    wallWidth = 2;
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 500; ++j) {
            myImage.setPixel(i, j, backgroundColor);
        }
    }

    for (int j = 0; j < mazeDimension; ++j) {
        drawVerticalWall(0, j);
        drawVerticalWall(mazeDimension, j);
    }
    for (int j = 0; j < mazeDimension; ++j) {
        drawHorizontalWall(j, 0);
        drawHorizontalWall(j, mazeDimension);
    }
    isInit = true;


    /*
             for (int i = 0; i <= mazeDimension; ++i) {
                 for (int j = 0; j < mazeDimension; ++j) {
                     drawVerticalWall(i, j);
                 }
             }

             for (int i = 0; i < mazeDimension; ++i) {
                 for (int j = 0; j <= mazeDimension; ++j) {
                     drawHorizontalWall(i, j);
                 }
             }*/

}

MyPoint MazeDrawer::identifyPoint(int i, int j) {
    int offset = 498 % mazeDimension;
    offset /= 2;
    i -= offset;
    j -= offset;
    int vCoord = i * mazeDimension / (498 - offset * 2);
    int hCoord = j * mazeDimension / (498 - offset * 2);
    if (vCoord >= mazeDimension || hCoord >= mazeDimension
            || hCoord < 0 || vCoord < 0) {
        return MyPoint(-1, -1);
    }
    return MyPoint(hCoord, vCoord);

}

void MazeDrawer::onMazeClicked(int i, int j) {
    if (isInit) {
        MyPoint p = identifyPoint(i, j);
        if (p == firstPoint) {
            clearPoint(p);
            firstPoint = MyPoint(-1, -1);
            return;
        }
        if (p == lastPoint) {
            lastPoint = firstPoint;
            firstPoint = MyPoint(-1, -1);
            clearPoint(p);
            return;
        }
        clearPoint(firstPoint);
        firstPoint = lastPoint;
        lastPoint = p;
        drawPoint(lastPoint);
    }
}

void MazeDrawer::drawPoint(MyPoint p) {
    this -> eraseSolution();
    if (p.hCoord == -1 || p.vCoord == -1) {
        return;
    }

    int offset = (498 % mazeDimension) / 2;
    int cellSize = 498 / mazeDimension;
    int hBegin = offset + cellSize * p.hCoord + cellSize / 2 - 2 ;
    int vBegin = offset + cellSize * p.vCoord + cellSize / 2 - 2 ;
    for (int i  = hBegin; i < hBegin + 8; ++i) {
        for (int j = vBegin; j < vBegin + 8; ++j) {
            myImage.setPixel(j, i, pointColor);
        }
    }
}

void MazeDrawer::clearPoint(MyPoint p) {
    if (p.hCoord == -1 || p.vCoord == -1) {
        return;
    }
    int offset = (498 % mazeDimension) / 2;
    int cellSize = 498 / mazeDimension;
    int hBegin = offset + cellSize * p.hCoord + cellSize / 2 - 2 ;
    int vBegin = offset + cellSize * p.vCoord + cellSize / 2 - 2 ;
    for (int i  = hBegin; i < hBegin + 8; ++i) {
        for (int j = vBegin; j < vBegin + 8; ++j) {
            myImage.setPixel(j, i, backgroundColor);
        }
    }
}

QPixmap MazeDrawer::getPixmap() {
    return QPixmap::fromImage(myImage);
}

void MazeDrawer::drawMaze(const std::vector<int> &hWalls, const std::vector<int> &vWalls) {
    horizontalWalls = hWalls;
    verticalWalls = vWalls;
    for (int i = 0; i < mazeDimension; ++i) {
        for (int j = 0; j < mazeDimension; ++j) {
            if (hWalls[i + mazeDimension * j] == 1) {
                drawHorizontalWall(i, j + 1);
            }
        }
    }

    for (int i = 0; i < mazeDimension; ++i) {
        for (int j = 0; j < mazeDimension; ++j) {
            if (vWalls[i + mazeDimension * j] == 1) {
                drawVerticalWall(i + 1, j);
            }
        }
    }

}

void MazeDrawer::drawVerticalWall(int hCoord, int vCoord) {
    int offset = 498 % mazeDimension;
    int cellSize = 498 / mazeDimension;
    offset /= 2;

    for (int i = offset + cellSize * hCoord; i < offset + cellSize * hCoord + wallWidth; ++i) {
        for (int j = offset + cellSize * vCoord; j < offset + cellSize * vCoord + cellSize + wallWidth; ++j) {
            myImage.setPixel(i, j, wallColor);
        }
    }


}

void MazeDrawer::drawHorizontalWall(int hCoord, int vCoord) {
    int offset = 498 % mazeDimension;
    int cellSize = 498 / mazeDimension;
    offset /= 2;

    for (int i = offset + cellSize * hCoord; i < offset + cellSize * hCoord + cellSize + wallWidth; ++i) {
        for (int j = offset + cellSize * vCoord; j < offset + cellSize * vCoord + wallWidth; ++j) {
            myImage.setPixel(i, j, wallColor);
        }
    }
}

void MazeDrawer::drawConnector(int a, int b, QRgb color) {
    if (a > b) {
        std::swap(a, b);
    }
    int offset = 498 % mazeDimension;
    int cellSize = 498 / mazeDimension;
    offset /= 2;
    if (std::abs(a - b) == 1) {
        int startV = offset + cellSize * (a / mazeDimension) + cellSize/2 - 1;
        int finishV = offset + cellSize * (a / mazeDimension) + cellSize/2 + 1;
        int startH = offset + cellSize * (a % mazeDimension) + cellSize / 2;
        int finishH = offset + cellSize * (a % mazeDimension) + cellSize + cellSize / 2;
        for (int i = startV; i < finishV; ++i) {
            for (int j = startH; j < finishH; ++j) {
                myImage.setPixel(j, i, color);
            }
        }

    } else {
        int startV = offset + cellSize * (a / mazeDimension) + cellSize/2;
        int finishV = offset + cellSize * (a / mazeDimension) + cellSize/2 + cellSize;
        int startH = offset + cellSize * (a % mazeDimension) + cellSize / 2 - 1;
        int finishH = offset + cellSize * (a % mazeDimension) + cellSize / 2 + 1;
        for (int i = startV; i < finishV; ++i) {
            for (int j = startH; j < finishH; ++j) {
                myImage.setPixel(j, i, color);
            }
        }
    }

}

void MazeDrawer::eraseSolution() {
    if (!solution.empty()) {
        int x = solution.back();
        solution.pop_back();

        while (!solution.empty()) {
            int y =  solution.back();
            solution.pop_back();
            drawConnector(x, y, backgroundColor);
            x = y;
        }
    }

}

void MazeDrawer::drawSolution() {
    if (firstPoint.hCoord != -1 && lastPoint.hCoord != -1) {
        this -> eraseSolution();
        MazeSolver solver(horizontalWalls, verticalWalls, mazeDimension);
        solution = solver.solve(firstPoint, lastPoint);
        auto tempSolution = solution;
        int x = tempSolution.back();
        tempSolution.pop_back();
        while (!tempSolution.empty()) {
            int y = tempSolution.back();
            tempSolution.pop_back();
            drawConnector(x, y, pathColor);
            x = y;
        }
    }
}

#include "cavityview.h"

CavityView::CavityView(QWidget *parent): QLabel(parent), cavityGenerator(nullptr) {
}

void CavityView::setCavityGenerator(CavityGenerator *c) {
    delete cavityGenerator;
    cavityGenerator = c;
}

void CavityView::drawCavity() {
    QImage myImage(500, 500, QImage::Format_RGB32);
    int size = cavityGenerator -> getSize();
    int offset = 500 % size;
    int cellSize = 500 / size;
    offset /= 2;
    for (int i = 0; i < size * cellSize; i++) {
        for (int j = 0; j < size * cellSize; j++) {
            int c = cavityGenerator -> getCell((i/cellSize) * size + j/cellSize);
            if (c == 1) {
                QRgb color = qRgb(0, 0, 0);
                myImage.setPixel(i, j, color);
            } else {
                QRgb color = qRgb(255, 255, 255);
                myImage.setPixel(i, j, color);
            }
        }
    }
    this -> setPixmap(QPixmap::fromImage(myImage));

}

bool CavityView::nextStep() {
    bool ret = cavityGenerator -> nextStep();
    drawCavity();
    if (!ret) {
        emit cavityFinished();
    }
    return ret;
}

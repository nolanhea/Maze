#include "mazeview.h"


MazeView::MazeView(QWidget *parent): QLabel(parent)
{

}

void MazeView::setMazeDrawer(MazeDrawer *md)
{
    mazeDrawer = md;
}

void MazeView::drawMaze(std::vector<int> h_walls,  std::vector<int> v_walls)
{
    mazeDrawer -> drawMaze(h_walls, v_walls);
    this -> setPixmap(mazeDrawer -> getPixmap());
}

void MazeView::drawSolution()
{
    mazeDrawer -> drawSolution();
    this -> setPixmap(mazeDrawer -> getPixmap());
}
void MazeView::mousePressEvent(QMouseEvent *event) {
    event -> accept();
    auto pos = event -> pos();
    int x = pos.x();
    int y = pos.y();
    mazeDrawer -> onMazeClicked(x, y);
    this -> setPixmap(mazeDrawer -> getPixmap());
    QLabel::mousePressEvent(event);
}

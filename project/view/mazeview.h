#ifndef MAZEVIEW_H
#define MAZEVIEW_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include "MazeDrawer.h"
class MazeView : public QLabel
{
public:
    MazeView(QWidget *parent = nullptr);
    void setMazeDrawer(MazeDrawer *md);
    void drawMaze(std::vector<int> h_walls,  std::vector<int> v_walls);
    void drawSolution();
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    MazeDrawer *mazeDrawer;
};

#endif // MAZEVIEW_H

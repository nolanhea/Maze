#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../maze/maze_generator.h"
#include "MazeDrawer.h"
#include <QDebug>
#include <QFileDialog>
#include <fstream>
#include "CavityView.h"
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    backgroundColor = qRgb(100, 100, 100);
    wallColor = qRgb(0, 0, 0);
    pointColor = qRgb(100, 0, 0);
    pathColor = qRgb(0, 0, 100);
    auto my_maze = MazeGenerator(10, 10);
    size = 10;
    v_walls = my_maze.first;
    h_walls = my_maze.second;
    MazeDrawer *drawer = new MazeDrawer(10, backgroundColor, wallColor, pointColor, pathColor);
    ui -> image -> setMazeDrawer(drawer);
    ui -> image -> drawMaze(h_walls, v_walls);
    CavityGenerator *cg = new CavityGenerator(ui -> cavitySize -> value(), ui -> liveLimit -> value(), ui -> deathLimit -> value());
    ui -> cavity -> setCavityGenerator(cg);
    ui -> cavity -> drawCavity();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_generateButton_clicked()
{
    size = ui -> size -> value();
    backgroundColor = qRgb(100, 100, 100);
    wallColor = qRgb(0, 0, 0);
    pointColor = qRgb(100, 0, 0);
    pathColor = qRgb(0, 0, 100);
    auto my_maze = MazeGenerator(size, size);
    v_walls = my_maze.first;
    h_walls = my_maze.second;
    MazeDrawer *drawer = new MazeDrawer(size, backgroundColor, wallColor, pointColor, pathColor);
    ui -> image -> setMazeDrawer(drawer);
    ui -> image -> drawMaze(h_walls, v_walls);
}


void MainWindow::on_solve_clicked()
{
    ui -> image -> drawSolution();
}


void MainWindow::on_generateManually_clicked()
{
    CavityGenerator *cg = new CavityGenerator(ui -> cavitySize -> value(), ui -> liveLimit -> value(), ui -> deathLimit -> value());
    ui -> cavity -> setCavityGenerator(cg); // deltes previous CavityGenerator
    ui -> cavity -> drawCavity();
}


void MainWindow::on_nextStep_clicked()
{
    ui -> cavity -> nextStep();
}


void MainWindow::on_pushButton_3_clicked()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_nextStep_clicked()));
    QObject::connect(ui -> cavity, &CavityView::cavityFinished, timer, &QTimer::stop);
    QObject::connect(ui -> cavity, &CavityView::cavityFinished, timer, &QTimer::deleteLater);
    timer->start(ui -> timeInterval -> value());
}


void MainWindow::on_saveMaze_clicked()
{
    QString filename= QFileDialog::getSaveFileName(this, "Save As");
    std::fstream fout;
    fout.open(filename.toStdString(), std::ios::out);
    fout << size << ' ' << size << '\n';
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fout << v_walls[i * size + j] << ' ';
        }
        fout << '\n';
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fout << h_walls[i * size + j] << ' ';
        }
        fout << '\n';
    }
}


void MainWindow::on_loadMaze_clicked()
{
    QString dir = QFileDialog::getOpenFileName(this, "Choose File");
    std::fstream fin;
    fin.open(dir.toStdString(), std::ios::in);

    fin >> size;
    fin >> size;
    v_walls.clear();
    h_walls.clear();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int a;
            fin >> a;
            v_walls.push_back(a);
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int a;
            fin >> a;
            h_walls.push_back(a);
        }
    }

    MazeDrawer *drawer = new MazeDrawer(size, backgroundColor, wallColor, pointColor, pathColor);
    ui -> image -> setMazeDrawer(drawer);
    ui -> image -> drawMaze(h_walls, v_walls);

}


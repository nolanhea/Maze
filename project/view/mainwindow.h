#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_generateButton_clicked();

    void on_solve_clicked();

    void on_generateManually_clicked();

    void on_nextStep_clicked();

    void on_pushButton_3_clicked();

    void on_saveMaze_clicked();

    void on_loadMaze_clicked();

private:
    QRgb backgroundColor;
    QRgb wallColor;
    QRgb pointColor;
    QRgb pathColor;
    int size;
    std::vector<int> v_walls;
    std::vector<int> h_walls;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileDialog>
#include <QString>
#include <grayscale.h>
#include <disparitymap.h>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

 private:
    Ui::MainWindow *ui;
    QImage *first_img;
    QImage *second_img;
    QImage *first_gray;
    QImage *second_gray;
    DisparityMap *disparity;
    QPixmap img_for_show;
    QGraphicsScene *scene1;
    QGraphicsView view1;
    QGraphicsScene *scene2;
    QGraphicsView view2;
    QGraphicsScene *scene3;
    QGraphicsView view3;
    int kernel_size;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_IMGLoad_pressed();
    void on_IMG2Load_pressed();
    void on_FindDisparity_pressed();
};

#endif // MAINWINDOW_H

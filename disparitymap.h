#ifndef DISPARITYMAP_H
#define DISPARITYMAP_H
#include <QImage>
#include <QColor>
#include <QTime>
class DisparityMap
{
private:
    QImage *left_img;
    QImage *right_img;
    QImage *disp_map;
public:
    DisparityMap();
    DisparityMap(DisparityMap &);
    ~DisparityMap();
    QImage& GetLeft();
    QImage& GetRight();
    QImage& GetDispMap();
    static void ExtendImage(QImage &, QImage &, int);
    void FindDisparity(QImage &,QImage&, int, int, int);
    int SSD(QImage&, QImage &, double *, int, int, int, int, int, int );
};

#endif // DISPARITYMAP_H

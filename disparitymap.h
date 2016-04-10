#ifndef DISPARITYMAP_H
#define DISPARITYMAP_H
#include <QImage>
#include <QColor>
#include <QStack>
#include <cmath>
class DisparityMap
{
private:
    QImage *left_img;
    QImage *right_img;
    QImage *disp_map;
    QImage *disp_map2;
    QStack <int> left_window;
    QStack <int> right_window;
public:
    DisparityMap();
    DisparityMap(DisparityMap &);
    ~DisparityMap();
    QImage& GetLeft();
    QImage& GetRight();
    QImage& GetDispMap();
    QImage& GetDispMap2();
    static void ExtendImage(QImage &, QImage &, int);
    void FindDisparity(QImage &,QImage&, int, int, int);
    int FindMinSum(QImage&, QImage&,int,int,int,int);
    int SSD(QImage&, QImage &, int, int, int, int );
};

#endif // DISPARITYMAP_H

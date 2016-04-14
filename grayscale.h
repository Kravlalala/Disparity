#ifndef GRAYSCALE_H
#define GRAYSCALE_H
#include <QImage>
#include <QColor>


class GrayScale
{

public:
    GrayScale();
    ~GrayScale();
    static QImage ConvToGrey(QImage &, QImage&);
};

#endif // GRAYSCALE_H

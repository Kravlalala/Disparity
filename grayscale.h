#ifndef GRAYSCALE_H
#define GRAYSCALE_H
#include <QImage>
#include <QColor>
#include <QStack>


class GrayScale
{

public:
    GrayScale();
    ~GrayScale();
    static QImage ConvToGrey(QImage &, QImage&, QStack <int>);
};

#endif // GRAYSCALE_H

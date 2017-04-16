#ifndef GRAYSCALE_H
#define GRAYSCALE_H
#include <QColor>
#include <QImage>

class GrayScale
{

public:
  GrayScale ();
  ~GrayScale ();
  static QImage ConvToGrey (QImage &, QImage &);
};

#endif // GRAYSCALE_H

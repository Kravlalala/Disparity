#include "grayscale.h"

GrayScale::GrayScale(){

}

GrayScale::~GrayScale(){

}

QImage GrayScale:: ConvToGrey(QImage &input_img, QImage &gray_img,QStack <int> undef_points){
    gray_img=input_img;
    QRgb *temp_line=NULL;
    QColor current_color;
    int height=input_img.height();
    int width=input_img.width();
    int red=0;
    int green=0;
    int blue=0;
    int alpha=0;
    int new_value=0;
    for(int x=0;x<=height-1;x++){
        temp_line=reinterpret_cast<QRgb*>(gray_img.scanLine(x));
        for(int y=0;y<=width-1;y++){
            current_color.setRgb(*temp_line);
            if(current_color.value()==0){
                undef_points.push(x);
                undef_points.push(y);
                *temp_line++=qRgb(0,0,255);
            }
            else{
            new_value=qRed(*temp_line)*0.299+qGreen(*temp_line)*0.587+qBlue(*temp_line)*0.114;
            red=new_value;
            green=new_value;
            blue=new_value;
            alpha=qAlpha(*temp_line);
            *temp_line++=qRgba(red > 255 ? 255 : red < 0 ? 0 : red, green > 255 ? 255 : green < 0 ? 0 : green, blue > 255 ? 255 : blue < 0 ? 0 : blue,alpha);
           }
        }
    }
    return gray_img;
}


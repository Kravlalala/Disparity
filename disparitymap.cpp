#include "disparitymap.h"

DisparityMap::DisparityMap(){
    left_img=new QImage;
    right_img=new QImage;
    disp_map=new QImage;
}
DisparityMap::DisparityMap(DisparityMap &object){
    left_img=new QImage;
    right_img=new QImage;
    disp_map=new QImage;
    if(object.GetLeft().format()!=0) *left_img=object.GetLeft();
    if(object.GetRight().format()!=0)*left_img=object.GetRight();
    if(object.GetDispMap().format()!=0)*disp_map=object.GetRight();
}
DisparityMap:: ~DisparityMap()
{
    delete left_img;
    delete right_img;
    delete disp_map;
}

QImage& DisparityMap::GetLeft(){
    return *left_img;
}
QImage& DisparityMap::GetRight(){
    return *right_img;
}
QImage& DisparityMap::GetDispMap(){
    return *disp_map;
}

void DisparityMap::ExtendImage(QImage &output_img,QImage& input_img, int kernel_size){
    int addition=kernel_size/2;
    int rows=input_img.height()+addition*2;
    int cols=input_img.width()+addition*2;
    QImage temp_img(cols,rows,input_img.format());
    QRgb *input_line;
    QRgb *temp_line;
    for(int x=addition;x<rows-addition;x++){
        temp_line=reinterpret_cast<QRgb*>(temp_img.scanLine(x));
        input_line=reinterpret_cast<QRgb*>(input_img.scanLine(x-addition));
        for(int y=addition;y<cols-addition;y++){
            temp_line[y]=input_line[y-addition];
        }
    }
    output_img=temp_img;
}
void DisparityMap:: FindDisparity(QImage &first_img,QImage &second_img, int disp_min, int disp_max, int kernel_size){
    ExtendImage(*left_img,first_img,kernel_size);
    ExtendImage(*right_img,second_img,kernel_size);
    QRgb *left_line;
    QRgb *right_line;
    QRgb *temp_line;
    QColor disp_color;
    QTime chronograph;
    bool undef_flag=false;
    int addition=kernel_size/2;
    int min_sum=1;
    int current_sum=0;
    int d1=0;
    int d2=0;
    int norm_fact=255/(disp_max-disp_min);
    int rows=left_img->height();
    int cols=left_img->width();
    double *SSD_Mat=new double[disp_max-disp_min+1];
    QImage temp_map(cols-addition*2,rows-addition*2,left_img->format());
    chronograph.start();
    for(int x=addition;x<rows-addition;x++){
        left_line=reinterpret_cast<QRgb*>(left_img->scanLine(x));
        temp_line=reinterpret_cast<QRgb*>(temp_map.scanLine(x-addition));
        for(int y=addition;y<cols-addition;y++){
            undef_flag=false;
            if(qRed(left_line[y])==0 && qGreen(left_line[y])==0 &&qBlue(left_line[y])==255){
                continue;
            }
            else{
                for(int d=disp_min;d<=disp_max;d++){
                    if((y+d)>=cols-addition){
                        temp_line[y-addition]=qRgb(0,0,0);
                        undef_flag=true;
                        break;
                    }
                    else{
                        current_sum=SSD(*left_img,*right_img, SSD_Mat, kernel_size, x, y, d, d1, disp_min);
                        if(d==disp_min){
                            min_sum=current_sum;
                            d1=d;
                        }
                        else{
                            if(current_sum<min_sum){
                                d1=d;
                                min_sum=current_sum;
                            }
                        }
                    }
                }
                if(undef_flag==false){
                    right_line=reinterpret_cast<QRgb*>(right_img->scanLine(x));
                    if((qRed(right_line[y+d1])==0 && qGreen(right_line[y+d1])==0 &&qBlue(right_line[y+d1])==255)){
                        continue;
                    }
                    else {
                        for (int d=-(d1+3);d<=-disp_min;d++){
                            if((y+d1+d)<0){
                                temp_line[y-addition]=qRgb(0,0,255);
                                undef_flag=true;
                                break;
                            }
                            else{
                                current_sum=SSD(*right_img,*left_img, SSD_Mat, kernel_size, x, y+d1,d, d1, disp_min);
                                if(d==-(d1+3)){
                                    min_sum=current_sum;
                                    d2=d;
                                }
                                else{
                                    if(current_sum<min_sum){
                                        d2=d;
                                        min_sum=current_sum;
                                    }
                                }
                            }
                        }
                    }
                }

            }
            if(undef_flag==false){
                if(abs(d1+d2)<=2){
                    disp_color.setHsv(0,0,(d1-disp_min)*norm_fact);
                    temp_line[y-addition]=disp_color.rgb();
                }
                else  temp_line[y-addition]=qRgb(0,0,255);
            }
        }
    }
    qDebug("Time elapsed: %d ms\n", chronograph.elapsed());
    *disp_map=temp_map;
}
int DisparityMap:: SSD(QImage &left_img, QImage &right_img, double *SSD_Mat, int kernel_size, int x, int y, int d,  int d1, int disp_min){
    QRgb *left_line;
    QRgb *right_line;
    QColor left_color;
    QColor right_color;
    int Il;
    int Ir;
    int sum=0;
    int addition=kernel_size/2;
    int squared_dif=0;
    if(d<0 && abs(d)<=d1){
        sum=SSD_Mat[abs(d)-disp_min];
    }
    else{
        for(int X0=x-addition;X0<=x+addition;X0++){
            for(int Y0=y-addition;Y0<=y+addition;Y0++){
                left_line=reinterpret_cast<QRgb*>(left_img.scanLine(X0));
                right_line=reinterpret_cast<QRgb*>(right_img.scanLine(X0));
                left_color.setRgb(left_line[Y0]);
                right_color.setRgb(right_line[Y0+d]);
                Il=left_color.value();
                Ir=right_color.value();
                squared_dif=(Ir-Il)*(Ir-Il);
                sum+=squared_dif;
            }
        }
        if(d>0){
            SSD_Mat[d-disp_min]=sum;
        }
    }
    return sum;
}


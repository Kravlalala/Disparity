#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    first_img=new QImage;
    second_img=new QImage;
    first_gray=new QImage;
    second_gray=new QImage;
    disparity=new DisparityMap;
    scene1=new QGraphicsScene(this);
    scene2=new QGraphicsScene(this);
    scene3=new QGraphicsScene(this);
    kernel_size=3;
}

MainWindow::~MainWindow(){
    delete ui;
    delete first_img;
    delete second_img;
    delete first_gray;
    delete second_gray;
    delete disparity;
    delete scene1;
    delete scene2;
    delete scene3;
}

void MainWindow::on_IMGLoad_pressed()
{
    QString image_path=QFileDialog::getOpenFileName(this,tr("Open file"),"",tr("PNG (*.png);;JPEG(*.jpg *.jpeg);;"));
    first_img->load(image_path);
    if(first_img->allGray()==false){
        GrayScale::ConvToGrey(*first_img,*first_gray);
    }
    else first_gray=first_img;
    img_for_show=QPixmap::fromImage(*first_img);
    view1.setScene(scene1);
    scene1->addPixmap(img_for_show);
    view1.show();
}

void MainWindow::on_IMG2Load_pressed()
{
    QString image_path=QFileDialog::getOpenFileName(this,tr("Open file"),"",tr("PNG (*.png);;JPEG(*.jpg *.jpeg);;"));
    second_img->load(image_path);
    if(second_img->allGray()==false){
        GrayScale::ConvToGrey(*second_img,*second_gray);
    }
    else second_gray=second_img;
    img_for_show=QPixmap::fromImage(*second_img);
    view2.setScene(scene2);
    scene2->addPixmap(img_for_show);
    view2.show();
}

void MainWindow::on_FindDisparity_pressed(){
    if(second_img->format()!=0 &&first_img->format()!=0){
        QTime start;
        start.start();
        disparity->FindDisparity(*first_gray,*second_gray,disp_min,disp_max,kernel_size);
        qDebug("Time elapsed: %d ms", start.elapsed());
        img_for_show=QPixmap::fromImage(disparity->GetDispMap());
        view3.setScene(scene3);
        scene3->addPixmap(img_for_show);
        view3.show();
        disparity->GetDispMap().save("E:\\Qt\\Projects\\disparity\\disparity map.png");
    }
}

void MainWindow::on_DispMin_spinBox_valueChanged(int arg1)
{
    disp_min=arg1;
}

void MainWindow::on_DispMax_spinBox_valueChanged(int arg1)
{
    disp_max=arg1;
}



void MainWindow::on_comboBox_currentTextChanged(const QString new_kernel_size)
{
    kernel_size = new_kernel_size.toInt();
}

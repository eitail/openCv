#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    size    = 6;
    size2   = 3;

    //menuInit();
    QLabel_Pic_Init();
    LoadImg();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::menuInit()
{
    qDebug() << "menuInit";
    status = new QStatusBar(this);
    menu[0] = new QMenu("File");
    menu[0]->addAction("Edit");
    menu[0]->addAction("Check");
    menu[0]->addAction("Tool");

     act[0] = new QAction("Create",this);
     act[0]->setShortcut(Qt::CTRL | Qt::Key_A );
     act[0]->setStatusTip("new ");

     act[1] = new QAction("open",this);
     act[1]->setCheckable(true);

    menu[1] = new QMenu("save");
    menu[1]->addAction(act[0]);
    menu[1]->addAction(act[1]);

    menu[2] = new QMenu("print");
    menu[2]->addAction("set ");
    menu[2]->addMenu(menu[1]);

    menuBar = new QMenuBar(this);
    menuBar->addMenu(menu[0]);
    menuBar->addMenu(menu[2]);
    menuBar->setGeometry(0,100,200,30);

    connect(menuBar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));

}

void MainWindow::trigerMenu(QAction* act)
{
    if(act->text() == "Create")
    {
        qDebug()<<"新建菜单被按下";
    }
}

//--------------------------------------------------------------------

void MainWindow::LoadImg()
{
    srcImage = cv::imread("/root/Demo_opencv/openCv/pic/3.jpg");
    if(!srcImage.data)
    {
           qDebug() << "Load img error!";
    }
    else
    {
        cv::cvtColor(srcImage,srcImage,CV_BGR2RGB);
        img = QImage((const unsigned char*)(srcImage.data),srcImage.cols,srcImage.rows,srcImage.cols*srcImage.channels(),QImage::Format_RGB888);
        ui->QL_dst->clear();
        img = img.scaled(ui->QL_src->width(),ui->QL_src->height());
        ui->QL_src->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::QLabel_Pic_Init()
{
    ui->QL_src->setGeometry(10,60,300,300);
    ui->QL_dst->setGeometry(10,380,300,300);
}

void MainWindow::putQlabel()
{
    img = QImage((const unsigned char*)(dstImage.data),dstImage.cols,dstImage.rows,dstImage.cols*dstImage.channels(),QImage::Format_RGB888);
    ui->QL_dst->clear();
    img = img.scaled(ui->QL_dst->width(),ui->QL_dst->height());
    ui->QL_dst->setPixmap(QPixmap::fromImage(img));
}

//--水平翻转--
void MainWindow::on_flip_horizontal_clicked()
{
    cv::flip(srcImage,dstImage,1);
    putQlabel();
}

//--垂直翻转--
void MainWindow::on_flip_vertical_clicked()
{
    cv::flip(srcImage,dstImage,0);
    putQlabel();
}

//--水平垂直翻转--
void MainWindow::on_flip_hor_and_ver_clicked()
{
    cv::flip(srcImage,dstImage,-1);
    putQlabel();
}

//--腐蚀--
void MainWindow::on_form_corrosion_clicked()
{
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(size, size), Point(-1, -1));
    erode(srcImage, dstImage, structureElement);
    putQlabel();
}

//--膨胀--
void MainWindow::on_form_swell_clicked()
{
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(size2, size2), Point(-1, -1));
    dilate(srcImage, dstImage, structureElement);
    putQlabel();
}

//--开运算--
void MainWindow::on_form_open_clicked()
{
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(size2,size2), Point(-1, -1));
    morphologyEx(srcImage, dstImage, CV_MOP_OPEN, structureElement);
    putQlabel();
}

//--闭运算--
void MainWindow::on_form_close_clicked()
{
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(size2, size2), Point(-1, -1));
    morphologyEx(srcImage, dstImage, CV_MOP_CLOSE, structureElement);
    putQlabel();
}

//--形态学梯度--
void MainWindow::on_form_gradient_clicked()
{
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(size2, size2), Point(-1, -1));
    morphologyEx(srcImage, dstImage, CV_MOP_GRADIENT, structureElement);
    putQlabel();
}

//--顶帽--
void MainWindow::on_form_top_clicked()
{
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(size2, size2), Point(-1, -1));
    morphologyEx(srcImage, dstImage, CV_MOP_TOPHAT, structureElement);
    putQlabel();
}

//--黑帽--
void MainWindow::on_form_black_clicked()
{
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(size2, size2), Point(-1, -1));
    morphologyEx(srcImage, dstImage, CV_MOP_BLACKHAT, structureElement);
    putQlabel();
}

//--均值滤波--
void MainWindow::on_filter_aver_clicked()
{
     blur(srcImage, dstImage, Size(11, 11), Point(-1, -1));
     putQlabel();
}

//--方框滤波--
void MainWindow::on_filter_box_clicked()
{
    boxFilter( srcImage, dstImage, -1, Size( 16, 16 ), Point(-1,-1));
    putQlabel();
}

//--高斯滤波--
void MainWindow::on_filter_gaussian_clicked()
{
    GaussianBlur(srcImage, dstImage, Size(11, 11), 11, 11);
    putQlabel();
}

//--中值滤波--
void MainWindow::on_filter_median_clicked()
{
    medianBlur(srcImage, dstImage, 3);
    putQlabel();

}

//--双边滤波--
void MainWindow::on_filter_bilateral_clicked()
{
    bilateralFilter(srcImage, dstImage, 15, 100, 5);
    putQlabel();
}

//--提取水平线--
void MainWindow::on_get_hor_clicked()
{


}

//--提取垂直线--
void MainWindow::on_get_ver_clicked()
{

}

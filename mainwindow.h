#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QDebug>

//#include <opencv.hpp>
 #include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>




using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QMenu*          menu[10];
    QAction*        act[10];
    QMenuBar*       menuBar;
    QStatusBar*     status;

    //-----------------------
    cv::Mat     srcImage;
    cv::Mat     dstImage;
    QImage      img;
    int         size;
    int         size2;

private:
    void menuInit();
    void LoadImg();
    void QLabel_Pic_Init();
    void putQlabel();

private:
    Ui::MainWindow *ui;

public slots:
    void trigerMenu(QAction* act);

private slots:
    void on_flip_horizontal_clicked();
    void on_flip_vertical_clicked();
    void on_flip_hor_and_ver_clicked();
    void on_form_corrosion_clicked();
    void on_form_swell_clicked();
    void on_form_open_clicked();
    void on_form_close_clicked();
    void on_form_gradient_clicked();
    void on_form_top_clicked();
    void on_form_black_clicked();
    void on_filter_aver_clicked();
    void on_filter_box_clicked();
    void on_filter_gaussian_clicked();
    void on_filter_median_clicked();
    void on_filter_bilateral_clicked();
    void on_get_hor_clicked();
    void on_get_ver_clicked();
};

#endif // MAINWINDOW_H

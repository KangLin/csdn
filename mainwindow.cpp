#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cdownload.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
     curl_global_cleanup();
    delete ui;
}

void OnThread()
{
    CDownLoad d;
    d.OnWork();
}

void MainWindow::on_pbStart_clicked()
{
    int num =  ui->edNumber->text().toInt();
    for(int i = 0; i < num; i++)
    {
        std::thread *t = new std::thread(OnThread);
        //if(t.joinable()) t.join();
    }
}

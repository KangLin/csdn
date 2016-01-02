#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cdownload.h"
#include <QThread>
#include <cnumber.h>

extern CNumber g_Number;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    ui->setupUi(this);
    connect(&m_Timer, SIGNAL(timeout()),
            this, SLOT(timeout()));
}

MainWindow::~MainWindow()
{
     curl_global_cleanup();
    delete ui;
}

void OnThread(void *para)
{
    MainWindow* pThis = (MainWindow*)para;
    CDownLoad d;
    d.OnWork(pThis->m_loopNumer);
}

void MainWindow::on_pbStart_clicked()
{
    m_Timer.start(1000);
    g_Number.m_StartTime = QDateTime::currentDateTime();
    m_loopNumer = ui->edLoopNumer->text().toInt();
    int num =  ui->edNumber->text().toInt();
    for(int i = 0; i < num; i++)
    {
        std::thread *t = new std::thread(OnThread, this);
        //if(t.joinable()) t.join();
    }
}

void MainWindow::timeout()
{
    ui->lbLoopNumber->setText(QString::number(g_Number.m_LoopNumber));
    ui->lbTotalNumber->setText(QString::number(g_Number.m_TotalNumber));
    ui->lbUseTime->setText(g_Number.GetUserTime());
}

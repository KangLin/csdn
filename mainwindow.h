#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pbStart_clicked();
    void timeout();
    
private:
    Ui::MainWindow *ui;
    QTimer m_Timer;
    
public:
    int m_loopNumer;
};

#endif // MAINWINDOW_H

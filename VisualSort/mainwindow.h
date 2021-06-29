#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "entry.h"
#include "sort.h"
#include <thread>
#include <random>
#include <array>
#include <QList>
#include <QTime>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_clicked();

private:
    void reset();       //重置所有排序项的值
    std::shared_ptr<std::thread> task;      //后台线程
    Sort s;
    const size_t _objects=300;          //要排序的项的个数
    Entry *entries;
    //因为此数组是程序的主体，所以不用容器，也不用担心数组的内存泄露，因为不会对数组进行更改
    std::vector<int> nums;      //项的值
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

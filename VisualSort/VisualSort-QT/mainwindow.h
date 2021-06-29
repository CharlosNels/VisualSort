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
    void reset();
    std::shared_ptr<std::thread> task;
    Sort s;
    const size_t _objects=150;
    std::shared_ptr<Entry> *entries;
    std::vector<int> nums;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

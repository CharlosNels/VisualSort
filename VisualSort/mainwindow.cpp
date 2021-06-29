#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(size());
    setMaximumSize(size());
    entries=new Entry[_objects];
    size_t w=(static_cast<size_t>(width())/_objects);
    for(size_t i=0;i<_objects;i++){
        entries[static_cast<size_t>(i)].setParent(ui->centralWidget);
        entries[static_cast<size_t>(i)].setGeometry(static_cast<int>(i*w),0,static_cast<int>(w),350);
        int r=(std::rand()%100)+1;
        entries[static_cast<size_t>(i)].setValue(r);
        nums.push_back(r);
    }
    QList<QString> vec{tr("Quick Sort"),
                tr("Quick Sort-MultiThread"),
                tr("Merge Sort"),tr("Heap Sort"),
                tr("Shell Sort"),tr("Insertion Sort"),
                tr("Selection Sort"),tr("Bubble Sort"),tr("std::Sort")};
    QStringList list(vec);
    ui->comboBox->addItems(list);
    ui->timelabel->setText(tr("Elapsed Time : 0 ms"));
    ui->complabel->setText(tr("0 Comparisions"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    //开始排序，必须另开一个后台线程，否则界面会卡死
    if(ui->comboBox->currentText()==tr("Quick Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.quick_sort_entries(entries,0,_objects-1,false);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+tr(" Comparisions"));
        }));

    }else if(ui->comboBox->currentText()==tr("Quick Sort-MultiThread")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.quick_sort_entries(entries,0,_objects-1,true);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+tr(" Comparisions"));
        }));
    }else if(ui->comboBox->currentText()==tr("Merge Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.merge_sort_entries(entries,0,_objects-1);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));

    }else if(ui->comboBox->currentText()==tr("Shell Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.shell_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));
    }else if(ui->comboBox->currentText()==tr("Heap Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.heap_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));

    }else if(ui->comboBox->currentText()==tr("Insertion Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.insert_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));

    }else if(ui->comboBox->currentText()==tr("Selection Sort")){

        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.select_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));

    }else if(ui->comboBox->currentText()==tr("Bubble Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.bubble_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));
    }else if(ui->comboBox->currentText()==tr("std::Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this]{
            QTime timer;
            timer.start();
            s.std_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));
    }
    task->detach();
}
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    Entry::delay=value;
}

void MainWindow::reset(){
    for(size_t i=0;i<_objects;i++){
        entries[i].setValue(nums[i]);
    }
    Entry::comps=0;
    ui->timelabel->setText(tr("Elapsed Time : 0 ms"));
    ui->complabel->setText(tr("0 Comparisions"));
}

void MainWindow::on_pushButton_clicked()
{
    std::thread([this]{reset();}).detach();
}

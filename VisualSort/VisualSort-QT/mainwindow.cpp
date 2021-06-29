#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(size());
    setMaximumSize(size());
    entries=new std::shared_ptr<Entry>[_objects];
    for(int i=0;i<_objects;i++){
        std::shared_ptr<Entry> tmp(new Entry(ui->centralWidget));
        entries[static_cast<size_t>(i)]=tmp;
        tmp->setGeometry(i*6,0,6,350);
        int r=(std::rand()%100)+1;
        tmp->setValue(r);
        nums.push_back(r);
    }
    QList<QString> vec{tr("Quick Sort"),
                tr("Quick Sort-MultiThread"),
                tr("Merge Sort"),tr("Heap Sort"),
                tr("Shell Sort"),tr("Insertion Sort"),
                tr("Selection Sort"),tr("Bubble Sort")};
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
    if(ui->comboBox->currentText()==tr("Quick Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this](){
            QTime timer;
            timer.start();
            s.quick_sort_entries(entries,0,_objects-1,false);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+tr(" Comparisions"));
        }));

    }else if(ui->comboBox->currentText()==tr("Quick Sort-MultiThread")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this](){
            QTime timer;
            timer.start();
            s.quick_sort_entries(entries,0,_objects-1,true);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+tr(" Comparisions"));
        }));
    }else if(ui->comboBox->currentText()==tr("Merge Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this](){
            QTime timer;
            timer.start();
            s.merge_sort_entries(entries,0,_objects-1);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));

    }else if(ui->comboBox->currentText()==tr("Shell Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this](){
            QTime timer;
            timer.start();
            s.shell_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));
    }else if(ui->comboBox->currentText()==tr("Heap Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this](){
            QTime timer;
            timer.start();
            s.heap_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));

    }else if(ui->comboBox->currentText()==tr("Insertion Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this](){
            QTime timer;
            timer.start();
            s.insert_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));

    }else if(ui->comboBox->currentText()==tr("Selection Sort")){

        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this](){
            QTime timer;
            timer.start();
            s.select_sort_entries(entries,_objects);
            ui->timelabel->setText(tr("Elapsed Time : ")+QString::number(timer.elapsed())+tr(" ms"));
            ui->complabel->setText(QString::number(Entry::comps/2)+" Comparisions");
        }));

    }else if(ui->comboBox->currentText()==tr("Bubble Sort")){
        task=std::shared_ptr<std::thread>(new std::thread(
                                              [this](){
            QTime timer;
            timer.start();
            s.bubble_sort_entries(entries,_objects);
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
        entries[i]->setValue(nums[i]);
    }
    Entry::comps=0;
    ui->timelabel->setText(tr("Elapsed Time : 0 ms"));
    ui->complabel->setText(tr("0 Comparisions"));
}

void MainWindow::on_pushButton_clicked()
{
    std::thread t([this](){reset();});
    t.detach();
}

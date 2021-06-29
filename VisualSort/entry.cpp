#include "entry.h"
#include "ui_entry.h"
#include <windows.h>
#include <thread>
#include <iostream>

int Entry::delay=0;

size_t Entry::comps=0;

Entry::Entry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Entry)
{
    ui->setupUi(this);
    connect(this,SIGNAL(ValueChanged(const int &)),this,SLOT(invalid()));
    connect(this,SIGNAL(ComparingChanged(const bool &)),this,SLOT(invalid()));
    connect(this,SIGNAL(ColorChanged(const QColor &)),this,SLOT(invalid()));
    connect(this,SIGNAL(SortingColorChanged(const QColor &)),this,SLOT(invalid()));
}

Entry::Entry(const Entry &ent):QWidget(ent.parentWidget()){
    std::cout<<"called copy func"<<std::endl;
    if(this!=&ent){
        _value=ent._value;
        _color=ent._color;
        _comparing=ent._comparing;
        sorting_color=ent.sorting_color;
        setParent(ent.parentWidget());
        setGeometry(ent.geometry());
    }
}

Entry::~Entry()
{
    delete ui;
}
bool Entry::operator<(Entry &a){
    setComparing(true);
    a.setComparing(true);
    QThread::msleep(static_cast<unsigned long>(Entry::delay));
    setComparing(false);
    a.setComparing(false);
    return _value<a.Value();
}
bool Entry::operator<=(Entry &a){
    setComparing(true);
    a.setComparing(true);
    QThread::msleep(static_cast<unsigned long>(Entry::delay));
    setComparing(false);
    a.setComparing(false);
    return _value<=a.Value();
}

Entry& Entry::operator=(const Entry &ent){
    std::cout<<"called = oper!"<<std::endl;
    if(this!=&ent){
        _value=ent._value;
        _color=ent._color;
        _comparing=ent._comparing;
        sorting_color=ent.sorting_color;
        setParent(ent.parentWidget());
        setGeometry(ent.geometry());
    }
    return *this;
}

Entry::Entry(Entry &&en){
    std::cout<<"called move func!"<<std::endl;
    if(this!=&en){
        _value=en._value;
        _color=en._color;
        _comparing=en._comparing;
        sorting_color=en.sorting_color;
        setParent(en.parentWidget());
        setGeometry(en.geometry());
    }
}

bool Entry::operator==(Entry &a){
    setComparing(true);
    a.setComparing(true);
    QThread::msleep(static_cast<unsigned long>(Entry::delay));
    setComparing(false);
    a.setComparing(false);
    return _value==a.Value();
}
bool Entry::operator>(Entry &a){
    setComparing(true);
    a.setComparing(true);
    QThread::msleep(static_cast<unsigned long>(Entry::delay));
    setComparing(false);
    a.setComparing(false);
    return _value>a.Value();
}
bool Entry::operator>=(Entry &a){
    setComparing(true);
    a.setComparing(true);
    QThread::msleep(static_cast<unsigned long>(Entry::delay));
    setComparing(false);
    a.setComparing(false);
    return _value>=a.Value();
}
const int &Entry::Value()const{
    return _value;
}
const QColor &Entry::Color()const{
    return _color;
}
const QColor &Entry::SortingColor()const{
    return sorting_color;
}
void Entry::setColor(const QColor &clr){
    _color=clr;
    emit ColorChanged(clr);
}
void Entry::setSortingColor(const QColor &clr){
    sorting_color=clr;
    emit SortingColorChanged(clr);
}
void Entry::setValue(const int &newVal){
    _value=newVal;
    emit ValueChanged(newVal);
}

const bool &Entry::Comparing()const{
    return _comparing;
}
void Entry::setComparing(const bool &cmp){
    if(cmp)
        comps++;
    _comparing=cmp;
    emit ComparingChanged(cmp);
}
void Entry::invalid(){
    repaint();
}
void Entry::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QPen(_comparing?sorting_color:_color));
    painter.setBrush(QBrush(_comparing?sorting_color:_color));
    painter.drawRect(1,height()-_value*height()/100,width()-2,_value*height()/100);
}
void swap(Entry &a,Entry &b){
    int temp=a.Value();
    a.setValue(b.Value());
    b.setValue(temp);
}
void swap(Entry *&a,Entry *&b){
    int temp=a->Value();
    a->setValue(b->Value());
    b->setValue(temp);
}

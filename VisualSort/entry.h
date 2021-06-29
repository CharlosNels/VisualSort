#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>
#include <QtGui>
#include <QtCore>

namespace Ui {
class Entry;
}
class Entry : public QWidget
{
    //对排序的控件项进行封装，使之可以进行比较,进行可视化
    Q_OBJECT
    Q_PROPERTY(QColor SortingColor READ SortingColor WRITE setSortingColor NOTIFY SortingColorChanged)
    Q_PROPERTY(QColor Color READ Color WRITE setColor NOTIFY ColorChanged)
    Q_PROPERTY(int Value READ Value WRITE setValue NOTIFY ValueChanged)
    Q_PROPERTY(bool Comparing READ Comparing WRITE setComparing NOTIFY ComparingChanged)
public:
    static int delay;
    static size_t comps;
    explicit Entry(QWidget *parent = nullptr);
    Entry(const Entry &);
    ~Entry()override;
    //重写比较符号
    bool operator<(Entry &);
    bool operator<=(Entry &);
    bool operator==(Entry &);
    bool operator>(Entry &);
    Entry& operator=(const Entry &);
    Entry(Entry &&);
    bool operator>=(Entry &);
    const int &Value()const;
    const QColor &Color()const;
    const QColor &SortingColor()const;
    const bool &Comparing()const;
public slots:
    void setComparing(const bool &);
    void setSortingColor(const QColor &);
    void setColor(const QColor &);
    void setValue(const int &);
    void invalid();
signals:
    void ComparingChanged(const bool &);
    void SortingColorChanged(const QColor &);
    void ColorChanged(const QColor &);
    void ValueChanged(const int &);
protected:
    void paintEvent(QPaintEvent *)override; //重写绘制函数
private:
    int _value=5;       //值，控件显示的高度
    bool _comparing=false;
    QColor _color=QColor(150,150,150);
    QColor sorting_color=QColor(70,70,70);
    Ui::Entry *ui;
};
void swap(Entry *&a,Entry *&b);
void swap(Entry &a,Entry &b);
#endif // ENTRY_H

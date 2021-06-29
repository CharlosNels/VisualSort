#ifndef SORT_H
#define SORT_H
#include "entry.h"
#include <QThread>
#include <vector>
#include <thread>
bool comp(Entry *a,Entry *b);
//此类对排序进行封装，使外部可以调用他的函数进行排序，而无需关心排序的具体细节
class Sort
{
private:            //这些函数是排序内部要用到的，不用暴露给外部
    size_t qsort(Entry *,size_t,size_t);
    void msort(Entry *,const size_t &,const size_t &,const size_t &);
    inline size_t Left(const size_t &);
    inline size_t Right(const size_t &);
    void BuildHeap(Entry *entries,const size_t &);
    void MHeapify(Entry *entries,const size_t &,const size_t &);
public:
    Sort();
    void bubble_sort_entries(Entry *,const size_t &);
    void quick_sort_entries(Entry *,const size_t &,const size_t &,const bool &);
    void merge_sort_entries(Entry *,const size_t &,const size_t &);
    void insert_sort_entries(Entry *,const size_t &);
    void select_sort_entries(Entry *,const size_t &);
    void heap_sort_entries(Entry *,const size_t &);
    void shell_sort_entries(Entry *,const size_t &);
    void std_sort_entries(Entry *,const size_t &);
};
#endif // SORT_H

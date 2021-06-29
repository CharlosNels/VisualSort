#ifndef SORT_H
#define SORT_H
#include "entry.h"
#include <QThread>
#include <vector>
#include <thread>
class Sort
{
private:
    size_t qsort(std::shared_ptr<Entry> *,size_t,size_t);
    void msort(std::shared_ptr<Entry> *,const size_t &,const size_t &,const size_t &);
    void swap(std::shared_ptr<Entry>,std::shared_ptr<Entry>);
    inline size_t Left(const size_t &);
    inline size_t Right(const size_t &);
    void BuildHeap(std::shared_ptr<Entry> *entries,const size_t &);
    void MHeapify(std::shared_ptr<Entry> *entries,const size_t &,const size_t &);
public:
    Sort();
    void bubble_sort_entries(std::shared_ptr<Entry> *,const size_t &);
    void quick_sort_entries(std::shared_ptr<Entry> *,const size_t &,const size_t &,const bool &);
    void merge_sort_entries(std::shared_ptr<Entry> *,const size_t &,const size_t &);
    void insert_sort_entries(std::shared_ptr<Entry> *,const size_t &);
    void select_sort_entries(std::shared_ptr<Entry> *,const size_t &);
    void heap_sort_entries(std::shared_ptr<Entry> *,const size_t &);
    void shell_sort_entries(std::shared_ptr<Entry> *,const size_t &);
};
#endif // SORT_H

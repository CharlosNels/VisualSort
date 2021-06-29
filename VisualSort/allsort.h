#ifndef ALLSORT_H
#define ALLSORT_H
#pragma once
namespace Sorts {
    template<class T>
    void swap(T &a, T &b) {
        T tmp(a);
        a = b;
        b = tmp;
    }
    /*冒泡排序*/
    template<class T, class Compare>
    void bubble_sort(T *arr, const int &size, Compare comp) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (comp(arr[i], arr[j])) {
                    swap(arr[i], arr[j]);
                }
            }
        }
    }

    template<class T>
    void bubble_sort(T *begin, const int &size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (begin[i] < begin[j]) {
                    swap(begin[i], begin[j]);
                }
            }
        }
    }
    /*快速排序*/
    template<class T,class Compare>
    int quick_sort_unit(T* arr, int a,int b,Compare comp) {
        T mid = arr[a];
        while (a < b) {
            while (a < b&&comp(arr[b], mid))b--;
            swap(arr[a], arr[b]);
            while (a < b && !comp(arr[a], mid)) a++;
            swap(arr[a], arr[b]);
        }
        return a;
    }
    template<class T,class Compare>
    void quick_sort(T* arr, const int &a,const int &b, Compare comp) {
        if (a < b) {
            int newPos = quick_sort_unit(arr, a, b,comp);
            quick_sort(arr, a, newPos - 1,comp);
            quick_sort(arr, newPos + 1, b, comp);
        }
    }
    template<class T>
    int quick_sort_unit(T* arr, int a, int b) {
        T mid = arr[a];
        while (a < b) {
            while (a < b && (arr[b] >= mid))b--;
            swap(arr[a], arr[b]);
            while (a < b && (arr[a] <= mid)) a++;
            swap(arr[a], arr[b]);
        }
        return a;
    }
    template<class T>
    void quick_sort(T* arr, const int &a,const int &b) {
        if (a < b) {
            size_t newPos = quick_sort_unit(arr, a, b);
            quick_sort(arr, a, newPos - 1);
            quick_sort(arr, newPos + 1, b);
        }
    }
    /*归并排序*/
    template<class T,class Compare>
    void merge_sort_unit(T *arr,const int &a,const int &mid,const int &b, Compare comp) {
        T *tmp = new T[b-a+1];
        int i = a;
        int j = mid + 1;
        int k;
        for (k = 0; i <= mid && j <= b; k++) {
            if (comp(arr[i], arr[j]))
                tmp[k] = arr[i++];
            else
                tmp[k] = arr[j++];
        }
        while (i <= mid)
            tmp[k++] = arr[i++];
        while (j <= b)
            tmp[k++] = arr[j++];
        for (i = a; i <= b; i++)
            arr[i] = tmp[i - a];
        delete[] tmp;
    }
    template<class T,class Compare>
    void merge_sort(T *arr, const int &a, const int &b, Compare comp) {
        if (a < b) {
            int mid = (a + b) / 2;
            merge_sort(arr, a, mid,comp);
            merge_sort(arr, mid + 1, b, comp);
            merge_sort_unit(arr, a,mid, b, comp);
        }
    }
    template<class T>
    void merge_sort_unit(T *arr, const int &a, const int &mid, const int &b) {
        T *tmp = new T[b - a + 1];
        int i = a;
        int j = mid + 1;
        int k;
        for (k = 0; i <= mid && j <= b; k++) {
            if (arr[i]<= arr[j])
                tmp[k] = arr[i++];
            else
                tmp[k] = arr[j++];
        }
        while (i <= mid)
            tmp[k++] = arr[i++];
        while (j <= b)
            tmp[k++] = arr[j++];
        for (i = a; i <= b; i++)
            arr[i] = tmp[i - a];
        delete[] tmp;
    }
    template<class T>
    void merge_sort(T *arr, const int &a, const int &b) {
        if (a < b) {
            int mid = (a + b) / 2;
            merge_sort(arr, a, mid);
            merge_sort(arr, mid + 1, b);
            merge_sort_unit(arr, a, mid, b);
        }
    }
    /*插入排序*/
    template<class T,class Compare>
    void insert_sort(T *arr,const int &len,Compare comp) {
        for (int i = 1; i < len; i++) {
            if (comp(arr[i] , arr[i - 1])) {
                int j = i - 1;
                int x = arr[i];
                arr[i] = arr[i - 1];
                while (comp(x , arr[j])) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = x;
            }
        }
    }
    template<class T>
    void insert_sort(T *arr, const int &len) {
        for (int i = 1; i < len; i++) {
            if (arr[i] < arr[i - 1]) {
                int j = i - 1;
                int x = arr[i];
                arr[i] = arr[i - 1];
                while (x < arr[j]) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = x;
            }
        }
    }
}

#endif // ALLSORT_H

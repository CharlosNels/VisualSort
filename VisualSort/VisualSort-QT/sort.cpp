#include "sort.h"

Sort::Sort()
{

}
void Sort::swap(std::shared_ptr<Entry> a,std::shared_ptr<Entry> b){
    int tmp=a->Value();
    a->setValue(b->Value());
    b->setValue(tmp);
}
void Sort::bubble_sort_entries(std::shared_ptr<Entry> * entries,const size_t &len){
    for(size_t i=0;i<len;i++){
        for(size_t j=0;j<len-i-1;j++){
            if(*entries[static_cast<size_t>(j)] > *entries[static_cast<size_t>(j+1)]){
                swap(entries[static_cast<size_t>(j)],entries[static_cast<size_t>(j+1)]);
            }
        }
    }
}
void Sort::insert_sort_entries(std::shared_ptr<Entry> * entries,const size_t &len){
    for(size_t i = 1; i < len; i++)
    {
        for(size_t j = i; j > 0; j--)
        {
            if (*entries[j] < *entries[j - 1])
            {
                swap(entries[j], entries[j - 1]);
            }
        }
    }
}
void Sort::msort(std::shared_ptr<Entry> * entries,const size_t &a,const size_t &mid,const size_t &b){
    std::vector<int> tmp;
    size_t i = a;
    size_t j = mid + 1;
    for (; (i <= mid) && (j <= b);) {
        tmp.push_back((*entries[i]<=*entries[j]?entries[i++]->Value():entries[j++]->Value()));
    }
    while (i <= mid)
        tmp.push_back(entries[i++]->Value());
    while (j <= b)
        tmp.push_back(entries[j++]->Value());
    for (i = a; i <= b; i++)
        entries[i]->setValue(tmp[i - a]);
}
void Sort::merge_sort_entries(std::shared_ptr<Entry> * entries,const size_t &a,const size_t &b){
    if (a<b) {
        size_t mid = (a + b) / 2;
        merge_sort_entries(entries, a, mid);
        merge_sort_entries(entries, mid + 1, b);
        msort(entries, a, mid, b);
    }
}
size_t Sort::qsort(std::shared_ptr<Entry> * entries,size_t a,size_t b){
    std::shared_ptr<Entry> mid = entries[a];
    while (a < b) {
         while ((a < b) && (*entries[b] >= *mid)) b--;
         swap(entries[a], entries[b]);
         while ((a < b) && (*entries[a] <= *mid)) a++;
         swap(entries[a], entries[b]);
    }
    entries[a]->setValue(mid->Value());
    return a;
}
void Sort::quick_sort_entries(std::shared_ptr<Entry> * entries,const size_t &a,const size_t &b,const bool &flag){
    if(a<b){
        size_t newPos=qsort(entries,a,b);
        if(flag){
            std::thread([this,entries,a,newPos](){quick_sort_entries(entries,a,newPos-1,true);}).detach();
            std::thread([this,entries,b,newPos](){quick_sort_entries(entries,newPos+1,b,true);}).detach();
        }else{
            quick_sort_entries(entries,a,newPos-1,false);
            quick_sort_entries(entries,newPos+1,b,false);
        }
    }
}

void Sort::select_sort_entries(std::shared_ptr<Entry> * entries,const size_t &len){
    for(size_t i = 0; i < len - 1; i++)
    {
        size_t min = i;
        for(size_t j = i + 1; j < len; j++)
        {
            if (*entries[j] < *entries[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            swap(entries[min], entries[i]);
        }
    }
}

size_t Sort::Left(const size_t &i){
    return i*2+1;
}

size_t Sort::Right(const size_t &i){
    return i*2+2;
}

void Sort::BuildHeap(std::shared_ptr<Entry> *entries,const size_t &len){
    for (int i = len/2-1; i >= 0; i--)
    {
        MHeapify(entries, i, len);

    }
}

void Sort::MHeapify(std::shared_ptr<Entry> *entries,const size_t &pos,const size_t &hsiz){
    size_t left = Left(pos);
    size_t right = Right(pos);

    size_t extremumIndex = pos;
    if (left < hsiz && *entries[left]>*entries[pos])
    {
        extremumIndex = left;
    }

    if (right < hsiz && *entries[right]>*entries[extremumIndex])
    {
        extremumIndex = right;
    }

    if (extremumIndex != pos)
    {
        swap(entries[extremumIndex], entries[pos]);
        MHeapify(entries, extremumIndex, hsiz);
    }
}

void Sort::heap_sort_entries(std::shared_ptr<Entry> * entries,const size_t &len){
    BuildHeap(entries,len);
    for (int i = len - 1; i > 0; i--)
    {
        swap(entries[i], entries[0]);
        MHeapify(entries, 0, i);
    }
}

void Sort::shell_sort_entries(std::shared_ptr<Entry> * entries,const size_t &len){
    for(int gap = len / 2; gap > 0; gap >>= 1)
    {
        for(int i = gap; i < len; i++)
        {
            for (int j = i - gap; j >= 0 && *entries[j] > *entries[j + gap]; j -= gap)
            {
                swap(entries[j], entries[j + gap]);
            }
        }
    }
}


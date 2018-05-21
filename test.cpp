#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<fstream>
#include <vector>

using namespace std;

int swap(int &a, int &b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}
void printAll(int *num,int count){
    for(int i=0; i<count; i++){
        cout <<num[i]<<" ";
    }
    cout<<endl;
    return;
}
void bubbleSort(int *num,int count){
    for(int i=0; i<count; i++){
        for(int j=0; j<i; j++){
            if(num[j]>num[i]){
                swap(num[j],num[i]);
            }
        }
    }
    //printAll(num,count);
    return;
}
void selectionSort(int *num,int count){
    int flag;

    for(int i=0; i<count;i++){
        int temp=num[i]; //放最小值
        flag=i;
        for(int j=i+1; j<count;j++){
            if(temp>num[j]){
                temp=num[j];
                flag=j;
            }
        }
        if(i!=flag) swap(num[i],num[flag]);
    }
    //printAll(num,count);
}
void insertSort(int *num,int count){
    for(int i=0; i<count; i++){
            int temp=num[i];
        for(int j=i-1; j>=0; j--){
            if(temp<num[j]) swap(num[j+1],num[j]);
            //printAll(num,count);
        }
    }
}

void quickSort(int *num, int left ,int right){
    if (right <= left) return;
    int pivotIndex=(int)(left+right)/2;
    int pivot=num[pivotIndex];
    swap(num[pivotIndex],num[right]);
    int swapIndex = left;
    for(int i=left;i<right;++i){
        if(num[i]<=pivot){
            swap(num[i],num[swapIndex]);
            swapIndex++;
        }
    }
    swap(num[right],num[swapIndex]);
    quickSort(num,left,swapIndex-1);
    quickSort(num,swapIndex+1,right);
}

void MaxHeapify(std::vector<int> &array, int root, int length){

    int left = 2*root,      // 取得left child
    right = 2*root + 1,     // 取得right child
    largest;                // largest用來記錄包含root與child, 三者之中Key最大的node

    if (left <= length && array[left] > array[root])
        largest = left;
    else
        largest = root;

    if (right <= length && array[right] > array[largest])
        largest = right;

    if (largest != root) {                         // 如果目前root的Key不是三者中的最大
        swap(array[largest], array[root]);         // 就調換root與三者中Key最大的node之位置
        MaxHeapify(array, largest, length);        // 調整新的subtree成Max Heap
    }
}

void BuildMaxHeap(std::vector<int> &array){

    for (int i = (int)array.size()/2; i >= 1 ; i--) {
        MaxHeapify(array, i, (int)array.size() - 1);     // length要減一, 因為heap從1開始存放資料
    }
}

void HeapSort(std::vector<int> &array){

    array.insert(array.begin(), 0);                     // 將index(0)閒置

    BuildMaxHeap(array);                                // 將array調整成Max Heap

    int size = (int)array.size() -1;                    // size用來記錄「目前要處理的矩陣」之長度
    for (int i = (int)array.size() -1; i >= 2; i--) {
        swap(array[1], array[i]);                       // 將最大值放到array的最後一個位置
        size--;
        MaxHeapify(array, 1, size);                     // 調整「忽略最後一個位置」的矩陣
    }

    array.erase(array.begin());                         // 將index(0)刪除
}

void PrintArray(std::vector<int> &array){
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    int count;
    int test_count=25;


    while(cin>>count){
        int num[count];
        float test_time[25];
        for(int i=0;i<25;i++){      //做25次
            float total_time = 0;
            clock_t start_time, end_time;
            srand(time(NULL));
            for(int j=0; j<count; j++){
                num[j]=(rand());
                //cout <<num[i]<<" ";
            }
            vector<int> array(num, num+sizeof(num)/sizeof(int));
            start_time = clock(); // mircosecond begin time
            //bubbleSort(num,count);
            selectionSort(num,count);
            //quickSort(num,0,count-1);
            //insertSort(num,count);
            //HeapSort(array);
            end_time = clock();
            total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
            cout<<i<<". "<<total_time<<endl;
            test_time[i]=total_time;
            //printAll(num,count);
        }
        ofstream file("test.txt");              //output the file
        for(int i=0; i<25; i++){
            if(i==24){
                file<<(float)test_time[i];
            } else{
                file<<(float)test_time[i]<<endl;
            }
        }
        file.close();
        cout<<"完成"<<endl;
    }


/*
    cin >>count;    //測試演算法
    float total_time = 0;
    clock_t start_time, end_time;
    int num[count];
    srand(time(NULL));
    for(int j=0; j<count; j++){
        num[j]=(rand());
    }

    start_time = clock(); // mircosecond begin time
    vector<int> array(num, num+sizeof(num)/sizeof(int));
    HeapSort(array);
    end_time = clock();
    total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    cout<<total_time<<endl;
    //printAll(num,count);
    PrintArray(array);
*/
    return 0;
}


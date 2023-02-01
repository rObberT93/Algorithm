/*
随机化快速排序
*/
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
//定义了一个数组，可以在此处改变数组大小，求数组长度（此处数组长度可以直接用SIZE，但此处只是给出一个define求数组长度的方法，方便今后使用）
#define SIZE 20
int a[SIZE];
#define GETLEN(a) sizeof(a)/sizeof(a[0])-1//宏定义获取数组长度的函数GETLEN

//生成一个随机数组，为了使创造的数组有重复的数字采取了对size求余的做法
void initRandomArray(){
    srand(unsigned(time(0)));
    for (int i=0; i<SIZE; i++) {
        a[i]=(int)rand()%SIZE;
    }
}

//打印数组
void printArray(const int  a[],int len){
    for (int i=0; i<=len; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

//取得划分点函数
//划分点的作用是将数组分为两部分，使得左边的所有数字都小于右边的数字
int getPivot(int a[],int left,int right){
    int pivot;
    if (left<right) {
        int low=left,high=right,key=a[left];
        while (low<high) {
            while(a[high]>=key&&low<high) {
                high--;
            }
            a[low]=a[high];
            while(a[low]<=a[high]&&low<high) {
                low++;
            }
            a[high]=a[low];
        }
        pivot=low;
        a[pivot]=key;
    }
    return pivot;
}
//普通快排
void quickSort(int a[],int left,int right){
    if (left<right) {
        int pivot=getPivot(a, left, right);
        quickSort(a,left,pivot-1);
        quickSort(a,pivot+1,right);
    }
}
//随机快排
//不同的是它在每次递归调用前随机选择一个数字作为划分点
void randomizedQuickSort(int a[],int left,int right){
    if (left<right) {
        srand(unsigned(time(NULL)));
        int randNum=rand()%(right-left+1)+left;
        swap(a[left], a[randNum]);
        int pivot=getPivot(a, left, right);
        randomizedQuickSort(a, left, pivot-1);
        randomizedQuickSort(a, pivot+1,right);
    }
}
int main(int argc, const char * argv[]) {
    initRandomArray();
    int len=GETLEN(a);
    printArray(a, len);
//    quickSort(a, 0,len);
    randomizedQuickSort(a, 0, len);
    printArray(a,len);
    return 0;
}

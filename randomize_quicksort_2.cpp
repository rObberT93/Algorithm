#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;
void insertionSort(int *a,int l,int r)
{
    if(r-l==0)return;
    for(int i=l+1;i<r;i++)
    {
        int j=i-1;
        int key=a[i];
        while(j>=l && a[j]>=key)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
}

template <typename T>
int _partition2(T arr[], int l, int r){
    swap( arr[l] , arr[rand()%(r-l+1)+l] );
    T v = arr[l];

    // arr[l+1...i) <= v; arr(j...r] >= v
    int i = l+1, j = r;
    while( true ){
        while( i <= r && arr[i] < v )
            i ++;
        while( j >= l+1 && arr[j] > v )
            j --;
        if( i > j )
            break;
        swap( arr[i] , arr[j] );
        i ++;
        j --;
    }

    swap( arr[l] , arr[j]);
    return j;
}
template <typename T>
void _quickSort(T arr[], int l, int r){

    // 对于小规模数组, 使用插入排序进行优化
    if( r - l <= 15 ){
        insertionSort(arr,l,r);
        return;
    }

    // 调用双路快速排序的partition
    int p = _partition2(arr, l, r);
    _quickSort(arr, l, p-1 );
    _quickSort(arr, p+1, r);
}

template <typename T>
void quickSort(T arr[], int n){

    srand(time(NULL));
    _quickSort(arr, 0, n-1);
}
int main()
{
    int n;
    cin>>n;
    int a[1000];
    for(int i=0;i<n;i++) cin>>a[i];
    quickSort(a,n);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    return 0;
}
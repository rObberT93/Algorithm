#include<iostream>
using namespace std;

void Merge(int *a,int low,int mid,int high)
{
    int i=low,j=mid+1,k=0;//low为第1有序区的第1个元素，i指向第1个元素, mid为第1有序区的最后1个元素
    int *temp=new int[high-low+1];//mid+1为第2有序区第1个元素，j指向第1个元素
    while(i<=mid&&j<=high)
    {
        if(a[i]<=a[j]) temp[k++]=a[i++];
        else temp[k++]=a[j++];
    }
    while(i<=mid) temp[k++]=a[i++];//若比较完之后，第一个有序区仍有剩余，则直接复制到t数组中
    while(j<=high) temp[k++]=a[j++];
    for(i=low,k=0;i<=high;i++,k++) a[i]=temp[k];//将排好序的存回

    delete []temp;//删除指针
}
void MergeSort(int *a,int low,int high)
{
    if(low<high)
    {
        int mid=low+((high-low)>>1);
        MergeSort(a,low,mid);
        MergeSort(a,mid+1,high);
        Merge(a,low,mid,high);
    }
    
    
}
int main(){
    int n;
    cin>>n;
    int a[1000];
    for(int i=0;i<n;i++) cin>>a[i];
    MergeSort(a,0,n-1);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    return 0;

}
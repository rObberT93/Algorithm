/*
数组第k大元素
*/
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
void swap(int &a,int &b)
{
    int tmp=a;
    a=b;
    b=tmp;
}
int partition(int *nums,int left,int right)
{
    srand(unsigned(time(NULL)));
    int pivot = left + (rand() % (right - left + 1));
    swap(nums[left],nums[pivot]);
    int base=nums[left];
    int i=left,j=right;
    while(i<j)
    {
        while(i<j && nums[j]<=base) j--;
        if(i<j) nums[i++]=nums[j];
        while(i<j && nums[i]>=base) i++;
        if(i<j) nums[j--]=nums[i];
    }
    nums[i]=pivot;
    return i;
}
int findKthLargest(int* nums,int n,int k) 
{
    int left = 0, right = n - 1;
    while (true) 
    {
        int pos = partition(nums, left, right);
        if (pos == k - 1) return nums[pos];
        else if (pos < k - 1) left = pos + 1;
        else right = pos - 1;
    }
}
int main()
{
    int a[1000];
    int n; cin>>n;
    for (int i=0;i<n;i++) cin>>a[i];
    int k; cin>>k;
    int res=findKthLargest(a,n,k);
    cout<<res;
}
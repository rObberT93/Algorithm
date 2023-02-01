#include<iostream>
using namespace std;

void insertion_sort(int *a,int n)
{
    if(n==1)return;
    for(int i=1;i<n;i++)
    {
        int j=i-1;
        int key=a[i];
        while(j>=0 && a[j]>=key)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
}
int main()
{
    int n;
    cin>>n;
    int a[1000];
    for(int i=0;i<n;i++) cin>>a[i];
    insertion_sort(a,n);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    return 0;
}
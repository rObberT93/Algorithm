#include<iostream>
using namespace std;

int INCRGAP=3;

void shell_sort(int *a,int n)
{
    for(int gap=n/ INCRGAP+1;gap>0;gap/= INCRGAP)
    // 步长初始化,注意如果当len<INCRGAP时，gap为0，所以为了保证进入循环，gap至少为1
    // 如果步进方式为gap=gap/2的话不用考虑
    {
        for(int i=0;i<gap;i++)
        {
            for(int j=i+gap;j<n;j+=gap)
            {
                if(a[j]<a[j-gap])
                {
                    int tmp=a[j];
                    int k=j-gap;
                    while(k>=0 &&a[k]>tmp)
                    {
                        a[k+gap]=a[k];
                        k-=gap;
                    }
                    a[k+gap]=tmp;
                }
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    int a[1000];
    for(int i=0;i<n;i++) cin>>a[i];
    shell_sort(a,n);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    return 0;
}
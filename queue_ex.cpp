/*
n个人(n<=100)围成一圈,从第一个人开始报数,数到m的人出列,
再由下一个人重新从1开始报数,数到m的人再出圈,……
依次类推,直到所有的人都出圈,请输出依次出圈人的编号
*/
#include<iostream>
#include<queue>
using namespace std;
queue<int>q;

int main()
{
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)
        q.push(i);
    int now=1;
    while(!q.empty())
    {
        if(now==m)
        {
            cout<<q.front()<<" ";
            q.pop();
            now=1;
        }
        else{
            q.push(q.front());// 实现环
            q.pop();// 维护队列中所有元素至多出现一次
            now++;
        }
    }
    return 0;

}
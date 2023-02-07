#include <iostream>
using namespace std;
/* 创建一个单链表 */
struct ListNode{
    int data;
    ListNode* next;
};
ListNode* createList(int n)// 初始化长度为n(+1)的链表
{
	ListNode *pHead,*end;
	pHead=new ListNode;
	pHead->data=0;
    end = pHead;
    for (int i = 1; i <=n; ++i) 
	{
        ListNode* pNewNode = new ListNode;
        cin>>pNewNode->data; // 将新节点的值赋值为i
        end->next = pNewNode; // 上一个节点指向这个新建立的节点
        end = pNewNode; // p节点指向这个新的节点
    }
	end->next=nullptr;
	return pHead;
}
void printList(ListNode* head)// 打印链表
{
	while(head->next!=nullptr)
	{
		head=head->next;
		cout<<head->data<<" ";
	}
	cout<<"\n";
}
void changeNode(ListNode*head,int n)// 修改第n个节点
{
	int i=0;
	ListNode*h=head;
	while(h->next!=nullptr&&i<n)
	{
		h=h->next;
		i++;
	}
	if(h!=NULL)
	{
		puts("输入要修改的值:");
		cin>>h->data;
	}
	else
		puts("该节点不存在");
}
void deleteNode(ListNode*head,int n)// 删除第n个节点
{
	ListNode*h=head;
	ListNode*pre=head;
	int i=0;
	while(i<n&&h!=NULL)
	{
		pre=h;// pre指向现在的h所指向的上一个
		h=h->next;
		i++;
	}
	if(h!=NULL)
	{
		pre->next=h->next;
		delete h;
	}
	else puts("该节点不存在");
}
void endInsert(ListNode*head,int n) // 后插法：在第n位之后插入值（插完之后是第n+1位）
{
	ListNode*h=head;
	ListNode*cur;
	int i=0;
	while(i<n&&h!=NULL)
	{
		h=h->next;// 找到要插入的位置
		i++;
	}
	if(h!=NULL)
	{
		cur=new ListNode;
		puts("请输入要插入的值:");
		cin>>cur->data;
		cur->next=h->next;
		h->next=cur;
	}
	else puts("该节点不存在");
}
void preInsert(ListNode*head,int n) // 前插法 在第n位之前插入值（插完之后是第n位）
{
	ListNode*h=head;
	ListNode*pre=head;
	int i=0;
	while(i<n&&h->next!=nullptr)
	{
		pre=h;
		h=h->next;
		i++;
	}
	if(h!=NULL)
	{
		ListNode*cur=new ListNode;
		puts("请输入要插入的值:");
		cin>>cur->data;
		pre->next=cur;
		cur->next=h;
	}
	else puts("该节点不存在");
}
void searchNode(ListNode*head,int n) // 查找第n个节点的值
{
	ListNode*h=head;
	int i=0;
	while(i<n&&h->next!=nullptr)
	{
		h=h->next;
		i++;
	}
	if(h!=NULL)
	{
		puts("该节点的值为:");
		cout<<h->data;
	}
	else puts("该节点不存在");
}
int main()
{
	puts("请输入初始链表节点数:");
	int n;cin>>n;
	puts("请输入各个节点的值:");
    ListNode* head =createList(n);
    printList(head);

	puts("输入要修改第几个节点(首元节点下标为1):");
	int changeIndex=0;cin>>changeIndex;
	changeNode(head,changeIndex);
	printList(head);

	puts("输入要删除第几个节点(首元节点下标为1):");
	int deleteIndex=0;cin>>deleteIndex;
	deleteNode(head,deleteIndex);
	printList(head);

	puts("后插法,输入要在第几个节点后插入节点(首元节点下标为1):");
	int endInsertIndex=0;cin>>endInsertIndex;
	endInsert(head,endInsertIndex);
	printList(head);

	puts("前插法,输入要在第几个节点前插入节点(首元节点下标为1):");
	int preInsertIndex=0;cin>>preInsertIndex;
	preInsert(head,preInsertIndex);
	printList(head);

	puts("输入要查找第几个节点的值(首元节点下标为1):");
	int searchIndex=0;cin>>searchIndex;
	searchNode(head,searchIndex);

    return 0;
}
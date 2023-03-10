#ifndef BST_H
#endif BST_H // 防止BST被重复引用
#include<iostream>
#include<assert.h>
#include<queue>
using namespace std;

template<typename Key, typename Value>
class BST
{
public:
	BST()
	{ //构造函数 默认构造一棵空二分搜索树
		root = NULL;
		count = 0;
		// root(nullptr),count(0) {}
	}
	~BST()
	{ // 析构函数
		destroy(root);
	}
	int size()
	{ // 返回二分搜索树种节点数量
		return count;
	}
	bool empty()
	{ //判断二分搜索树是否为空
		return count == 0;
	}
	void insert(Key key,Value value)
	{ // 向二分搜索树中插入一个新的(key, value)数据对
		root = insert(root,key,value);
	}
	bool contain(Key key)
	{ // 查看二分搜索树中是否存在键key
		return contain(root,key);
	}
	bool search(Key key)
	{ // 在二分搜索树中搜索键key所对应的值 如果这个值不存在 返回null
		return search(root,key);
	}
	void preOrder() // 前序遍历
	{
		preOrder(root);
	}
	void inOrder() //中序遍历
	{
		inOrder(root);
	}
	void postOrder() //后序遍历
	{
		postOrder(root);
	}
	/*
	层序遍历
	将每层的节点存在队列中
	然后进行出队（取出节点）和入队（存入下一层的节点）的操作
	*/
	void levelOrder()
	{
		levelOrder(root);
	}
	Key maxKey() // 返回树中最大键值
	{
		assert(count != 0);
		Node* maxNode=maxKey(root);
		return maxNode->key;
	}
	key minKey() // 返回树中最小键值
	{
		assert(count != 0);
		Node* minNode = minKey(root);
		return minNode->key;
	}
	void removeMin() //删除树中最小键值
	{
		if(root)
			root=removeMin(root);
	}
	void removeMax() //删除树中最大键值
	{
		if (root)
			root = removeMax(root);
	}
	void remove(Key key) //删除树中指定键值 
	{
		root = remove(root, key);
	}

private:
// 树中的节点为私有的类，外界不需要了解二分搜索树节点的具体信息
	struct Node
	{//二分搜索树中的节点
		Key key;
		Value value;
		Node* left;
		Node* right;
		Node(Key key, Value value)
		{//Node的构造函数
		/*两种构造方法
		1.this指针
		2.内置构造函数
		*/
			this->key = key;
			this->value = value;
			this->left = this->right = NULL;
			// key(key),value(value),left(nullptr),right(nullptr) {} 节点构造函数
		}
		Node(Node* node)
		{
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
			// key(node->key),value(node->value),left(node->left),right(node->right) {} 节点构造函数
		}
	};
	Node* root;//二分搜索树根节点
	int count;//二分搜索树中的节点数

	void destroy(Node* node)
	{ //本质就是后序遍历
		if(node != NULL)
		{
		destroy(node->left);
		destroy(node->right);
		delete node;
		}
	}

	// 向以node为根的二分搜索树中, 插入节点(key, value), 使用递归算法
	// 返回插入新节点后的二分搜索树的根
	Node* insert(Node* node,Key key,Value value)
	{
		if(node == nullptr)
		{ // 根节点不存在 此节点为第一个节点
			count++;
			Node* root = new Node(key,value);
			return root;
		}
		if(key==node->key) // 递归终止条件 
			node->value=value;
		else if(key < node->key) // 看左节点
			node->left=insert(node,left,key,value);
		else 
			node->right=insert(node->right,key,value);
		return node;
	}
	bool contain(Node* node,Key key)
	{ // 查看以node为根的二分搜索树中是否包含键值为key的节点, 使用递归算法
		if(node==nullptr) 
			return false;
		if(node->key==key) 
			return true;
		if(node->key < key) 
			return contain(node->right,key);
		if(key<node->key)
			return contain(node->left,key);
	}
	Value* search(Node* node.Key key)
	{
		if(node==nullptr) 
			return nullptr;
		if(node->key==key) 
			return &(node->value);
		if(node->key < key) 
			return search(node->right,key);
		if(key<node->key)
			return search(node->left,key);
	}
	void preOrder(Node* node) // 前序遍历
	{
		if(node==nullptr)
			return;
		cout<<node->key<<endl;
		preOrder(root->left);
		preOrder(root->right);
	}
	void inOrder(Node* node) //中序遍历
	{
		if(node==nullptr)
			return;
		inOrder(node->left);
		cout<<node->key<<endl;
		inOrder(node->right);
	}
	void postOrder(Node* node) //后序遍历
	{
		if(node==nullptr)
			return;
		postOrder(node->left);
		postOrder(node->right);
		cout<<node->key<<endl;
	}
	void levelOrder(Node* node)
	{
		queue<Node*>que;
		que.push(root);
		while(!qu.empty())
		{
			Node* tmp=que.front();
			que.pop();
			cout<<tmp->key<<endl;
			if(tmp->left!=nullptr)
				que.push(tmp->left);
			if(tmp->right!=nullptr)
				que.push(tmp->right);
		}
	}
	Node* maxKey(Node* node) // 返回最大键值
	{
		if(node->right==nullptr) // 右节点为空 没有比当前节点大的键值
			return node;
		return maxKey(node->right);
	}
	Node* minKey(Node* node) // 返回最小键值
	{
		if(node->left==nullptr)
			return node;
		return minKey(node->left);
	}
	Node* removeMin(Node* node) 
	// 删除掉以node为根的二分搜索树中的最大节点 返回删除节点后新的二分搜索树的根
	{
		if(node->left==nullptr)
		{
			Node* rightnode=node->right;
			delete node;
			count--;
			return rightnode;
		}
		node->left=removeMin(node->left);
		return node;
	}
	Node* removeMax(Node* node)
	{
		if(node->right==nullptr)
		{
			Node* leftnode=node->left;
			delete node;
			count--;
			return leftnode;
		}
		node->right=removeMax(node->right);
		return node;
	}
	Node* remove(Node* node,Key key)
	// 删除掉以node为根的二分搜索树中键值为key的节点, 递归算法
	// 返回删除节点后新的二分搜索树的根
	{
		if(node==nullptr)
			return node;
		if(node->key<key)
		{
			node->right=remove(node->right);
			return node;
		}
		else if(key<node->key)
		{
			node->left=remove(node->left);
			return node;
		}
		else 
		{
			if(node->left==nullptr)
			{
				Node* rightnode=node->right;
				delete node;
				count--;
				return rightnode;
			}
			if(node->right==nullptr)
			{
				Node* leftnode=node->left;
				delete node;
				count--;
				return leftnode;
			}
			Node* newnode = new Node(minKey(node->right));
			count++; //创建了一个新结点先将节点数量+1，因为下一步的删除指定子树最小节点的函数会将节点数量-1
			newnode->right = removeMin(node->right);
			newnode->left = node->left;
			delete node;
			count--;
			return newnode;
		}
	}
};
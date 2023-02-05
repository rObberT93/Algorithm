#include<vector>
using namespace std;
class DisjSet
{
	private:
		vector<int>parent;
		vector<int>rank;
	public:
		DisjSet(int max_size): parent(vector<int>(max_size)) ,rank(vector<int>(max_size))
		// member initialize list
		{
			for(int i=0;i<max_size;i++)
			{
				// 初始化每一个元素的根节点为自身
				parent[i]=i;
			}
		}
		// 找到一个元素的根节点
		int find(int x)
		{
			if(parent[x]==x)
				return x;
			else
				return find(parent[x]);
		}
		// 优化查找 路径压缩
		int find_plus(int x)
		{
			if(x==parent[x])
				return x;
			else
			{
				parent[x]=find(parent[x]);
				return parent[x];
			}
			/*
			等价写法
			return x == parent[x] ? x : (parent[x] = find(parent[x]));
			*/ 
		}
		// 合并两个元素所在的集合
		void to_union(int x1,int x2)
		{
			int p1=find(x1);
			int p2=find(x2);
			parent[p1]=p2;
		}
		// 优化合并
		void to_union_plus(int x1,int x2)
		{
			int f1=find(x1);
			int f2=find(x2);
			if(rank[f1]>rank[f2])
				parent[f2]=f1;
			else if(rank[f1]<rank[f2])
				parent[f1]=f2;
			else // 高度一样
			{
				parent[f1]=f2; // 任意合并
				++rank[f2];
			}
		}
		// 判断两个元素是否属于同一个集合
		bool is_same(int e1,int e2)
		{
			return find(e1)==find(e2);
		}
};
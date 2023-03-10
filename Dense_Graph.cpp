#ifndef _GRAPH_H_
#define _GRAPH_H_
#include<iostream>
#include<queue>
#include<limits.h>
#include<algorithm>
using namespace std;

// 定义常量
const int VISITTED=1;
const int UNVISITTED=0;
const int INF=INT_MAX;

// 边的结构体
struct edge
{
	int start;// 起点
	int end;// 终点
	int wt;// 权重
};
// 图的虚类 表示一些图中需要实现的基本函数
class Graph
{
	private:
		void operator=(const Graph&){} // 赋值
		Graph(const Graph&){} // 拷贝函数
	public:
		Graph(){}
		virtual ~Graph(){}
		virtual void Init(int n)=0;// 初始化
		virtual int n()=0;// 返回图的顶点数
		virtual int e()=0;// 返回图的边数
		virtual int first(int v)=0;// 返回第一个
		virtual int next(int v,int w)=0;// 返回下一个
		virtual void setEdge(int val,int v2,int wght)=0; //给两个点之间的边来设计权重
		virtual void delEdge(int v1,int v2)=0;//删掉两点之间的边
		virtual bool isEdge(int i,int j)=0;// 判断是否为存在的边
		virtual int weight(int v1,int v2)=0;// 取权重

		virtual int getMark(int v)=0;// 取出标记
		virtual void setMark(int v ,int val)=0;// 进行标记
};
// 使用邻接矩阵进行存储
class Graphm:public Graph // 图中承接虚类的基本函数实现
{
	private:
		int numVertex;// 节点数
		int numEdge;// 边数
		int **matrix; //邻接矩阵
		int *mark; //存放是否访问该点的数组
		bool ishui;// 判断是否为回路
	public:
		Graphm(int numVert){Init(numVert);}// 构造函数
		~Graphm() // 析构函数
		{
			delete []mark;
			for(int i=0;i<numVertex;i++)
				delete []matrix[i];
			delete matrix;
		}
		void Init(int n) // 初始化函数
		{
			numVertex=n; // 初始化节点总数
			numEdge=0; // 未连边
			mark=new int[n]; // 初始化空访问数组
			for(int i=0;i<numVertex;i++)
				mark[i]=UNVISITTED; // 初始化节点为未访问
			matrix=(int**)new int*[numVertex]; // 建立二维数组
			for(int i=0;i<numVertex;i++)
				matrix[i]=new int[numVertex];
			for(int i=0;i<numVertex;i++)
				for(int j=0;j<numVertex;j++)
					matrix[i][j]=0; // 初始化权重为0
			ishui=true;
		}
		int n(){return numVertex;} // 取出图中顶点数
		int e(){return numEdge;} // 取出图中的边数

		int first(int v) // 返回v的第一个邻居
		{
			for(int i=0;i<numVertex;i++)
				if(matrix[v][i]!=0) 
					return i;
			return numVertex; // 如果不存在，就返回n
		}
		int next(int v,int w) // 返回v在w后的第一个邻居
		{
			for(int i=w+1;i<numVertex;i++)
				if(matrix[v][i]!=0)
					return i;
			return numVertex;
		}
		void setEdge(int v1,int v2,int wt)// 设置v1和v2之间的边权重为wt
		{
			if(matrix[v1][v2]==0) // 如果没有边 增加一条边
				numEdge++;
			matrix[v1][v2]=matrix[v2][v1]=wt;
		}
		void delEdge(int v1,int v2) // 删除v1和v2之间的边
		{
			if(matrix[v1][v2]!=0)
				numEdge--;
			matrix[v1][v2]=0;
		}
		bool isEdge(int v1,int v2) // 判断v1和v2之间是否有边
		{
			return matrix[v1][v2]!=0;
		}
		int weight(int v1,int v2){return matrix[v1][v2];}// 返回v1和v2两点间的权重
		int getMark(int v){return mark[v];}// 返回v这个点是否被标记
		void setMark(int v,int val){mark[v]=val;}// 设置某节点的访问数组
		void initMark(){for(int i=0;i<numVertex;i++)mark[i]=UNVISITTED;}// 初始化访问数组
		void print() // 打印邻接矩阵
		{
			for(int i=0;i<numVertex;i++)
			 	for(int j=0;j<numVertex;j++)
					cout<<matrix[i][j]<<" ";
				cout<<endl;
		}

		/*
		深度优先搜索遍历图：
		给定了图以及开始的顶点v，
		如果顶点v没有被访问过，则输出v并计数加1，将顶点v置为已访问。
		然后以v为顶点开始寻找一条路径进行搜索，
		搜索到底时退后一步寻找其他路径，直到所有顶点都被访问为止。
		*/
		int num=0; // 回路中定点数量
		void DFS(Graphm* G,int v)
		{
			if(G->getMark(v)==UNVISITTED)// 如果v这个节点未访问
			{
				if(num==G->n()-2)// last vertex
					cout<<v;
				else
					cout<<v<<" ";
				num++;
			}
			G->setMark(v,VISITTED); //将v置为已访问
			for(int w=G->first(v);w<G->n();w=G->next(v,w)) // for循环 递归调用函数
				if(G->getMark(w)==UNVISITTED)
					DFS(G,w);
		}
		/*
		广度优先搜索遍历图：
		使用了数据结构队列
		给定图以及开始顶点start
		将start存入队列进行访问后，将start出队并将其所有相邻顶点入队，重复此操作直到所有顶点访问完成
		注意：在代码最后加了一个判断图中是否存在未访问顶点的判断，当存在未访问顶点时说明该图为非连通图
		*/
		void BFS(Graphm* G,int start)
		{
			int v,w;
			queue<int>q;
			int cnt=0;
			q.push(start);
			G->setMark(start,VISITTED);
			while(!q.empty())
			{
				v=q.front();
				if(cnt==G->n()-2)
					cout<<v;
				else
					cout<<v<<" ";
				q.pop();
				for(w=G->first(v);w<G->n();w=G->next(v,w))
				{
					if(G->getMark(w)==UNVISITTED)
					{
						G->setMark(w,VISITTED);
						q.push(w);
					}
				}
                cnt++;
			}
			for(int i=1;i<numVertex;i++)
			{
				if(G->getMark(i)==UNVISITTED)
				{
					ishui=false;
					break;
				}
			}
		}
		/*
		求单源最短路径：
		给定图以及存放路径长度的数组D、开始顶点s、存放具体路径的字符串数组n。
		先挑选一条从s出发的边，然后比较是直接连接更近还是走其他的边更近，经过比较后选出两点间最短的路径。
		*/
		int minVertex(Graph* G,int *D)
		// returns the vertex with the smallest distance that has not been visited yet
		{
			int i,v=-1;
			for(i=0;i<G->n();i++)// 先找到一个未被访问的节点
			{
				if(G->getMark(i)==UNVISITTED)
				{
					v=i;
					break;
				}
			}
			for(i++;i<numVertex;i++) // 从已找到的这个节点向后找到小于这个节点的
				if((G->getMark(i)==UNVISITTED)&&(D[i]<D[v]))// 如果存在 更新
					v=i;
			return v;// 如果不存在，也能返回已经找到的节点
		}
		void Dijkstra(Graphm* G,int *D,int s,string n[])
		{
			for(int i=0;i<G->n();i++)
			{
				int v=minVertex(G,D);// 找到一个最短的边
				if(D[v]==INF)// 如果这个节点度数为0
					return;
				G->setMark(v,VISITTED);// 置为已访问
				for(int w=G->first(v);w<G->n();w=G->next(v,w))
				{
					if(D[w]>(D[v]+G->weight(v,w)))
					{
						D[w]=D[v]+G->weight(v,w);// 更新路径长度
						n[w]=n[v]+" " + std::to_string(w);// string *n是完整路径
					}
				}
			}
		}
		/*
		求最小生成树：
		给定图以及开始顶点s、开始顶点s与各点距离数组D、表示边的数组e。
		首先添加连接顶点s的一条最短边，
		然后将这两个顶点作为一个整体，添加连接它们的一条最短边，
		一直进行扩充直到包含所有顶点为止。
		*/
        //find the minimum spanning tree (MST) of a graph
		void Prim(Graphm* G, int* D,int s,struct edge e[])
        // D[i] represents the minimum distance from the starting vertex s to vertex i.
        // struct edge e[]: an array of struct edge, e[i] represents an edge in the MST
		{
			int *V=new int[G->n()];
            // V[w] represents the vertex that is connected to vertex w in the MST
			int ans=0;// the number of edges in the MST
			for(int i=1;i<G->n();i++)
			{
				int v=minVertex(G,D);// find the next vertex to add to the MST
				G->setMark(v,VISITTED);
				if(v!=s)// if the current vertex v is not the starting vertex s.
				{
					if(V[v]<v) // which vertex is smaller, V[v] or v
					{ // assigns the edges to the edge array e[] accordingly.
						e[ans].start=V[v];
						e[ans].end=v;
						e[ans].wt=G->weight(V[v],v);
					}
					else
					{
						e[ans].start=v;
						e[ans].end=V[v];
						e[ans].wt=G->weight(V[v],v);
					}
					ans++;
				}
				if(D[v]==INF) // there are no more vertices to add to the MST
				    return;
				for(int w=G->first(v);w<G->n();w=G->next(v,w))
				{
					if(D[w]>G->weight(v,w))
					{
						D[w]=G->weight(v,w);
						V[w]=v;
					}
                    // the path to vertex w through vertex v is now the shortest path known so far,
                    // v is recorded as the vertex in the MST that is connected to w
				}
			}
		}
		bool isHui(){return ishui;}//判断是否有回路
};

// 以下为测试代码
bool cmp(edge &a,edge &b){return a.wt<=b.wt;}// sort函数辅助函数

int main()
{
    int p=0,m=0; // p为顶点数，m为边数
    cin>>p>>m;
    Graphm graph(p+1);
    Graphm* G=&graph;

    //建立图中的边
    cout<<"input egde:"<<endl;
    for(int i=0;i<m;i++)
    {
        int a=0,b=0,c=0;// 起点 终点 权重
        cin>>a>>b>>c;
        graph.setEdge(a,b,c);
    }

    // 广度优先
    cout<<"BFS:"<<endl;
    graph.BFS(G,1);
    cout<<endl;
    graph.initMark();

    // 深度优先
    cout<<"DFS:"<<endl;
    graph.DFS(G,1);
    cout<<endl;
    graph.initMark();

    int *distance=new int[p+1];
    string *n=new string[p+1];

    for (int i=0;i<p+1;i++) 
        n[i]="1 "+std::to_string(i);
    for (int i=0;i<p+1;i++)
    {
        if(i==1)
            distance[i]=0;
        else if(G->weight(1,i)==0)
            distance[i]=INF;
        else
            distance[i]=G->weight(1,i);
    }

    // 单源最短路径
    cout<<"Dijkstra:"<<endl;
    graph.Dijkstra(G,distance,1,n);
    for (int i=2;i<p+1;i++)
        cout<<n[i]<<" : "<<distance[i]<<endl;
    graph.initMark();
    
    edge *e = new edge[p-1];

    for (int i=1;i<p+1;i++)
    {
        if(i==1) 
            distance[i]=0;
        else 
            distance[i]=INF;
    }

    // 根据最小树中边的权重进行排序，权重小的放在前面
    cout<<"Prim:"<<endl;
    graph.Prim(G,distance,1,e);
    sort(e,e+m-2,cmp);
    for(int i=0;i<p-1;i++)
        cout<<e[i].start<<" "<<e[i].end<<" "<<e[i].wt<<endl;

    // 判断回路
    cout<<"Is it a huilu?"<<endl;
    if(graph.isHui()==true) 
        cout<<"YES"<<endl;
    else 
        cout<<"NO"<<endl;
    
    system("pause");
    return 0;
}

/*
6 7
1 2 1
1 5 2
2 3 3
2 5 4
3 4 5
4 5 6
4 6 7
*/

# endif
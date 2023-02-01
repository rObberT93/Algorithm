#include<iostream>
using namespace std;

#define DEFAULT_CAPACITY 128

typedef struct _Heap {
	int* arr;		//存储堆元素的数组
	int size;		//当前已存储的元素个数
	int capacity;	//当前的存储容量
}Heap;


bool initHeap(Heap& heap, int* original, int size);//初始化堆
static void buildHeap(Heap& heap);//建立最大堆
static void adjustDown(Heap& heap, int index);//向下调整具体步骤
static bool insertHeap(Heap& heap, int value);//插入元素
static void adjustUp(Heap& heap, int index);//向上比较，维护最大堆
static bool popMax(Heap& heap, int& value);//弹出最大元素

//初始化堆
bool initHeap(Heap& heap, int* original, int size) {
	//如果默认大小比size小，则申请默认大小的空间，否则申请size大小的空间
	int capacity = DEFAULT_CAPACITY > size ? DEFAULT_CAPACITY : size;
	heap.arr = new int[capacity];
	if (!heap.arr)return false;
	heap.capacity = capacity;
	heap.size = 0;
	//如果存在原始数据，则拷贝过来
	if (size > 0) {
		memcpy(heap.arr, original, size * sizeof(int));
		heap.size = size;
		buildHeap(heap);
	}
	return true;
}
 
/*从最后一个父节点开始（heap.size) - 1 / 2）（因为size是从1开始，所以要先减去1）
逐个调整所有的父节点（直到根节点），确保每一个父节点都是最大堆，最后
整体上形成一个最大堆*/
void buildHeap(Heap& heap) {
	for (int i = (heap.size - 1) / 2; i >= 0; i--) {
		adjustDown(heap, i);
	}
}
 
void adjustDown(Heap& heap, int index) {
	int cur = heap.arr[index];  //记录父节点值
	int parent, child;
 
	/*判断是否存在大于当前结点的子节点，如果不存在，则堆本身平衡，不需要
	调整，如果存在，则将最大子节点与之交换，交换后，如果这个子节点还有
	子节点（即parent*2+1<heap.size 成立）则要按照相同步骤对这个子节点进行
	调整*/
	for (parent = index; (parent * 2 + 1) < heap.size; parent = child) {
		child = parent * 2 + 1; //左子节点

		//取两个子节点最大结点
		if (((child + 1) < heap.size) && (heap.arr[child + 1] > heap.arr[child])) {
			child++;
		}
		if (cur >= heap.arr[child])break;//不大于，跳出循环
		else {
			/*大于当前父节点，进行交换，然后从子节点位置继续向下调整，
			即for从第二次循环开始，初始值都为上一次的子节点位置*/
			heap.arr[parent] = heap.arr[child];
			heap.arr[child] = cur;
		}
	}
}

//插入元素
bool insertHeap(Heap& heap, int value) {
	if (heap.size == heap.capacity) {
		fprintf(stderr, "栈空间耗尽!\n");
		return false;
	}
 
	int index = heap.size;
	heap.arr[heap.size++] = value;//先赋值value，再size++
	adjustUp(heap, index);
    return true;
}
 
void adjustUp(Heap& heap, int index) {
	if (index < 0 || index >= heap.size) {
		//如果只有一个结点（插入的结点）inedx<0，或者大于堆的最大值，return掉
		return;
	}
	int temp = heap.arr[index];//temp为插入的值
	while (index > 0) {
		
		int parent = (index - 1) / 2;
		if (parent >= 0) {   //如果索引没有出界，就执行想要操作
			if (heap.arr[parent] < temp) {
				heap.arr[index] = heap.arr[parent];
				heap.arr[parent] = temp;
				index = parent;
			}
			else break;    //如果没有比父结点大，则跳出
		}
		else break;  //越界，结束循环
	}
}

//弹出根节点 最大元素
bool popMax(Heap& heap, int& value) {
	if (heap.size < 1)return false;
	value = heap.arr[0];
 
	//将size-1的位置值赋给根节点，size本身又--
	/*相当于
		heap.arr[0] = heap.arr[heap.size-1];
		heap.size--;
	*/
	heap.arr[0] = heap.arr[--heap.size];
	adjustDown(heap, 0);  //向下执行堆调整
	return true;
}

int main() 
{
	Heap hp;
	int orignArry[] = { 1,2,3,87,93,82,92,86,95 };
 
	if (!initHeap(hp, orignArry, sizeof(orignArry) / sizeof(orignArry[0]))) {
		fprintf(stderr, "初始化堆失败！\n"); //输出到控制台
		exit(-1);
	}
 
	for (int i = 0; i < hp.size; i++) {
		cout <<"arr["<<i<<"]="<<hp.arr[i] << endl;
	}
    insertHeap(hp, 99);
	printf("在堆中插入新的元素99, 插入结果：\n");
	for (int i = 0; i < hp.size; i++) {
		cout << "第" << i << "个数为：" << hp.arr[i] << endl;
    }
    int value;
	while (popMax(hp, value)) {
		cout << "依次出列最大元素：" << value << endl;
    }
	system("pause");
	return 0;
}
#include<iostream>
using namespace std;

#define DEFAULT_CAPACITY 128

typedef struct _Heap {
	int* arr;		//存储堆元素的数组
	int size;		//当前已存储的元素个数
	int capacity;	//当前的存储容量
}Heap;

bool initHeap(Heap& heap, int* original, int size);
static void buildHeap(Heap& heap);
static void adjustDown(Heap& heap, int index);

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
int main() {
 
	Heap hp;
	int orignArry[] = { 1,2,3,87,93,82,92,86,95 };
 
	if (!initHeap(hp, orignArry, sizeof(orignArry) / sizeof(orignArry[0]))) {
		fprintf(stderr, "初始化堆失败！\n"); //输出到控制台
		exit(-1);
	}
 
	for (int i = 0; i < hp.size; i++) {
		cout <<"arr["<<i<<"]="<<hp.arr[i] << endl;
	}
	system("pause");
	return 0;
}
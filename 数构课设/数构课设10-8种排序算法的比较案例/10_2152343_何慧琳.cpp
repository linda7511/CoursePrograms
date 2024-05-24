#include <iostream>
#include <time.h>
using namespace std;
const int DefaultSize = 100;


//待排序数据表的类定义
class element {
    friend class datalist;
public:
    element() :key(0),link(0) {};
    int getKey(int i = 0)
    { //提取关键码
        if (i == 0)//参数为0直接取整个key
            return key;
        else {//参数不为0，取key的第i位，即随机数从个位开始数的第i位
            if (i == 1)
                return key % 10;
            else
                return (key / (10 * (i - 1))) % 10;
        }
    }
    void setKey(const int x) { key = x; }//设置元素关键码
    void setLink(int l) { link = l; }//设置后一个元素的序号
    int getLink() { return link; }//取下一个元素序号
    element* operator =(element& x) { this->key = x.key; this->link = x.link; return this; }
private:
    int key;//关键码，此项目中key即生成随机数的数值
    int link;//后面一个元素的序号
};
class datalist {
    friend void BubbleExchange(datalist& list, const int i, int& exchange);
    friend void BubbleSort(datalist& list);
    friend int SelectExchange(datalist& list, const int i);
    friend void SelectSort(datalist& list);
    friend int Insert(datalist& list, int i);
    friend void InsertSort(datalist& list);
    friend int ShellInsert(datalist& list, const int gap);
    friend void ShellSort(datalist& list);
    friend int Partition(datalist& list, int low, int high, int& change_time);
    friend int FilterDown(datalist& heap, const int i, const int EndOfHeap);
    friend void HeapSort(datalist& list);
    friend int merge(datalist& initlist, datalist& mergedlist, const int m1, const int m2, const int n);
    friend int MergePass(datalist& initlist, datalist& mergedlist, const int len);
    friend void MergeSort(datalist& list);
    friend void RadixSort(datalist& list, const int d, const int radix);
public:
    datalist(int Maxsz=DefaultSize):MaxSize(Maxsz),CurrentSize(Maxsz)
    {//构造函数
        vector = new element[Maxsz];
    }
    void swap(element& x, element& y)
    {//交换
        element temp = x;
        x = y;
        y = temp;
    }
    void setdata(int i, int k) { vector[i].key = k; }//初始化数据表中第i个元素
private:
    element* vector;//存储向量
    int MaxSize, CurrentSize;//最大与当前个数
};


//冒泡排序
void BubbleExchange(datalist& list, const int i, int& exchange)
{
    exchange = 0;//交换标志置0，假定未交换
    for (int j = list.CurrentSize - 1; j >= i; j--)//从最后一个元素开始往前检查到pass为止
        if (list.vector[j - 1].getKey() >list.vector[j].getKey()) { //逆序
            list.swap(list.vector[j - 1], list.vector[j]);//交换
            exchange ++; //有交换，交换标志+1
        }
}
void BubbleSort(datalist& list)
{//冒泡法将list中的元素从小到大排好序
    clock_t start,end;//记录程序起始和结束的时间
    start = clock();
    int pass = 1;//已排好序的元素个数（也即遍历趟数）
    int exchange = 1;//一趟遍历中是否有元素交换的标识
    long long int change_time = 0;//统计交换次数
    while (pass < list.CurrentSize && exchange) {
        BubbleExchange(list, pass, exchange);
        change_time += exchange;//交换次数累加
        pass++;
    }
    end = clock();
    cout << "冒泡排序所用时间：" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "冒泡排序交换次数：" << change_time << endl;
}

//选择排序
int SelectExchange(datalist& list, const int i)
{//两两比较，将最小的元素交换到第i个位置
    int k = i;
    int change_time = 0;
    for (int j = i + 1; j < list.CurrentSize; j++) {
        if (list.vector[j].getKey() < list.vector[k].getKey())
            k = j;
        if (k != i) {
            list.swap(list.vector[i], list.vector[k]);
            change_time++;//交换次数加一
        }
    }
    return change_time;
}
void SelectSort(datalist& list)
{
    clock_t start, end;//记录程序起始和结束的时间
    start = clock();
    long long int change_time = 0;//统计交换次数
    for (int i = 0; i < list.CurrentSize-1; i++)
        change_time+=SelectExchange(list, i);
    end = clock();
    cout << "选择排序所用时间：" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "选择排序交换次数：" << change_time << endl;
}

//直接插入排序
int Insert(datalist& list, int i)
{//将第i个元素在list的第0-（i-1）个位置中找到符合顺序的插入位置
    int change_time=0;//统计插入一个元素的比较次数
    element temp = list.vector[i];
    int j = i;
    //将j挪到首个不比vector[i]大的元素后,比它大的元素都往后挪一位
    while (j > 0 && temp.getKey() < list.vector[j - 1].getKey()) {
        list.vector[j] = list.vector[j - 1];
        j--;
        change_time++;
    }
    list.vector[j] = temp;//插入vector[i]到第j个位置
    change_time++;
    return change_time;
}
void InsertSort(datalist& list)
{//按关键码key非递减顺序对表进行排序
    long long int change_time = 0;//统计交换次数
    clock_t start, end;//记录程序起始和结束的时间
    start = clock();
    for (int i = 1; i < list.CurrentSize; i++)
        change_time+=Insert(list, i);
    end = clock();
    cout << "直接插入排序所用时间：" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "直接插入排序交换次数：" << change_time << endl;
}

//希尔排序
int ShellInsert(datalist& list, const int gap)
{//对list中相隔gap的元素分到一段序列，用直接插入排序法对每段序列进行排序
    int change_time = 0;//统计一趟希尔排序交换次数
    for (int i = gap; i < list.CurrentSize; i++) {
        int j = i;
        //将vector[i]在其gap序列中找到合适位置插入
        element temp = list.vector[i];
        while (j >= gap && list.vector[j].getKey() < list.vector[j - gap].getKey()) {
            list.vector[j] = list.vector[j -= gap];
            change_time++;
        }
        list.vector[j] = temp;
        change_time++;
    }
    return change_time;
}
void ShellSort(datalist& list)
{
    clock_t start, end;//记录程序起始和结束的时间
    start = clock();
    int change_time = 0;//统计交换次数
    int gap = list.CurrentSize / 2;//子序列间隔
    while (gap) {//循环，直到gap为零
        change_time+=ShellInsert(list, gap);//对各子序列用直接插入排序法排序
        gap = gap == 2 ? 1 : (gap / 2.2);//修改gap大小
    }
    end = clock();
    cout << "希尔排序所用时间：" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "希尔排序交换次数：" << change_time << endl;
}

//快速排序
int Partition(datalist& list, int low, int high,int& change_time)
{//将比基准位置元素小的元素都交换到基准元素左边，pivotpos返回经划分后基准元素的位置
    int pivotpos = low;//设置初始基准位置
    element& pivot = list.vector[low];
    for (int i = low + 1; i <= high; i++) {
        int j = i;
        if (list.vector[i].getKey() < pivot.getKey() && ++pivotpos != i) {
            //每找到一个比pivot小的元素将pivotpos往后移一位，
            //此时若pivotpos指向的元素不为刚找到的元素，则交换二者
            list.swap(list.vector[i], list.vector[pivotpos]);
            change_time++;//交换次数+1
        }
    }
    //将pivot与pivotpos指向的元素，即最后一个比pivot小的元素交换位置
    list.swap(pivot, list.vector[pivotpos]);
    change_time++;
    return pivotpos;
}
int QuickSort(datalist& list, int left, int right)
{//在待排序区间left~right中递归进行快速排序
    static int change_time;
    if (left < right) {
        int pivotpos= Partition(list, left, right,change_time);//划分左右子区间,统计交换次数
        QuickSort(list, left, pivotpos-1);//在左子区间递归进行快速排序
        QuickSort(list, pivotpos + 1, right);//在右子区间递归进行快速排序
    }
    return change_time;
}

//堆排序
int FilterDown(datalist& heap,const int i, const int EndOfHeap)
{//从第i个结点开始自上向下调整为最大堆
    int change_time=0;//统计交换次数
    int current = i;
    int child = 2 * i + 1;
    element temp = heap.vector[i];
    while (child <= EndOfHeap) {
        if (child + 1 < EndOfHeap && heap.vector[child].getKey() < heap.vector[i + 1].getKey())
            child = child + 1;//child取大孩子
        if (temp.getKey() >= heap.vector[child].getKey())
            break;//根节点的值大于子节点中的较大值，满足最大堆条件，循环结束
        else {
            heap.vector[current] = heap.vector[child];//将根节点置为较大值孩子
            current = child;//current指向较大孩子处，继续向下调整直到找到temp适合插入的位置
            child = 2 * child + 1;//更新child
            change_time++;//交换次数+1
        }
    }
    heap.vector[current] = temp;//插入temp
    return change_time;
}
void HeapSort(datalist& list)
{//将表中元素按非递减顺序排列有序
    clock_t start, end;//记录程序起始和结束的时间
    start = clock();
    int change_time = 0;//统计交换次数
    for (int i = (list.CurrentSize - 2) / 2; i >= 0; i--)//从最后一个非叶结点开始
        change_time+=FilterDown(list,i, list.CurrentSize - 1);//将表转化为初始堆
    for (int i = list.CurrentSize - 1; i >= 1; i--) {
        list.swap(list.vector[0], list.vector[i]);//将本趟的堆顶，即尚未排好序的元素中最大的元素交换到从后往前数第一个未确定的位置
        change_time+=FilterDown(list, 0, i - 1);//重建最大堆
    }
    end = clock();
    cout << "堆排序所用时间：" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "堆排序交换次数：" << change_time << endl;
}

//归并排序
int  merge(datalist& initlist, datalist& mergedlist, const int m1, const int m2, const int n)
{//将initlist中m1~m2-1，m2~n两段序列按元素从小到大的顺序存入mergedlist
    int comp_time = 0;//统计比较次数
    int p1 = m1, p2 = m2, pm = 0;//分别为第一、二段序列扫描指针，目标数据表扫描指针
    while (p1 < m2 && p2 < n) {
        if (initlist.vector[p1].getKey() <= initlist.vector[p2].getKey())
            mergedlist.vector[pm++] = initlist.vector[p1++];
        else
            mergedlist.vector[pm++] = initlist.vector[p2++];
        comp_time++;//比较次数+1
    }
    if (p1 < m2)//第一段序列剩余
        for (int n1 = pm, n2 = p1; n1 < n && n2 < m2; n1++, n2++)
            mergedlist.vector[n1] = initlist.vector[n2];
    else//第二段序列剩余
        for (int n1 = pm, n2 = p2; n1 < n && n2 < n; n1++, n2++)
            mergedlist.vector[n1] = initlist.vector[n2];
    return comp_time;
}
int MergePass(datalist& initlist, datalist& mergedlist, const int len)
{//进行一趟归并排序
    int comp_time=0;//统计比较次数
    int i = 0;
    while (i + 2 * len <= initlist.CurrentSize - 1) {
        comp_time +=merge(initlist, mergedlist, i, i + len,i + 2 * len);
        i += 2 * len;
    }
    if (i + len <= initlist.CurrentSize - 1)
        //剩余序列长度大于len小于2len，拆成len长度+剩余的一段序列，将二者合并
        comp_time += merge(initlist, mergedlist, i, i + len,initlist.CurrentSize);
    else for (int j = i; j <= initlist.CurrentSize - 1; j++)
        //剩余序列长度小于len直接照搬
        mergedlist.vector[j] = initlist.vector[j];
    return comp_time;
}
void MergeSort(datalist& list)
{//按关键码非递减的顺序对表list中对象排序
    clock_t start, end;//记录程序起始和结束的时间
    start = clock();
    int comp_time = 0;//统计比较次数
    datalist templist(list.MaxSize);//创建一个辅助数据表
    int len = 1;
    while (len < list.CurrentSize) {
        comp_time+=MergePass(list, templist, len);
        len *= 2;
        comp_time+=MergePass(templist, list, len);
        len *= 2;
    }
    end = clock();
    cout << "归并排序所用时间：" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "归并排序比较次数：" << comp_time << endl;
}

//基数排序
void RadixSort(datalist& list, const int d, const int radix) 
{
    clock_t start, end;//记录程序起始和结束的时间
    start = clock();
    int change_time = 0;//统计交换次数
    int *rear=new int[radix], *front=new int[radix];//开辟n个队列，front和rear分别指向队头队尾
    for (int i = 1; i < list.CurrentSize; i++)
        list.vector[i].setLink(i + 1);
    list.vector[list.CurrentSize-1].setLink(0); //静态链表初始化
    int current = 1; //链表扫描指针
    for (int i = d; i > 0; i--) { //做 d 趟分配.收集
        for (int j = 0; j < radix; j++) front[j] = 0;
        while (current != 0) { //逐个对象分配
            int k = list.vector[current].getKey(i);
            //取当前对象关键码的第 i 位
            if (front[k] == 0) //原链表为空,对象链入
                front[k] = current;
            else //原链表非空,链尾链入
                list.vector[rear[k]].setLink(current);
            rear[k] = current; //修改链尾指针
            current = list.vector[current].getLink();
            change_time++;
        }
        int j = 0; //从0号队列开始收集
        while (front[j] == 0) j++; //空队列跳过
        current = front[j];
        list.vector[0].setLink(current);
        int last = rear[j];
        change_time++;
        for (int k = j + 1; k < radix; k++) //逐个队列链接
            if (front[k]) {//队列不为空,收集
                list.vector[last].setLink(front[k]);
                last = rear[k];
                change_time++;
            }
        list.vector[last].setLink(0);
    }
    end = clock();
    cout << "基数排序所用时间：" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "基数排序交换次数：" << change_time << endl;
}


int main()
{
    cout << "**          排序算法比较          **" << endl;
    cout << "====================================" << endl;
    cout << "**          1---冒泡排序          **" << endl;
    cout << "**          2---选择排序          **" << endl;
    cout << "**          3---直接插入排序      **" << endl;
    cout << "**          4---希尔排序          **" << endl;
    cout << "**          5---快速排序          **" << endl;
    cout << "**          6---堆排序            **" << endl;
    cout << "**          7---归并排序          **" << endl;
    cout << "**          8---基数排序          **" << endl;
    cout << "**          9---退出程序          **" << endl;
    cout << "====================================" << endl;
    int num;//要生成的随机数的个数
    cout << "请输入要产生的随机数的个数：";
    while (1) {
        cin >> num;
        if (cin.fail() || num <= 1) {
            cout << "输入错误，请重新输入：";
            cin.clear();
            cin.ignore(100, '\n');
        }
        else
            break;
    }
    datalist list(num);//创建一个数据表
    cout << endl;
    while (1) {
        cout << "请选择排序算法：";
        int opt;
        while (1) {
            cin >> opt;
            if (cin.fail() || opt < 1 || opt>9) {
                cout << "输入错误，请重新输入：";
                cin.clear();
                cin.ignore(100, '\n');
            }
            else
                break;
        }
        switch (opt) {
        case 1:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //生成num个随机数并初始化数据表
                list.setdata(i, rand());
            BubbleSort(list);
            cout << endl;
            break;
        case 2:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //生成num个随机数并初始化数据表
                list.setdata(i, rand());
            SelectSort(list);
            cout << endl;
            break;
        case 3:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //生成num个随机数并初始化数据表
                list.setdata(i, rand());
            InsertSort(list);
            cout << endl;
            break;
        case 4:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //生成num个随机数并初始化数据表
                list.setdata(i, rand());
            ShellSort(list);
            cout << endl;
            break;
        case 5:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //生成num个随机数并初始化数据表
                list.setdata(i, rand());
            clock_t start, end;
            start = clock();
            {int change_time = QuickSort(list, 0, num - 1); 
            end = clock();
            cout << "快速排序所用时间：" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
            cout << "快速排序交换次数：" << change_time << endl;}
            cout << endl;
            break;
        case 6:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //生成num个随机数并初始化数据表
                list.setdata(i, rand());
            HeapSort(list);
            cout << endl;
            break;
        case 7:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //生成num个随机数并初始化数据表
                list.setdata(i, rand());
            MergeSort(list);
            cout << endl;
            break;
        case 8:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++)//生成num个随机数并初始化数据表
                list.setdata(i, rand());
            RadixSort(list, num, 10);//将随机数的每一位作为一位关键码，则radix为10
            cout << endl;
            break;
        case 9:
            cout << "程序结束，按任意键退出...";
            cin.ignore(1000, '\n');
            while (!getchar())
                ;
            return 0;
        }
    }
    return 0;
}

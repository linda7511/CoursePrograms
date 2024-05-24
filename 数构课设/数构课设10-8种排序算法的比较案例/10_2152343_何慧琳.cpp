#include <iostream>
#include <time.h>
using namespace std;
const int DefaultSize = 100;


//���������ݱ���ඨ��
class element {
    friend class datalist;
public:
    element() :key(0),link(0) {};
    int getKey(int i = 0)
    { //��ȡ�ؼ���
        if (i == 0)//����Ϊ0ֱ��ȡ����key
            return key;
        else {//������Ϊ0��ȡkey�ĵ�iλ����������Ӹ�λ��ʼ���ĵ�iλ
            if (i == 1)
                return key % 10;
            else
                return (key / (10 * (i - 1))) % 10;
        }
    }
    void setKey(const int x) { key = x; }//����Ԫ�عؼ���
    void setLink(int l) { link = l; }//���ú�һ��Ԫ�ص����
    int getLink() { return link; }//ȡ��һ��Ԫ�����
    element* operator =(element& x) { this->key = x.key; this->link = x.link; return this; }
private:
    int key;//�ؼ��룬����Ŀ��key���������������ֵ
    int link;//����һ��Ԫ�ص����
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
    {//���캯��
        vector = new element[Maxsz];
    }
    void swap(element& x, element& y)
    {//����
        element temp = x;
        x = y;
        y = temp;
    }
    void setdata(int i, int k) { vector[i].key = k; }//��ʼ�����ݱ��е�i��Ԫ��
private:
    element* vector;//�洢����
    int MaxSize, CurrentSize;//����뵱ǰ����
};


//ð������
void BubbleExchange(datalist& list, const int i, int& exchange)
{
    exchange = 0;//������־��0���ٶ�δ����
    for (int j = list.CurrentSize - 1; j >= i; j--)//�����һ��Ԫ�ؿ�ʼ��ǰ��鵽passΪֹ
        if (list.vector[j - 1].getKey() >list.vector[j].getKey()) { //����
            list.swap(list.vector[j - 1], list.vector[j]);//����
            exchange ++; //�н�����������־+1
        }
}
void BubbleSort(datalist& list)
{//ð�ݷ���list�е�Ԫ�ش�С�����ź���
    clock_t start,end;//��¼������ʼ�ͽ�����ʱ��
    start = clock();
    int pass = 1;//���ź����Ԫ�ظ�����Ҳ������������
    int exchange = 1;//һ�˱������Ƿ���Ԫ�ؽ����ı�ʶ
    long long int change_time = 0;//ͳ�ƽ�������
    while (pass < list.CurrentSize && exchange) {
        BubbleExchange(list, pass, exchange);
        change_time += exchange;//���������ۼ�
        pass++;
    }
    end = clock();
    cout << "ð����������ʱ�䣺" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "ð�����򽻻�������" << change_time << endl;
}

//ѡ������
int SelectExchange(datalist& list, const int i)
{//�����Ƚϣ�����С��Ԫ�ؽ�������i��λ��
    int k = i;
    int change_time = 0;
    for (int j = i + 1; j < list.CurrentSize; j++) {
        if (list.vector[j].getKey() < list.vector[k].getKey())
            k = j;
        if (k != i) {
            list.swap(list.vector[i], list.vector[k]);
            change_time++;//����������һ
        }
    }
    return change_time;
}
void SelectSort(datalist& list)
{
    clock_t start, end;//��¼������ʼ�ͽ�����ʱ��
    start = clock();
    long long int change_time = 0;//ͳ�ƽ�������
    for (int i = 0; i < list.CurrentSize-1; i++)
        change_time+=SelectExchange(list, i);
    end = clock();
    cout << "ѡ����������ʱ�䣺" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "ѡ�����򽻻�������" << change_time << endl;
}

//ֱ�Ӳ�������
int Insert(datalist& list, int i)
{//����i��Ԫ����list�ĵ�0-��i-1����λ�����ҵ�����˳��Ĳ���λ��
    int change_time=0;//ͳ�Ʋ���һ��Ԫ�صıȽϴ���
    element temp = list.vector[i];
    int j = i;
    //��jŲ���׸�����vector[i]���Ԫ�غ�,�������Ԫ�ض�����Ųһλ
    while (j > 0 && temp.getKey() < list.vector[j - 1].getKey()) {
        list.vector[j] = list.vector[j - 1];
        j--;
        change_time++;
    }
    list.vector[j] = temp;//����vector[i]����j��λ��
    change_time++;
    return change_time;
}
void InsertSort(datalist& list)
{//���ؼ���key�ǵݼ�˳��Ա��������
    long long int change_time = 0;//ͳ�ƽ�������
    clock_t start, end;//��¼������ʼ�ͽ�����ʱ��
    start = clock();
    for (int i = 1; i < list.CurrentSize; i++)
        change_time+=Insert(list, i);
    end = clock();
    cout << "ֱ�Ӳ�����������ʱ�䣺" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "ֱ�Ӳ������򽻻�������" << change_time << endl;
}

//ϣ������
int ShellInsert(datalist& list, const int gap)
{//��list�����gap��Ԫ�طֵ�һ�����У���ֱ�Ӳ������򷨶�ÿ�����н�������
    int change_time = 0;//ͳ��һ��ϣ�����򽻻�����
    for (int i = gap; i < list.CurrentSize; i++) {
        int j = i;
        //��vector[i]����gap�������ҵ�����λ�ò���
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
    clock_t start, end;//��¼������ʼ�ͽ�����ʱ��
    start = clock();
    int change_time = 0;//ͳ�ƽ�������
    int gap = list.CurrentSize / 2;//�����м��
    while (gap) {//ѭ����ֱ��gapΪ��
        change_time+=ShellInsert(list, gap);//�Ը���������ֱ�Ӳ�����������
        gap = gap == 2 ? 1 : (gap / 2.2);//�޸�gap��С
    }
    end = clock();
    cout << "ϣ����������ʱ�䣺" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "ϣ�����򽻻�������" << change_time << endl;
}

//��������
int Partition(datalist& list, int low, int high,int& change_time)
{//���Ȼ�׼λ��Ԫ��С��Ԫ�ض���������׼Ԫ����ߣ�pivotpos���ؾ����ֺ��׼Ԫ�ص�λ��
    int pivotpos = low;//���ó�ʼ��׼λ��
    element& pivot = list.vector[low];
    for (int i = low + 1; i <= high; i++) {
        int j = i;
        if (list.vector[i].getKey() < pivot.getKey() && ++pivotpos != i) {
            //ÿ�ҵ�һ����pivotС��Ԫ�ؽ�pivotpos������һλ��
            //��ʱ��pivotposָ���Ԫ�ز�Ϊ���ҵ���Ԫ�أ��򽻻�����
            list.swap(list.vector[i], list.vector[pivotpos]);
            change_time++;//��������+1
        }
    }
    //��pivot��pivotposָ���Ԫ�أ������һ����pivotС��Ԫ�ؽ���λ��
    list.swap(pivot, list.vector[pivotpos]);
    change_time++;
    return pivotpos;
}
int QuickSort(datalist& list, int left, int right)
{//�ڴ���������left~right�еݹ���п�������
    static int change_time;
    if (left < right) {
        int pivotpos= Partition(list, left, right,change_time);//��������������,ͳ�ƽ�������
        QuickSort(list, left, pivotpos-1);//����������ݹ���п�������
        QuickSort(list, pivotpos + 1, right);//����������ݹ���п�������
    }
    return change_time;
}

//������
int FilterDown(datalist& heap,const int i, const int EndOfHeap)
{//�ӵ�i����㿪ʼ�������µ���Ϊ����
    int change_time=0;//ͳ�ƽ�������
    int current = i;
    int child = 2 * i + 1;
    element temp = heap.vector[i];
    while (child <= EndOfHeap) {
        if (child + 1 < EndOfHeap && heap.vector[child].getKey() < heap.vector[i + 1].getKey())
            child = child + 1;//childȡ����
        if (temp.getKey() >= heap.vector[child].getKey())
            break;//���ڵ��ֵ�����ӽڵ��еĽϴ�ֵ����������������ѭ������
        else {
            heap.vector[current] = heap.vector[child];//�����ڵ���Ϊ�ϴ�ֵ����
            current = child;//currentָ��ϴ��Ӵ����������µ���ֱ���ҵ�temp�ʺϲ����λ��
            child = 2 * child + 1;//����child
            change_time++;//��������+1
        }
    }
    heap.vector[current] = temp;//����temp
    return change_time;
}
void HeapSort(datalist& list)
{//������Ԫ�ذ��ǵݼ�˳����������
    clock_t start, end;//��¼������ʼ�ͽ�����ʱ��
    start = clock();
    int change_time = 0;//ͳ�ƽ�������
    for (int i = (list.CurrentSize - 2) / 2; i >= 0; i--)//�����һ����Ҷ��㿪ʼ
        change_time+=FilterDown(list,i, list.CurrentSize - 1);//����ת��Ϊ��ʼ��
    for (int i = list.CurrentSize - 1; i >= 1; i--) {
        list.swap(list.vector[0], list.vector[i]);//�����˵ĶѶ�������δ�ź����Ԫ��������Ԫ�ؽ������Ӻ���ǰ����һ��δȷ����λ��
        change_time+=FilterDown(list, 0, i - 1);//�ؽ�����
    }
    end = clock();
    cout << "����������ʱ�䣺" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "�����򽻻�������" << change_time << endl;
}

//�鲢����
int  merge(datalist& initlist, datalist& mergedlist, const int m1, const int m2, const int n)
{//��initlist��m1~m2-1��m2~n�������а�Ԫ�ش�С�����˳�����mergedlist
    int comp_time = 0;//ͳ�ƱȽϴ���
    int p1 = m1, p2 = m2, pm = 0;//�ֱ�Ϊ��һ����������ɨ��ָ�룬Ŀ�����ݱ�ɨ��ָ��
    while (p1 < m2 && p2 < n) {
        if (initlist.vector[p1].getKey() <= initlist.vector[p2].getKey())
            mergedlist.vector[pm++] = initlist.vector[p1++];
        else
            mergedlist.vector[pm++] = initlist.vector[p2++];
        comp_time++;//�Ƚϴ���+1
    }
    if (p1 < m2)//��һ������ʣ��
        for (int n1 = pm, n2 = p1; n1 < n && n2 < m2; n1++, n2++)
            mergedlist.vector[n1] = initlist.vector[n2];
    else//�ڶ�������ʣ��
        for (int n1 = pm, n2 = p2; n1 < n && n2 < n; n1++, n2++)
            mergedlist.vector[n1] = initlist.vector[n2];
    return comp_time;
}
int MergePass(datalist& initlist, datalist& mergedlist, const int len)
{//����һ�˹鲢����
    int comp_time=0;//ͳ�ƱȽϴ���
    int i = 0;
    while (i + 2 * len <= initlist.CurrentSize - 1) {
        comp_time +=merge(initlist, mergedlist, i, i + len,i + 2 * len);
        i += 2 * len;
    }
    if (i + len <= initlist.CurrentSize - 1)
        //ʣ�����г��ȴ���lenС��2len�����len����+ʣ���һ�����У������ߺϲ�
        comp_time += merge(initlist, mergedlist, i, i + len,initlist.CurrentSize);
    else for (int j = i; j <= initlist.CurrentSize - 1; j++)
        //ʣ�����г���С��lenֱ���հ�
        mergedlist.vector[j] = initlist.vector[j];
    return comp_time;
}
void MergeSort(datalist& list)
{//���ؼ���ǵݼ���˳��Ա�list�ж�������
    clock_t start, end;//��¼������ʼ�ͽ�����ʱ��
    start = clock();
    int comp_time = 0;//ͳ�ƱȽϴ���
    datalist templist(list.MaxSize);//����һ���������ݱ�
    int len = 1;
    while (len < list.CurrentSize) {
        comp_time+=MergePass(list, templist, len);
        len *= 2;
        comp_time+=MergePass(templist, list, len);
        len *= 2;
    }
    end = clock();
    cout << "�鲢��������ʱ�䣺" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "�鲢����Ƚϴ�����" << comp_time << endl;
}

//��������
void RadixSort(datalist& list, const int d, const int radix) 
{
    clock_t start, end;//��¼������ʼ�ͽ�����ʱ��
    start = clock();
    int change_time = 0;//ͳ�ƽ�������
    int *rear=new int[radix], *front=new int[radix];//����n�����У�front��rear�ֱ�ָ���ͷ��β
    for (int i = 1; i < list.CurrentSize; i++)
        list.vector[i].setLink(i + 1);
    list.vector[list.CurrentSize-1].setLink(0); //��̬�����ʼ��
    int current = 1; //����ɨ��ָ��
    for (int i = d; i > 0; i--) { //�� d �˷���.�ռ�
        for (int j = 0; j < radix; j++) front[j] = 0;
        while (current != 0) { //����������
            int k = list.vector[current].getKey(i);
            //ȡ��ǰ����ؼ���ĵ� i λ
            if (front[k] == 0) //ԭ����Ϊ��,��������
                front[k] = current;
            else //ԭ����ǿ�,��β����
                list.vector[rear[k]].setLink(current);
            rear[k] = current; //�޸���βָ��
            current = list.vector[current].getLink();
            change_time++;
        }
        int j = 0; //��0�Ŷ��п�ʼ�ռ�
        while (front[j] == 0) j++; //�ն�������
        current = front[j];
        list.vector[0].setLink(current);
        int last = rear[j];
        change_time++;
        for (int k = j + 1; k < radix; k++) //�����������
            if (front[k]) {//���в�Ϊ��,�ռ�
                list.vector[last].setLink(front[k]);
                last = rear[k];
                change_time++;
            }
        list.vector[last].setLink(0);
    }
    end = clock();
    cout << "������������ʱ�䣺" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
    cout << "�������򽻻�������" << change_time << endl;
}


int main()
{
    cout << "**          �����㷨�Ƚ�          **" << endl;
    cout << "====================================" << endl;
    cout << "**          1---ð������          **" << endl;
    cout << "**          2---ѡ������          **" << endl;
    cout << "**          3---ֱ�Ӳ�������      **" << endl;
    cout << "**          4---ϣ������          **" << endl;
    cout << "**          5---��������          **" << endl;
    cout << "**          6---������            **" << endl;
    cout << "**          7---�鲢����          **" << endl;
    cout << "**          8---��������          **" << endl;
    cout << "**          9---�˳�����          **" << endl;
    cout << "====================================" << endl;
    int num;//Ҫ���ɵ�������ĸ���
    cout << "������Ҫ������������ĸ�����";
    while (1) {
        cin >> num;
        if (cin.fail() || num <= 1) {
            cout << "����������������룺";
            cin.clear();
            cin.ignore(100, '\n');
        }
        else
            break;
    }
    datalist list(num);//����һ�����ݱ�
    cout << endl;
    while (1) {
        cout << "��ѡ�������㷨��";
        int opt;
        while (1) {
            cin >> opt;
            if (cin.fail() || opt < 1 || opt>9) {
                cout << "����������������룺";
                cin.clear();
                cin.ignore(100, '\n');
            }
            else
                break;
        }
        switch (opt) {
        case 1:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //����num�����������ʼ�����ݱ�
                list.setdata(i, rand());
            BubbleSort(list);
            cout << endl;
            break;
        case 2:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //����num�����������ʼ�����ݱ�
                list.setdata(i, rand());
            SelectSort(list);
            cout << endl;
            break;
        case 3:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //����num�����������ʼ�����ݱ�
                list.setdata(i, rand());
            InsertSort(list);
            cout << endl;
            break;
        case 4:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //����num�����������ʼ�����ݱ�
                list.setdata(i, rand());
            ShellSort(list);
            cout << endl;
            break;
        case 5:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //����num�����������ʼ�����ݱ�
                list.setdata(i, rand());
            clock_t start, end;
            start = clock();
            {int change_time = QuickSort(list, 0, num - 1); 
            end = clock();
            cout << "������������ʱ�䣺" << (double)((end - start) / CLOCKS_PER_SEC) << endl;
            cout << "�������򽻻�������" << change_time << endl;}
            cout << endl;
            break;
        case 6:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //����num�����������ʼ�����ݱ�
                list.setdata(i, rand());
            HeapSort(list);
            cout << endl;
            break;
        case 7:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++) //����num�����������ʼ�����ݱ�
                list.setdata(i, rand());
            MergeSort(list);
            cout << endl;
            break;
        case 8:
            srand(unsigned int(time(0)));
            for (int i = 0; i < num; i++)//����num�����������ʼ�����ݱ�
                list.setdata(i, rand());
            RadixSort(list, num, 10);//���������ÿһλ��Ϊһλ�ؼ��룬��radixΪ10
            cout << endl;
            break;
        case 9:
            cout << "�����������������˳�...";
            cin.ignore(1000, '\n');
            while (!getchar())
                ;
            return 0;
        }
    }
    return 0;
}

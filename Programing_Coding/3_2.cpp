#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

string start, endd;
queue<string> q;//存储状态
int len;//状态的长度

int bfs()
{
    unordered_map<string, int> d;//存储该状态下的坐标
    q.push(start);//将初始状态入队列
    d[start] = 0;//初始状态距离为0
    int dx[6] = {-3, -2, -1, 1, 2, 3};//6个向量左三、左二、左一、右一、右二、右三
    
    while (q.size())//当队列为空时结束bfs算法
    {
        string t = q.front();//出队列,命名为状态t
        q.pop();
        int distance = d[t];//取出t状态的距离distance
        if(t == endd) return distance;//如果t状态和终止状态相等,退出bfs,返回distance
        
        int k =  t.find('*');//找出空杯所在的位置
        for (int i = 0; i < 6; i ++ )//枚举6个向量
        {
            int a = k + dx[i];//加上偏移量后点的坐标
            if(a >= 0 && a < len)//如果没有越界
            {
                swap(t[a], t[k]);//交换位置,获取新的状态
                if(!d.count(t))//如果该状态未被遍历则更新该状态的距离,入队列
                {
                    d[t] = distance + 1;
                    q.push(t);
                }
                swap(t[a], t[k]);//还原现场,因为还有剩余的向量并没有被枚举过
            }
        }
    }
    return -1;//如果没有找到的话,返回-1
}

int main()
{
    cin.tie(0);//cin加速器
    
    cin >> start;//读入开始状态
    
    cin >> endd;//读入终止状态
    
    len = start.length();//获取状态的长度
    
    cout << bfs();//输出答案
    
    return 0;
}
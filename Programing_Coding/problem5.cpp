// 学车费用
// 排序规则： 先按总费用从多到少排序，若总费用相同则按姓名的ASCII码序从小到大排序，
// 若总费用相同而且姓名也相同则按编号（即输入时的顺序号，从1开始编）从小到大排序。

/*
    知识点补充: 
        stringstream 是C++中一个强大的流类,用于字符串的输入输出操作
        #include <sstream>  // 必须包含这个头文件
        stringstream：既可读又可写
        istringstream：只读（从字符串读取）
        ostringstream：只写（写入字符串）

        stringstream 是一个字符串流，它把字符串当作一个连续的字符序列，
        并维护一个内部指针来跟踪当前读取位置。

        提取运算符 >>：根据目标类型读取数据
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;

class Student {
public: 
    string m_name;
    vector<int> m_prices;
    int m_total; 
    int m_id;
    Student() : m_total(0) , m_id(0) {}
};

static bool compare(Student stu1, Student stu2) {
    // 如果费用相等,按照姓名排序
    if (stu1.m_total == stu2.m_total) {
        // 如果姓名也相同,按照输入顺序排序
        if (stu1.m_name == stu2.m_name) {
            return stu1.m_id < stu2.m_id;
        }
        return stu1.m_name < stu2.m_name;
    }
    else {
        // 费用由多到少排序
        return stu1.m_total > stu2.m_total;
    }
}

int main() {
    int n;
    cin >> n;
    cin.ignore();  // 忽略第一行后面的换行符

    // 读取并且创建学生类
    vector<Student> students(n);
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);  // 读取整行
        stringstream ss(line);

        // 读取id
        students[i].m_id = i + 1;

        // 读取姓名
        string name;
        ss >> name;
        students[i].m_name = name;

        // 读取各个费用
        // 这里读取到回车就终止
        int price;
        while(ss >> price) {
            students[i].m_prices.push_back(price);
        }

        // 计算费用总和
        int total = 0;
        for (int j = 0; j < students[i].m_prices.size(); j++) {
            total += students[i].m_prices[j];
        }
        students[i].m_total = total;
    }

    sort(students.begin(),students.end(),compare);

    for (int j = 0; j < students.size(); j++) {
        // 输出排名
        cout << j+1 << " ";
        // 输出姓名
        cout << students[j].m_name << " ";
        // 输出总费用
        cout << students[j].m_total << endl;
    }
}
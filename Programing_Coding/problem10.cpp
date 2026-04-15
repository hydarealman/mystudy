// 迷你搜索引擎
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cctype>
using namespace std;

class File{
public: 
    string title;
    vector<string> text;

    File() {}

    // 逐行添加文件内容
    void addLine(const string& line) {
        text.push_back(line);
    }

    // 返回文件总行数
    int getLineCount() const {
        return text.size();
    }

    // 获取指定行的内容
    string getLine(int lineNum) const {
        if (lineNum >= 0 && lineNum < text.size()) {
            return text[lineNum];
        }
        return "";
    }
};

// 将大写转换为小写
string toLower(const string& s) {
    string result = s;
    transform(result.begin(),result.end(),result.begin(),::tolower);
    return result;
}

// 分割一行文本为单词
vector<string> splitLine(const string& line) {
    vector<string> words;
    stringstream ss(toLower(line));
    string word;
    while(ss >> word) {
        words.push_back(word);
    }
    return words;
}

int main() {
    // 读取N个文件文件
    int N;
    cin >> N;
    cin.ignore(); // 忽略换行符

    vector<File> Files(N);

    // 建立倒排索引
    // 索引结果: 单词 -> 文件索引集合
    unordered_map<string, unordered_map<int, unordered_set<int>>> invertedIndex;
    
    // 读取每个文件
    for (int fileIdx = 0; fileIdx < N; fileIdx++) {
        // 读取文件标题
        string name;
        getline(cin,name);  
        Files[fileIdx].title = name;
        
        // 读取文件内容
        int lineNum = 0;  // 当前行号
        while(true) {
            string line;        
            getline(cin,line);

            if (line == "#") {
                break;
            }

            // 逐行存储文件内容
            Files[fileIdx].addLine(line);

            // 处理当前行的单词,建立索引
            vector<string> words = splitLine(line);

            // 去重: 同一行的同一个单词只记录一次
            unordered_set<string> uniqueWords(words.begin(), words.end());
        
            // 更新倒排索引
            for (const string& word : uniqueWords) {
                invertedIndex[word][fileIdx].insert(lineNum);
            }

            lineNum++;
        }
    }

    // 读取M个查询
    int M;
    cin >> M;
    cin.ignore(); // 忽略换行符

    // 处理每个查询
    for (int i = 0; i < M; i++) {
        string query;
        getline(cin, query);

        // 分割查询词
        vector<string> queryWords = splitLine(query);

        if (queryWords.empty()) {
            cout << "0\nNot Found\n";
            continue;
        }

        // 1.找到包含所有查询词的文件
        unordered_set<int> commonFiles;  // 包含所有查询词的文件索引

        // 初始化: 用第一个查询词的文件集合
        if (invertedIndex.count(queryWords[0])) {
            for (const auto& entry : invertedIndex[queryWords[0]]) {
                commonFiles.insert(entry.first);  // entry.first是文件索引
            }
        }

        // 取交集: 确保文件包含所有查询词
        for (size_t i = 1; i < queryWords.size(); i++) {
            const string& word = queryWords[i];

            if (!invertedIndex.count(word)) {
                // 如果某个词在任何文件中都不存在，交集为空
                commonFiles.clear();
                break;
            }

            unordered_set<int> currentFiles;
            for (const auto& entry : invertedIndex[word]) {
                currentFiles.insert(entry.first);
            }

            // 取交集
            unordered_set<int> newCommonFiles;
            for (int fileIdx : commonFiles) {
                if (currentFiles.count(fileIdx)) {
                    newCommonFiles.insert(fileIdx);
                }
            }
            commonFiles = newCommonFiles;
        }

        // 2. 输出符合条件的文件数
        cout << commonFiles.size() << endl;
        // 如果没有符合条件的文件则输出未找到
        if (commonFiles.empty()) {
            cout << "Not Found\n";
        } 
        else {
             // 如果有符合条件的文件: 按文件输入顺序输出（0到N-1）
            for (int fileIdx = 0; fileIdx < N; fileIdx++) {
                if (commonFiles.count(fileIdx)) {
                    // 输出文件标题
                    cout << Files[fileIdx].title << endl;

                    //收集相关行号
                    unordered_set<int> relevantLines;
                    for (const string& word : queryWords) {
                        if (invertedIndex.count(word) && 
                            invertedIndex[word].count(fileIdx)) {
                            const unordered_set<int>& lines = invertedIndex[word][fileIdx];
                            relevantLines.insert(lines.begin(), lines.end());
                        }
                    }

                    // 将行号转换为向量并排序（按行号顺序输出）
                    vector<int> sortedLines(relevantLines.begin(), relevantLines.end());
                    sort(sortedLines.begin(), sortedLines.end());

                    // 输出包含查询词的行
                    for (int lineNum : sortedLines) {
                        cout << Files[fileIdx].getLine(lineNum) << endl;
                    }
                }
            }
        }
    
    }
}
// 鱼
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
using namespace std;

class Point {
public:
    Point() {}
    Point(int x,int y) : m_x(x),m_y(y){}
    int m_x,m_y;
};

// 计算两个向量的平方距离
int get_distance_sqrt(Point a, Point b) {
    int abx = b.m_x - a.m_x;
    int aby = b.m_y - a.m_y;
    return abx*abx + aby*aby;
}

int dotProduct(Point A, Point B, Point C) {
    // 计算向量BA与向量BC的点积
    int BAx = A.m_x - B.m_x;
    int BAy = A.m_x - B.m_x;
    int BCx = C.m_x - B.m_x;
    int BCy = C.m_x - B.m_x;
    return BAx * BCx + BAy * BCy;
}

int main() {
    int n;
    cin >> n;
    vector<Point> Points(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        Points[i] = Point(x,y);
    }
    
    vector<unordered_map<char,Point>> result;

    // 暴力查找每一个可以构成鱼的六元组
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            if (b == a) {
                continue;
            }
            for (int c = 0; c < n; c++) {
                if (c == a || c == b) {
                    continue;
                }
                if (get_distance_sqrt(Points[a],Points[b]) != get_distance_sqrt(Points[a],Points[c])) {
                    continue;
                }
                for (int d = 0; d < n; d++) {
                    if (d == a || d == b || d == c){
                        continue;
                    }
                    if (get_distance_sqrt(Points[b],Points[d]) != get_distance_sqrt(Points[c],Points[d])) {
                        continue;
                    }
                    for (int e = 0; e < n; e++) {
                        if (e == a || e == b || e == c || e == d) {
                            continue;
                        }
                        for (int f = 0; f < n; f++) {
                            if (f == a || f == b || f == c || f == d || f == e) {
                                continue;
                            }
                            if (get_distance_sqrt(Points[d],Points[e]) != get_distance_sqrt(Points[d],Points[f])) {
                                continue;
                            }
                            
                            // 角BAD,角BDA,角CAD,角CDA都是锐角
                            // 角ADE,角ADF大于90度
                            if (dotProduct(Points[b],Points[a],Points[d]) > 0 &&
                                dotProduct(Points[b],Points[d],Points[a]) > 0 &&
                                dotProduct(Points[c],Points[a],Points[d]) > 0 &&
                                dotProduct(Points[c],Points[d],Points[a]) > 0 &&
                                dotProduct(Points[a],Points[d],Points[e]) < 0 &&
                                dotProduct(Points[a],Points[d],Points[f]) < 0
                                ) {
                                // 维护可以构成鱼的六元组
                                unordered_map<char,Point> umap;
                                umap.insert(make_pair('A',Points[a]));
                                umap.insert(make_pair('B',Points[b]));
                                umap.insert(make_pair('C',Points[c]));
                                umap.insert(make_pair('D',Points[d]));
                                umap.insert(make_pair('E',Points[e]));
                                umap.insert(make_pair('F',Points[f]));
                                result.push_back(umap);
                            }
                        }
                    }
                }
            }
        }
    }
    cout << result.size();
}
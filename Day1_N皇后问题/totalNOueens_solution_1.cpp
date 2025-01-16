// 用于提交 Leetcode 第52题，N皇后 II
// 测试链接：https://leetcode.cn/problems/n-queens-ii/description/
// 这是解法 1

class Solution {
public:
    int totalNQueens(int n) {
        int path[10];
        return f(path, 0, n);
    }

    int f(int path[], int i, int n){
        if (i == n) return 1;
        int ans = 0;
        for (int j = 0 ; j < n ; ++j){
            if (check(path, i, j)){
                path[i] = j;
                ans += f(path, i + 1, n);
            }
        }
        return ans;
    }

    bool check(int path[], int i, int j){
        for (int k = 0 ; k < i ; ++k){
            if (path[k] == j || abs(k - i) == abs(path[k] - j)) return false;
        }
        return true;
    }
};

// �����ύ Leetcode ��52�⣬N�ʺ� II
// �������ӣ�https://leetcode.cn/problems/n-queens-ii/description/
// ���ǽⷨ 2

class Solution {
public:
    int totalNQueens(int n) {
        int limit = (1 << n) - 1;
        return f(limit, 0, 0, 0);
    }

    int f(int limit, int col, int left, int right){
        if (col == limit) return 1;
        int ban = col | left | right;
        int allow = limit & (~ban);
        int ans = 0;
        while (allow != 0){
            int status = allow & (-allow);
            allow ^= status;
            ans += f(limit, col | status, (left | status) >> 1, (right | status) << 1);
        }
        return ans;
    }

};

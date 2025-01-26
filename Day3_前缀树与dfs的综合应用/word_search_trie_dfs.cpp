//本程序用于提交LeetCode 第212题 单词搜索II
//测试链接为 ：https://leetcode.cn/problems/word-search-ii/description/
//本程序中dfs的三大剪枝策略以及trie的应用值得研究 

class Solution {
public:
	
	//建立前缀树，遍历棋盘每一个格子展开dfs 
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        build(words);
        vector<string> res;
        for (int i = 0 ; i < board.size() ; ++i){
            for (int j = 0 ; j < board[0].size() ; ++j){
                dfs(board, i, j, 1, res);
            }
        }
        return res;
    }

	//build与insert方法：建立前缀树Trie 
	//这里前缀树的end标记异于普通前缀树，用于标记在此处结尾的字符串长什么样子。 
    const static int N = 3e5 + 9, M = 26;
    int trie[N][M], pass[N];
    string end[N];
    int cnt;
    void build(vector<string>& words){
        cnt = 1;
        for (auto word : words) insert(word);
    }

    void insert(string word){
        int cur = 1;
        pass[cur]++;
        for (int i = 0, path ; i < word.length() ; ++i){
            path = word[i] - 'a';
            if (trie[cur][path] == 0) trie[cur][path] = (++cnt);
            cur = trie[cur][path];
            pass[cur]++;
        }
        end[cur] = word;
    }
    
    
	//深度优先搜索过程 
	//board是棋盘
	//i，j是当前准备搜索的格子行列索引
	//t是上一个考察的前缀树节点编号
	//res用于收集答案 
	//函数的返回值代表搜索到了几个答案 
    int dfs(vector<vector<char>>& board, int i, int j, int t, vector<string>& res){ 
	   	
    	//搜索越界，或者当前为0（即已经搜索过的格子），直接返回0，代表当前函数未搜集到答案。剪枝！ 
        if (i < 0 || i > board.size() - 1 || j < 0 || j > board[0].size() - 1 || board[i][j] == 0) return 0;
        int cur = board[i][j];
        int road = cur - 'a';
        t = trie[t][road]; // 从t出发，由road路径来到子节点 
        
        //这里实际上是两种情形
		//1. t == 0，这意味着前缀树并不存在这个子节点，也就是说这时dfs收集到的路径不符合words[]数组中任何一个单词的样式。于是剪枝！
		//2. t != 0,但是 pass[t] == 0，由于每次dfs时，一旦收集到答案就会将pass值修改（后面必须加上这一步操作）。这种情况意味着当前答案已被收集过。于是剪枝！
		//由于 t == 0 时，pass[t]的值也为0,于是可以合并为一个 pass[t] == 0 的条件判断。 
        if (pass[t] == 0) return 0;  
        
        board[i][j] = 0; //将当前搜索过的格子记为0，防止子过程重复遍历同一个格子。 
        int fix = 0; //fix变量用于记录当前dfs函数收集到了几个答案         
        
        //开始收集答案。本dfs函数收集到的答案数 == 当前格子有多少答案 + 往上、下、左、右走一个格子有多少答案。 
        if (end[t].length() != 0){
        	// 前缀树在当前节点的end值长度不为0，意味着当前格子有答案 
        	//收集答案，更新fix值
			//收集后的end失去了作用，置为空 
            fix++;
            res.push_back(end[t]);
            end[t] = "";
        }
        //往上、下、左、右走一个格子，收集答案。
        fix += dfs(board, i - 1, j, t, res);
        fix += dfs(board, i + 1, j, t, res);
        fix += dfs(board, i, j - 1, t, res);
        fix += dfs(board, i, j + 1, t, res);
        
        pass[t] -= fix; //更新pass的值 
        board[i][j] = cur; //恢复现场，不能对其它dfs造成影响 
        return fix;
    }
};

//本程序用于提交牛客网真题-字典树的实现
//测试链接为：https://www.nowcoder.com/practice/a55a584bc0ca4a83a272680174be113b 
//本程序中的实现方式为：静态数组法


class Solution {
  public:

	//准备好全局变量
    const static int N = 2e6 + 5, M = 26;
    int trie[N][M];
    int pass[N], end[N];
    int cnt;

    vector<string> trieU(vector<vector<string> >& operators) {
        cnt = 1; //cnt置为1，意味着从根节点开始建树 
        vector<string> res;
        for (const auto i : operators) {
            if (i[0] == "1") insertWord(i[1]);
            else if (i[0] == "2") deleteWord(i[1]);
            else if (i[0] == "3") {
                res.push_back(searchWord(i[1]) ? "YES" : "NO");
            } else {
                res.push_back(to_string(prefixNumber(i[1])));
            }
        }
        clear();
        return res;
    }

	//往字典树中插入单词 
    void insertWord(string s) {
        int cur = 1; //当前来到根节点，下同 
        pass[cur]++; 
        for (int i = 0, path ; i < s.length() ; ++i) {
            path = s[i] - 'a'; //找出即将走的路径 
            if (trie[cur][path] == 0) trie[cur][path] = (++cnt); //若无这条路径，新建出来 
            cur = trie[cur][path];
            pass[cur]++;
        }
        end[cur]++;
    }
	
	//查询某单词在字典树中是否出现（必须是完整的单词，不能仅是前缀） 
    bool searchWord(string s) {
        int cur = 1;
        for (int i = 0, path ; i < s.length() ; ++i) {
            path = s[i] - 'a';
            if (trie[cur][path] == 0) return false;
            cur = trie[cur][path];
        }
        return end[cur]; //用于指示找到的到底是完整的单词还是某单词的前缀。
    }

	//查询字典树中具有某前缀的单词数 
    int prefixNumber(string prefix) {
        int cur = 1;
        for (int i = 0, path ; i < prefix.length() ; ++i) {
            path = prefix[i] - 'a';
            if (trie[cur][path] == 0) return 0;
            cur = trie[cur][path];
        }
        return pass[cur];
    }

	//将单词从字典树中删去 
    void deleteWord(string s) {
    	//必须是字典树中存在这个单词，才有删除的必要 
        if (searchWord(s)) {
            int cur = 1;
            pass[cur]--;
            for (int i = 0, path ; i < s.length() ; ++i) {
                path = s[i] - 'a';
                if ((--pass[trie[cur][path]]) == 0) {trie[cur][path] = 0; return;} //假若下一节点pass减为0，意味着这条路径没有字符串使用了，直接剪去。 
                cur = trie[cur][path];
            }
            end[cur]--;
        }
    }

	//这个方法是为了防止测试平台跑多个用测试例时，前面的用例在全局变量中遗留的脏数据影响后面的用例
	//因此，每次跑完一个用例，就要将全局数组清零
    void clear(){
        memset(pass, 0, sizeof(pass));
        memset(end, 0, sizeof(end));
        memset(trie, 0, sizeof(trie));
    }
};
 

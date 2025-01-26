//�����������ύLeetCode ��212�� ��������II
//��������Ϊ ��https://leetcode.cn/problems/word-search-ii/description/
//��������dfs�������֦�����Լ�trie��Ӧ��ֵ���о� 

class Solution {
public:
	
	//����ǰ׺������������ÿһ������չ��dfs 
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

	//build��insert����������ǰ׺��Trie 
	//����ǰ׺����end���������ͨǰ׺�������ڱ���ڴ˴���β���ַ�����ʲô���ӡ� 
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
    
    
	//��������������� 
	//board������
	//i��j�ǵ�ǰ׼�������ĸ�����������
	//t����һ�������ǰ׺���ڵ���
	//res�����ռ��� 
	//�����ķ���ֵ�����������˼����� 
    int dfs(vector<vector<char>>& board, int i, int j, int t, vector<string>& res){ 
	   	
    	//����Խ�磬���ߵ�ǰΪ0�����Ѿ��������ĸ��ӣ���ֱ�ӷ���0������ǰ����δ�Ѽ����𰸡���֦�� 
        if (i < 0 || i > board.size() - 1 || j < 0 || j > board[0].size() - 1 || board[i][j] == 0) return 0;
        int cur = board[i][j];
        int road = cur - 'a';
        t = trie[t][road]; // ��t��������road·�������ӽڵ� 
        
        //����ʵ��������������
		//1. t == 0������ζ��ǰ׺��������������ӽڵ㣬Ҳ����˵��ʱdfs�ռ�����·��������words[]�������κ�һ�����ʵ���ʽ�����Ǽ�֦��
		//2. t != 0,���� pass[t] == 0������ÿ��dfsʱ��һ���ռ����𰸾ͻὫpassֵ�޸ģ�������������һ�������������������ζ�ŵ�ǰ���ѱ��ռ��������Ǽ�֦��
		//���� t == 0 ʱ��pass[t]��ֵҲΪ0,���ǿ��Ժϲ�Ϊһ�� pass[t] == 0 �������жϡ� 
        if (pass[t] == 0) return 0;  
        
        board[i][j] = 0; //����ǰ�������ĸ��Ӽ�Ϊ0����ֹ�ӹ����ظ�����ͬһ�����ӡ� 
        int fix = 0; //fix�������ڼ�¼��ǰdfs�����ռ����˼�����         
        
        //��ʼ�ռ��𰸡���dfs�����ռ����Ĵ��� == ��ǰ�����ж��ٴ� + ���ϡ��¡�������һ�������ж��ٴ𰸡� 
        if (end[t].length() != 0){
        	// ǰ׺���ڵ�ǰ�ڵ��endֵ���Ȳ�Ϊ0����ζ�ŵ�ǰ�����д� 
        	//�ռ��𰸣�����fixֵ
			//�ռ����endʧȥ�����ã���Ϊ�� 
            fix++;
            res.push_back(end[t]);
            end[t] = "";
        }
        //���ϡ��¡�������һ�����ӣ��ռ��𰸡�
        fix += dfs(board, i - 1, j, t, res);
        fix += dfs(board, i + 1, j, t, res);
        fix += dfs(board, i, j - 1, t, res);
        fix += dfs(board, i, j + 1, t, res);
        
        pass[t] -= fix; //����pass��ֵ 
        board[i][j] = cur; //�ָ��ֳ������ܶ�����dfs���Ӱ�� 
        return fix;
    }
};

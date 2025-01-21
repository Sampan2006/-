//�����������ύţ��������-�ֵ�����ʵ��
//��������Ϊ��https://www.nowcoder.com/practice/a55a584bc0ca4a83a272680174be113b 
//�������е�ʵ�ַ�ʽΪ����̬���鷨


class Solution {
  public:

	//׼����ȫ�ֱ���
    const static int N = 2e6 + 5, M = 26;
    int trie[N][M];
    int pass[N], end[N];
    int cnt;

    vector<string> trieU(vector<vector<string> >& operators) {
        cnt = 1; //cnt��Ϊ1����ζ�ŴӸ��ڵ㿪ʼ���� 
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

	//���ֵ����в��뵥�� 
    void insertWord(string s) {
        int cur = 1; //��ǰ�������ڵ㣬��ͬ 
        pass[cur]++; 
        for (int i = 0, path ; i < s.length() ; ++i) {
            path = s[i] - 'a'; //�ҳ������ߵ�·�� 
            if (trie[cur][path] == 0) trie[cur][path] = (++cnt); //��������·�����½����� 
            cur = trie[cur][path];
            pass[cur]++;
        }
        end[cur]++;
    }
	
	//��ѯĳ�������ֵ������Ƿ���֣������������ĵ��ʣ����ܽ���ǰ׺�� 
    bool searchWord(string s) {
        int cur = 1;
        for (int i = 0, path ; i < s.length() ; ++i) {
            path = s[i] - 'a';
            if (trie[cur][path] == 0) return false;
            cur = trie[cur][path];
        }
        return end[cur]; //����ָʾ�ҵ��ĵ����������ĵ��ʻ���ĳ���ʵ�ǰ׺��
    }

	//��ѯ�ֵ����о���ĳǰ׺�ĵ����� 
    int prefixNumber(string prefix) {
        int cur = 1;
        for (int i = 0, path ; i < prefix.length() ; ++i) {
            path = prefix[i] - 'a';
            if (trie[cur][path] == 0) return 0;
            cur = trie[cur][path];
        }
        return pass[cur];
    }

	//�����ʴ��ֵ�����ɾȥ 
    void deleteWord(string s) {
    	//�������ֵ����д���������ʣ�����ɾ���ı�Ҫ 
        if (searchWord(s)) {
            int cur = 1;
            pass[cur]--;
            for (int i = 0, path ; i < s.length() ; ++i) {
                path = s[i] - 'a';
                if ((--pass[trie[cur][path]]) == 0) {trie[cur][path] = 0; return;} //������һ�ڵ�pass��Ϊ0����ζ������·��û���ַ���ʹ���ˣ�ֱ�Ӽ�ȥ�� 
                cur = trie[cur][path];
            }
            end[cur]--;
        }
    }

	//���������Ϊ�˷�ֹ����ƽ̨�ܶ���ò�����ʱ��ǰ���������ȫ�ֱ�����������������Ӱ����������
	//��ˣ�ÿ������һ����������Ҫ��ȫ����������
    void clear(){
        memset(pass, 0, sizeof(pass));
        memset(end, 0, sizeof(end));
        memset(trie, 0, sizeof(trie));
    }
};
 

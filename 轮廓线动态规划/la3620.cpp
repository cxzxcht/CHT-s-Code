// LA3620 Manhattan Wiring
// Rujia Liu
//���仯���� 
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 100000000;

int nrows, ncols;
int G[10][10];

// ��ͷ��ţ�0��ʾ�޲�ͷ��1��ʾ������2��ͨ��2��ʾ������3��ͨ

struct State {
  int up[9]; // up[i](0<=i<m)��ʾ��i�д��������Ϸ��Ĳ�ͷ���
  int left; // ��ǰ�񣨼���һ��Ҫ���õķ������Ĳ�ͷ

  // �����Ʊ���
  int encode() const {
    int key = left;
    for(int i = 0; i < ncols; i++) key = key * 3 + up[i];
    return key;
  }

  // ��(row,col)����һ���·���UDLR�ֱ�Ϊ�÷������������ĸ��߽��ϵĲ�ͷ���
  // ��������״̬�����T��ɹ�����true��ʧ�ܷ���false
  bool next(int row, int col, int U, int D, int L, int R, State& T) const {
    if(row == nrows - 1 && D != 0) return false; // �������·������в�ͷ
    if(col == ncols - 1 && R != 0) return false; // �������ұ߲����в�ͷ

    int must_left = (col > 0 && left != 0); // �Ƿ����Ҫ�����ͷ
    int must_up = (row > 0 && up[col] != 0); // �Ƿ����Ҫ���ϲ�ͷ

    if((must_left && L != left) || (!must_left && L != 0)) return false; // ���ͷ��ƥ��
    if((must_up && U != up[col]) || (!must_up && U != 0)) return false; // �ϲ�ͷ��ƥ��
    if(must_left && must_up && left != up[col]) return false; // �����ͷ���ϲ�ͷ�����ڣ����߱���ƥ��

    // ������״̬��ʵ����ֻ�е�ǰ�е��²�ͷ��left��ͷ�б仯
    for(int i = 0; i < ncols; i++) T.up[i] = up[i];
    T.up[col] = D;
    T.left = R;
    return true;
  }
};

int memo[9][9][59049]; // 3^10

// ��ǰҪ���ø���(row, col)��״̬ΪS��������С�ܳ���
int rec(int row, int col, const State& S) {
  if(col == ncols) { col = 0; row++; }
  if(row == nrows) return 0;

  int key = S.encode();
  int& res = memo[row][col][key];
  if(res >= 0) return res;
  res = INF;

  State T;
  if(G[row][col] <= 1) { // �ո�0�������ϰ���1��
    if(S.next(row, col, 0, 0, 0, 0, T)) res = min(res, rec(row, col+1, T)); // ���������ﶼ������
    if(G[row][col] == 0) // ����ǿո񣬿������ߡ������߲��ֲܷ棬����������һ�����Ӹ��ӵ�ĳ�����߽磨6�������
      for(int t = 1; t <= 2; t++) { // ö���ߵ����ࡣt=1��ʾ2�ߣ�t=2��ʾ3��
        if(S.next(row, col, t, t, 0, 0, T)) res = min(res, rec(row, col+1, T) + 2); // ��<->��
        if(S.next(row, col, t, 0, t, 0, T)) res = min(res, rec(row, col+1, T) + 2); // ��<->��
        if(S.next(row, col, t, 0, 0, t, T)) res = min(res, rec(row, col+1, T) + 2); // ��<->��
        if(S.next(row, col, 0, t, t, 0, T)) res = min(res, rec(row, col+1, T) + 2); // ��<->��
        if(S.next(row, col, 0, t, 0, t, T)) res = min(res, rec(row, col+1, T) + 2); // ��<->��
        if(S.next(row, col, 0, 0, t, t, T)) res = min(res, rec(row, col+1, T) + 2); // ��<->��
      }
  }
  else {
    int t = G[row][col] - 1; // ����Ϊ2��3������ͷ������1��2������Ҫ��1
    // �����߲��ֲܷ棬����������һ�����Ӹ����м�����ֺ�ĳһ���߽磨4�������
    if(S.next(row, col, t, 0, 0, 0, T)) res = min(res, rec(row, col+1, T) + 1); // ���ϱ߽����
    if(S.next(row, col, 0, t, 0, 0, T)) res = min(res, rec(row, col+1, T) + 1); // ���±߽����
    if(S.next(row, col, 0, 0, t, 0, T)) res = min(res, rec(row, col+1, T) + 1); // ����߽����
    if(S.next(row, col, 0, 0, 0, t, T)) res = min(res, rec(row, col+1, T) + 1); // ���ұ߽����
  }
  return res;
}

int main() {
  while(scanf("%d%d", &nrows, &ncols) == 2 && nrows && ncols) {
    for(int i = 0; i < nrows; i++)
      for(int j = 0; j < ncols; j++)
        scanf("%d", &G[i][j]);
    State S;
    memset(&S, 0, sizeof(S));
    memset(memo, -1, sizeof(memo));
    int ans = rec(0, 0, S);
    if(ans == INF) ans = 0;
    printf("%d\n", ans/2);
  }
  return 0;
}

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <cmath>
//#define NDEBUG
#include <assert.h>
#include "limorton/numberProblems.h"
#include "limorton/displayInfo.h"
#include "limorton/sort.h"
#include "limorton/search.h"
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
class Solution {
private:
    vector<int> maxInWin;
public:
    string reverseWords(string s) {
        int size1 = s.size();
        int p1 = 0, p2 = 0;
        string ans;
        ans.resize(size1, ' ');
        cout << ans << "end" << endl;
        while( p2 < size1){
            while(s[p1] == ' ')
                ++p1;
            p2 = p1;
            while(s[p2] != ' ' && p2 < size1)
                ++p2;
            --p2;
            cout << "p1 = " << p1 << endl;
            cout << "p2 = " << p2 << endl;
            int l = p1, r = p2;
            while(l <= p2){
                ans[l++] = s[r--];
            }
            p1 = p2 + 2;
            if(p1 >= size1)
                break;
        }
        return ans;
    }
};

int main()
{
//    Solution sol;
//    string s = "let's join leetcode!";
//    string ans = sol.reverseWords(s);
//    cout << s << endl;
//    cout << ans << endl;
    int i;
    int a[8] = {2, 5, 4, 8, 6, 7, 1, 3};
    while(cin >> i){
        srand(0);
        int b[8];
        for(int j = 0; j < 8; ++j)
            b[j] = a[j];
        cout << Randomized_Select(b, 0, 7, i) << endl;
    }
//    srand(0);
//    Quick_Sort(a, 0, 7);
//    cout_Array(a, 8);

    system("pause");
    return 0;
}

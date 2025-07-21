#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution {
private:
    unordered_map<char, vector<int>> hash;
public:
    string removeDuplicateLetters(string s) {
        int l = s.size();
        for(int i = 0;i < l;i++) {
            if(hash.find(s[i]) == hash.end()) {
                vector<int> tmp{i};
                hash[s[i]] = tmp;
            }
            else {
                hash[s[i]].push_back(i);
            }
        }
        for(auto it : hash) {
            if(it.second.size() != 1) {
                for(auto iter : it.second) {
                    if(it.second.size() == 1) break;
                    string tmp = s;
                    tmp.erase(find(it.second.begin(), it.second.end(), iter) - it.second.begin(), 1);
                    if(tmp < s) {
                        s = tmp;
                        it.second.erase(find(it.second.begin(), it.second.end(), iter));
                    }
                }
            }
        }
        return s;
    }
};
int main() {
    string s;
    cin >> s;
    Solution Sol;
    cout << Sol.removeDuplicateLetters(s);
    return 0;
}
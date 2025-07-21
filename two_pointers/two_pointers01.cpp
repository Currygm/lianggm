#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    string makeFancyString(string s) {
        int l = s.size(), left = 0, right = 0, count = 0;
        string result;
        for( ; left < l; ) {
            count = 0;
            while(right < l && s[left] == s[right]) {
                count++;
                right++;
            }
            if(count >= 3) {
                result.append(s, left, 2);
            }
            else {
                result.append(s, left, count);
            }
            left = right;
        }
        return result;
    }
};

int main() {
    string s;
    cin >> s;
    Solution Sol;
    cout << Sol.makeFancyString(s) << endl;
    return 0;
}
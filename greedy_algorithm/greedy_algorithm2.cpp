#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(const string& a, const string& b){
    string s1 = a + b, s2 = b + a;
    return s1 > s2;
}
class Solution {
private:
    vector<string> hash;
public:
    void int_to_string(int b){
        string a;
        if(b == 0){
            a += '0';
            hash.push_back(a);
            return;
        }
        while(b > 0){
            a += (b%10 + '0');
            b = b / 10;
        }
        reverse(a.begin(), a.end());  //<algorithm>中的函数
        hash.push_back(a);
    }
    string largestNumber(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0;i < n;i++){
            int_to_string(nums[i]);
        }
        string result;
        sort(hash.begin(), hash.end(), cmp);  //<algorithm>中的函数
        string a;
        a += '0';
        if(hash[0] == a){
            result += '0';
            return result;
        }
        for(int i = 0;i < n;i++){
            result += hash[i];
        }
        return result;
    }
};
int main(){
    int n, tmp;
    cin >> n;
    vector<int> nums;
    for(int i = 0;i < n;i++){
        cin >> tmp;
        nums.push_back(tmp);
    }
    Solution sol;
    cout << sol.largestNumber(nums);
    return 0;
}
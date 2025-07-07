#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
class Solution{
private:
    int count = 0;
public:
    int maxEvents(vector<vector<int>>& events){
        int l = events.size(), maxDay = 0;
        for(int i = 0;i < l;i++){
            maxDay = max(maxDay, events[i][1]);  //记录最大的截止日期
        }
        sort(events.begin(), events.end());
        priority_queue<int, vector<int>, greater<int>> mq; //最小堆，用于升序保存各个会议的结束日期，即最小的放在最前面
        //遍历每一个日期
        for(int i = 1, j = 0;i <= maxDay;i++){
            //筛选处开始时间早于i天的会议
            while(j < l && events[j][0] <= i){
                mq.emplace(events[j][1]);
                j++;
            }
            //将结束时间早于i天的过滤掉
            while(!mq.empty() && mq.top() < i){
                mq.pop();
            }
            //在符合条件的会议中挑选出结束时间最早的
            if(!mq.empty()){
                count++;
                mq.pop();
            }
        }
        return count;
    }
};
int main(){
    int n = 0, a = 0, b = 0;
    cin >> n;
    vector<vector<int>> events;
    for(int i = 0;i < n;i++){
        vector<int> event;
        cin >> a >> b;
        event.push_back(a);
        event.push_back(b);
        events.push_back(event);
    }
    Solution sol;
    int result = sol.maxEvents(events);
    cout << result;
}
# 最多可以参加的会议数目

## 问题

给你一个数组`events`，其中`events[i] = [startDayi, endDayi]`，表示会议`i`开始于 `startDayi`，结束于`endDayi`。
你可以在满足`startDayi <= d <= endDayi`中的任意一天`d`参加会议`i`。在任意一天`d`中只能参加一场会议。
请你返回你可以参加的**最大**会议数目。

## 解题思路

本题采用了**贪心算法**的思想。
整体的思路是：先得到所有会议的**最后日期**`maxDay`，然后遍历一遍`maxDay`之前的每一个日期，在该日期的会议中挑选其中...

## 代码

``` C++
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
```

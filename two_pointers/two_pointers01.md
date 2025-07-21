# 删除字符使字符串变好

## 问题

一个字符串如果没有**三个连续**相同字符，那么它就是一个**好字符串**。
给你一个字符串`s`，请你从`s`删除**最少**的字符，使它变成一个**好字符串**。
请你返回删除后的字符串。题目数据保证答案总是**唯一的**。

## 解题思路

此处很显然可以采用**双指针法**， 使用`left`和`right`分别遍历`s`，并用`count`记录`right`和`left`之间相同的连续字符个数，若大于等于3则只将其中一部分添加到`result`中。

## 代码

``` C++
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
```

其中使用到了[字符串string](https://blog.csdn.net/qq_37941471/article/details/82107077)和[其中append](https://blog.csdn.net/liuweiyuxiang/article/details/83687452)的相关用法。

## 复杂度分析

- **时间复杂度**：`O(l)`，`l`表示字符串`s`的长度。
- **空间复杂度**：`O(l)`。

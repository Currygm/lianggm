# 最大数

> 本题来自[力扣官网](https://leetcode.cn/problems/largest-number/description/?envType=problem-list-v2&envId=greedy)。

## 问题

给定一组**非负整数**`nums`，重新排列每个数的顺序（每个数*不可拆分*）使之组成一个**最大**的整数。
注意：输出结果可能非常大，所以你需要返回一个**字符串**而不是整数。

## 解题思想

- 本题应用了**贪心算法**
  
> **贪心算法**本质上是将在寻求全局最优解时，每一步都选取当前状态下的最佳解（**局部最优解**），且要保证当前的选择不会影响后续的选择，即通过局部最优解求得全局最优解。更具体的解释可参考[洛谷作者U•ェ•*U的文章](https://www.luogu.com/article/ypgck6qv)。

- 要想得到一个最大的整数，则应该尽可能让**更高位**的数字更大。例如`442`和`109`的组合可以得到`442109`和`109442`，显然当最高位为`4`时得到的整数是最大的，即`442109`。因此我们思路就是在选择数字时尽可能让**高位**的数字**更大**。思路是显而易见的，但应该如何用计算机的语言表示出来呢。
- 有一种很直观的思路：先对已给的数组进行**排序**，但不是一般的排序，而是将**最高位最大**的数字排在前面。如果直接对`int`类型的数据进行排序会出现很多问题，例如`33`和`330`要如何处理？我们观察可知`33330`是最大的，但在计算机语言中要说明这个事情并不容易，读者可以自行尝试。
- 我们发现，对两个**相同长度**的`int`类型数字比较，其实就是在比较他们的**字典序**。为了方便计算机处理，我们可以将所有的`int`类型转换成`string`类型。
  
```C++
void int_to_string(int b){
    string a;
    if(b == 0){  //特殊处理整数为0的情况
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
```

- 接着用`<algorithm>`中的`sort`函数排序。根据**贪心算法**的思想，我们在排序过程中每次都选择能使得**当前整数最大**的方法。具体操作为在将两个数组合时，先得到二者组合的两种情况，通过`string`类型的比较判断哪种组合更大。

```C++
bool cmp(const string& a, const string& b){
    string s1 = a + b, s2 = b + a;
    return s1 > s2;
}
```

> C++中的`sort(start, end, cmp)`函数可以使我们的排序更加便捷，其中`start`表示容器第一个元素的**指针**或**迭代器**,`end`表示容器最后一个元素的下一位置的**指针**或**迭代器**，`cmp`表示自定义的排序规则，可以是**比较函数**或**正则表达式**。更加详细的介绍可以查看[C语言中文网](https://c.biancheng.net/view/7457.html)

- 根据上述思想，每次调用**比较函数**得到两个数的**最大组合**其实都是在求取**局部最优解**，将整个容器的元素全部完成排序后即可得到**全局最优解**，即**最大整数**。

## 代码

```C++
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
        if(hash[0] == a){        //这里是特殊处理vector中只有0的情况
            result += '0';
            return result;
        }
        for(int i = 0;i < n;i++){
            result += hash[i];
        }
        return result;
    }
};
```

更简洁的版本,两种方法在本质上都是一样的，下面的代码应用了更多`C++STL`中的函数，使得代码更加简洁，且运行速度更快。

```C++
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string res="";
        vector<string> num;
        for(int e:nums){
            string t=to_string(e);
            num.push_back(t);
        }
        auto cmp=[](string s, string t){
            return s+t>t+s;
        };
        sort(num.begin(), num.end(), cmp);
        for(string t: num){
            res=res+t;
        }
        
        if(res[0]=='0') return "0";
        else return res;
    }
    
};
```

## 复杂度分析

>以下只分析第一个版本。

- **时间复杂度**：`O(nlog nlog m)`，`m`表示容器中最大的数，转换成字符串的长度数量级与`log m`相同，`n`表示容器的大小，每次**比较函数**的时间复杂度为`O(log m)`，用`sort`对`n`个排序，需要调用`nlog n`次**比较函数**，即总的时间复杂度为`O(nlog nlog m)`。
- **空间复杂度**：`O(n)`， 即`hash`中的元素个数。
  
// https://leetcode.com/problems/array-partition-i/
// using hashmap to replace sort for increased efficiency

#include <algorithm>
#include <string>
#include <sstream>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <math.h>
#include <stdlib.h>

#define ff first
#define ss second
 
using namespace std; 

// int arrayPairSum(vector<int>& nums)
// {
//     int sum = 0;
//     sort(nums.begin(), nums.end());
//     for(int i = 0; i < nums.size(); i += 2) sum += nums[i];
//     return sum;
// }

int arrayPairSum(vector<int>& nums)
{
    vector<int> t(20001);
    for(int& i : nums)
        t[i + 10000]++;
    int ans = 0;
    bool even = true;
    for(int i = 0, count = 0; count < nums.size(); i++)
    {
        while(t[i]--)
        {
            if(even) ans += i - 10000;
            even = !even;
            count++;
        }
    }
    return ans;
}

int main()
{
	// freopen("input","r",stdin);
    // freopen("output.txt","w",stdout);

    vector<vector<int>> m = {{1, 4, 3, 2}};
    vector<int> res = arrayPairSum(m);
    // for(int i = 0; i < res.size(); i++) cout<<res[i]<<" ";


	return 0;
}































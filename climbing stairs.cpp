// https://leetcode.com/problems/climbing-stairs/
// finding nth fibonacci number in log(n)

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

// int climbStairs(int n)
// {
//     if(n == 1) return 1;
//     if(n == 2) return 2;
//     int dp1 = 2, dp2 = 1, ans = 0;
//     for(int i = 2; i < n; i++)
//     {
//         ans = dp1 + dp2;
//         dp2 = dp1;
//         dp1 = ans;
//     }
//     return ans;
// }

int climbStairs(int n)
    {
        vector<vector<int> > f = {{1, 1}, {1, 0}};
        return exp(f, n)[0][0];
    }
    vector<vector<int> > exp(vector<vector<int> > &f, int n)
    {
        vector<vector<int> > a = {{1, 0}, {0, 1}};
        while(n)
        {
            if(n % 2 == 1)
                a = prod(a, f);
            n /= 2;
            f = prod(f, f);
        }
        return a;
    }
    vector<vector<int> > prod(vector<vector<int> > &a, vector<vector<int> > &b)
    {
        vector<vector<int> > c;
        for(int i = 0; i < a.size(); i++)
        {
            vector<int> row;
            for(int j = 0; j < a[0].size(); j++)
            {
                int k = 0;
                for(int l = 0; l < a.size(); l++)
                    k += a[i][l] * b[l][j];
                row.push_back(k);
            }
            c.push_back(row);
        }
        return c;
    }

int main()
{
	// freopen("input","r",stdin);
    // freopen("output.txt","w",stdout);

    vector<int> res = climbStairs(50);
    // for(int i = 0; i < res.size(); i++) cout<<res[i]<<" ";


	return 0;
}































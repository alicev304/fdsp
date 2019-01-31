// https://www.codechef.com/problems/FIBQ
// implementation of segment tree for ranged query, interesting math

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
#define MOD 1000000007
 
using namespace std; 

vector<long long> a(100005);
vector<long long> Fibonacci(1000005);

void matmul(vector<vector<long long>>& m1, vector<vector<long long>> m2)
{
	long long m00 = ((m1[0][0] * m2[0][0]) % MOD + (m1[0][1] * m2[1][0]) % MOD) % MOD;
	long long m01 = ((m1[0][0] * m2[0][1]) % MOD + (m1[0][1] * m2[1][1]) % MOD) % MOD;
	long long m10 = ((m1[1][0] * m2[0][0]) % MOD + (m1[1][1] * m2[1][0]) % MOD) % MOD;
	long long m11 = ((m1[1][0] * m2[0][1]) % MOD + (m1[1][1] * m2[1][1]) % MOD) % MOD;
	m1[0][0] = m00;
	m1[0][1] = m01;
	m1[1][0] = m10;
	m1[1][1] = m11;
	return;
}

void power(vector<vector<long long>>& matrix, long long n)
{
	if(n < 2) return;
	vector<vector<long long>> fib = {{1, 1}, {1, 0}};
	power(matrix, n / 2);
	matmul(matrix, matrix);
	if(n % 2 == 1) matmul(matrix, fib);
	if(n < 1000005) Fibonacci[n] = matrix[1][0] % MOD;
	return;
}

long long fibonacci(long long n)
{
	vector<vector<long long>> fib = {{1, 1}, {1, 0}};
	if(n == 0) return 0;
	if(n < 1000004 && Fibonacci[n] != 0) return Fibonacci[n];
	power(fib, n - 1);
	return fib[0][0];
}

struct node
{
	long long x;
	long long y;
};
node zero;
vector<node> st(400025);

node tree_merge(node n1, node n2)
{
	node res;
	if(n2.x == -1) return n1;
	if(n1.x == -1) return n2;
	res.y = ((n1.x * n2.x) % MOD + (n1.y * n2.y) % MOD + (n1.y + n2.y) % MOD) % MOD;
	res.x = ((n1.x + n2.x) % MOD + (n1.x * n2.x) % MOD + (n1.x * n2.y) % MOD + (n1.y * n2.x) % MOD) % MOD;
	return res;
}

void tree_build(int l, int r, int i)
{
	if(l == r)
	{
		if(a[l] == 1) st[i].y = 0;
		else st[i].y = fibonacci(a[l] - 1);
		st[i].x = fibonacci(a[l]);
	}
	else
	{
		int mid = l + (r - l) / 2;
		tree_build(l, mid, 2 * i + 1);
		tree_build(mid + 1, r, 2 * i + 2);
		st[i] = tree_merge(st[2 * i + 1], st[2 * i + 2]);
	}
	return;
}

node query_q(int lo, int hi, int l, int r, int i)
{
	if(lo > r || hi < l) return zero;
	if(lo >= l && hi <= r) return st[i];
	int mid = lo + (hi - lo) / 2;
	return tree_merge(query_q(lo, mid, l, r, 2 * i + 1), query_q(mid + 1, hi, l, r, 2 * i + 2));
}

void query_c(int lo, int hi, int l, int r, int i)
{
	if(lo > l || hi < l) return;
	if(lo == hi)
	{
		if(r == 1) st[i].y = 0;
		else st[i].y = fibonacci(r - 1);
		st[i].x = fibonacci(r);
		a[l] = r % MOD;
		return;
	}
	int mid = lo + (hi - lo) / 2;
	query_c(lo, mid, l, r, 2 * i + 1);
	query_c(mid + 1, hi, l, r, 2 * i + 2);
	st[i].y = ((st[2 * i + 1].x * st[2 * i + 2].x) % MOD + (st[2 * i + 1].y * st[2 * i + 2].y) % MOD + 
		(st[2 * i + 1].y + st[2 * i + 2].y) % MOD) % MOD;
	st[i].x = ((st[2 * i + 1].x + st[2 * i + 2].x) % MOD + (st[2 * i + 1].x * st[2 * i + 2].x) % MOD + 
		(st[2 * i + 1].x * st[2 * i + 2].y) % MOD + (st[2 * i + 1].y * st[2 * i + 2].x) % MOD) % MOD;
	return;
}

int main()
{
	// freopen("input","r",stdin);
    // freopen("output.txt","w",stdout);

	zero.x = -1;
	zero.y = -1;

    int n, m;
    cin >> n >> m;

    Fibonacci[1] = 1;
    for(int i = 2; i < 1000005; i++) Fibonacci[i] = (Fibonacci[i - 1] + Fibonacci[i - 2]) % MOD;

    for(int i = 0; i < n; i++) cin >> a[i];

    tree_build(0, n - 1, 0);

    char query;
    long long l, r, x, y;
    while(m--)
    {
    	cin >> query;
    	if(query == 'Q')
    	{
    		cin >> l >> r;
    		cout << query_q(0, n - 1, l - 1, r - 1, 0).x << endl;
    	}
    	else
    	{
    		cin >> x >> y;
    		query_c(0, n - 1, x - 1, y, 0);
    	}
    }    

	return 0;
}






























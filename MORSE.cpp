/* 
   MORSE
   compute the kth dictionary order string with m number of 'o' and n '-'.
   first pre-calculate binomial expressions to speed up binomal calc.
   input limited with n <= 100, m<= 100, k <= 1000000000
 */


#include <iostream>

using namespace std;

const int MAX_NUM = 200;
const int LIMIT = 1000000001;

long long bino[MAX_NUM + 1][MAX_NUM + 1];
int n, m, k, C;

void precompute()
{
	bino[0][0] = 1;
	for (int i = 1; i <= MAX_NUM; ++i)
	{
		bino[i][0] = 1;
		for (int j = 1; j <= i/2; ++j)
		{
			bino[i][j] = bino[i][j-1] * (i-j+1) / (j);
			if (bino[i][j] >= LIMIT)
				bino[i][j] = LIMIT;
		}
		for (int j = i/2 + 1; j <= i; ++j)
		{
			bino[i][j] = bino[i][i - j];
		}
	}
}

int main()
{
	precompute();
	
	cin >> C;

	while (C--)
	{
		cin >> n >> m >> k;
		
		string res;
		
		if (n == 0)
		{
			// invalid input check
			if (k > 1)
				continue;
				
			while (m--)
			{
				res.push_back('o');
			}
		}
		
		while (n > 0)
		{
			if (bino[n+m-1][n-1] >= k)
			{
				res.push_back('-');
				--n;
				if (bino[n+m][n] == k)
				{
					while (m--)
					{
						res.push_back('o');
					}
					while (n--)
					{
						res.push_back('-');
					}
					break;
				}
			}
			else
			{
				res.push_back('o');
				k -= bino[n+m-1][n-1];
				--m;
			}
		}
		
		cout << res.c_str() << endl;
	}
	
	return 0;
}

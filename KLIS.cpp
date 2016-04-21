/*입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 가 주어진다. 각 테스트 케이스의 첫 줄에는 수열에 포함된 원소의 수 N (<= 500) 과 K 가 주어진다. K 는 32비트 부호 있는 정수에 저장할 수 있다. 그 다음 줄에 N개의 정수로 수열이 주어진다. 각 정수는 1 이상 100,000 이하이며, 같은 수는 두 번 등장하지 않는다.
주어진 수열의 LIS 는 최소 K 개 있다고 가정해도 좋다.

출력
각 테스트케이스마다 두 줄을 출력한다. 첫 줄에는 LIS 의 길이 L 을 출력하고, 그 다음 줄에 L 개의 정수로 K번째 LIS 를 출력한다.*/
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_ARRAY = 500;
const int MAX_K = (0x7fffffff) * 10;

int C, n, k;
int arrays[MAX_ARRAY];
int cache[MAX_ARRAY+1];
long long counts[MAX_ARRAY+1];

// return possible LIS after selecting selected
int compute(int selected, long long &selectedCnt)
{
	int &ret = cache[selected+1];
	long long &cnt = counts[selected+1];
	selectedCnt = cnt;
	if (ret != -1)
		return ret;
	
	ret = 0;
	cnt = 1;
	int me = (selected == -1) ? -1 : arrays[selected];
	
	for (int i = selected+1; i < n; ++i)
	{
		if (me < arrays[i])
		{
			long long iCnt;
			int temp = 1 + compute(i, iCnt);
			if (ret < temp)
			{
				ret = temp;
				cnt = iCnt;
			}
			else if (ret == temp)
			{
				cnt += iCnt;
			}
		}
	}
	
	if (cnt > MAX_K)
		cnt = (long long)MAX_K + 1;
		
	selectedCnt = cnt;
	return ret;
}

int main()
{
	std::cin >> C;
	
	while (C--)
	{
		std::cin >> n >> k;
		memset(cache, -1, sizeof(int)*MAX_ARRAY+1);
		memset(counts, -1, sizeof(int)*MAX_ARRAY+1);
		memset(arrays, 0, sizeof(int)*MAX_ARRAY);
		
		for (int i = 0; i < n; ++i)
			std::cin >> arrays[i];
		
		long long cc;
		int L = compute(-1, cc);
		std::cout << L << std::endl;
		
		//for (int i = 0; i < n+1; ++i)
		//	std::cout << i << "with" << arrays[i] << ":" << cache[i] << ": " << counts[i] << std::endl;
		
		// 3 2 1 6 5 4 9 8 7
		std::vector<int> res;
		int index = -1;
		int lastChoosed = -1;
		while (L--)
		{
			vector< pair< int, int > > pairs;
			
			for (int i = index+1; i < n; ++i)
			{
				int nextLen = cache[i+1];
				if (nextLen == L) // ok
				{
					pairs.push_back(make_pair(i, arrays[i]));
					//cout << i << "selected" << endl;
				}
			}
			
			sort(pairs.begin(), pairs.end(), [](const pair<int, int>& left, const pair<int, int>& right) {
				return left.second < right.second;
			});
			
			for (auto it = pairs.begin(); it != pairs.end(); ++it)
			{
				if (lastChoosed > it->second)
					continue;
					
				//cout << "sorted:" << it->first << endl; 
				long long cnt = counts[it->first + 1];
				if (cnt < k)
				{
					k -= cnt;
					//cout << "skipped" << endl;
				}
				else
				{
					//cout << "choose" << endl;
					res.push_back(it->second);
					index = it->first;
					lastChoosed = it->second;
					break;
				}
			}
		}
		
		for (auto number : res)
		{
			std::cout << number << " ";
		}
		std::cout << std::endl;
	}
	
	return 0;
}

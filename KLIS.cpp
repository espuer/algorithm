/*입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 가 주어진다. 각 테스트 케이스의 첫 줄에는 수열에 포함된 원소의 수 N (<= 500) 과 K 가 주어진다. K 는 32비트 부호 있는 정>수에 저장할 수 있다. 그 다음 줄에 N개의 정수로 수열이 주어진다. 각 정수는 1 이상 100,000 이하이며, 같은 수는 두 번 등장하지 않는다.
주어진 수열의 LIS 는 최소 K 개 있다고 가정해도 좋다.

출력
각 테스트케이스마다 두 줄을 출력한다. 첫 줄에는 LIS 의 길이 L 을 출력하고, 그 다음 줄에 L 개의 정수로 K번째 LIS 를 출력한다.*/
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_ARRAY = 500;
const long long MAX_K = (long long)(0x7fffffff) * 10;

int C, n, k;
int arrays[MAX_ARRAY];
int cache[MAX_ARRAY+1];
long long counts[MAX_ARRAY+1];
std::vector< std::vector< std::pair< int, int > > > choices;

void reconstruct(int index, std::vector<int>& res, int k)
{
	for (auto& p : choices[index+1])
	{
		int cnt = counts[p.first+1];
		if (cnt > k)
		{
			res.push_back(p.second);
			reconstruct(p.first, res, k);
			break;
		}
		else
		{
			k -= cnt;
		}
	}	
}

// return possible LIS after selecting selected
int compute(int selected)
{
    int &ret = cache[selected+1];
    long long &cnt = counts[selected+1];
    if (ret != -1)
        return ret;

    ret = 0;
    cnt = 1;
    int me = (selected == -1) ? -1 : arrays[selected];

    for (int i = selected+1; i < n; ++i)
    {
        if (me < arrays[i])
        {
            int temp = 1 + compute(i);
            if (ret < temp)
            {
                ret = temp;
                cnt = counts[i+1];
                choices[selected+1].clear();
                choices[selected+1].push_back(std::make_pair(i, arrays[i]));
            }
            else if (ret == temp)
            {
                cnt += counts[i+1];
                choices[selected+1].push_back(std::make_pair(i, arrays[i]));
            }
        }
    }
        
    if (cnt > MAX_K)
        cnt = (long long)MAX_K + 1;
        
    sort(choices[selected+1].begin(), choices[selected+1].end(), [](const pair<int, int>& left, const pair<int, int>& right) {
		return left.second < right.second;
	});

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
        choices.clear();
        choices.resize(n+1, std::vector< std::pair< int, int > >());

        for (int i = 0; i < n; ++i)
            std::cin >> arrays[i];

        int L = compute(-1);
        std::cout << L << std::endl;

        //for (int i = 0; i < n+1; ++i)
        //    std::cout << i << "with" << arrays[i] << ":" << cache[i] << ": " << counts[i] << std::endl;
        // 3 2 1 6 5 4 9 8 7
        std::vector<int> res;
        reconstruct(-1, res, k);
        

        for (auto number : res)
        {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}


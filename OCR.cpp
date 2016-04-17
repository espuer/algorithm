/*  
	OCR (Optical Character Recognition) problem.
	typically modeled with hidden Markov Model.
	trying to solve the problem using similar way of Viterbi algorithm.

	TODO: make code working for DP
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int MAX_WORD = 500;
const int MAX_WORD_LENGTH = 10;
const int MAX_SENTENCE_LENGTH = 100;

int m, q;
char word[MAX_WORD][MAX_WORD_LENGTH+1];
double T[MAX_WORD+1][MAX_WORD]; // prob appearnce of j after i
double M[MAX_WORD][MAX_WORD]; // prob define i to j through OCR
int R[MAX_SENTENCE_LENGTH];
int result[MAX_SENTENCE_LENGTH+1];
double cache[MAX_WORD][MAX_WORD];
int choice[MAX_SENTENCE_LENGTH];

int n;
int find(int index)
{
	if (index == 0)
		return -1;
	
	
}

double getProb(int previous, int r, int& resultIndex)
{
	double &ret = cache[previous][r];
	if (ret != 1)
		return ret;
	
	double maxVal = -1e200;
	int choice = -1;
	for (int thisMatch = 0; thisMatch < m; ++i)
	{
		double res = T[previous][thisMatch] + M[thisMatch][r];
		if (res > maxVal)
		{
			choice = thisMatch;
			maxVal = res;
		}
	}
	
	resultIndex = choice;
	return ret = maxVal;
}

int findWord(string word)
{
	for (int i = 0; i < m; ++i)
		if (word.compare(char[i]) == 0)
			return i;
	
	return -1;
}

// make sure to use T[i+1][j] when from i to j
int main()
{
	cin >> m >> q;
	
	for (int i = 0; i < m; ++i)
		cin >> word[i];
	
	for (int i = 0; i < m; ++i)
		cin >> M[0][i];
	
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			cin >> T[i+1][j];
	
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			cin >> M[i][j];
	
	for (int k = 0; k < q; ++k)
	{
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			char temp[MAX_WORD_LENGTH+1];
			cin >> temp;
			R[i] = findWord(string(temp));
		}
		
		for (int i = 0; i < m; ++i)
			result[0] = max(T[0][i]);
			
		for (int i = 1; i < n; ++i)
		{
			double res = 0;
			int resultIndex = -1;
			for (int j = 0; j < m; ++j)
			{
				double tempRes = tryFind(result[i-1], j, R[i]);
				if (res < tempRes)
				{
					res = tempRes;
					resultIndex = j;
				}
			}
			
			result[i] = resultIndex;
		}
	}
	
	return 0;
}

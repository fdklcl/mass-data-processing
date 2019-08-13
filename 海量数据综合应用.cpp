#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <time.h>
#include <algorithm>
#include <functional>
using namespace std;

/*有一个大文件,找出其重复次数最多的前十个数字,并输出其重复的次数*/
int main()
{
	srand((unsigned int)time(NULL));
	FILE* fw = fopen("datax.txt", "wb");
	if (NULL == fw)
	{
		perror("file open fail !");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 200000; ++i)
	{
		int data = rand();
		fwrite(&data, sizeof(int), 1, fw);
	}
	fclose(fw);

	FILE* fr = fopen("datax.txt", "rb");
	if (NULL == fr)
	{
		perror("file open fail !");
		exit(EXIT_FAILURE);
	}

	const int fileSize = 11;
	FILE* pFile[fileSize] = { nullptr };
	for (int i = 0; i < fileSize; ++i)
	{
		char fileName[20];
		sprintf(fileName, "datax%d.txt", i + 1);
		pFile[i] = fopen(fileName, "wb+");
		if (NULL == pFile[i])
		{
			perror("file open fail !");
			exit(EXIT_FAILURE);
		}
	}

	int data = 0;
	int fileIndex = 0;
	while (fread(&data, sizeof(int), 1, fr) > 0)
	{
		fileIndex = data % fileSize;
		fwrite(&data, sizeof(int), 1, pFile[fileIndex]);
	}
	
	unordered_map<int, int> map;
	
	using p = pair<int, int>;
	using FUNC = function<bool(p&, p&)>;
	priority_queue<p, vector<p>, FUNC> minheap([](auto& a, auto& b)->bool 
	{
		return a.second > b.second;
	});
	
	for (int i = 0; i < fileSize; ++i)
	{
		
		fseek(pFile[i], 0, SEEK_SET);

		while (fread(&data, sizeof(int), 1, pFile[i]) > 0)
		{
			map[data]++;
		}

		int k = 0;
		auto it = map.begin();

		if (minheap.empty())
		{
			for (; it != map.end() && k < 10; ++k ,++it)
			{
				minheap.push(*it);
			}
		}

		for(;it != map.end();++it)
		{
			if (it->second > minheap.top().second)
			{
				minheap.pop();
				minheap.push(*it);
			}
		}

		map.clear();
	}

	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << "key:" << pair.first << "    " << "value:" << pair.second << endl;
		minheap.pop();
	}

	for (int i = 0; i < fileSize; ++i)
	{
		fclose(pFile[i]);
	}
	fclose(fr);
	return 0;
}

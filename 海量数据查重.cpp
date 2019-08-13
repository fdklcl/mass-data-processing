#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<time.h>
using namespace std;

/*找出1000000个数据中那些数据重复*/
#if 0
int main()
{
	srand((unsigned int)time(NULL));
	vector<int> vec;
	for (int i = 0; i < 100; ++i)
	{
		vec.push_back(i);
	}
	vec.push_back(3);
	unordered_set<int> set;
	for (int val : vec)
	{
		auto it = find(set.begin(), set.end(), val);
		if (it != set.end())
		{
			cout << "key:" << *it << endl;
		}
		else
		{
			set.insert(it, val);
		}
	}
	return 0;
}
#endif

/*找出1000000万个数据中那些数据重复，并输出其重复的次数*/
#if 0
int main()
{
	srand((unsigned int)time(NULL));
	vector<int> vec;
	for (int i = 0; i < 100; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	//统计次数
	unordered_map<int, int> map;
	for (int val : vec)
	{
		map[val]++;//其包含了三个操作
	}
	for_each(map.begin(), map.end(), [](pair<int, int> val)
	{
		cout << "key:" << val.first << " " << "value:" << val.second << endl;
	});
	/*
	for (pair<int, int> val : map)
	{
		if (val.second != 1)
		{
			cout << "key:" << val.first << " " << "value:" << val.second << endl;
		}
	}
	*/
	return 0;
}
#endif

/*有一个大文件,存储了50亿个整数,内存限制400M,找出那些数据是重复的,并输出其重复的次数*/
#if 0
int main()
{
	FILE* fw = fopen("data.txt", "wb");
	if (NULL == fw)
	{
		cerr << "open file fail !" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 20000; ++i)
	{
		int data = rand();
		fwrite(&data,sizeof(int),1,fw);
	}
	fclose(fw);
	FILE* fr = fopen("data.txt", "rb");
	if (NULL == fr)
	{
		cerr << "open file fail !" << endl;
		exit(EXIT_FAILURE);
	}

	const int fileSize = 11;
	FILE* pFile[fileSize] = { nullptr };
	for (int i = 0; i < fileSize; ++i)
	{
		char fileName[20];
		sprintf(fileName, "data%d.txt", i + 1);
		pFile[i] = fopen(fileName, "wb+");
	}

	int data = 0;
	int fileIndex = 0;
	while (fread(&data, sizeof(int), 1, fr) > 0)
	{
		fileIndex = data % fileSize;
		fwrite(&data, sizeof(int), 1, pFile[fileIndex]);
	}

	for (int i = 0; i < fileSize; ++i)
	{
		unordered_map<int, int> map;
		int data = 0;
		while (fread(&data, sizeof(int), 1, pFile[i]) > 0)
		{
			map[data]++;
		}
		for (pair<int, int> val : map)
		{
			if (val.second > 1)
			{
				cout << "key:" << val.first << " " << "value:" << val.second << endl;
			}
		}
	}
	
	for (int i = 0; i < fileSize; ++i)
	{
		fclose(pFile[i]);
	}
	fclose(fr);
	return 0;
}
#endif

/*有两个文件a和b,找出文件b中那些数据和文件a中的数据是重复的*/
#if 0
int main()
{
	//写入数据
	FILE* fw1 = fopen("dataa.txt", "wb");
	if (NULL == fw1)
	{
		cerr << "open file fail !" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 2000; ++i)
	{
		int data = rand();
		fwrite(&data, sizeof(int), 1, fw1);
	}
	fclose(fw1);

	FILE* fw2 = fopen("datab.txt", "wb");
	if (NULL == fw2)
	{
		cerr << "open file fail !" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 2000; ++i)
	{
		int data = rand();
		fwrite(&data, sizeof(int), 1, fw2);
	}
	fclose(fw2);
	//打开文件,准备读数据
	FILE* fr1 = fopen("dataa.txt", "rb");
	if (NULL == fr1)
	{
		cerr << "open file fail !" << endl;
		exit(EXIT_FAILURE);
	}
	FILE* fr2 = fopen("datab.txt", "rb");
	if (NULL == fr2)
	{
		cerr << "open file fail !" << endl;
		exit(EXIT_FAILURE);
	}

	unordered_set<int> set;
	int data = 0;
	while (fread(&data, sizeof(int), 1, fr1) > 0)
	{
		set.insert(data);
	}
	while (fread(&data, sizeof(int), 1, fr2) > 0)
	{
		auto it = find(set.begin(), set.end(), data);
		if (it != set.end())
		{
			cout << "key:" << *it << endl;
		}
	}
}
#endif
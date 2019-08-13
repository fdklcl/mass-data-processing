#include<iostream>
#include<vector>
#include<queue>
#include<assert.h>
#include<time.h>
#include<algorithm>
using namespace std;

/*有一组数据,求其中最大的前十个数据*/
#if 0
int main()
{
	srand((unsigned int)time(NULL));
	vector<int> vec;
	for (int i = 0; i < 200000; ++i)
	{
		vec.push_back(i);
	}

	priority_queue<int,vector<int>,greater<int>> queue;
	int k = 0;
	for (; k < 10; ++k)
	{
		queue.push(vec[k]);
	}
	for (; k < 200000; ++k)
	{
		if (vec[k] > queue.top())
		{
			queue.pop();
			queue.push(vec[k]);
		}
	}
	while (!queue.empty())
	{
		cout << queue.top() << " ";
		queue.pop();
	}
	cout << endl;
	return 0;
}
#endif
/*有一组数据,求其中最小的前十个数据*/
#if 0
int main()
{
	srand((unsigned int)time(NULL));
	vector<int> vec;
	for (int i = 0; i < 200000; ++i)
	{
		vec.push_back(i);
	}

	priority_queue<int> queue;    //默认为大根堆
	int k = 0;
	for (; k < 10; ++k)
	{
		queue.push(vec[k]);
	}
	for (; k < 200000; ++k)
	{
		if (vec[k] < queue.top())
		{
			queue.pop();
			queue.push(vec[k]);
		}
	}
	while (!queue.empty())
	{
		cout << queue.top() << " ";
		queue.pop();
	}
	cout << endl;
	return 0;
}
#endif

/*有一组数据,求其中第10小的数据*/
#if 0
int main()
{
	srand((unsigned int)time(NULL));
	vector<int> vec;
	for (int i = 0; i < 200000; ++i)
	{
		vec.push_back(i);
	}

	priority_queue<int> queue;    //默认为大根堆
	int k = 0;
	for (; k < 10; ++k)
	{
		queue.push(vec[k]);
	}
	for (; k < 200000; ++k)
	{
		if (vec[k] < queue.top())
		{
			queue.pop();
			queue.push(vec[k]);
		}
	}
	
	cout << queue.top();
	cout << endl;
	return 0;
}
#endif

/*有一个大文件,内存限制200M,找出文件中最大的前十个数字*/
#if 0
int main()
{
	srand((unsigned int)time(NULL));
	FILE* fw = fopen("datat.txt", "wb");
	if (NULL == fw)
	{
		perror("file open fail !");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 200000; ++i)
	{
		int data = rand() % 10000 + 1;
		fwrite(&data,sizeof(int),1,fw);
	}
	fclose(fw);

	FILE* fr = fopen("datat.txt","rb");
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
		sprintf(fileName, "datat%d.txt", i + 1);
		pFile[i] = fopen("fileName", "wb+");
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

	int k = 0;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	while (k < 10 && fread(&data, sizeof(int), 1, pFile[0]) > 0)
	{
		minHeap.push(data);
		k++;
	}
	for (int i = 0; i < fileSize; ++i)
	{
		while (fread(&data, sizeof(int), 1, pFile[i]) > 0)
		{
			if (data > minHeap.top())
			{
				minHeap.pop();
				minHeap.push(data);
			}
		}
	}

	while(!minHeap.empty())
	{
		cout << minHeap.top() << " ";
		minHeap.pop();
	}
	cout << endl;

	for (int i = 0; i < fileSize; ++i)
	{
		fclose(pFile[i]);
	}
	fclose(fr);
	return 0;
}
#endif
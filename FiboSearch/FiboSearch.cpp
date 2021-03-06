// FiboSearch.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#define	MAX	21

struct element {
	int key;
};
typedef struct element	record;
record data[MAX] = {
	2, 5, 7, 9, 17, 21, 25, 33, 46, 89, 100, 121, 127, 139, 237, 279, 302, 356,
	455, 467, 500
};

int F[50];  // fibonacci array

void FibonacciArray(int *a)
{
	int i;

	a[0] = 1;
	a[1] = 1;
	for (i = 2; i < 50; i++) {
		a[i] = a[i - 1] + a[i - 2];
	}
}

/**
 * 更为一般，易于理解的Fibonacci 查找算法
 * 参见 http://www.cnblogs.com/Allen-win/p/7364414.html
 */
int FibonacciSearch(int *a, int n, int key)
{
	int k = 0, i;
	int mid, low = 1, high = n;

	while (n > F[k] - 1) {
		k++;
	}

	for (i = n + 1; i <= F[k] - 1; i++) {
		a[i] = a[n];
	}

	while (low <= high) {
		mid = low + F[k - 1] - 1;
		if (a[mid] > key) {
			high = mid - 1;
			k = k - 1;
		}
		else if (a[mid] < key) {
			low = mid + 1;
			k = k - 2;
		}
		else {
			if (mid <= n) {
				return mid;
			}
			else if (mid > n) {
				return n; // 这些是由最后一个数据复制得到的填充数据
			}
		}
	}

	return 0; // NOT found.
}

/**
 * 上面算法的递归版本
 */
int FiboSearch(int *a, int k, int low, int high, int key)
{
	int mid = low + F[k - 1] - 1;
	if (a[mid] == key) {
		if (mid > MAX) {
			mid = MAX;
		}
		return mid;
	}

	if (low > high) {
		return 0;
	}

	if (a[mid] > key) {
		high = mid - 1;
		k = k - 1;
		return FiboSearch(a, k, low, high, key);
	}
	else {
		low = mid + 1;
		k = k - 2;
		return FiboSearch(a, k, low, high, key);
	}

	return 0; // NOT found.
}

/**
 * 计算Fibonacci 数
 * n 是索引
 * 比如给出n=3，返回2
 *     给出n=6, 返回8
 */
int fib(int n)
{
	if (n <= 1) {
		return n;
	}
	else {
		return fib(n - 2) + fib(n - 1);
	}
}

/**
 * 由n 反推其对应的最大Fibonacci 数的索引
 * 比如n=1, 返回3
 *     n=2, 返回4
 *     n=3, 返回4
 *     ...
 *     n=20,返回8
 *     n=21,返回8
 *     ...
 */
int fibindex(int n)
{
	int temp = 1;

	while (fib(temp) <= n + 1) {
		temp++;
	}

	return temp - 1;
}

/**
 * 此算法以Fibonacci 查找树为基础，
 * 与之后看到的其他讲解Fibonacci 查找算法不同
 * 此算法有bug,找不到500
 */
int fibsearch(int n, int key)
{
	int index;
	int mid;
	int fn1;
	int fn2;
	int temp;

	index = fibindex(n);
	mid = fib(index - 1);
	fn1 = fib(index - 2);
	fn2 = fib(index - 3);

	while (mid != 0) {
		if (key < data[mid - 1].key) {
			if (fn2 <= 0) {
				mid = 0;
			}
			else {
				mid = mid - fn2;
				temp = fn1;
				fn1 = fn2;
				fn2 = temp - fn2;
			}
		}
		else if (key > data[mid - 1].key) {
			if (fn1 <= 1) {
				mid = 0;
			}
			else {
				mid = mid + fn2;
				fn1 = fn1 - fn2;
				fn2 = fn2 - fn1;
			}
		}
		else {
			return mid - 1;
		}
	}

	return -1;
}

//int main()
//{
//	int found;
//	int value;
//
//	while (1) {
//		printf("\nplease input the value for search(0-500) ==> ");
//		scanf_s("%d", &value);
//		if (value != -1) {
//			found = fibsearch(MAX, value);
//			if (found != -1) {
//				printf("found the value:%d[%d]\n", value, found);
//			}
//			else {
//				printf("have NOT found value:%d\n", value);
//			}
//		}
//		else {
//			exit(1);
//		}
//	}
//}

//int main()
//{
//	int a[MAX + 1] = {
//		0, 2, 5, 7, 9, 17, 21, 25, 33, 46, 89, 100, 121, 127, 139, 237, 279, 302, 356,
//		455, 467, 500 };
//	int arr[100] = { 0 };
//	for (int i = 0; i < MAX + 1; i++ ) {
//		arr[i] = a[i];
//	}

//	FibonacciArray(F);

//	int result;
//	int key = 59;
//
//	while (1) {
//		printf("\nplease input the value for search ==> ");
//		scanf_s("%d", &key);
//		if (key != -1) {
//			result = FibonacciSearch(arr, MAX, key);
//			if (result != 0) {
//				printf("found the value, a[%d]==%d", result, key);
//			}
//			else {
//				printf("NOT found %d", key);
//			}
//		}
//		else {
//			exit(1);
//		}
//	}
//}

int main()
{
	int a[MAX + 1] = {
		0, 2, 5, 7, 9, 17, 21, 25, 33, 46, 89, 100, 121, 127, 139, 237, 279, 302, 356,
		455, 467, 500 };
	int arr[100] = { 0 };
	int i;
	for (i = 0; i < MAX + 1; i++) {
		arr[i] = a[i];
	}

	FibonacciArray(F);

	int result, k = 0;
	int key;
	int n = MAX;

	while (n > F[k] - 1) {
		k++;
	}

	for (i = n + 1; i <= F[k] - 1; i++) {
		arr[i] = arr[n];
	}

	while (1) {
		printf("\nplease input the value for search ==> ");
		scanf_s("%d", &key);
		if (key != -1) {
			
			result = FiboSearch(arr, k, 1, MAX, key);
			if (result != 0) {
				printf("found the value, a[%d]==%d", result, key);
			}
			else {
				printf("NOT found %d", key);
			}
		}
		else {
			exit(1);
		}
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

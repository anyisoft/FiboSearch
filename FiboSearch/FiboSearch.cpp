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

int main()
{
	int found;
	int value;

	while (1) {
		printf("\nplease input the value for search(0-500) ==> ");
		scanf_s("%d", &value);
		if (value != -1) {
			found = fibsearch(MAX, value);
			if (found != -1) {
				printf("found the value:%d[%d]\n", value, found);
			}
			else {
				printf("have NOT found value:%d\n", value);
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

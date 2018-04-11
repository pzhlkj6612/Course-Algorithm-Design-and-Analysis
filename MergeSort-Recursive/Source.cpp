#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO defaultOutInfo;

int stepNum = 0;
int length = 10;
int max_number_of_digits = 2;

template<class Type>
void Merge(Type arr[], int L, int M, int R) {

	//print status before each step
	{
		GetConsoleScreenBufferInfo(hOut, &defaultOutInfo);//Get current (default) color
		std::cout << stepNum++ << ":\t";
		for (int i = 0; i < length; i++) {
			SetConsoleTextAttribute(hOut, defaultOutInfo.wAttributes);//Reset color
			if (i >= L && i <= R) {
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);//Red text
				std::cout << arr[i] << "\t";
				continue;
			}
			std::cout << arr[i] << "\t";
		}
		SetConsoleTextAttribute(hOut, defaultOutInfo.wAttributes);//Reset color
		std::cout << std::endl;
	}

	int LEFT_SIZE = M - L + 1;
	int RIGHT_SIZE = R - (M + 1) + 1;//M + 1, do you know why I do it?
	int *left = new int[LEFT_SIZE];
	int *right = new int[RIGHT_SIZE];

	for (int i = L; i <= M; i++) {
		left[i - L] = arr[i];
	}
	for (int i = M + 1; i <= R; i++) {
		right[i - (M + 1)] = arr[i];
	}

	int i = 0, j = 0, k = L;

	while (i < LEFT_SIZE && j < RIGHT_SIZE) {
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	while (i < LEFT_SIZE) {
		arr[k++] = left[i++];
	}
	while (j < RIGHT_SIZE) {
		arr[k++] = right[j++];
	}

	//print status after each step
	{
		GetConsoleScreenBufferInfo(hOut, &defaultOutInfo);//Get current (default) color
		std::cout << " " << "\t";
		for (int i = 0; i < length; i++) {
			SetConsoleTextAttribute(hOut, defaultOutInfo.wAttributes);//Reset color
			if (i >= L && i <= R) {
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//Red text
				std::cout << arr[i] << "\t";
				continue;
			}
			std::cout << arr[i] << "\t";
		}
		SetConsoleTextAttribute(hOut, defaultOutInfo.wAttributes);//Reset color
		std::cout << std::endl;
	}

	system("pause>NUL");
}

template<class Type>
void MergeSort(Type arr[], int L, int R) {
	if (L == R)
		return;
	int M = (L + R) / 2;
	MergeSort(arr, L, M);
	MergeSort(arr, M + 1, R);
	Merge(arr, L, M, R);//
	/*
	Merge():

	M is the position of cutting point, but extra process is needed, for example:

	0,1,2,3,4,5,6,7,8	9 numbers, M = 1/2 * (0 + 8) = 4, Left = {0,1,2,3,4},	Right = {5,6,7,8}
	0,1,2,3,4,5,6,7		8 numbers, M = 1/2 * (0 + 7) = 3, Left = {0,1,2,3},		Right = {4,5,6,7}
	0,1,2,3,4,5,6		7 numbers, M = 1/2 * (0 + 6) = 3, Left = {0,1,2,3},		Right = {4,5,6}

	We can find that Right team's first index must equal to M + 1.
	And, the length of each team is (R - L + 1), so I will do "add 1" in Merge() necessarily.
	*/
}

int main(void) {
	srand((unsigned int)time(NULL));
	int *s = new int[length];

	int mod = 1, mod_basic = 10;
	while (0 != max_number_of_digits--) {
		mod *= mod_basic;
	}

	for (int i = 0; i < length; i++) {
		s[i] = rand()*rand()*rand() % mod;
	}

	{
		std::cout << "In:\t";
		for (int i = 0; i < length; i++) {
			std::cout << s[i] << "\t";
		}

		std::cout << std::endl;
		for (int i = 0; i < length; i++) {
			std::cout << "------";
		}
		std::cout << std::endl;
	}

	system("pause>NUL");

	MergeSort(s, 0, length - 1);

	{
		for (int i = 0; i < length; i++) {
			std::cout << "------";
		}
		std::cout << std::endl;

		std::cout << "Out:\t";
		for (int i = 0; i < length; i++) {
			std::cout << s[i] << "\t";
		}
		std::cout << std::endl;
	}

	system("pause >NUL");
}

#include <iostream>
#include <time.h>
#include <windows.h>


HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

int stepNum = 0;
int length = 8;

template<class Type>
void SplitAndSort(Type arr[], int L, int R) {

	//print status before each step
	{
		GetConsoleScreenBufferInfo(hOut, &csbi);//Get current (default) color
		std::cout << stepNum++ << ":\t";
		for (int i = 0; i < length; i++) {
			SetConsoleTextAttribute(hOut, csbi.wAttributes);//Reset color
			if (i >= L && i <= R) {
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);//Red text
				std::cout << arr[i] << "\t";
				continue;
			}
			std::cout << arr[i] << "\t";
		}
		SetConsoleTextAttribute(hOut, csbi.wAttributes);//Reset color
		std::cout << std::endl;
	}

	int M = (L + R) / 2;

	int LEFT_SIZE = M - L + 1;
	int RIGHT_SIZE = R - (M + 1) + 1;
	Type *left = new Type[LEFT_SIZE];
	Type *right = new Type[RIGHT_SIZE];

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
		GetConsoleScreenBufferInfo(hOut, &csbi);//Get current (default) color
		std::cout << " " << "\t";
		for (int i = 0; i < length; i++) {
			SetConsoleTextAttribute(hOut, csbi.wAttributes);//Reset color
			if (i >= L && i <= R) {
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//Red text
				std::cout << arr[i] << "\t";
				continue;
			}
			std::cout << arr[i] << "\t";
		}
		SetConsoleTextAttribute(hOut, csbi.wAttributes);//Reset color
		std::cout << std::endl;
	}

	system("pause>NUL");
}

template<class Type>
void MergeSort(Type arr[], int n) {
	Type *temp = new Type[n];

	int currentHead, currentFoot = 0;
	int processLength = 1;

	while (processLength <= n) {
		processLength *= 2;
		currentHead = 0;//Start from scratch

		while (currentHead < n) {
			currentFoot = currentHead + processLength - 1;
			SplitAndSort(arr, currentHead, currentFoot);
			currentHead = currentFoot + 1;
		}
	}
}

int main(void) {
	srand((unsigned int)time(NULL));
	int *arr = new int[length];

	for (int i = 0; i < length; i++) {
		arr[i] = rand()*rand()*rand() % 100;
	}

	{
		std::cout << "In:\t";
		for (int i = 0; i < length; i++) {
			std::cout << arr[i] << "\t";
		}

		std::cout << std::endl;
		for (int i = 0; i < length; i++) {
			std::cout << "------";
		}
		std::cout << std::endl;
	}

	system("pause>NUL");

	MergeSort(arr, length - 1);

	{
		for (int i = 0; i < length; i++) {
			std::cout << "------";
		}
		std::cout << std::endl;

		std::cout << "Out:\t";
		for (int i = 0; i < length; i++) {
			std::cout << arr[i] << "\t";
		}
		std::cout << std::endl;
	}

	system("pause >NUL");
}

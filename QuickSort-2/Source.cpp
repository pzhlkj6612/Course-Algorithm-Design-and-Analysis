#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;


void MoveCursorFromCurrentPosition(SHORT deltaX, SHORT deltaY) {
	GetConsoleScreenBufferInfo(hOut, &csbi);
	SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X + deltaX, csbi.dwCursorPosition.Y + deltaY });
}

//Unused
void ClearCurrentLineAfterContent() {
	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y };
	SHORT charCount = csbi.dwSize.X - csbi.dwCursorPosition.X - 1;
	while (charCount-- > 0) {
		std::cout << ' ';
	}
	SetConsoleCursorPosition(hOut, beginningPos);
}

void ClearAfterLines(SHORT lineCount) {
	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y };
	while (lineCount >= 0) {
		SetConsoleCursorPosition(hOut, { 0, csbi.dwCursorPosition.Y + lineCount });
		SHORT width = csbi.dwSize.X;
		while (width-- > 0) {
			std::cout << ' ';
		}
		lineCount--;
	}
	SetConsoleCursorPosition(hOut, beginningPos);
}


void OutSeparateLineInNextLine() {
	GetConsoleScreenBufferInfo(hOut, &csbi);
	SHORT width = csbi.dwSize.X;;
	while (width-- > 1) {
		std::cout << '_';
	}
	std::cout << std::endl << std::endl;
}

void OutStandHead() {
	std::cout << "\t";
}


int sortTime = 0;

template<class Type> void OutSortInfo(Type key) {
	sortTime++;
	OutStandHead();
	std::cout << "Key = " << key << "  -  " << "Sort func time: " << sortTime << std::endl;
	std::cout << std::endl;
}


int length = 8;

template<class Type> void OutArray(Type arr[]) {
	OutStandHead();
	for (int ii = 0; ii < length; ii++) {
		std::cout << arr[ii] << "\t";
	}
	std::cout << std::endl;
}
//Unused
template<class Type> void OutArrayWithKey(Type arr[], Type key) {
	std::cout << "<" << key << ">";
	OutArray();
}


void OutCopyOperation_GoBackToXZero(int dest, int src) {
	ClearAfterLines(2);

	OutStandHead();

	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };
	SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y + 2 });

	for (int ii = 0; ii < length; ii++) {

		GetConsoleScreenBufferInfo(hOut, &csbi);
		COORD tempPos = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };

		if (src == dest) {
			if (ii == src) {

				SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
				std::cout << "¡ý";
				SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
				std::cout << "¡ü";
			}
		}
		else {
			if (ii == src) {

				SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
				std::cout << "¡ý";
				if (src < dest) {
					SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
					std::cout << " \\___";
				}
				else if (src > dest) {
					SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X - 4  , csbi.dwCursorPosition.Y - 1 });
					std::cout << "____/";
				}
			}
			else if (ii == dest) {

				SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
				std::cout << "¡ü";
				if (src < dest) {
					SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X - 4 , csbi.dwCursorPosition.Y - 1 });
					std::cout << "____/";
				}
				else if (src > dest) {
					SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y - 1 });
					std::cout << " \\___";
				}
			}
			else {
				if ((src < ii && ii < dest) || (dest < ii && ii < src)) {
					SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X - 4 , csbi.dwCursorPosition.Y - 1 });
					std::cout << "________";

				}
			}
		}

		SetConsoleCursorPosition(hOut, tempPos);

		std::cout << "\t";
	}
	SetConsoleCursorPosition(hOut, beginningPos);
}

void OutLessThanKey_GoBackToXZero(int index, int limiter, bool yes) {
	ClearAfterLines(2);

	OutStandHead();

	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };
	SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y + 2 });

	for (int ii = 0; ii < length; ii++) {

		GetConsoleScreenBufferInfo(hOut, &csbi);

		if (ii == index) {
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
			std::cout << "|";
			if (yes) {
				SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
				std::cout << "< key ?";
			}
			else {
				SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
				if (ii == limiter) {
					std::cout << "| < key X";
				}
				else {
					std::cout << "< key X";
				}
			}
		}
		else if (ii == limiter) {
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
			std::cout << "|";
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
			std::cout << "|";
		}

		SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y });

		std::cout << "\t";
	}
	SetConsoleCursorPosition(hOut, beginningPos);
}

void OutMoreThanKey_GoBackToXZero(int index, int limiter, bool yes) {
	ClearAfterLines(2);

	OutStandHead();

	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };
	SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y + 2 });

	for (int ii = 0; ii < length; ii++) {

		GetConsoleScreenBufferInfo(hOut, &csbi);

		if (ii == index) {
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
			std::cout << "|";
			if (yes) {
				SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
				std::cout << "> key ?";
			}
			else {
				SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
				if (ii == limiter) {
					std::cout << "| > key X";
				}
				else {
					std::cout << "> key X";
				}
			}
		}
		else if (ii == limiter) {
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
			std::cout << "|";
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
			std::cout << "|";
		}

		SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y });

		std::cout << "\t";
	}
	SetConsoleCursorPosition(hOut, beginningPos);
}

void OutAssignKeyOperation_GoBackToXZero(int index) {
	ClearAfterLines(2);

	OutStandHead();

	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };
	SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y + 2 });

	for (int ii = 0; ii < length; ii++) {

		GetConsoleScreenBufferInfo(hOut, &csbi);

		if (ii == index) {
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
			std::cout << "¡ü";
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
			std::cout << "key";
		}

		SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y });

		std::cout << "\t";
	}
	SetConsoleCursorPosition(hOut, beginningPos);
}

void OutSelectKeyAndLimiterOperation_GoBackToXZero(int index, int limiter) {
	ClearAfterLines(2);

	OutStandHead();

	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };
	SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y + 2 });

	for (int ii = 0; ii < length; ii++) {

		GetConsoleScreenBufferInfo(hOut, &csbi);

		if (ii == index) {
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
			std::cout << "¡ý";
			SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 1 });
			std::cout << "key";
		}

		SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y });

		std::cout << "\t";
	}
	SetConsoleCursorPosition(hOut, beginningPos);
}


template<class Type> void QuickSort2(Type arr[], int L, int R) {
	//Ref: https://baike.baidu.com/item/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/369842?fromtitle=%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F#3_6

	if (L >= R)
		return;

	Type key = arr[L];
	int lp = L;
	int rp = R;

	//Out new sort func info, Prepare to move rp and Pause
	{
		OutSeparateLineInNextLine();
		OutSortInfo(key);
		OutArray(arr);//First print
		OutSelectKeyAndLimiterOperation_GoBackToXZero(L, R);
		system("pause >NUL");
	}

	while (lp < rp) {
		while (lp < rp && key <= arr[rp]) {
			//Out moving rp and Pause
			{
				OutMoreThanKey_GoBackToXZero(rp, lp, true);
				system("pause >NUL");
			}
			rp--;
		}

		//Out last rp and Pause
		{
			OutMoreThanKey_GoBackToXZero(rp, lp, false);
			system("pause >NUL");
		}

		//Out lp = rp and Pause
		{
			OutCopyOperation_GoBackToXZero(lp, rp);
			system("pause >NUL");
		}
		arr[lp] = arr[rp];

		//Prepare to move lp and Pause
		{
			MoveCursorFromCurrentPosition(0, 3);
			OutArray(arr);
		}

		while (lp < rp && arr[lp] <= key) {
			//Out moving lp and Pause
			{
				OutLessThanKey_GoBackToXZero(lp, rp, true);
				system("pause >NUL");
			}
			lp++;
		}

		//Out last lp and Pause
		{
			OutLessThanKey_GoBackToXZero(lp, rp, false);
			system("pause >NUL");
		}

		//Out rp = lp and Pause
		{
			OutCopyOperation_GoBackToXZero(rp, lp);
			system("pause >NUL");
		}
		arr[rp] = arr[lp];

		//Prepare to move rp and Pause
		{
			MoveCursorFromCurrentPosition(0, 3);
			OutArray(arr);
		}
	}

	//Out lp = key and Pause
	{
		OutAssignKeyOperation_GoBackToXZero(lp);
		system("pause >NUL");
	}
	arr[lp] = key;

	//Prepare to print next sort func 
	{
		MoveCursorFromCurrentPosition(0, 3);
	}

	QuickSort2(arr, L, lp - 1);
	QuickSort2(arr, lp + 1, R);
}


int main(void) {
	//int aaa[] = { 8,6,7,4,1,5,2,3 };
	int aaa[] = { 18,-6,-97,94,-1,65,-62,73 };

	length = sizeof(aaa) / sizeof(aaa[0]);

	//Out before sort and Pause
	{
		std::cout << "IN" << std::endl;
		OutArray(aaa);
		std::cout << std::endl;
		system("pause >NUL");
	}

	QuickSort2(aaa, 0, length - 1);

	//Out after sort
	{
		OutSeparateLineInNextLine();
		OutArray(aaa);
		std::cout << "END" << std::endl;
	}
		
	system("set /p =");//Press Enter key to exit
}
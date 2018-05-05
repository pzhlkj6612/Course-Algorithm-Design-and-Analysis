#include <iostream>
#include <windows.h>


HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;


void MoveCursorFromCurrentPosition(SHORT deltaX, SHORT deltaY) {
	GetConsoleScreenBufferInfo(hOut, &csbi);
	SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X + deltaX, csbi.dwCursorPosition.Y + deltaY });
}

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
	std::cout << std::endl;
}

void OutStandHead() {
	std::cout << "\t";
}


int length = 10;

void OutPlainArray_GoBackToXZero(int arr[]) {
	OutStandHead();

	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };

	for (int i = 0; i < length; i++) {
		std::cout << arr[i] << "\t";
	}
	SetConsoleCursorPosition(hOut, beginningPos);
}

void OutColorizedArrayItem_GoBackToXZero(int arr[], int index, int textColor) {
	OutStandHead();

	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };
	MoveCursorFromCurrentPosition(0, 2);

	int i = index;
	while (i-- > 0) {
		std::cout << "\t";
	}

	GetConsoleScreenBufferInfo(hOut, &csbi);
	SetConsoleCursorPosition(hOut, { csbi.dwCursorPosition.X , csbi.dwCursorPosition.Y - 2 });
	SetConsoleTextAttribute(hOut, textColor);
	std::cout << arr[index];
	SetConsoleTextAttribute(hOut, csbi.wAttributes);

	SetConsoleCursorPosition(hOut, beginningPos);
}

void OutRefArrow_GoBackToXZero(int index) {
	if (index >= length)
		return;

	OutStandHead();

	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };

	int i = index;
	while (i-- > 0) {
		std::cout << "\t";
	}

	std::cout << "¡ü";

	SetConsoleCursorPosition(hOut, beginningPos);
}

void OutColorizedArrayWithArrow_GoBackToXZero(int arr[], int index, int lengthArr[]) {
	GetConsoleScreenBufferInfo(hOut, &csbi);
	COORD beginningPos = { 0, csbi.dwCursorPosition.Y };

	ClearCurrentLineAfterContent();
	ClearAfterLines(2);

	OutPlainArray_GoBackToXZero(arr);

	//Green -- need fix...
	{
		int refIndex = index >= length ? length - 1 : index;

		for (int i = refIndex; i >= 1; i--) {

			if (i == 1) {
				if (lengthArr[0] + 1 == lengthArr[1]) {
					OutColorizedArrayItem_GoBackToXZero(arr, 0, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
			}
			else {
				for (int currentIndex = i; currentIndex >= 0; ) {
					if (lengthArr[currentIndex] > 1) {
						OutColorizedArrayItem_GoBackToXZero(arr, currentIndex, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

						int remainingCount = lengthArr[currentIndex] - 1;

						for (int k = remainingCount; k > 0; k--) {
							OutColorizedArrayItem_GoBackToXZero(arr, currentIndex - k, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						}

						currentIndex -= lengthArr[currentIndex];
					}
					else {
						currentIndex--;
					}
				}
			}
		}
	}

	//Red
	{
		if (index < length) {
			for (int i = index; i >= 0; i--) {
				int distanceFromIndex = index - i;
				if (distanceFromIndex <= lengthArr[index] - 1) {//In range
					for (int count = distanceFromIndex; count >= 0; count--) {
						OutColorizedArrayItem_GoBackToXZero(arr, index - count, FOREGROUND_RED | FOREGROUND_INTENSITY);
					}
				}
			}
		}
	}

	//Yellow
	{
		if (index < length) {
			OutColorizedArrayItem_GoBackToXZero(arr, index, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
	}

	MoveCursorFromCurrentPosition(0, 1);
	OutRefArrow_GoBackToXZero(index);
	SetConsoleCursorPosition(hOut, beginningPos);
}


int FLISDyna(int arr[]) {
	int *lengthArr = new int[length];
	for (int i = 0; i < length; i++) {
		lengthArr[i] = 1;
	}

	int counter = 1;
	for (int i = 1; i < length; i++) {
		if (arr[i - 1] + 1 == arr[i]) {
			lengthArr[i] += counter;
			counter++;
		}
		else {
			counter = 1;
		}
		//Out
		{
			OutColorizedArrayWithArrow_GoBackToXZero(arr, i, lengthArr);
			system("pause>NUL");
		}
	}

	//Out
	{
		OutColorizedArrayWithArrow_GoBackToXZero(arr, length, lengthArr);
	}

	int longestLength = 1;
	for (int i = 0; i < length; i++) {
		if (lengthArr[i] > longestLength) {
			longestLength = lengthArr[i];
		}
	}

	return longestLength;
}
int main(void) {
	int *arr = new int[length] { 0, 1, 2, 3, 4, 3, 2, 4, 1, 2, 3, 4 };
	MoveCursorFromCurrentPosition(0, 1);
	std::cout << "\tFind the longest increasing substring:" << std::endl;
	OutSeparateLineInNextLine();
	int result = FLISDyna(arr);
	MoveCursorFromCurrentPosition(0, 2);
	std::cout << "\tThe length of the longest increasing substring = " << result << std::endl;
	system("pause>NUL");
}

/* Python 2

Hightlighted:
http://pygments.org/demo/6738649/

Run online:
https://repl.it/repls/UnfortunateEnormousExecutables <- is permanent?

def Find(arr):
	counter = 1
	recordArr = [1] * len(arr)
	for i in range(len(arr) - 1):
		if arr[i] + 1 == arr[i + 1]:
			recordArr[i] += counter
			counter += 1
		else:
			counter = 1
			longest = 1
	for record in recordArr:
		if record > longest:
			longest = record
	return longest

arr = [4, 1, 2, 3, 4, 3, 2, 4, 1, 2, 3, 4]
print Find(arr)

*/
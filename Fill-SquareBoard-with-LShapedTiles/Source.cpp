#include <iostream>
#include <windows.h>


int tileNum = 0;
int Board[64][64];
int size = sizeof(Board) / sizeof(Board[0]);

void ChessBoard(int row, int column, int Srow, int Scolumn, int size) {
	if (size == 1)return;

	int currentTile = ++tileNum;//(Number of sign) add one
	size /= 2;//Separate chessboard

	//Left+Top
	if (Srow < row + size && Scolumn < column + size) {
		//Existed
		ChessBoard(row, column, Srow, Scolumn, size);
	}
	else {
		//Not existed
		Board[row + size - 1][column + size - 1] = currentTile;//Sign at corner
		ChessBoard(row, column, row + size - 1, column + size - 1, size);
	}

	//Left+Bottom
	if (Srow >= row + size && Scolumn < column + size) {
		//Existed
		ChessBoard(row + size, column, Srow, Scolumn, size);
	}
	else {
		//Not existed
		Board[row + size][column + size - 1] = currentTile;//Sign at corner
		ChessBoard(row + size, column, row + size, column + size - 1, size);
	}

	//Right+Top
	if (Srow < row + size && Scolumn >= column + size) {
		//Existed
		ChessBoard(row, column + size, Srow, Scolumn, size);
	}
	else {
		//Not existed
		Board[row + size - 1][column + size] = currentTile;//Sign at corner
		ChessBoard(row, column + size, row + size - 1, column + size, size);
	}

	//Right_Bottom
	if (Srow >= row + size && Scolumn >= column + size) {
		//Existed
		ChessBoard(row + size, column + size, Srow, Scolumn, size);
	}
	else {
		//Not existed
		Board[row + size][column + size] = currentTile;//Sign at corner
		ChessBoard(row + size, column + size, row + size, column + size, size);
	}
}

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO defaultOutInfo;

void OutColorfulBlock(int num) {
	GetConsoleScreenBufferInfo(hOut, &defaultOutInfo);
	if (num == 0) {
		std::cout << "  ";
	}
	else {
		switch (num % 14) {//num % size
		case(0): {SetConsoleTextAttribute(hOut, BACKGROUND_RED); break; }
		case(1): {SetConsoleTextAttribute(hOut, BACKGROUND_GREEN); break; }
		case(2): {SetConsoleTextAttribute(hOut, BACKGROUND_BLUE); break; }
		case(3): {SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_INTENSITY); break; }
		case(4): {SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_INTENSITY); break; }
		case(5): {SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_INTENSITY); break; }
		case(6): {SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN); break; }
		case(7): {SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE); break; }
		case(8): {SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE); break; }
		case(9): {SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY); break; }
		case(10): {SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY); break; }
		case(11): {SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); break; }
		case(12): {SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE); break; }
		case(13): {SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); break; }
		}//I don't have enough color :(
		std::cout << "  ";
		SetConsoleTextAttribute(hOut, defaultOutInfo.wAttributes);
	}
}

int main(void) {
	SetConsoleTitle("Fill-SquareBoard-with-LShapedTiles");

	std::cout << "Board size: " << size << "x" << size << std::endl;

	int specialRow = 0, specialColumn = 0;//Avoid death loop from incorrect input
	while (true) {
		std::cout << "Enter COLUMN number of the special block: ";
		std::cin >> specialColumn;
		if (specialColumn >= 0 && specialColumn < size) break;
	}
	while (true) {
		std::cout << "Enter ROW number of the special block: ";
		std::cin >> specialRow;
		if (specialRow >= 0 && specialRow < size) break;
	}
	std::cout << std::endl;
	std::cout << "Special block: (" << specialColumn << "," << specialRow << ")" << std::endl;

	ChessBoard(0, 0, specialRow, specialColumn, size);

	std::cout << std::endl;
	std::cout << "+";
	for (int i = 0; i < size + 1; i++) {
		std::cout << "--";
	}
	std::cout << "+" << std::endl;
	std::cout << "| X";
	for (int i = 0; i < size; i++) {
		if (i < 10)std::cout << " " << i;
		else std::cout << i % 100;
	}
	std::cout << "|" << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << "|";
		if (i < 10)std::cout << " " << i;
		else std::cout << i % 100;
		for (int j = 0; j < size; j++) {
			OutColorfulBlock(Board[i][j]);
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "+";
	for (int i = 0; i < size + 1; i++) {
		std::cout << "--";
	}
	std::cout << "+" << std::endl;
	system("pause>NUL");
	return 0;
}

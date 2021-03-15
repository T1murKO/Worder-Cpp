#include "Header.h"
//оптимизация кода
//указатель на функцию инг или ру
// экстерное сохранение и рандомный выход

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char addWord[] = "Add new word";
	char startLearningStr[] = "Start learning";
	char ViewAllWords[] = "View All Words";
	char PrintFinished[] = "Print Finished";
	char exit[] = "Exit";
	char* MenuStrings[] = { addWord,startLearningStr,ViewAllWords,PrintFinished,exit };
	int activeItem = 0;
	int strSize = 5;
	COORD pos;
	int tap = 0;
	int wordsNum = countOfWords();
	Words *wordsData = new Words[500];
	wordsData = loadWordsData(wordsData);
	Learned* learnedData = new Learned[500];
	learnedData = loadLearnedData(learnedData);
	checkForRepeating(learnedData,first);
	checkForRepeating(learnedData,second);
	HANDLE HandleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int activeColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	int defaultColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
	while (true) {
		system("cls");
		system("color 0F");
		for (int i = 0; i < strSize; i++) {
			if (i != activeItem)
				SetConsoleTextAttribute(HandleOut, defaultColor);
			else
				SetConsoleTextAttribute(HandleOut, activeColor);
			pos.X = 0;
			pos.Y = i+1;
			SetConsoleCursorPosition(HandleOut, pos);
				cout << MenuStrings[i];
		}
	OneMore:
			tap = _getch();
				switch (tap) {
				case 72: {
					activeItem--;
					if (activeItem < 0) activeItem = strSize - 1;
				}break;
				case 80: {
					activeItem++;
					if (activeItem > strSize - 1) activeItem = 0;
				}break;
				case 13: {
					if (activeItem == 0) {
						addNewWord(wordsData, wordsNum);
						saveWords(wordsData, wordsNum);
					}
					if (activeItem == 1) {
						chooseLearning(wordsData, wordsNum,learnedData);
					}
					if (activeItem == 2) {
						ShowAllWords(wordsData,wordsNum);
					}
					if (activeItem == 3) {
						printFinished();
					}
					if (activeItem == 4) {
						return 0;
					}
				}break;
				case 27: {
					
					saveWords(wordsData, wordsNum);
					return 0;
				}break;
				default: {
					goto OneMore;
				}
				}

		}
	return 0;
	system("pause");
	}
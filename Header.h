#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <fstream>
#include "stru.h"
#include <time.h>
#define IDI_ICON1                       102
//#define DEBUG
using namespace std;

enum part { first = 1, second };
int countOfWords();
Words* loadWordsData(Words*);
Words* addNewWord(Words*, int&);
void saveWords(Words*, int);
void chooseLearning(Words*, int&,Learned*);
int* selection(Words*, int, int, int);
void startLearning(Words*, int&, int,int*,int);
void learning(Words*, int, int, int*, int);
void testingENG(Words*, int, int, int*);
void testingRU(Words*, int, int, int*);
inline Words* deleteWord(Words*, int&);
inline int* changeID(int*, int);
inline void swap(int*, int*);
Learned* addLearned(Words*, Learned*, int&, int*, int,int);
Learned* loadLearnedData(Learned*);
void saveLearned(Learned*, int);
int getTime(int(*)(tm));
int _month(tm);
int _day(tm);
void checkForRepeating(Learned*,part);
void startRepeating(Learned*,int, int*, int,part);
inline Learned* deleteLearned(Learned*, int&, int);
char* deleteSpaces(char*, int);
char* deleteUnderLine(char*, int);
void ShowAllWords(Words* , int );
void printFinished();
int* boubleSort(int*, int);
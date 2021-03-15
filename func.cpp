#include "Header.h"


int countOfWords() {
	FILE* file = nullptr;
	int sz = 0;
	errno_t err = fopen_s(&file, "wordsData.txt", "r");
	if (err)
		cout << "The file wordsData.txt was not opened\n";
	else {
		fscanf_s(file, "%d", &sz);
		fclose(file);
	}
	
	return sz;
}
int countOfLearned() {
	FILE* file = nullptr;
	int sz = 0;
	errno_t err = fopen_s(&file, "LearnedData.txt", "r");
	if (err)
		cout << "The file LearnedData.txt was not opened\n";
	else {
		fscanf_s(file, "%d", &sz);
		fclose(file);
	}

	return sz;
}
char* deleteSpaces(char* sentance, int sz) {
	char s = ' ';
	char p = '_';
	for (int i = 0; i < sz; i++) {
		if (sentance[i] == s) {
			sentance[i] = p;
		}
	}

	return sentance;
}
char* deleteUnderLine(char* sentance, int sz) {
	char s = ' ';
	char p = '_';
	for (int i = 0; i < sz; i++) {
		if (sentance[i] == p) {
			sentance[i] = s;
		}
	}

	return sentance;
}
Words* addNewWord(Words* wordsData,int &sz) {
	system("cls");
	char s = '_';
	char* word = nullptr;
	char* translation = nullptr;
	int hardness = 0;
	char buff[256];
	int temp = 0;
	int strsz = 0;
	cout << "Input new word or expression: ";
	cin.getline(buff, 256);
	strsz = strlen(buff);
	if (buff[strsz-1] == ' ')
		buff[strsz-1] = '\0';
	word = new char[strsz];
	strcpy_s(word, strsz+1, buff);
	if (word[0] == ' ') {
		memmove(word, word + 1, strsz);
	}
	cout << "Input translation: ";
	cin.getline(buff, 256);
	strsz = strlen(buff);
	if (buff[strsz-1] == ' ')
		buff[strsz-1] = '\0';
	translation = new char[strsz];
	strcpy_s(translation, strsz + 1, buff);
	if (translation[0] == ' ') {
		memmove(translation, translation + 1, strsz);
	}
	wordsData[sz].word = word;
	wordsData[sz].translation = translation;
	wordsData[sz].hardness = 1;
	wordsData[sz].stage = 1;
	sz++;
	word = nullptr;
	return wordsData;
}
void saveWords(Words* wordsData,int sz){
	for (int i = 0; i < sz; i++) {
		wordsData[i].word = deleteSpaces(wordsData[i].word, strlen(wordsData[i].word));
		wordsData[i].translation = deleteSpaces(wordsData[i].translation, strlen(wordsData[i].translation));
	}
	FILE* file = nullptr;
	errno_t err = fopen_s(&file, "WordsData.txt", "w");
	if (err)
		cout << "The file wordsData.txt was not opened\n";
	else {
		fprintf_s(file, "%d%s", sz, "\n");
		fclose(file);
		fopen_s(&file, "wordsData.txt", "a");
		for (int i = 0; i < sz; i++) {
			fprintf_s(file, "%s%s", wordsData[i].word, " ");
			fprintf_s(file, "%s%s", wordsData[i].translation, " ");
			fprintf_s(file, "%d%s", wordsData[i].hardness, " ");
			fprintf_s(file, "%d%s", wordsData[i].stage, "\n");
		}
		fclose(file);
	}
}
void chooseLearning(Words* wordsData, int& sz, Learned* learnedData) {
	int stage1 = 0;
	int stage2 = 0;
	int stage3 = 0;
	int stage4 = 0;
	int stage = 0;
	int wordsToLearn = 0;
	for (int i = 0; i != sz; i++) {
		if (wordsData[i].stage == 1)
			stage1++;
		else if (wordsData[i].stage == 2)
			stage2++;
		else if (wordsData[i].stage == 3)
			stage3++;
		else if (wordsData[i].stage == 4)
			stage4++;
	}
ChooseWords:
	system("cls");
	cout << "_________________________________\n\n";
	cout << "Now you have " << stage1 << " words in first stage\n";
	cout << "Now you have " << stage2 << " words in second stage\n";
	cout << "Now you have " << stage3 << " words in third stage\n";
	cout << "Now you have " << stage4 << " words in fourth stage\n\n";
	cout << "Please choose stage to learn: ";
	cin >> stage;
	cout << "Input number of words to learn: ";
	cin >> wordsToLearn;
	cin.ignore(1, '\n');
	system("cls");
	if (((stage == 1) && (stage1 < wordsToLearn)) ||
		((stage == 2) && (stage2 < wordsToLearn)) ||
		((stage == 3) && (stage3 < wordsToLearn)) ||
		((stage == 4) && (stage4 < wordsToLearn))) {
		cout << "There arent enough words in the stage choose another one please: \n\n";
		int tap = _getch();
		goto ChooseWords;
	}
	int* wordsID = new int[wordsToLearn];
	switch (stage) {
	case 1: {
		wordsID = selection(wordsData, sz, wordsToLearn, 1);
		startLearning(wordsData, sz, wordsToLearn, wordsID, 1);
	}break;
	case 2: {
		wordsID = selection(wordsData, sz, wordsToLearn, 2);
		startLearning(wordsData, sz, wordsToLearn, wordsID, 2);
	}break;
	case 3: {
		wordsID = selection(wordsData, sz, wordsToLearn, 3);
		startLearning(wordsData, sz, wordsToLearn, wordsID, 3);
	}break;
	case 4: {
		wordsID = selection(wordsData, sz, wordsToLearn, 4);
		startLearning(wordsData, sz, wordsToLearn, wordsID, 4);
		int learnedNum = countOfLearned();
		learnedData = addLearned(wordsData, learnedData, learnedNum, wordsID, wordsToLearn, 1);
		for (int i = 0; i < learnedNum; i++) {
			learnedData[i].word = deleteSpaces(learnedData[i].word, strlen(learnedData[i].word));
			learnedData[i].translation = deleteSpaces(learnedData[i].translation, strlen(learnedData[i].translation));
		}
		saveLearned(learnedData, learnedNum);
		system("cls");
		cout << "Congratulations!You have successfuly learned theese words: \n";
		int j = 0;
		for (int i = 0; i < wordsToLearn; i++) 
		{
			wordsData[wordsID[i]].word = deleteUnderLine(wordsData[wordsID[i]].word, strlen(wordsData[wordsID[i]].word));
			wordsData[wordsID[i]].translation = deleteUnderLine(wordsData[wordsID[i]].translation, strlen(wordsData[wordsID[i]].translation));
			cout << wordsData[wordsID[i]].word << " - " << wordsData[wordsID[i]].translation << endl;
			
		}
		wordsID = boubleSort(wordsID, wordsToLearn);
		for (int i = 0; i < wordsToLearn; i++)
		{
			wordsData = deleteWord(wordsData, sz);
		}
		
		int tap = _getch();
		
	}
	}
	for (int i = 0; i < sz; i++) {
		wordsData[i].word = deleteSpaces(wordsData[i].word, strlen(wordsData[i].word));
		wordsData[i].translation = deleteSpaces(wordsData[i].translation, strlen(wordsData[i].translation));
}
	saveWords(wordsData, sz);
}
int* boubleSort(int* arr,int sz) {
	for (int i = 0; i < sz; i++) {
		for (int j = i; j < sz-1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return arr;
}

inline Words* deleteWord(Words* wordsData, int& sz) {
	for (int i = 0; i < sz-1; i++)
		wordsData[i] = wordsData[i + 1];
	sz--;
	return wordsData;
}
void saveLearned(Learned* learnedData, int learnedNum) {
	FILE* file = nullptr;
	errno_t err = fopen_s(&file, "LearnedData.txt", "w");
	if (err){
		cout << "LearnedData.txt was not open\n";
	}
	else {
		fprintf_s(file, "%d%s", learnedNum, "\n");
		fclose(file);
		err = fopen_s(&file, "LearnedData.txt", "a");
		if (err) {
			cout << "LearnedData.txt was not open\n";
		}
		else {
			for (int i = 0; i < learnedNum; i++) {
				fprintf_s(file, "%s%s", learnedData[i].word, " ");
				fprintf_s(file, "%s%s", learnedData[i].translation, " ");
				fprintf_s(file, "%d%s", learnedData[i].day, " ");
				fprintf_s(file, "%d%s", learnedData[i].month, " ");
				fprintf_s(file, "%d%s", learnedData[i].stage, "\n");
			}
			fclose(file);
		}
	}
}
Learned* addLearned(Words* wordsData,Learned* learnedData, int &learnedNum, int* wordsID,int wordsToLearn,int stage) {
	int j = 0;
	for (int i = learnedNum; i < learnedNum+wordsToLearn; i++) {
		learnedData[i].word = wordsData[wordsID[j]].word;
		learnedData[i].translation = wordsData[wordsID[j]].translation;
		learnedData[i].day = getTime(_day);
		learnedData[i].month = getTime(_month);
		learnedData[i].stage = stage;
		j++;
	}
	learnedNum += wordsToLearn;
	return learnedData;
}
int getTime(int(*returnFuncion)(tm)) {
	struct tm newtime;
	__time64_t long_time;
	char timebuf[8] = { "" };
	errno_t err;
	_time64(&long_time);
	err = _localtime64_s(&newtime, &long_time);
	return returnFuncion(newtime);
}
int _day(tm newtime) {
	int day = newtime.tm_mday;
	return day;
}
int _month(tm newtime) {
	int month = newtime.tm_mon;
	return month+1;
	}
int* selection(Words* wordsData, int sz, int WordsToLearn, int stage) {
	int* wordsID = new int[	WordsToLearn];
	int y = 0;
	for (int i = 0; i != sz; i++) {
		if (wordsData[i].stage == stage) {
			for (int j = i; j < WordsToLearn + i; j++) {
				wordsData[j].word = deleteUnderLine(wordsData[j].word, strlen(wordsData[j].word));
				wordsData[j].translation = deleteUnderLine(wordsData[j].translation, strlen(wordsData[j].translation));
				wordsID[y] = j;
				y++;
			}
			return wordsID;
		}
		
	}
}
inline int* changeID(int* wordsID, int wordsToLearn) {
	for (int i = 0; i < wordsToLearn; i++) {
		int randomer = rand() % wordsToLearn;
		int temp = wordsID[i];
		wordsID[i] = wordsID[randomer];
		wordsID[randomer] = temp;
	}
	return wordsID;
}
inline void swap(int &left,int &right) {
	int temp = left;
	left = right;
	right = temp;
}
void startLearning(Words* wordsData,int &sz,int wordsToLearn,int* wordsID,int stage) {
	cout << "Now please learn " << wordsToLearn << " words\n\n";
	int tap = _getch();
	learning(wordsData, sz, wordsToLearn, wordsID, stage);
	testingENG(wordsData, sz, wordsToLearn, wordsID);
	testingRU(wordsData, sz, wordsToLearn, wordsID);
}
void learning(Words* wordsData, int sz, int wordsToLearn, int* wordsID, int stage) {
	system("cls");
	int learnedIter = 0;
	int tap = 0;
	bool check = 0;
	int* learnedID = new int[wordsToLearn];
	int wordsIter = 0;
	Repeat:
	for (int i = 0; i < wordsToLearn; i++) {
		for (int u = 0; u < wordsToLearn; u++)
			if (learnedID[u] == wordsID[wordsIter]) {
				wordsIter++;
				check = 1;
				break;
			}
		if (check == 1) {
			check = 0;
			continue;
		}

		cout << wordsData[wordsID[wordsIter]].word << " - " << wordsData[wordsID[wordsIter]].translation << endl;
		cout << "\n\n Press y or n";
		Nothing:
		tap = _getch();
		if (tap == 110 || tap == 242) {
			wordsIter++;
			system("cls");
			continue;
		}
		else if (tap == 121 || tap == 237)	{
			learnedID[learnedIter] = wordsID[wordsIter];
			wordsData[wordsID[wordsIter]].stage++;
			learnedIter++;
			wordsIter++;
			system("cls");
			continue;
		}
		goto Nothing;
	}
	if (learnedIter == wordsToLearn) {
        wordsID = changeID(wordsID, wordsToLearn);
		return;
	}
	wordsIter = 0;
	goto Repeat;
}
void testingENG(Words* wordsData, int sz, int wordsToLearn, int* wordsID){
	system("cls");
	int learnedIter = 0;
	char buff[256];
	int* passedID = new int[wordsToLearn];
	bool check = 0;
	int wordsIter = 0;
	Mistake:
	for (int i = 0; i < wordsToLearn; i++) {
		for (int u = 0; u < wordsToLearn; u++)
			if (passedID[u] == wordsID[wordsIter]) {
				check = 1;
				wordsIter++;
				break;
			}
		if (check == 1) {
			check = 0;
			continue;
		}
		cout << "Part 1:" << endl << "Input translation of these words to English: " << endl << wordsData[wordsID[wordsIter]].translation << " - ";
		cin.getline(buff, 256);
		int sz = strlen(buff);
		char* answer = new char[sz];
		strcpy_s(answer, sz +	1, buff);
		sz = strlen(wordsData[wordsID[wordsIter]].word);
		char* word = new char[sz];
		strcpy_s(word, sz + 1, wordsData[wordsID[wordsIter]].word);
			if (!strcmp(answer,word)) {
			passedID[learnedIter] = wordsID[wordsIter];
			learnedIter++;
			wordsIter++;
			system("cls");
		}
		else {
			system("cls");
			cout << "Your are wrong!!!\n\n";
			cout << wordsData[wordsID[wordsIter]].translation << " - " << wordsData[wordsID[wordsIter]].word  << endl;
			int tap = _getch();
			wordsIter++;
			system("cls");
		}
	}
	if (learnedIter == wordsToLearn) {
		wordsID = changeID(wordsID, wordsToLearn);
		return;
	}
	wordsIter = 0;
	goto Mistake;
}
void testingRU(Words* wordsData, int sz, int wordsToLearn, int* wordsID){
	system("cls");
	int wordsIter = 0;
	int learnedIter = 0;
	char buff[256];
	int* passedID = new int[wordsToLearn];
	bool check = 0;
	Mistake:
	for (int i = 0; i < wordsToLearn; i++) {
		for (int u = 0; u < wordsToLearn; u++)
			if (passedID[u] == wordsID[wordsIter]) {
				check = 1;
				wordsIter++;
				break;
			}
		if (check == 1) {
			check = 0;
			continue;
		}
		cout <<"Part 2:" << endl << "Input translation of these words to Russian: "<< endl << wordsData[wordsID[wordsIter]].word << " - ";
		cin.getline(buff, 256);
		int sz = strlen(buff);
		char* answer = new char[sz];
		strcpy_s(answer, sz +	1, buff);
		sz = strlen(wordsData[wordsID[wordsIter]].translation);
		char* word = new char[sz];

		strcpy_s(word, sz + 1, wordsData[wordsID[wordsIter]].translation);
			if (!strcmp(answer,word)) {
			passedID[learnedIter] = wordsID[wordsIter];
			learnedIter++;
			wordsIter++;
			system("cls");
		}
		else {
			system("cls");
			cout << "Your are wrong!!!\n\n";
			cout << wordsData[wordsID[wordsIter]].word << " - " << wordsData[wordsID[wordsIter]].translation << endl;
			int tap = _getch();
			wordsIter++;
			system("cls");
		}
	}
	if (learnedIter == wordsToLearn) {
		wordsID = changeID(wordsID, wordsToLearn);
		return;
	}
	wordsIter = 0;
	goto Mistake;
}
Learned* loadLearnedData(Learned* learnedData) {
	char* word = nullptr;
	char* translation = nullptr;
	int day = 0;
	int month = 0;
	int temp = 0;
	char buff[256];
	int stage = 0;
	int strsz = 0;
	FILE* file = nullptr;
	int sz = 0;
	errno_t err = fopen_s(&file, "LearnedData.txt", "r");
	if (err) {
		cout << "The file LearnedData.txt was not opened\n";
		int tap = _getch();
	}
	else {
		fscanf_s(file, "%d", &sz);
		for (int j = 0; j < sz; j++) {
			for (int i = 0; i < 5; i++) {
				switch (i)
				{
				case 0:
					fscanf_s(file, "%s", buff, _countof(buff));
					strsz = strlen(buff);
					word = new char[strsz];
					strcpy_s(word, strsz + 1, buff);
					learnedData[j].word = word;
					break;
				case 1:
					fscanf_s(file, "%s", buff, _countof(buff));
					strsz = strlen(buff);
					translation = new char[strsz];
					strcpy_s(translation, strsz + 1, buff);
					learnedData[j].translation = translation;
					break;
				case 2:
					fscanf_s(file, "%d", &day);
					learnedData[j].day = day;
					break;
				case 3:
					fscanf_s(file, "%d", &month);
					learnedData[j].month = month;
					break;
				case 4:
					fscanf_s(file, "%d", &stage);
					learnedData[j].stage = stage;
				}
			}
			
			
			
			
			
		}
		fclose(file);
	}
	word = nullptr;
	translation = nullptr;
	return learnedData;
}
Words* loadWordsData(Words* wordsData) {
	char* word = NULL;
	char* translation = NULL;
	int hardness = 0;
	int stage = 0;
	char buff[256];
	int strsz = 0;
	FILE* file = nullptr;
	int sz = 0;
	errno_t err = fopen_s(&file, "WordsData.txt", "r");
	if (err) {
		cout << "The file wordsData.txt was not opened\n";
		int tap = _getch();
	}
	else {
		fscanf_s(file, "%d", &sz);
		for (int j = 0; j < sz; j++) {
			for (int i = 0; i < 4; i++) {
				switch (i)
				{
				case 0:
					fscanf_s(file, "%s", buff, _countof(buff));
					strsz = strlen(buff);
					word = new char[strsz];
					strcpy_s(word, strsz + 1, buff);
					wordsData[j].word = word;
					break;
				case 1:
					fscanf_s(file, "%s", buff, _countof(buff));
					strsz = strlen(buff);
					translation = new char[strsz];
					strcpy_s(translation, strsz + 1, buff);
					wordsData[j].translation = translation;
					break;
				case 2:
					fscanf_s(file, "%d", &hardness);
					wordsData[j].hardness = hardness;
					break;
				case 3:
					fscanf_s(file, "%d", &stage);
					wordsData[j].stage = stage;
					break;
				}
			}
		}
		fclose(file);
	}
	return wordsData;
}
void printFinished() {
	system("cls");
	char buff[256];
	int temp = 0;
	int strsz = 0;
	char* word;
	char* translation;
	int sz = 0;
	FILE* file;
	errno_t err = fopen_s(&file, "FinshedData.txt", "r");
	if (err) {
		cout << "The file FinshedData.txt was not opened\n";
		int tap = _getch();
	}
	else {
		while(!feof(file))
		{
			fscanf_s(file, "%s", buff, _countof(buff));
			fscanf_s(file, "%s", buff, _countof(buff));
			sz++;
		}
		fclose(file);
	}
	err = fopen_s(&file, "FinshedData.txt", "r");
	cout << "--------------------\nAll learned words:\n";
	for (int i = 1; i < sz; i++)
	{
		fscanf_s(file, "%s", buff, _countof(buff));
		strsz = strlen(buff);
		word = new char[strsz];
		strcpy_s(word, strsz + 1, buff);
		cout << i << ")" << deleteUnderLine(word, strsz) << " - ";
		fscanf_s(file, "%s", buff, _countof(buff));
		strsz = strlen(buff);
		translation = new char[strsz];
		strcpy_s(translation, strsz + 1, buff);
		cout << deleteUnderLine(translation, strsz) << endl;
	}
	fclose(file);
	int tap = _getch();
}
inline int daysDifference(int day,int month){
	int todaysDay = getTime(_day);
	int todaysMonth = getTime(_month);
	if (todaysMonth == month)
		return todaysDay - day;
	else
		return todaysDay + (31 - day);

}	

void checkForRepeating(Learned* learnedData,part stage) {
	system("cls");
	int repeatNum = 0;
	int todaysDay = getTime(_day);
	int todaysMonth = getTime(_month);
	int size = countOfLearned();
		for (int i = 0; i < size; i++) {
			if (learnedData[i].stage == stage)
				if (daysDifference(learnedData[i].day,learnedData[i].month) >= 14)
					repeatNum++;

		}
		int *wordsID = nullptr;
		if (repeatNum >= 15)
		{
			repeatNum = 15;
			wordsID = new int[repeatNum];
		}
		else
			wordsID = new int[repeatNum];
		int j = 0;
		for (int i = 0; i < size; i++) {
			if (j == repeatNum)
				break;
			if(learnedData[i].stage == stage)
			if (daysDifference(learnedData[i].day, learnedData[i].month) >= 14)
			{
				wordsID[j] = i;
				j++;
			}
		}
	if (repeatNum >= 8)
		cout << "You have " << repeatNum << " words to repeat and learn completetely "<< stage << " stage, would you like to do this?\n\n press y or n\n";
	else
		return;
	OneMore:
	int tap = _getch();
	if (tap == 110 || tap == 240) {
		cout << "\nOK, dont be lazzy, do it next time\n";
		int tap = _getch();
		system("cls");
		return;
	}
	if (tap == 121 || tap == 237) {
		startRepeating(learnedData,size, wordsID, repeatNum,stage);
		return;
		int tap = _getch();
	}
	goto OneMore;
}
void startRepeating(Learned* learnedData,int learnedNum, int* dataWordsID,int sz,part stage){
	Words* learnedWords = new Words[sz];
	int* wordsID = new int[sz];
	for (int i = 0; i < sz; i++) {
		int x = dataWordsID[i];
		learnedData[x].word = deleteUnderLine(learnedData[x].word, strlen(learnedData[x].word));
		learnedData[x].translation = deleteUnderLine(learnedData[x].translation, strlen(learnedData[x].translation));
	}
	int j = 0;
	for (int i = 0; i < sz; i++) {
		int x = dataWordsID[i];
		wordsID[i] = i;
		learnedWords[i].word = learnedData[x].word;
		learnedWords[i].translation = learnedData[x].translation;
		learnedWords[i].hardness = 1;
		learnedWords[i].stage = 1;
	}
	learning(learnedWords,sz,sz,wordsID,1);
	testingENG(learnedWords, sz, sz, wordsID);
	testingRU(learnedWords, sz, sz, wordsID);
	system("cls");
	if (stage == 1) {
		cout << "These words were nearly learned, there are left a bit: \n";
		for (int i = 0; i < sz; i++) {
			int x = dataWordsID[i];
			cout << learnedWords[i].word << " - " << learnedWords[i].translation << endl;
			learnedData[x].stage++;
			learnedData[x].day = getTime(_day);
			learnedData[x].month = getTime(_month);
		}
		sz = countOfLearned();
	}
	else {
		for (int i = 0; i < sz; i++) {//удаление пробелов в выученом
			int x = wordsID[i];
			learnedData[x].word = deleteSpaces(learnedData[x].word, strlen(learnedData[x].word));
			learnedData[x].translation = deleteSpaces(learnedData[x].translation, strlen(learnedData[x].translation));
		}
		FILE* file = nullptr;//сохранение выученых
		errno_t err = fopen_s(&file, "FinshedData.txt", "a");
		if (err) {
			cout << "FinshedData.txt was not open\n";
		}
		else {
			fprintf_s(file, "%s", "\n");
			for (int i = 0; i < sz; i++) {
				int x = dataWordsID[i];
				fprintf_s(file, "%s%s", learnedData[x].word, " ");
				fprintf_s(file, "%s%s", learnedData[x].translation, " ");
			}
			fclose(file);
		}
		cout << "These words were completly learned, thanks for your fervour: \n";
		for (int i = 0; i < sz; i++) {
			int x = dataWordsID[i];
			cout << learnedWords[x].word << " - " << learnedWords[x].translation << endl;

			learnedData = deleteLearned(learnedData, learnedNum, x - i);
		}
		learnedNum = learnedNum - sz;

	}
	learnedWords = nullptr;
	for (int i = 0; i < learnedNum; i++) {
		learnedData[i].word = deleteSpaces(learnedData[i].word, strlen(learnedData[i].word));
		learnedData[i].translation = deleteSpaces(learnedData[i].translation, strlen(learnedData[i].translation));
	}
	saveLearned(learnedData, learnedNum);
	int tap = _getch();

}
inline Learned* deleteLearned(Learned* learnedData, int& sz, int j) {
	for (int i = j; i < sz - 1; i++)
		learnedData[i] = learnedData[i + 1];
	return learnedData;
}
void ShowAllWords(Words* wordsData,int sz) {
	system("cls");
	for (int i = 0; i != sz; i++) {
		wordsData[i].word = deleteUnderLine(wordsData[i].word, strlen(wordsData[i].word));
		wordsData[i].translation = deleteUnderLine(wordsData[i].translation, strlen(wordsData[i].translation));
	}
	int j = 1;
	cout << "------------------------\n";
	cout << "Stage 1 has:\n";
	for (int i = 0; i < sz; i++) {
		if (wordsData[i].stage == 1) {
			cout << j << ") " << wordsData[i].word << "\t - \t" << wordsData[i].translation << endl;
			j++;
		}
	}
	cout << "\n------------------------\n";
	cout << "Stage 2 has:\n";
	j = 1;
	for (int i = 0; i < sz; i++) {
		if (wordsData[i].stage == 2) {
			cout << j << ") " << wordsData[i].word << "\t - \t" << wordsData[i].translation << endl;
			j++;
		}
	}
	j = 1;
	cout << "\n------------------------\n";
	cout << "Stage 3 has:\n";
	for (int i = 0; i < sz; i++) {
		if (wordsData[i].stage == 3) {
			cout << j << ") " << wordsData[i].word << "\t - " << wordsData[i].translation << endl;
			j++;
		}
	}
	j = 1;
	cout << "\n------------------------\n";
	cout << "Stage 4 has:\n";
	for (int i = 0; i < sz; i++) {
		if (wordsData[i].stage == 4) {
			cout << j << ") " << wordsData[i].word << "\t - \t" << wordsData[i].translation << endl;
			j++;
		}
	}

	int tap = _getch();
	return;
}
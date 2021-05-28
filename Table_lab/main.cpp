#include "sorttab.h"
#include "treetab.h"
#include "arrhash.h"
#include <string>
#include <locale.h>
#include <sstream>
#include <fstream>

typedef std::string Key;

int** tMark = NULL;
Key* tKey = NULL;
int tDataCount = 0, MemSize = 10;
TTable *pTab = NULL;

int TypeGenNumbers()
{
	setlocale(LC_ALL, "Russian");

	int Type;
	std::cout << "Select the type of filling:\n 1. From the file.txt \n 2. From the random machine\n ";
	do
	{
		std::cin >> Type;
		if (Type == 1)
		{
			std::cout << "Select the type of table:\n 1. Scan Table \n 2. Sort Table\n 3. Tree Table\n 4. Hash Table" << std::endl;
			do
			{
				std::cin >> Type;
				if (Type == 1)
					return 1;
				else if (Type == 2)
					return 2;
				else if (Type == 3)
					return 3;
				else if (Type == 4)
					return 4;
				else std::cout << "Wrong number, try again" << std::endl;
			} while (1);
		}
		if (Type == 2)
		{
			std::cout << "Select the type of table:\n 1. Scan Table \n 2. Sort Table\n 3. Tree Table\n 4. Hash Table" << std::endl;
			do
			{
				std::cin >> Type;
				if (Type == 1)
					return 5;
				else if (Type == 2)
					return 6;
				else if (Type == 3)
					return 7;
				else if (Type == 4)
					return 8;
				else std::cout << "Wrong number, try again" << std::endl;
			} while (1);
		}
		std::cout << "Wrong number, try again"<<std::endl;
	} while (1);
}
void del()
{
	delete[] tKey;
	for (int i = 0; i < 5; i++)
		delete tMark[i];
	delete[] tMark;
	delete pTab;
}
void gFile(int typetable)
{
	std::ifstream file("D:\\Downloads\\input.txt");
	if (file.is_open())
	{
		std::string line1;
		while (std::getline(file, line1))
			tDataCount++;

		file.clear();
		file.seekg(0, std::ios::beg);

		MemSize = tDataCount + 10;
		switch (typetable)
		{
		case 1: pTab = new TScanTable(MemSize); break;
		case 2: pTab = new TSortTable(MemSize); break;
		case 3: pTab = new TTreeTable(); break;
		case 4: pTab = new TArrayHash(MemSize + 100); break;
		}
		tMark = new int* [MemSize];
		tKey = new std::string[MemSize];
		for (int i = 0; i < MemSize; i++)
			tMark[i] = new int[5];
		std::cout << "File is opened" << std::endl;
		std::string line2;
		for (int k = 0; std::getline(file, line2); k++)
		{
			std::istringstream iss(line2);
			std::string token;
			for (int i=0;std::getline(iss, token, '|');i++)
			{
				if (i == 0) tKey[k] = token;
				if ((i >= 1) && (i <= 5))
					tMark[k][i-1] = std::stoi(token); //перевод string в int
			}
		}
		for (int i = 0; i < tDataCount; i++)
		{
			pTab->InsRecord(tKey[i], tMark[i]);
		}
		file.close();
	}
	else std::cout << "Opening error"<<std::endl;
}
void KeyEnt()
{
	std::string a, b, c, d, e;
	for (int i = 0; i < tDataCount; i++)
	{
		a = rand() % 25 + 65;
		b = rand() % 25 + 97;
		c = rand() % 25 + 97;
		d = rand() % 25 + 97;
		e = rand() % 25 + 97;
		tKey[i] = a + b + c + d + e;
	}
}
void generator(int typetable)
{
	std::cout << "Enter records amount" << std::endl;
	std::cin >> tDataCount;
	MemSize = tDataCount + 10;
	switch (typetable)
	{
	case 1: pTab = new TScanTable(MemSize); break;
	case 2: pTab = new TSortTable(MemSize); break;
	case 3: pTab = new TTreeTable(); break;
	case 4: pTab = new TArrayHash(100); break;
	default: break;
	}
	tMark = new int* [MemSize];
	tKey = new std::string[MemSize];
	for (int i = 0; i < MemSize; i++)
	{
		tMark[i] = new int[5];
		for (int j = 0; j < 5; j++)
			tMark[i][j] = rand() % 4 + 2;
	}
	KeyEnt();
	int* mr;
	for (int i = 0; i < tDataCount; i++)
	{
		pTab->InsRecord(tKey[i], tMark[i]);
	}
}
void mainmenu(int sortflag = 1)
{
	Key key;
	int delta;
	do
	{
		std::cout << "select option\n" << "0 - Exit\n"
			<< "1 - Insert record\n" << "2 - Find record\n"
			<< "3 - Delete record\n" << "4 - Print table\n";
		std::cin >> delta;
		system("cls");
		if (delta != 0 && delta != 4)
		{
			std::cout << "Enter a key\n";
			std::cin.ignore();
			std::getline(std::cin, key);
		}
		switch (delta)
		{
		case 0: break;
		case 1:
		{
			if (!pTab->IsFull())
			{
				if (!pTab->FindRecord(key))
				{
					std::cout << "Insert key marks (4)" << std::endl;
					for (int j = 0; j < 5; j++)
						std::cin >> tMark[tDataCount][j];
					pTab->InsRecord(key, tMark[tDataCount]);
					tDataCount++;
					std::cout << "Record added" << std::endl;
				}
				else std::cout << "Insert Error: Record is being\n";
			}
			else std::cout << "Insert Error: Table is full\n";
		}break;
		case 2:
		{
			int* mr;
			mr = pTab->FindRecord(key);
			if (mr != NULL)
			{
				std::cout << key << std::endl;
				for (int j = 0; j < 5; j++)
					std::cout << mr[j] << " ";
			}
			else std::cout << "Record is not found\n";
		}break;
		case 3:
		{
				if (pTab->FindRecord(key))
				{
					pTab->DelRecord(key);
					std::cout << "Record Deleted" << std::endl;
					tDataCount--;
				}
				else std::cout << "Record is not found\n";
		}break;
		case 4:
		{
			if (sortflag)
				std::cout << *pTab << std::endl;
			else pTab->Print();
		} break;
		default: std::cout << "Wrong number, try again\n"; delta = 1;
		}
	} 	while (delta);
}
void menu(void)
{
	int Type = TypeGenNumbers();
	if (Type == 5)
	{
		generator(1);
		mainmenu();
	}
	else if (Type == 1)
	{
		gFile(1);
		mainmenu();
	}
	else if (Type == 6)
	{
		generator(2);
		mainmenu(0);
	}
	else if (Type == 2)
	{
		gFile(2);
		mainmenu(0);
	}
	else if (Type == 7)
	{
		generator(3);
		mainmenu();
	}
	else if (Type == 3)
	{
		gFile(3);
		mainmenu();
	}
	else if (Type == 8)
	{
		generator(4);
		mainmenu();
	}
	else if (Type == 4)
	{
		gFile(4);
		mainmenu();
	}
}
int main(int argc, char* argv)
{
	std::srand(time(NULL));
	menu();
	del();
	return 0;
}
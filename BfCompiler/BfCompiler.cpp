#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

char* brainfuckCommands;

int8_t memory[256];

int memoryPointerLocation = 0;

int codePointerLocation = 0;
int lastOpenBracketLocation = -1;
int nextClosedBracketLocation = -1;

int randomNum = 0;

void ClearMemory()
{
	memoryPointerLocation = 0;
	codePointerLocation = 0;
	nextClosedBracketLocation = -1;
	lastOpenBracketLocation = -1;
	for (int i = 0; i < sizeof(memory) / sizeof(memory[0]); i++) memory[i] = 0;
}

void HandleComma()
{
	bool success = false;
	string answer;
	cout << "\nVoer een karakter in:";
	while (!success)
	{
		cin >> answer;
		if (answer.length() == 1) success = true;
		else cout << "\nInput moet 1 karakter zijn!\nVoer een karakter in:";
	}
	memory[memoryPointerLocation] = (int)answer[0];
}

void HandleSemicolon()
{
	int invoerGetal = 0;
	cout << "\nVoer een getal in:";
	if (cin >> invoerGetal) {
		memory[memoryPointerLocation] = static_cast<unsigned char>(invoerGetal);
	}
	else {
		cout << "\nFout: Ongeldige invoer.\nVoer een getal in:";
	}
}

int HandleOpenBracket(int length)
{
	lastOpenBracketLocation = codePointerLocation;

	for (int i = codePointerLocation; i < length; i++)
	{
		if (brainfuckCommands[i] != ']') continue;
		nextClosedBracketLocation = i;
		break;
	}

	if (nextClosedBracketLocation == -1)
	{
		cout << "\n'[' haakje gevonden zonder matchende ']'!";
		return -1;
	}

	if (memory[memoryPointerLocation] == 0)
	{
		codePointerLocation = nextClosedBracketLocation - 1;
	}

	nextClosedBracketLocation = -1;
	return 0;
}

int HandleCloseBracket()
{
	if (lastOpenBracketLocation == -1)
	{
		cout << "\n']' haakje gevonden zonder matchende '['!";
		return -1;
	}

	if (memory[memoryPointerLocation] != 0)
	{
		codePointerLocation = lastOpenBracketLocation - 1;
	}

	lastOpenBracketLocation = -1;
	return 0;
}

int ExecuteCode(int length)
{
	bool finishedCode = false;
	while (!finishedCode)
	{
		char nextCommand = brainfuckCommands[codePointerLocation];

		int handleCharacterResult = 0;
		switch (nextCommand)
		{
			case '>':
				if (memoryPointerLocation < 255) memoryPointerLocation += 1;
				break;
			case '<':
				if (memoryPointerLocation > 0) memoryPointerLocation -= 1;
				break;
			case '+':
				memory[memoryPointerLocation] += 1;
				break;
			case '-':
				memory[memoryPointerLocation] -= 1;
				break;
			case '.':
				cout << (char)memory[memoryPointerLocation];
				break;
			case ':':
				cout << (int)memory[memoryPointerLocation];
				break;
			case '/':
				cout << " / ";
				break;
			case ',':
				HandleComma();
				break;
			case ';':
				HandleSemicolon();
				break;
			case '[':
				handleCharacterResult = HandleOpenBracket(length);
				if (handleCharacterResult == -1) return -1;
				break;
			case ']':
				handleCharacterResult = HandleCloseBracket();
				if (handleCharacterResult == -1) return -1;
				break;
			case '?':
				randomNum = rand() % 256;
				memory[memoryPointerLocation] = randomNum;
				break;
			default:
				break;
		}
		codePointerLocation += 1;

		if (codePointerLocation > length) finishedCode = true;
	}
	cout << '\n';

	return 0;
}

int TryReadNewFile()
{
    cout << "Geef Brainfuck Bestand (*.bf): ";

    string fileName;
    cin >> fileName;

	if (fileName == "q" || fileName == "Q")
	{
		cout << "Programma afsluiten...\n";
		return -1;
	}

    int length;

	ifstream stream(fileName);

	stream.seekg(0, ios::end);
	length = stream.tellg();
	stream.seekg(0, ios::beg);

	if (length <= 0)
	{
		cout << "Bestand bestaat niet of is leeg.\n";
		return -1;
	}

	brainfuckCommands = new char[length];
	stream.read(brainfuckCommands, length);
	stream.close();

	ClearMemory();

	int result = ExecuteCode(length);
	return result;
}




int main()
{
	int result = 0;
	while (result == 0)	
		result = TryReadNewFile();

	return 0;
}

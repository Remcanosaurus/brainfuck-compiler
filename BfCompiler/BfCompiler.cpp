#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char* brainfuckCommands;

int8_t memory[256];

int memoryPointerLocation = 0;

int codePointerLocation = 0;
int lastOpenBracketLocation = -1;
int nextClosedBracketLocation = -1;

void ClearMemory()
{
	memoryPointerLocation = 0;
	codePointerLocation = 0;
	for (int i = 0; i < sizeof(memory) / sizeof(memory[0]); i++) memory[i] = 0;
}

void HandleComma()
{
	bool success = false;
	string answer;
	while (!success)
	{
		cin >> answer;
		if (answer.length() == 1) success = true;
		else cout << "Input must be 1 character!";
	}
	memory[memoryPointerLocation] = (int)answer[0];
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
			case ',':
				HandleComma();
				break;
			case '[':
				handleCharacterResult = HandleOpenBracket(length);
				if (handleCharacterResult == -1) return -1;
				break;
			case ']':
				handleCharacterResult = HandleCloseBracket();
				if (handleCharacterResult == -1) return -1;
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

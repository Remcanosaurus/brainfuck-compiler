#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char* brainfuckCommands;

int TryReadNewFile()
{
    cout << "Enter brainfuck file: ";

    string fileName;
    cin >> fileName;

    int length;

	ifstream stream(fileName);

	stream.seekg(0, ios::end);
	length = stream.tellg();
	stream.seekg(0, ios::beg);

	if (length <= 0)
	{
		cout << "File is empty or does not exist." << endl;
		return -1;
	}

	brainfuckCommands = new char[length];
	stream.read(brainfuckCommands, length);
	stream.close();

	// Compiler Logic

	return 0;
}




int main()
{
	int result = 0;
	while (result == 0)	
		result = TryReadNewFile();

	return 0;
}

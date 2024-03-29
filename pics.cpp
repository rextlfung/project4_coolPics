/**
 * pics.cpp
 * Project UID 8b3bcc444eb500121e420f7e2e359014
 *
 * EECS 183, Fall 2019
 * Project 4: CoolPics
 *
 * Tin Long Rex Fung, Isaac Lok-Tin Li
 * rexfung, isaliac
 *
 * This program reads data from a .txt file and converts it into a .bmp file.
 * It draws cool pictures!!!
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

#include "Line.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Graphics.h"

/**
 * Requires: Nothing.
 * Modifies: cout.
 * Effects:  Prints an opening message.
 */
void printOpener();

/**
 * Requires: Nothing.
 * Modifies: cout.
 * Effects:  Prints a closing message.
 */
void printCloser();

/**
 * Requires: Nothing.
 * Modifies: cout.
 * Effects:  Prints a menu.
 */
void printMenu();

/**
 * Requires: ins is in good state.
 * Modifies: cin, ins.
 * Effects:  Closes ins if it is open. Keeps reading filename from the user
 *           (and appends .txt) until the file is successfully opened.
 *           Returns the name of the file that was opened.
 */
string openFile(ifstream& ins);

/**
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects:  Returns str with all of its alphabetical characters lowercased.
 */
string tolower(string str);

/**
 * Requires: Nothing.
 * Modifies: cin, drawer.
 * Effects:
 *     Opens a file
 *     Start with a blank canvas (drawer)
 *     Start reading from file.  For each line....
 *        Read the 1st character to determine shape
 *        Read the shape:  L reads a line, C reads a circle, T read a triangle
 *            R reads a rectangle.
 *            For any other character, clears drawer and prints
 *            "Error in input file: " << [character already read]
 *            << [all chars remaining on the line] << endl;
 *        Draw shape on canvas
 *     Close file
 *     Print "[Loaded filename]"
 */
void loadFile(Graphics& drawer);

/**
 * Requires: Nothing.
 * Modifies: cout, drawer.
 * Effects:
 *     Read filename from user
 *     concatenate filename with .bmp
 *     Write image to file.
 *     Print "[Wrote filename]"
 */
void writeFile(const Graphics& drawer);

int main()
{
	Graphics drawer;
	string command;
	printOpener();
	printMenu();

	// read first command from user
	cin >> command;
	cout << endl;
	command = tolower(command);

	// read user's input until he or she quits
	while (command != "quit")
	{
		if (command == "load")
		{
			loadFile(drawer);
		}
		else if (command == "write")
		{
			writeFile(drawer);
		}
		else
		{
			cout << "Invalid command" << endl << endl;
		}

		printMenu();

		// read next command
		cin >> command;
		cout << endl;
		command = tolower(command);
	}

	printCloser();
}

void writeFile(const Graphics& drawer)
{
	// Asks user for filename, and creates filename.bmp, a BMP image
	string filename;
	cin >> filename;
	filename += ".bmp";
	drawer.writeFile(filename);
	cout << "[Wrote " << filename << "]" << endl;
	return;
}

void loadFile(Graphics& drawer)
{
	// get file name and open file
	ifstream inf;
	string filename = openFile(inf);

	// make canvas blank
	drawer.clear();

	// declare loop variables
	char shape = ' '; // set to ' ' in case of nothing being read into shape
	Line drawL;
	Triangle drawT;
	Circle drawC;
	Rectangle drawR;

	// read and draw shape accordingly
	while (inf.eof() != true) {
		inf >> shape;
		if (shape == 'L') {
			drawL.read(inf);
			drawL.draw(drawer);
		}
		else if (shape == 'T') {
			drawT.read(inf);
			drawT.draw(drawer);
		}
		else if (shape == 'C') {
			drawC.read(inf);
			drawC.draw(drawer);
		}
		else if (shape == 'R') {
			drawR.read(inf);
			drawR.draw(drawer);
		}
		else if (shape != ' ') { // Only notifies user of invalid input if
			drawer.clear();		 // there is actually an input, not ' '
			cout << "Error in input file: " << shape;
			string remainingChars;
			getline(inf, remainingChars);
			cout << remainingChars << endl;
		}
		shape = ' '; // reset shape to prevent it from carrying over to next
					 // loop, in case next loop fails to update shape
	}
	// close file
	inf.close();

	// Print "[Loaded filename]"
	cout << "[Loaded " << filename << "]" << endl;
	return;
}

string tolower(string str)
{
	// loop to set each char of str to lower case
	for (int i = 0; i < str.length(); i++) {
		str[i] = ::tolower(str[i]); // standard cctype library function
	}
	return str;
}


// Don't change the implementations below!

void printMenu()
{
	cout << "Command:            Description:" << endl
		<< "--------            ------------" << endl
		<< "load filename       Loads data from a txt file" << endl
		<< "write filename      Creates a bmp image from data" << endl
		<< "quit                Quits the program" << endl << endl;
}


void printOpener()
{
	cout << "=================================================" << endl
		<< "               Welcome to CoolPics" << endl
		<< "=================================================" << endl << endl;
}

void printCloser()
{
	cout << "=================================================" << endl
		<< "            Thanks for using CoolPics!" << endl
		<< "=================================================" << endl;
}

string openFile(ifstream& ins)
{
	string fileName;

	// close stream if open
	if (ins.is_open())
	{
		ins.clear();
		ins.close();
	}

	// get filename
	cin >> fileName;
	fileName = fileName + ".txt";
	ins.open(fileName);

	// keep retrying if failed to open
	while (ins.fail())
	{
		cout << "Error in opening " << fileName
			<< ". Enter another file name: ";
		ins.clear();
		cin >> fileName;
		fileName = fileName + ".txt";
		ins.open(fileName);
	}

	return fileName;
}

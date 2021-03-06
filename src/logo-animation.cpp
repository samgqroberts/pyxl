#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
using namespace std;

#include "Logging.h"
#include "AnimationEngine.h"

#define NEWLINE        "\n"

void fileToStringVector(vector<string> * filecontents, string filename) {
  vector<string> lines;
  string line;
	ifstream myfile (filename);
	if (myfile.is_open()) {
    while(getline(myfile, line)) {
      lines.push_back(line);
		}
		myfile.close();
	} else {
		cout << "Unable to open file";
	}
  // rectangularize it with blank space
  long widestLineWidth = 0;
  for (int l = 0; l < lines.size(); l++) {
    if (lines[l].size() > widestLineWidth) {
      widestLineWidth = lines[l].size();
    }
  }
  for (int l = 0; l < lines.size(); l++) {
    string line = lines[l];
    for (int c = line.size() ; c < widestLineWidth ; c++) {
      line += " ";
    }
    lines[l] = line;
  }
  *filecontents = lines;
}

int main (int argc, char* argv[])
{
  logf("\n\n--------PROGRAM START--------");

  if (argc != 2) {
    cout << "Error: must specify a .txt file as command line arg" << endl;
    return 1;
  }
  string filename = argv[1];
  // get contents of text file
  vector<string> filecontents;
	fileToStringVector(&filecontents, filename);

  // initialize curses screen
	initscr();
  curs_set(0);
  noecho();
  nodelay(stdscr, TRUE);

  // initialize AnimationEngine
  AnimationEngine engine (filecontents);

  // end curses window
	endwin();

  return 0;
}

#include "game.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include<cmath>

using namespace std;


/* ======================================
* PART 2 - Show
* In response to the commands.txt
* Return robots in order
* =====================================*/


//
// Cout in an accending order
bool compareRobots(const Robot& x, Robot& y) { return x.rid < y.rid; }

// Print all robots
void printRobots(const vector<Robot>& robotContainer)
{
	vector<Robot> robotVec = robotContainer;
	// Sort vector container in order
	sort(robotVec.begin(), robotVec.end(), compareRobots);
	for (Robot i : robotVec)
	{
		cout << i.rid << " " << i.tid << " " << i.xpos << " " << i.ypos << endl;

	}
}

/* ======================================
* PART 3 - Origin
* In response to the commands.txt
* Return robots number order from origin, with in the
* distance of n
* =====================================*/

// Origin function
void within(const vector<Robot>& robotContainer, int n)
{
	vector<Robot> robotVec = robotContainer;
	sort(robotVec.begin(), robotVec.end(), compareRobots);
	unsigned int count = 1;
	for (Robot& i : robotVec)
	{
		int distance = abs(i.xpos) + abs(i.ypos);
		if (distance <= n) {
			++count;
		}
	}
	cout << count << '\n';
}


/* ======================================
* **************NOTICE!!*****************
* Within visual studio. CurrentPos function is
* required to be above Move function in order
* to compile correctly
* =====================================*/

bool currentPos(const vector<Robot>& robotContainer, int& xpos, int& ypos)
{
	for (const Robot& i : robotContainer)
	{
		if (i.xpos == xpos) {
			if (i.ypos == ypos) {
				return false;
			}
		}
	}
	return true;
}

/* ======================================
* PART 4 - Move Robot Functions
* In response to the commands.txt
* Return robots number order from origin, with in the
* distance of n
* =====================================*/

// Move robot x/y pos and increment travel count
void move(vector<Robot>& robotContainer, int r)
{
	for (int i = 0; i < robotContainer.size(); i++)
	{
		if (robotContainer[i].rid == r)
		{
			int xpos = robotContainer[i].xpos;
			int ypos = robotContainer[i].ypos;
			unsigned int dir = robotContainer[i].direction;
			//make the move according to the direction of teh robot
			if (dir == 1) { ypos++; robotContainer[i].travelled++; }
			else if (dir == 2) { xpos++; robotContainer[i].travelled++; }
			else if (dir == 3) { ypos--; robotContainer[i].travelled++; }
			else if (dir == 4) { xpos--; robotContainer[i].travelled++; }
			if (currentPos(robotContainer, xpos, ypos))
			{
				robotContainer[i].xpos = xpos;
				robotContainer[i].ypos = ypos;
			}
		}
	}
}

// turn robot. default facing north
// North = 0
// East = 1
// South = 2
// West = 3
void turnleft(vector<Robot>& robotContainer, int r)
{

	for (int i = 0; i < robotContainer.size(); i++)
	{
		unsigned int direction;
		if (robotContainer[i].rid == r)
		{
			int dir = robotContainer[i].direction - 1;
			if (dir == 0)
				dir = 4;
			robotContainer[i].direction = dir;
		}
	}
}

void turnright(vector<Robot>& robotContainer, int r)
{
	for (int i = 0; i < robotContainer.size(); i++)
	{
		unsigned int direction;
		if (robotContainer[i].rid == r)
		{
			int dir = robotContainer[i].direction + 1;
			if (dir == 5)
				dir = 1;
			robotContainer[i].direction = dir;
		}
	}
}


/* ======================================
* PART 5 - Travel
* In response to the commands.txt
* Return robots number order of travel.
* =====================================*/

// Sort incremeneted travel in accending order
bool sortByDistance(const Robot& a, const Robot& b) { return a.travelled < b.travelled; }


// 
//this functions show the distance travelled by robotContainer the robots
void travelled(const vector<Robot>& robotContainer)
{
	vector<Robot> robotVec = robotContainer;
	unsigned int count = 0;
	sort(robotVec.begin(), robotVec.end(), sortByDistance);
	//sorting according to the distance travelled
	for (Robot i : robotVec)
	{
		cout << i.rid << " " << i.travelled << endl;
	}
}





/* ======================================
* PART 1 - ReadIn
* Read in file from cmd.txt
* Vector to store robots and attributes
* =====================================*/

vector<string> split_string(const string& s) {
	auto space = find(s.cbegin(), s.cend(), ' ');
	vector<string> v;

	v.push_back(string(s.cbegin(), space));

	while (space != s.cend()) {
		auto start = ++space;
		space = find(start, s.cend(), ' ');
		v.push_back(string(start, space));
	}

	return v;
}


//Read in start text file
vector<Robot> cinRobots()
{
	int rid;
	int tid;
	int xpos;
	int ypos;

	ifstream strtfile;
	strtfile.open("start.txt");
	vector<Robot> robotVec;
	if (strtfile.is_open())
	{
		strtfile >> rid >> tid >> xpos >> ypos;
		while (strtfile)
		{
			//Pushing on to stack
			robotVec.push_back(Robot(rid, tid, xpos, ypos, 1));
			strtfile >> rid >> tid >> xpos >> ypos;
		}
	}
	else
		cout << "File could not be opened";
	return robotVec;
}


void readCommands(vector<Robot>& robotVec)
{
	ifstream cmdfile;
	cmdfile.open("commands.txt");
	if (cmdfile.is_open())
	{
		string command;
		getline(cmdfile, command);
		while (cmdfile)
		{
			auto v1 = split_string(command);
			int position = command.find(" ");
			if (position != string::npos)//checking if the command is two word
			{
				string str = command.substr(0, position);
				int  n = stoi(command.substr(position + 1));
				if (str == "within")
				{
					within(robotVec, n);
				}
				else if (str == "turnright")
				{
					turnright(robotVec, n);
				}
				else if (str == "turnleft")
				{
					turnleft(robotVec, n);
				}
				else if (str == "move")
				{
					move(robotVec, n);
				}
			}
			else
			{
				// Part 2
				if (command == "show")
				{
					printRobots(robotVec);
				}
				else if (command == "travelled")
				{
					travelled(robotVec);
				}
			}
			// Stop reoccuring output
			getline(cmdfile, command);
		}
	}
	else
		cout << "Error opening commands.txt\n";
}


int main()
{
	// Call functions
	vector<Robot> robotVec = cinRobots();
	readCommands(robotVec);
	return 0;
}
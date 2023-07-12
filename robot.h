#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <string>

class Robot {
	int rNum, tNum, xPos, yPos, direction, distanceTravelled;
public:
	//constructor for a robot
	Robot(int rNum, int tNum, int xPos, int yPos, int direction) :
		rNum(rNum), tNum(tNum), xPos(xPos), yPos(yPos), direction(direction)

	{
		distanceTravelled = 0;
	}
};

#endif // !ROBOT_H

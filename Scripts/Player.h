#ifndef PLAYER
#define PLAYER
#include "Object.h"

enum direction
{
	Right = 0, Up = 4, Left = 8, Down = 12
};

class Player :public Object
{
private:
	int score;
	int lives;
	int lifeIncrements; //The number of times the lives increased due to increase in score
public:
	Player(string n, int initialR, int initialC, string imagename);
	string getScore();
	int getScoreInt();
	int getLives();
	bool loseLive(); //returns false if player lost all lives
	void move(int, int);
	void increaseScore(int);
	bool checkLiveBonus(); //returns true if score is high enough to increase lives
	void restart();
	void setImage(string);
	void addSnapshots(string str[12]);
	direction dir;
};

#endif
#include "Player.h"

Player::Player(string n, int initialR, int initialC, string imagename) :Object(n, initialR, initialC, imagename)
{
	score = 0;
	lifeIncrements = 0;
	lives = 3;
	dir = Right;

}

string Player::getScore()
{
	string str = to_string(score);
	return str;

}

int Player::getScoreInt()
{
	
	return score;

}

int Player::getLives()
{
	return lives;
}


bool Player::loseLive() //returns false if player lost all lives
{
	--lives;
	if (lives == 0) //checks if the player lost all lives
		return false;
	else {
		curColumn = initialColumn;
		curRow = initialRow;
		updatePosition();
		return true;
	}
}

void Player::move(int horizontal, int vertical)
{
	curColumn = vertical;
	curRow = horizontal;
	updatePosition();
}

void Player::increaseScore(int n)
{
	score += n;
	if (checkLiveBonus()) //checks if score is high enough to increase lives
		lives++;
}

bool Player::checkLiveBonus() //checks if score is high enough to increase lives
{
	if (score > (lifeIncrements + 1) * 10000) { //so that every time the player earns 10000 points, lives are incremented
		++lifeIncrements;
		return true;
	}
	return false;
}

void Player::restart() {
	curColumn = initialColumn;
	curRow = initialRow;
	updatePosition();
	score = 0;
	lifeIncrements = 0;
	lives = 3;
}

void Player::setImage(string s) {
	texture.loadFromFile(s);
	shape.setTexture(&texture);
}

void Player::addSnapshots(string str[12]) { 
	snapshot.clear();
	snapshot.resize(16);
	for (int i = 0; i < 4; i++)
	{
		snapshot[0 + 4 * i].loadFromFile(str[0 + 3 * i]);
		snapshot[1 + 4 * i].loadFromFile(str[1 + 3 * i]);
		snapshot[2 + 4 * i].loadFromFile(str[2 + 3 * i]);
		snapshot[3 + 4 * i].loadFromFile(str[1 + 3 * i]);
	}

	snapshotIndex = 0;
}
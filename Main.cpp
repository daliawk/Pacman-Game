#include"Screen.h"
#include<sstream>

bool runLevel(Screen&, Player&, RenderWindow&, Event&, char&);
Text FinalText;
Player pacman("pacman", 15, 8, "pacman.png");
Ghost ghosts[4];
Clock timerP, timerG, fruitTimer, freightTimer;
vector<RectangleShape> lives;
Texture liveTexture;
string gender;
pair<bool, bool> s;
bool freight =0,cong=1;
fstream playersData;
vector<pair<string, int>> players;
pair<string, int> myPlayer; //the player who is playing
vector<Text> playerText;
bool flag = 0; //to get the data to the Text vector 1 time


bool sortbysec(const pair<string, int>& a,
	const pair<string, int>& b)
{
	return (a.second > b.second);
}

//SoundBuffer buffer;
//Sound sound;
int main()
{
	RenderWindow window;
	/*buffer.loadFromFile("pacman_beginning.wav");
	sound.setBuffer(buffer);
	sound.play();*/
	Font font;
	font.loadFromFile("aerial.ttf");
	Text temp;
	Text Ready; Ready.setString("Ready!");
	Ready.setPosition(Vector2f(55 + 7 * 32, 62 + 11 * 32));
	Ready.setCharacterSize(28);
	Ready.setFillColor(Color::White);
	Ready.setFont(font);
	FinalText.setCharacterSize(60);
	FinalText.setPosition(Vector2f(70, 70 + 10 * 32));
	FinalText.setFillColor(Color::White); FinalText.setFont(font);
	Text choosePlayer;
	choosePlayer.setString("1) New Player OR 2) Existing Player ?");
	choosePlayer.setPosition(Vector2f(55 + 2 * 32, 62 + 11 * 32));
	choosePlayer.setCharacterSize(23);
	choosePlayer.setFillColor(Color::White);
	choosePlayer.setFont(font);
	Text newPlayer;
	string newP = "Enter a name: ";
	newPlayer.setString(newP);
	newPlayer.setPosition(Vector2f(55 + 2 * 32, 62 + 11 * 32));
	newPlayer.setCharacterSize(23);
	newPlayer.setFillColor(Color::White);
	newPlayer.setFont(font);
	Text chooseAvatar;
	chooseAvatar.setString("1) Pacman OR 2) Ms Pacman ?");
	chooseAvatar.setPosition(Vector2f(55 + 2 * 32, 62 + 11 * 32));
	chooseAvatar.setCharacterSize(23);
	chooseAvatar.setFillColor(Color::White);
	chooseAvatar.setFont(font);
	Text chooseLevel;
	chooseLevel.setString("1)Easy  2)Medium  3)Hard");
	chooseLevel.setPosition(Vector2f(55 + 2 * 32, 62 + 11 * 32));
	chooseLevel.setCharacterSize(23);
	chooseLevel.setFillColor(Color::White);
	chooseLevel.setFont(font);
	window.create(VideoMode(800, 800), "Maze");


	ghosts[0].setGhost("blinky", 7, 8, "blinky.png", "blinky2.png", "blinky3.png", true, true);//setting Blinky above the ghost house and prepared to move at the beginning of the game
	ghosts[1].setGhost("pinky", 9, 8, "pinky.png", "pinky2.png", "pinky3.png", true, true);//setting Pinky int the middle of the ghost house and prepared to move at the beginning of the game
	ghosts[2].setGhost("inky", 9, 7, "inky.png", "inky2.png", "inky3.png", false, false);//setting Inky in the left of the ghost house and wouldn't start moving at the beginning of the game
	ghosts[3].setGhost("clyde", 9, 9, "clyde.png", "clyde2.png", "clyde3.png", false, false);//setting Clyde in the left of the ghost house and wouldn't start moving at the beginning of the game

	pacman.addSnapshots("pacman.png", "pacman2.png", "pacman3.png");

	liveTexture.loadFromFile("pacman.png");
	lives.resize(3);
	for (int i = 0; i < 3; i++)
	{
		lives[i].setPosition(64 + 32 * i, 64 + 32 * 21);
		lives[i].setSize(Vector2f(32, 32));
		lives[i].setTexture(&liveTexture);
	}


	Screen myScreen(pacman, ghosts);

	Event e;

	char movement = ' ';

	bool gameOn = false;//If the game is working
	bool avatarChosen = false;//If the player has chosen which avatar to play with
	bool isLevelChosen = false;
	bool playerChosen = false;
	int eva = 0;

	playersData.open("players.txt");
	if (playersData.fail())
	{
		cout << "Couldn't retrieve doctors data\n";
		exit(1);
	}
	string str;  int score; //name & score of player
	stringstream ss;

	while (!playersData.eof())
	{
		getline(playersData, str);
		ss.clear();
		ss = stringstream(str);
		str.clear();
		while (ss >> str && ss>>score)
		{
			players.push_back(make_pair(str, score));
			str.clear();
		}
	}
	playersData.close();
	sort(players.begin(), players.begin() + players.size(), sortbysec);
	//cout << "players size is " << players.size() << endl;
	while (window.isOpen())
	{
		while (!eva)
		{
			while (window.pollEvent(e))
				if (e.type == Event::Closed)
					window.close();

				else if (e.type == Event::KeyPressed)
					if (e.key.code == Keyboard::Numpad1 || e.key.code == Keyboard::Num1)
						eva = 1;
					else if (e.key.code == Keyboard::Num2 || e.key.code == Keyboard::Numpad2)
						eva = 2;
					
				
			for (int i = 0; i < 4; i++)
				ghosts[i].updateAnimation();
			pacman.updateAnimation();

			window.clear();
			myScreen.drawAll(window);

			window.draw(choosePlayer);
			
			window.display();
		}
		while (!playerChosen && eva==1)
		{
			while (window.pollEvent(e))
				if (e.type == Event::Closed)
					window.close();
				else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter)
				{
					playerChosen = 1;
					myPlayer.first = str;
					myPlayer.second = 0;
					if (players.size() >= 5)
						players[4] = myPlayer;
					else
						players.push_back(myPlayer);
					myScreen.setHighScore(0);
				}
				else if (e.type == sf::Event::TextEntered)
				{
					//cout << "Text\n";
					if (e.text.unicode < 128)
						str += (char)e.text.unicode;
					newP += (char)e.text.unicode;
					newPlayer.setString(newP);
				}
				//else
					//playerChosen = 1;
			for (int i = 0; i < 4; i++)
				ghosts[i].updateAnimation();
			pacman.updateAnimation();

			window.clear();
			myScreen.drawAll(window);

			window.draw(newPlayer); //cout << str << endl;

			window.display();
		}

		while (!playerChosen && eva == 2)
		{
			//cout << "Here\n";
			if (!flag)
			{
				for (int i = 0; i < players.size(); i++)
				{
					str.clear();
					str += to_string(i+1);
					str += ' ';
					str += players[i].first;
					//str += ' ';
					//str += to_string(players[i].second);
					temp.setString(str);
					temp.setPosition(Vector2f(100 + 2 * 32, 62 + (11+i) * 32));
					temp.setCharacterSize(23);
					temp.setFillColor(Color::White);
					temp.setFont(font);
					playerText.push_back(temp);
				}
				flag = 1;
			}

			while (window.pollEvent(e))
				if (e.type == Event::Closed)
					window.close();
				else if (e.type == Event::KeyPressed)
				{
					if ((e.key.code == Keyboard::Num1 || e.key.code == Keyboard::Numpad1) && players.size() >= 1) {
						myPlayer = players[0];
						myScreen.setHighScore(players[0].second);
						playerChosen = 1;
					}
					else if ((e.key.code == Keyboard::Num2 || e.key.code == Keyboard::Numpad2) && players.size() >= 2) {
						myPlayer = players[1];
						myScreen.setHighScore(players[1].second);
						playerChosen = 1;
					}
					else if ((e.key.code == Keyboard::Num3 || e.key.code == Keyboard::Numpad3) && players.size() >= 3) {
						myPlayer = players[2];
						myScreen.setHighScore(players[2].second);
						playerChosen = 1;
					}
					else if ((e.key.code == Keyboard::Num4 || e.key.code == Keyboard::Numpad4) && players.size() >= 4) {
						myPlayer = players[3];
						myScreen.setHighScore(players[3].second);
						playerChosen = 1;
					}
					else if ((e.key.code == Keyboard::Num5 || e.key.code == Keyboard::Numpad5) && players.size()>=5) {
						myPlayer = players[4];
						myScreen.setHighScore(players[4].second);
						playerChosen = 1;
					}
				}

			for (int i = 0; i < 4; i++)
				ghosts[i].updateAnimation();
			pacman.updateAnimation();

			window.clear();
			myScreen.drawAll(window);
			for (int i = 0; i < playerText.size(); i++)
				window.draw(playerText[i]);
			window.display();
		}


		while (!gameOn) {
			while (window.pollEvent(e))
				if (e.type == Event::Closed)
					window.close();
				else if (e.type == Event::KeyPressed)
					
					if (!avatarChosen) 
					{
						if (e.key.code == Keyboard::Numpad1 || e.key.code == Keyboard::Num1)
						{
							gender = "man";
							pacman.setImage("pacman.png");
							pacman.addSnapshots("pacman.png", "pacman2.png", "pacman3.png");
							avatarChosen = true;
						}
						else if (e.key.code == Keyboard::Num2 || e.key.code == Keyboard::Numpad2)
						{
							gender = "girl";
							pacman.setImage("mspacman.png");
							pacman.addSnapshots("mspacman.png", "mspacman2.png", "mspacman3.png");
							avatarChosen = true;
						}
					}
					else if (!isLevelChosen) {
						if (e.key.code == Keyboard::Num1 || e.key.code == Keyboard::Numpad1) {
							myScreen.setLevel(1);
							isLevelChosen = true;
						}
						else if (e.key.code == Keyboard::Num2 || e.key.code == Keyboard::Numpad2) {
							myScreen.setLevel(2);
							isLevelChosen = true;
						}
						else if (e.key.code == Keyboard::Num3 || e.key.code == Keyboard::Numpad3) {
							myScreen.setLevel(3);
							isLevelChosen = true;
						}
					}
					else if (e.key.code == Keyboard::Space)
						gameOn = true;
			for (int i = 0; i < 4; i++)
				ghosts[i].updateAnimation();
			pacman.updateAnimation();

			window.clear();
			myScreen.drawAll(window);

			if (!avatarChosen)
				window.draw(chooseAvatar);
			else if (!isLevelChosen)
				window.draw(chooseLevel);
			else
				window.draw(Ready);
			window.display();
		}

		while (gameOn) {
			gameOn = runLevel(myScreen, pacman, window, e, movement);
			pacman.updateAnimation();
			window.clear();
			myScreen.drawAll(window);


			if (!gameOn) {
				window.draw(FinalText);
				avatarChosen = false;
				isLevelChosen = false;
				pacman.restart();
				for (int i = 0; i < 4; i++)
					ghosts[i].restart();
			}
			for (int i = 0; i < lives.size(); i++)
				window.draw(lives[i]);
			window.display();
		}
	}

	return 0;
}

bool runLevel(Screen& myScreen, Player& pacman, RenderWindow& window, Event& e, char& movement) {
	while (window.pollEvent(e))
	{
		if (e.type == Event::Closed)
			window.close();
		else if (e.type == Event::KeyPressed)
		{

			switch (e.key.code)
			{
			case Keyboard::Up:
				movement = 'U';
				if (gender == "man") {
					pacman.addSnapshots("pacman-up.png", "pacman2-up.png", "pacman3-up.png");
					pacman.updateAnimation();
				}
				else {
					pacman.addSnapshots("mspacman-up.png", "mspacman2-up.png", "mspacman3-up.png");
					pacman.updateAnimation();
				}
				break;
			case Keyboard::Down:
				movement = 'D';
				if (gender == "man") {
					pacman.addSnapshots("pacman-down.png", "pacman2-down.png", "pacman3-down.png");
					pacman.updateAnimation();
				}
				else {
					pacman.addSnapshots("mspacman-down.png", "mspacman2-down.png", "mspacman3-down.png");
					pacman.updateAnimation();
				}
				break;
			case Keyboard::Right:
				movement = 'R';
				if (gender == "man") {
					pacman.addSnapshots("pacman.png", "pacman2.png", "pacman3.png");
					pacman.updateAnimation();
				}
				else {
					pacman.addSnapshots("mspacman.png", "mspacman2.png", "mspacman3.png");
					pacman.updateAnimation();
				}
				break;
			case Keyboard::Left:
				movement = 'L';
				if (gender == "man") {
					pacman.addSnapshots("pacman-left.png", "pacman2-left.png", "pacman3-left.png");
					pacman.updateAnimation();
				}
				else {
					pacman.addSnapshots("mspacman-left.png", "mspacman2-left.png", "mspacman3-left.png");
					pacman.updateAnimation();
				}
				break;
			}
		}
	}
	if (timerP.getElapsedTime().asMilliseconds() > 200) {

		s = myScreen.updatePac(movement);
		cong = s.first;
		
		if (cong)
		{
			/*buffer.loadFromFile("cong.wav");
			sound.setBuffer(buffer);
			sound.play();*/
			FinalText.setString("Congratulations");
			if (pacman.getScoreInt() > myPlayer.second)
			{
				myPlayer.second = pacman.getScoreInt();
				myScreen.setHighScore(myPlayer.second);
				for (int i = 0; i < players.size(); i++)
					if (players[i].first == myPlayer.first)
						players[i].second = myPlayer.second;
			}
			playersData.open("players.txt");
			for (int i = 0; i < players.size(); i++)
			{
				playersData << players[i].first << " " << to_string(players[i].second);
				if (i < players.size() - 1)
					playersData << endl;
			}
			return false;
		}
		if (s.second)
		{
			freight = 1;
			for (int i = 0; i < 4; i++)
				ghosts[i].freightMode();
		}
		if (myScreen.ghostCollision())
		{
			if (freight)
			{
				pacman.increaseScore(100);

			}
			else
			{
				if (!pacman.loseLive())
				{
					/*buffer.loadFromFile("pacman_death.wav");
					sound.setBuffer(buffer);
					sound.play();*/
					FinalText.setString("GameOver!!");
					if (pacman.getScoreInt() > myPlayer.second)
					{
						myPlayer.second = pacman.getScoreInt();
						myScreen.setHighScore(myPlayer.second);
						for (int i = 0; i < players.size(); i++)
							if (players[i].first == myPlayer.first)
								players[i].second = myPlayer.second;
					}
					playersData.open("players.txt");
					for (int i = 0; i < players.size(); i++)
					{
						playersData << players[i].first << " " << to_string(players[i].second);
						if (i < players.size() - 1)
							playersData << endl;
					}
					return false;
				}
				for (int i = 0; i < 4; i++)
					ghosts[i].restart();
			}
			
			movement = ' ';
		}
	

		timerP.restart();
	}
	if (timerG.getElapsedTime().asMilliseconds() > 500 - 80 * myScreen.getLevel()) {

		myScreen.updateGhosts(freight);
		if (freight)
		{
			if (freightTimer.getElapsedTime().asSeconds() > 7)
			{
				freight = 0;
				for (int i = 0; i < 4; i++)
					ghosts[i].unFreight();
			}

		}
		else
			freightTimer.restart();
		if (myScreen.ghostCollision())
		{
			if (freight)
			{
				pacman.increaseScore(100);
				
			}
			else
			{
				if (!pacman.loseLive())
				{
					/*buffer.loadFromFile("pacman_death.wav");
					sound.setBuffer(buffer);
					sound.play();*/
					FinalText.setString("GameOver!!");
					if (pacman.getScoreInt() > myPlayer.second)
					{
						myPlayer.second = pacman.getScoreInt();
						myScreen.setHighScore(myPlayer.second);
						for (int i = 0; i < players.size(); i++)
							if (players[i].first == myPlayer.first)
								players[i].second = myPlayer.second;
					}
					playersData.open("players.txt");
					for (int i = 0; i < players.size(); i++)
					{
						playersData << players[i].first << " " << to_string(players[i].second);
						if (i < players.size() - 1)
							playersData << endl;
					}
					return false;
				}
				for (int i = 0; i < 4; i++)
					ghosts[i].restart();
			}
			movement = ' ';
		}
		timerG.restart();
	}

	if (lives.size() != pacman.getLives())
	{
		lives.resize(pacman.getLives());
		for (int i = 0; i < lives.size(); i++)
		{
			lives[i].setPosition(64 + 32 * i, 64 + 32 * 22);
			lives[i].setSize(Vector2f(32, 32));
			lives[i].setTexture(&liveTexture);
		}
	}
	if (myScreen.isFruitAdded())
		fruitTimer.restart();
	else {
		if (fruitTimer.getElapsedTime().asSeconds() > 10 * myScreen.getLevel()) {
			myScreen.addFruit();
		}
	}


	return true;
}

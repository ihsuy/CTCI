#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

struct CD
{
	string title;
	string song;

	CD(const string& t, const string& s)
	:title(t), song(s){}
};

struct CDbox
{
	const int capacity = 65;

	list<CD> CDStack;

	vector<string> titles;

	list<CD>::iterator picker_hand;

	CDbox(const vector<CD>& CDs)
	{
		if(CDs.size()>capacity)
		{
			throw runtime_error("Too many CDs. CDbox can only hold up to " + to_string(capacity) + " CDs");
		}

		for(auto& CD : CDs)
		{
			CDStack.push_back(CD);

			titles.push_back(CD.title);
		}

		picker_hand = CDStack.begin();

	}

	vector<string> get_CDtitles()
	{
		return titles;
	}

	CD* pickCD(const int& CD_index)
	{
		// move picker hand to target CD position
		for(int mv = 0; mv < CD_index; ++mv)
		{
			if(not pickerHand_moveRight())
			{
				say("Couldn't find CD at " + to_string(CD_index) + "th slot");
				return nullptr;
			}
		}

		say("Picking up CD titled \"" + picker_hand->title + "\"");
		// pick up the CD
		CD* chosenCD = &(*picker_hand);

		// move picker hand back
		for(int mv = 0; mv < CD_index; ++mv)
		{
			pickerHand_moveLeft();
		}

		return chosenCD;
	}

	bool pickerHand_moveLeft()
	{
		say("picker hand is moving to the left...");

		if(picker_hand != CDStack.begin())
		{
			picker_hand--;

			return true;
		}
		else
		{
			say("Picker has reached the left most slot of the CDbox");

			return false;
		}
	}

	bool pickerHand_moveRight()
	{
		say("picker hand is moving to the right...");

		if(picker_hand != CDStack.end())
		{
			picker_hand++;

			return true;
		}
		else
		{
			say("Picker has reached the right most slot of the CDbox");
			// move picker back
			while(picker_hand != CDStack.begin())
			{
				pickerHand_moveLeft();
			}

			return false;
		}
	}

	void say(const string& msg)
	{
		cout << "CDbox: " << msg << endl;
	}
};

struct speaker
{
	string music;

	speaker(){}

	void play_music(CD* cd)
	{
		music = cd->song;
		cout << "speaker: " << music << "..." << endl;
	}
};

struct userInterface
{
	vector<string> titles;

	int money_box;

	bool paid;

	int userChoice;

	bool userReady;


	userInterface(const vector<string>& t): titles(t), money_box(0), paid(false), userChoice(0), userReady(false) {}

	void display_titles()
	{
		for(int i = 0; i < titles.size(); ++i)
		{
			cout << i << ". " << titles[i] << endl;
		}
	}

	void enterChoice()
	{
		if(not paid)
		{
			cout << "Please pay first." << endl;
		}
		else
		{
			cout << "Please enter the number of CD: ";
			cin >> userChoice;
			userReady = true;
		}
	}

	void insertCoin()
	{
		paid = true;
		money_box++;
	}

	void begin()
	{
		display_titles();

		cout << "Play your favorite song.\nInsert a coin?(y/n)" << endl;
		string inp;
		cin >> inp;

		if(inp == "y" or inp == "yes")
		{
			insertCoin();

			enterChoice();
		}
	}

	void end()
	{
		paid = false;
		userReady = false;
	}

	int get_choice()
	{
		return userChoice;
	}

	void say(const string& msg)
	{
		cout << "userInterface: " << msg << endl;
	}
	
};

struct jukebox
{

	speaker* spkr;
	CDbox* cdb;
	userInterface* ui;

	jukebox(const vector<CD>& CDs)
	: spkr(new speaker()), cdb(new CDbox(CDs)), ui(new userInterface(cdb->titles)){}

	void run()
	{
		while(true)
		{
			ui->begin();

			if(not ui->userReady)
			{
				ui->say("Thank you! See you next time!");
				continue;
			}

			CD* chosen_cd = cdb->pickCD(ui->userChoice);

			if(chosen_cd == nullptr)
			{
				ui->say("This CD doesn't exist.");
				continue;
			}

			spkr->play_music(chosen_cd);

			ui->say("Music is over. Thank you! See you next time!");

			ui->end();
		}
	}
};

int main()
{
	vector<CD> CDs
	{
		CD("Sign", "todoite kurerunokana"),
		CD("Hanabi", "mouikkai mouikkai"),
		CD("365days", "sanbyakurokujyugo nichi no"),
		CD("Tokyo", "toukyou wa atomodori shinai"),
		CD("Himawari", "kurayamini saiteiru himawari"),
		CD("Kimigasuki", "kimigasuki kimigasuki"),
		CD("Gitai", "asufaruto tobihaneru")
	};
	
	jukebox myjuke(CDs);
	myjuke.run();
	return 0;
}
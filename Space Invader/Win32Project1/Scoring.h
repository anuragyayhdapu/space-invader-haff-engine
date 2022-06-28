#pragma once
#include <fstream>
class Scoring
{
private:
	int highscore = 0;	// overall highscore
	int d_trav = 0;		// distance travelled
	double t_time = 0;	// total time
	int score = 0;		// curremt score

public:
	Scoring();
	~Scoring();

	int getHighScore() { return highscore; }
	int getScore() { return score; }
	int getDistanceTraveld() { return d_trav; }
	double getTotalTime() { return t_time; }

	void setScore(int);
	void setHighScore(int h) { highscore = h; }
	void setDistanceTraveld(int d) { d_trav = d; }
	void setTotalTime(double t) { t_time = t; }

	void WriteToFile();

};


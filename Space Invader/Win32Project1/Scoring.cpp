#include "Scoring.h"


Scoring::Scoring()
{
	// initialization, reading scores from file
	std::ifstream file;
	file.open("score.txt");
	file >> highscore >> d_trav;
	file.close();

	score = 0;
	t_time = 0;
}


Scoring::~Scoring()
{
}


void Scoring::WriteToFile()
{
	// write all score to the file before exiting
	std::ofstream file2;
	file2.open("score.txt");
	file2 << highscore << std::endl << d_trav;
	file2.close();
}

void Scoring::setScore(int s)
{
	score = s;

	if (highscore < score)
		setHighScore(score);
}
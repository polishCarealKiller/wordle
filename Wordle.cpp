#include <fstream>
#include <string>
#include <iostream>
#include "Wordle.h"
#include <stdlib.h>
#include <time.h>


int wordle::count_lines(std::fstream& f)
{
	int count = 0;
	if(f.is_open())
	{
		std::string tp;
		while(std::getline(f, tp))
			count++;
	}
	f.clear();
	f.seekg(0);
	return count;
}

std::string wordle::get_line(std::fstream& f, int l)
{
	int length = wordle::count_lines(f);
	if( l < 1 || l > length )
		throw std::length_error("get_line()");
	
	std::string result;
	for(int i = 0; i < l; i++)
		std::getline(f, result);
	f.clear();
	f.seekg(0);
	return result;
}

std::string wordle::get_random_word(std::fstream& f)
{
	int length = wordle::count_lines(f);
	std::srand(time(NULL));
	int i = std::rand() % length + 1;

	return wordle::get_line(f, i);
}

bool wordle::check_words(std::string correct, std::string toCheck) //!!! I assume the words are of equal length
{
	int l = correct.size();

	for(int j = 0; j < l; j++)
	{
		wordle::LetterState letterState = wordle::LetterState::DontExist;
		
		for(int i = 0; i < l; i++)
		{
			if(correct[i] == toCheck[j] && i == j)
			{
				letterState = wordle::LetterState::CorrectPlace;
				break;
			}	
			else if(correct[i] == toCheck[j])
			{
				letterState = wordle::LetterState::IncorrectPlace;
			}
		}	

		switch(letterState)
		{
			case wordle::LetterState::DontExist: std::cout << "\033[1;37;41m" << toCheck[j];break;
			case wordle::LetterState::CorrectPlace: std::cout << "\033[1;37;42m" << toCheck[j];break;
			case wordle::LetterState::IncorrectPlace: std::cout << "\033[1;37;46m" << toCheck[j];break;
		}
	}

	std::cout << "\033[0m\n";
	return correct == toCheck;
}

int wordle::search_line_of_word(std::fstream& f, std::string w)
{
	std::string b;
	int result = 0;
	int index = 1;
	while(std::getline(f,b))
	{
		if(b == w)
		{
			result = index;
			break;
		}	

		index++;

	}
	
	f.clear();
	f.seekg(0);

	return result;
}

bool wordle::word_validation(std::fstream& f, std::string w)
{
	if(w.size() != 5)
		return false;

	bool result = false;

	if(wordle::search_line_of_word(f, w) > 0)
		result = true;

	return result;

}


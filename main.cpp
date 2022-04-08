#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Wordle.h"


void win();

int main()
{
	std::fstream dictionary;
	dictionary.open("dictionary.txt", std::ios::in);
	
	if(dictionary.is_open())
	{
		bool wined = false;
		std::string randomWord = wordle::get_random_word(dictionary);
		std::string answear;

		std::cout << "Guess word (You have 5 attempts)" << std::endl;
		for(int i = 0; i < 5; i++)
		{	
			std::cin >> answear;	
			
			if(!wordle::word_validation(dictionary, answear))
			{
				std::cout << "\7";
				i--;
				continue;
			}

			if(wordle::check_words(randomWord, answear))
			{
				wined = true;
				win();
				break;
			}

			std::cout << "\7";
		}

		if(!wined)
		{
			std::cout << "Correct word: " << randomWord << std::endl;
		}

		dictionary.close();
	}

	return 0;
}


void win()
{
	std::cout << "Wow! 🎉 Congratulate🎉 \n";
}

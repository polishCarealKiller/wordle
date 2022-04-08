#include <fstream>
#include <string>

namespace wordle
{
	enum class LetterState
	{
		DontExist, CorrectPlace, IncorrectPlace
	};

	int count_lines(std::fstream& f);

	std::string get_line(std::fstream& f, int l);

	std::string get_random_word(std::fstream& f);

	bool check_words(std::string correct, std::string toCheck); //!!! I assume the words are of equal length

	int search_line_of_word(std::fstream& f, std::string w);

	bool word_validation(std::fstream& f, std::string w);
}

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

void constructRandomWords(std::vector<std::string> &words, int numOfWords)
{
	for(int i = 0; i < numOfWords; i++)
	{
		std::string randomWord;
		int len = rand() % (16 - 2) + 2; // [2, 16) = [2, 15] length
		for(int j = 0; j < len; j++){
			randomWord = randomWord + (char)(rand() % (123 - 97) + 97); // [97, 123) = [97, 122] small letters
		}
		//std::cout << i+1 << ". word: " << randomWord << '\n';
		words.push_back(randomWord);
	}
}


void setRatings(std::vector<std::string> &words, std::vector<float> &ratings, std::vector<std::string> &queryVect, std::string query) // from 0 - 1
{
	for(int i = 0; i < words.size(); ++i) // gre cez use rezultate
	{
		int matchNow = 0, numLettersSource = (words.at(i)).size();
		float totalMatch = 0, rating = 0.0;
		if (query == words.at(i))	ratings.push_back(1.0);
		else
		{
			for(int j = 0; j < queryVect.size(); ++j)
			{
			    for(int k = 0; k < (words.at(i)).size() && k < (queryVect.at(j)).size(); ++k)
                {
                    if((queryVect.at(j))[k] == (words.at(i))[k]) ++totalMatch;
                    else if(((queryVect.at(j))[k] >= 'A' && (queryVect.at(j))[k] <= 'Z') && ((queryVect.at(j))[k] + 32 == (words.at(i))[k])) totalMatch += 0.5;
                    else if(((queryVect.at(j))[k] >= 'a' && (queryVect.at(j))[k] <= 'z') && ((queryVect.at(j))[k] - 32 == (words.at(i))[k])) totalMatch += 0.5;
                }
			}
			rating = totalMatch / numLettersSource;
			ratings.push_back(rating);
		}
	}
}

void printRatings(std::vector<float> &ratings, std::vector<std::string> &words)
{
    for(int i = 0; i < ratings.size(); ++i)
        std::cout << words.at(i) << ' ' << ratings.at(i) << '\n';
    std::cout << '\n';
}

void printWords(std::vector<std::string> &words)
{
	for(int i = 0; i < words.size(); i++)
		std::cout << "Word " << i << ": " << words.at(i) << '\n';
}

int main()
{
	srand(time(NULL));
	std::vector<std::string> words;
	std::vector<float> ratings;
	std::vector<std::string> queryVect;
	std::string query, temp;
	constructRandomWords(words, 10);
	printWords(words);
	std::cout << "Just search M8: ";
	getline(std::cin, query);
	std::stringstream ss(query);

    while(ss >> temp)   queryVect.push_back(temp); // razcleni query
	setRatings(words, ratings, queryVect, query);
	printRatings(ratings, words);
	return 0;
}
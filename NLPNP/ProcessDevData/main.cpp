// author:buptlijun

// output queries without keywords into a file

/// divide the original dev data to specific domains
/// consider only the first 5 columns
/// 0    1     2      3      4
/// ID query domain intent slot
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int main(void)
{
	string indomainFile = "../data/indomain_dev.tsv";
	string noWeatherQueriesFile = "../data/noKeyWordsQueries.txt";
	vector<string> keyWords = { "weather", "temperature", "forecast", "how hot", "how cold", "how warm" , "snow", "wind", "rain"};
	ifstream ifIn(indomainFile);
	ofstream ofNoWeather(noWeatherQueriesFile);
	string line;
	while (getline(ifIn, line))
	{
		int index;
		vector<string> vec;
		while (vec.size() < 5)
		{
			index = line.find_first_of('\t');
			vec.push_back(line.substr(0, index));
			line = line.substr(index + 1);
		}

		// extract the first 5 colums into a vector<string>
		string query = vec[1];

		bool findFlag = false;
		for (auto s : keyWords)
		{
			if (query.find(s) != string::npos)
			{
				findFlag = true;
				break;
			}
		}
		if (!findFlag)
			ofNoWeather << query << endl;
	}
	ifIn.close();
	ofNoWeather.close();
}
/// Extract query-domain from QEP Grep file

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void extractFile(string QEPGrepFile, string queryDomainFile)
{
	ifstream qepIn(QEPGrepFile);
	ofstream queryDomainOut(queryDomainFile);

	if (!qepIn)
	{
		cout << QEPGrepFile << ", File not exist" << endl;
		return;
	}
	long long totalNum = 0;
	long long posNum = 0;
	string line;
	while (getline(qepIn, line))
	{
		if (line.find("Query: {") != string::npos)
		{
			int sIndex = line.find("{");
			int eIndex = line.find("}");
			string query = line.substr(sIndex + 1, eIndex - sIndex - 1);
			queryDomainOut << query << "\t";
		}
		if (line.find("QAS Domains   = [") != string::npos)
		{
			string domain = "-1";
			if (line.find("Weather") != string::npos)
			{
				domain = "+1";
				posNum++;
			}
			totalNum++;
			queryDomainOut << domain << endl;
		}
	}

	qepIn.close();
	queryDomainOut.close();
	cout << "total: " << totalNum << endl;
	cout << "positive: " << posNum << endl;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Usage:" << endl;
		cout << "ExtractFromQEPGrep.exe QEPGrepFile queryDomainFile" << endl;
		return 0;
	}
	string QEPGrepFile = argv[1];
	string queryDomainFile = argv[2];
	extractFile(QEPGrepFile, queryDomainFile);
	return 0;
}
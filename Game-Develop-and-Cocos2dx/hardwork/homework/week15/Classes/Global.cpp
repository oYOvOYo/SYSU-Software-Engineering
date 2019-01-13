#include "Global.h"

#include <regex>
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;

string Global::gameSessionId = "";
long Global::score = 0;

Global::Global()
{
}

Global::~Global()
{
}

string Global::vectorChar2String(vector<char> *buffer) {
	string rst;
	for (char ch : *buffer) {
		rst.push_back(ch);
	}
	return rst;
}

string Global::getSessionIdFromHeader(string head) {
	regex nlp("\\r\\n");
	string header = regex_replace(head, nlp, " ");
	regex pattern(".*GAMESESSIONID=(.*) Content-Type.*");
	//match_results<std::string::const_iterator> result;
	cmatch result;
	bool valid = regex_match(header.c_str(), result, pattern);

	if (!valid) {
		return "";
	}
	return result[1];
}
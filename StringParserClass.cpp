/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>

#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;
using namespace KP_StringParserClass;

char *pStartTag;
char *pEndTag;
bool areTagsSet;

StringParserClass::StringParserClass(void) {
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

StringParserClass::~StringParserClass(void) {
	cleanup();
}

int StringParserClass::setTags(const char *pStart, const char *pEnd) {

	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}

	int start = strlen(pStart);
	pStartTag = (new char(start +1));
	int end = strlen(pEnd);
	pEndTag = (new char(end + 1));

	strncpy(pStartTag, pStart, start);
	strncpy(pEndTag, pEnd, end);

	areTagsSet = true;
	return SUCCESS;

}

int StringParserClass::getDataBetweenTags(char *pDataToSearchThru,
		std::vector<std::string> &myVector) {

	myVector.clear();

	if (pStartTag == NULL || pEndTag == NULL || areTagsSet == false) {
		return ERROR_TAGS_NULL;
	} else if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}

	char* data;
	int num;
	while (findTag(pStartTag, pDataToSearchThru, data) == SUCCESS) {

		num = findTag(pStartTag, pDataToSearchThru, data);
		pDataToSearchThru = *(&data);
		string s;
		char *pEnd;
		char* pStart = *(&data);
		char *pNStart = 0;
		char *pNEnd = 0;

		if (num == SUCCESS) {
			pNStart = pDataToSearchThru;
			pStart = pNStart;

			num = findTag(pEndTag, pStart, pEnd);
			switch(num) {
			case SUCCESS:
				pNEnd = pStart;
				s.assign(pNStart, *(&pNEnd) - pNStart);
				myVector.push_back(s);
				pStart = pEnd;
				pDataToSearchThru = pEnd;
				break;
			}
		}
	}

	return SUCCESS;
}

void StringParserClass::cleanup() {
	if (pStartTag) {
		delete[] pStartTag;
	}
	if (pEndTag) {
		delete[] pEndTag;
	}
	areTagsSet = false;
}

int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
		char *&pEnd) {

	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}

	int x = strlen(pTagToLookFor);
	int i = 0;
	while (pStart[i] != 0) {
		bool b = true;

		if (pStart[i] == '<') {
			for (int j = 0; j < x; j++) {
				if (pEnd[i + j] != pTagToLookFor[j]) {
					b = false;
				}
			}
			if (b == true) {
				*pStart = pStart[i];
				*pEnd = pStart[i + x];
				return SUCCESS;
			}
		}
		i++;
	}
	return FAIL;
}









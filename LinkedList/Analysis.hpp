#pragma once
#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <string>
#include "ReviewLL.hpp"

using namespace std;

namespace Analysis {
	void sentimentSummary(ReviewList& list); //summary based on sentiment score
	void summary(ReviewList& list, WordList& good, WordList& bad); //summary
}



#endif
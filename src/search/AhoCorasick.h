//
//  aho-corasick.hpp
//  PCC
//
//  Created by Rafael Nunes G. da Silveira on 23/10/2015.
//  Copyright © 2015 Rafael Nunes. All rights reserved.
//

#ifndef AhoCorasick_h
#define AhoCorasick_h

#include <vector>
#include <unordered_map>
#include "OccurrenceList.h"
#include "ExactSearchStrategy.h"
#include "Occurrence.h"
#include "../input/FileReader.h"

class AhoCorasick : public ExactSearchStrategy{
public:
	AhoCorasick();
	virtual ~AhoCorasick();
	virtual std::vector<OccurrenceMultiplePatterns> search(std::string text, std::vector<std::string> patterns);
private:
	Node* build_fail(Node* firstNode);
	Node* build_goto(std::vector<std::string> patterns);
};

class Node {
    
public:
    Node *fail;
    OccurrenceList ocurrencies;
    std::unordered_map<char , Node*> transitions;
    
    Node();
};

#endif /* AhoCorasick_h */

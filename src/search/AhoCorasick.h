//
//  aho-corasick.hpp
//  PCC
//
//  Created by Rafael Nunes G. da Silveira on 23/10/2015.
//  Copyright © 2015 Rafael Nunes. All rights reserved.
//

#ifndef aho_corasick_hpp
#define aho_corasick_hpp

#include <vector>
#include <unordered_map>
#include "OccurrenceList.h"

// Considera-se o alfabeto o conjunto de valores da tabela ASCII
class Node {

public:
    Node *fail;
    OccurrenceList ocurrencies;
    std::unordered_map<char , Node*> transitions;

    Node();
};

#endif /* aho_corasick_hpp */

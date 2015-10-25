//
//  aho-corasick.cpp
//  PCC
//
//  Created by Rafael Nunes G. da Silveira on 23/10/2015.
//  Copyright © 2015 Rafael Nunes. All rights reserved.
//

#include "AhoCorasick.h"
#include "Occurrence.h"
#include <string>
#include <vector>
#include <queue>

using namespace std;

AhoCorasick::AhoCorasick() { 
}

AhoCorasick::~AhoCorasick() {
}

Node::Node(){
}

Node* AhoCorasick::build_goto(vector<string> patterns){
    Node *firstNode = new Node();
    Node *currentNode; // sail with it
    
    int j; // index
    int m; // pattern length
    char currentChar;// current char of the pattern
    int next = 0; // node id counter
    
    unordered_map<char, Node*>::const_iterator iterator; // auxiliar iterator
    std::pair<char, Node*> newTransition; // new transition
    
    for (int k = 0; k < patterns.size(); k++) {
        currentNode = firstNode;
        j = 0;
        m = patterns[k].size();
        
        currentChar = patterns[k].at(j);
        
        while ((j < m) && ((iterator = currentNode->transitions.find(currentChar)) != currentNode->transitions.end()))
        {
            currentNode = iterator->second;
            j++;
            currentChar = patterns[k].at(j);
        }
        
        while (j < m)
        {
            next++;
            newTransition = make_pair(currentChar, new Node()); // create the new transition
            currentNode->transitions.insert(newTransition); // add the transition to the currentNode map of transitions
            currentNode = newTransition.second; // update the currentNode
            j++;
            currentChar = patterns[k].at(j);
        }
        
        currentNode->ocurrencies.push_front(patterns[k]); // Add to this node its ocurrencies
    }
    
    // Adding empty transitions for all chars that are not in the patterns
    for (int i = 0 ; i < 256; i++) {
        if ((iterator = firstNode->transitions.find((char)i)) != firstNode->transitions.end()) {
            newTransition = make_pair((char)i, firstNode);
            firstNode->transitions.insert(newTransition);
        }
    }
    
    return firstNode;
}

Node* AhoCorasick::build_fail(Node* firstNode){
    queue<Node*> auxQueue;
    
    unordered_map<char, Node*>::const_iterator iterator; // auxiliar iterator
    std::pair<char, Node*> newTransition; // new transition
    
    for (int i = 0; i < 256; i++) {
        if ((iterator = firstNode->transitions.find((char)i)) != firstNode->transitions.end()) {
            if (firstNode != iterator->second){ // If its not the firstNode we enqueue
                auxQueue.push(iterator->second);
                iterator->second->fail = firstNode;
            }
        }
    }
    
    Node *currentNode;
    Node *nextNode;
    Node *failNode;
    
    while (auxQueue.size()){
        currentNode = auxQueue.front();
        auxQueue.pop();
        
        for (int i = 0; i < 256; i++) {
            if ((iterator = currentNode->transitions.find((char)i)) != currentNode->transitions.end()){
                nextNode = iterator->second;
                auxQueue.push(nextNode);
                
                failNode = currentNode->fail;
                
                while ((iterator = failNode->transitions.find((char)i)) == failNode->transitions.end()) {
                    failNode = iterator->second->fail;
                }
                
                nextNode->fail = iterator->second->transitions.at((char)i);
                
                nextNode->ocurrencies.push_back(&nextNode->fail->ocurrencies);
            }
        }
    }
    return firstNode;
}

vector<OccurrenceMultiplePatterns> AhoCorasick::search(string text, vector<string> patterns){
    
    //Build goto and fail for the automata
    Node *firstNode = build_goto(patterns);
    build_fail(firstNode);
    
    unordered_map<char, Node*>::const_iterator iterator; // auxiliar iterator
    
    Node *currentNode = firstNode;
    
    vector<OccurrenceMultiplePatterns> occurrenciesReturn;
    
    //search
    for (int i = 0 ; i < text.size(); i++) {
        
        while ((iterator = currentNode->transitions.find(text[i])) == currentNode->transitions.end()) {
            currentNode = currentNode->fail;
        }
        
        currentNode = iterator->second;
        
        OccurrenceListNode *currentOcc = currentNode->ocurrencies.head;
        
        while (currentOcc!=NULL) {
            occurrenciesReturn.push_back(OccurrenceMultiplePatterns(0, (i - currentOcc->occurrence.size() + 1), currentOcc->occurrence));
        }
    }
    
    return occurrenciesReturn;
    
}

int main(int argc, const char * argv[]) {
    return 0;
}

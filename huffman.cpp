#include <string>
#include <cstdlib>
#include <queue>
#include <map>
#include <iostream>
#include <iomanip> 
#include "huffman.h"

HuffmanNode::HuffmanNode(char c, int freq)
{
    this->c = c;
    this->freq = freq;
    this->left = nullptr;
    this->right = nullptr;
    this->root = nullptr;
}

std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNode::Compare>*
HuffmanNode::__freq_queue(std::string str)
{
    auto* freq_queue = new std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNode::Compare>;
    std::map<char, int> freq_map;
    for(auto it=str.begin();it!=str.end();it++) {
        if( freq_map.find(*it) != freq_map.end() ) {
            freq_map[*it] = freq_map[*it] + 1;
        } else {
            freq_map[*it] = 1;
        }
    }

    for(auto it=freq_map.begin();it!=freq_map.end();it++) {
        HuffmanNode* node = new HuffmanNode(it->first, it->second);
        freq_queue->push(node);
    }

    return freq_queue;
}

HuffmanNode::HuffmanNode(std::string str)
{
    left = nullptr;
    right = nullptr;
    auto* freq_queue = __freq_queue(str);
    HuffmanNode* root;
    while( freq_queue->size() > 1 ) {
        HuffmanNode* n1 = freq_queue->top();
        freq_queue->pop();
        HuffmanNode* n2 = freq_queue->top();
        freq_queue->pop();
        
        // new HuffmanNode
        char key = n1->c + n2->c;
        int value = n1->freq + n2->freq;
        root = new HuffmanNode(key, value);
        root->left = n1;
        root->right = n2;

        // reverse reference
        n1->root = root;
        n2->root = root;

        freq_queue->push(root);
    }
    this->root = root;
}

void HuffmanNode::print(HuffmanNode* p, int indent)
{
    if(p != NULL) {
        if(p->right) {
            print(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<< "(" << p->c << ", " << p->freq << ")" << "\n ";
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            print(p->left, indent+4);
        }
    }
}

int main() {
    HuffmanNode x("xxxxxyyyyzzzwwi");
    HuffmanNode* ref = x.root;
    x.print(ref, 0);
}
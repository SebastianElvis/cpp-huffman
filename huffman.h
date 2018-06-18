#include <queue>
#include <vector>
#include <string>


class HuffmanNode {    

public:
    char c;
    int freq;
    HuffmanNode* root;
    HuffmanNode* left;
    HuffmanNode* right;

    class Compare {
    public:
        bool operator()(HuffmanNode *a, HuffmanNode *b) {
            return a->freq < b->freq;
        }
    };

    HuffmanNode(std::string str);
    HuffmanNode(char c, int freq);
    void print(HuffmanNode* p, int indent);
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNode::Compare>* __freq_queue(std::string str);
};

std::string huffman_encode(std::string str);
std::string huffman_decode(std::string str);
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//Use cplusplus.com as refernce for priority_queue structure.
struct HuffmanCode{
	//For printing final paths for decoding.
	struct huffChar{
		char id;
		string code;
		huffChar(char id, string code): id(id),code(code){}
	};
	//Huffman node struct.
	struct huffNode{
		char data;
		int freq;
		huffNode* left = NULL, *right = NULL;
		huffNode(){}
		huffNode(int freq) : data('\0'),freq(freq){}
		huffNode(char data, int freq) : data(data),freq(freq){}
		~huffNode(){delete left;delete right;}
	};
	//Using templates, I can keep my priority_queue sorted from least to greatest. Learned in CSE 165.
	//We compare frequencies.
	struct min{
		//for huffman Nodes:
		bool operator()(huffNode* n1, huffNode* n2){
			return (n1->freq > n2->freq);
		}
		//for huffman Char:
		bool operator()(huffChar n1, huffChar n2){
			return ((int)(n1.id) > (int)(n2.id));
		}
	};
	//Use print using depth-first.
	void prnt(huffNode* root, string str, priority_queue<huffChar,vector<huffChar>,min> &output){
		if(root == NULL)
			return;
		if(root->data != '\0'){
			huffChar temp(root->data, str);
			output.push(temp);
		} 
		prnt(root->left, str + "0",output);
		prnt(root->right, str + "1",output);
	}
	//Huffman struct begins.
	//Reference to main node.
	huffNode* root;
	HuffmanCode() {}
	void decode(int* data, int* freq){
		priority_queue<huffNode*,vector<huffNode*>, min> list;
		for(int i = 0; i < 6; ++i)
			list.push(new huffNode(data[i], freq[i]));
		while(list.size() != 1){
			huffNode *left = list.top();
			list.pop();
			huffNode *right = list.top();
			list.pop();
			root = new huffNode(left->freq + right->freq);
			root->left  = left;
			root->right = right;
			list.push(root);
		}
		//Need to create a huffVar vector to sort the output of huffman chars and freq
		priority_queue<huffChar,vector<huffChar>,min> output;
		prnt(list.top(), "",output);
		while(!output.empty()){
			cout << (output.top()).id << ":" << (output.top()).code << endl;
			output.pop();
		}
	}
	~HuffmanCode(){delete root;}
};
int main(){
	HuffmanCode data;
	int* id = new int[6]; int *freq = new int[6];
	for(int i = 0; i < 6; i++){
		int num;
		cin >> num;
		freq[i] = num;
		id[i] = ((char)(65+i));
	}
	data.decode(id, freq);
	delete id;
	delete freq;
	return 0;
 }
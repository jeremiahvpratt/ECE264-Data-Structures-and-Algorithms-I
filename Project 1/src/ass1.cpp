/*
Jeremiah Pratt
Program develops stack and queue data structures from scratch, implementing singly linked lists also created from scratch
Program also parses an input text file of commands to demonstrate functionality

due 4/5/2017 before midnight

Note: didn't take code from these people, just theory suggestions and debugging help

CITATIONS: Chris Watkins, Chris Curro, both who helped me debug and walked me through concepts of templates and class inheritance in c++.

It is currently 11:26pm the night the assignment is due, so here's a "TO DO" list to make my code better:
	
	-Define class functions separately to reduce clutter
	-Define classes and functions in separate files to make navigating code easier
	-Create separate error checking functions to reduce clutter in checking for already existent, nonexistent, or empty SimpleLists

	I hope you enjoy reading this code as much as I enjoyed writing it. You can take that however you want.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
//#include <stdlib>
using namespace std;


//Base class for data structures to be implemented later
//Implements shared functionality between Stacks and Queues
//Written as template to accomodate all possible data types

template <class s_type> class SimpleList{
		
	private:
		
		//Nested class defining each "node" in a list
		//Stores piece of data and points to next piece	
		class Node {

                	public:
                        	s_type data;
                        	Node *data_next;
				Node (s_type dat, Node *next) : data(dat), data_next(next)
					{}

        	};
		Node* start_list;					//Pointer to beginning of list
		Node* end_list;						//Pointer to end of list
		string name;						//Name of list
	
	public:

                virtual void push(s_type d) = 0;                        //Push a new Node to top of the stack
                virtual s_type pop() = 0;	                        //Retrieve and remove node from stack
						
                SimpleList(string n) : name(n), end_list(nullptr), start_list(nullptr)
                        {}

                string getName() {                                      //Fcn. for retrieving name

                        return name;

                }

                Node* getStart() {					//Fcn. for retrieving pointer to start of list

                        return start_list;

                }

	protected:
		void makeNodeStart(s_type d) {				//Insert a node at the start of a list
			
			Node *start = new Node(d, this -> start_list);
			this -> start_list = start;
			
			if(end_list == nullptr){
							end_list = start;
			
			}
			
		}
		void makeNodeEnd(s_type d) {				//Insert a node at the end of a list
			
			Node *end = new Node(d, nullptr);
			
			if(end_list != nullptr){
	
				end_list -> data_next = end;

			}

			end_list = end;
			
			if(start_list == nullptr){
				
				start_list = end;
				
			}
		
		}	
		s_type deleteNode() {				  	//Delete first node
			
			Node* temp = start_list;
			if((start_list -> data_next == nullptr) || (start_list == nullptr)){
				
				start_list = nullptr;
				end_list = nullptr;
				
			}
			else{
				
				start_list = start_list -> data_next;
				
			}
			
			s_type dat = temp -> data;
			delete temp;
			return dat;
		}
	
};


//Implementation of stack data structure using SimpleList
template<class s_type>
class Stack : public SimpleList<s_type>{
	public:
	
		Stack(string n) : SimpleList<s_type>(n)
			{}		
		
		void push(s_type d) {					//Push data to start of stack
			
			this->makeNodeStart(d);
		}
		
		s_type pop() {						//Remove and return first data in stack
			
			return this -> deleteNode();
			
		}
};


//Implementation of queue data structure using SimpleList
template<class s_type>
class Queue : public SimpleList<s_type> {
	public:
		
		Queue(string n) : SimpleList<s_type>(n)
			{}
		
		void push(s_type d) {					//Push data to end of queue
			
			this -> makeNodeEnd(d);
			
		}
		
		s_type pop() {						//Remove and return first data in queue
			
			return this -> deleteNode();
			
		}
};


//Linear search for name in lists of stacks of a given type
template<class s_type>
typename list<SimpleList<s_type>*>::iterator searchList(string w, list<SimpleList<s_type> *> & listSL){

	for(typename list<SimpleList<s_type> *>::iterator ci = listSL.begin(); ci != listSL.end(); ++ci){
		
		if(((*ci) -> getName()) == w){

			return ci;
		
		}
		
	}
	return listSL.end();
	
}


//Parsing input file line by line, using conditionals to check each word of the input command line
//NOTE: checking for data type first may allow for code condensing, with more time this could be implemented
void parseItAll(string inFile, string outFile){
	
	string currentLine;
	string currentWord;
	string extraCurrentWord;
	string extraExtraCurrentWord;
	
	ifstream input(inFile.c_str());
	ofstream output(outFile.c_str());
	
	list<SimpleList<int> *> listSLi;		//All integer lists
	list<SimpleList<double> *> listSLd;		//All double lists
	list<SimpleList<string> *> listSLs;		//All string lists
	
	while(getline(input, currentLine)){
		
		istringstream iss(currentLine);
		iss >> currentWord >> extraCurrentWord;
		
		//Governing if function for "create" case
		if( currentWord == "create" ){
			
			iss >> extraExtraCurrentWord;
			
			output << "PROCESSING COMMAND: " << currentWord << " " << extraCurrentWord << " " << extraExtraCurrentWord << endl;
			
			if( extraCurrentWord.substr(0,1) == "i"){
								
				SimpleList<int> *pSLi;
				
				if( searchList(extraCurrentWord, listSLi) != listSLi.end() ){
					
					output << "ERROR: This name already exists!" << endl;
				
				}
				
				else if(extraExtraCurrentWord == "stack"){
									
					pSLi = new Stack<int>(extraCurrentWord);
					listSLi.push_front(pSLi);
					
				}
				
				else if(extraExtraCurrentWord == "queue"){
					
					pSLi = new Queue<int>(extraCurrentWord);
					listSLi.push_front(pSLi);
					
				}
				
				
			}
			else if( extraCurrentWord.substr(0,1) == "d"){
				
				SimpleList<double> *pSLd;
				
				if( searchList(extraCurrentWord, listSLd) != listSLd.end()){
					
					output << "ERROR: This name already exists!" << endl;
					
				}
				
				else if(extraExtraCurrentWord == "stack"){	
				
				pSLd = new Stack<double>(extraCurrentWord);
					listSLd.push_front(pSLd);
					
				}
				
				else if(extraExtraCurrentWord == "queue"){
				
					pSLd = new Queue<double>(extraCurrentWord);
					listSLd.push_front(pSLd);
				
				}
			
			}
			
			else if( extraCurrentWord.substr(0,1) == "s"){
				
				SimpleList<string> *pSLs;
				
				if( searchList(extraCurrentWord, listSLs) != listSLs.end()){
					
					output << "ERROR: This name already exists!" << endl;
					
				}
				
				else if(extraExtraCurrentWord == "stack"){
					
					pSLs = new Stack<string>(extraCurrentWord);
					listSLs.push_front(pSLs);
					
				}
				
				else if(extraExtraCurrentWord == "queue"){
					
					pSLs = new Queue<string>(extraCurrentWord);
					listSLs.push_front(pSLs);
					
				}
				
			}			
				
		}
		
		
		
		//Governing if funciton for "push" case
		else if( currentWord == "push"){

			iss >> extraExtraCurrentWord;
			
			output << "PROCESSING COMMAND: " << currentWord << " " << extraCurrentWord << " " << extraExtraCurrentWord << endl;
			
			if( extraCurrentWord.substr(0,1) == "i"){
	
				list<SimpleList<int>*>::iterator ci;	
				ci = searchList(extraCurrentWord, listSLi);
					
				if(ci == listSLi.end()){
					
					output << "ERROR: This name does not exist!" << endl;
					
				}
					
				else{
					
					(*ci) -> push( stoi(extraExtraCurrentWord) );
					
				}
					
			}
			
			else if( extraCurrentWord.substr(0,1) == "d"){
				
				list<SimpleList<double>*>::iterator ci;
				ci = searchList(extraCurrentWord, listSLd);
				
				if( ci == listSLd.end()){
					
					output << "ERROR: This name does not exist!" << endl;
					
				}
				
				else{
					
					(*ci) -> push( stod(extraExtraCurrentWord) );
					
				}
				
			}
			
			else if( extraCurrentWord.substr(0,1) == "s"){
				 				
				list<SimpleList<string>*>::iterator ci;
				ci = searchList(extraCurrentWord, listSLs);
				
				if( ci == listSLs.end()){
					
					output << "ERROR: This name does not exist!" << endl;
					
				}
				
				else{
					
					(*ci) -> push( extraExtraCurrentWord );
					
				}
				
			}
		}
		
		
		//Governing if function for "pop" case
		else if(currentWord == "pop"){
			
			
			output << "PROCESSING COMMAND: " << currentWord << " " << extraCurrentWord << endl;
			
			if( extraCurrentWord.substr(0,1) == "i"){
					
				list<SimpleList<int>*>::iterator ci;
				ci = searchList(extraCurrentWord, listSLi);
					
				if(ci == listSLi.end()){
					
					output << "ERROR: This name does not exist!" << endl;
					
				}
				
				else if((*ci) -> getStart() == NULL){
					
					output << "ERROR: This list is empty!" << endl;
					
				}
				
				else{
					
					output << "Value popped: " << (*ci) -> pop() << endl;
					
				}
					
			}
			
			else if( extraCurrentWord.substr(0,1) == "d"){
				
				list<SimpleList<double>*>::iterator ci;
				ci = searchList(extraCurrentWord, listSLd);
				
				if( ci == listSLd.end()){
					
					output << "ERROR: This name does not exist!" << endl;
					
				}
				
				else if((*ci) -> getStart() == NULL){
					
					output << "ERROR: This list is empty!" << endl;
					
				}
				
				else{
					
					output << "Value popped: " << (*ci) -> pop() << endl;
					
				}
				
			}
			
			else if( extraCurrentWord.substr(0,1) == "s"){
				
				list<SimpleList<string>*>::iterator ci;
				ci = searchList(extraCurrentWord, listSLs);
				
				if( ci == listSLs.end()){
					
					output << "ERROR: This name does not exist!" << endl;
					
				}
				
				else if((*ci) -> getStart() == NULL){ 					
					output << "ERROR: This list is empty!" << endl;
					
				}
				
				else{
					
					output << "Value popped: " << (*ci) -> pop() << endl;
					
				}
				
			}
		}

			
	}
	
	input.close();
	output.close();
}

//Opening input and output streams 
//Not used in final implementation but it's 11:24 pm and I'm scared that if I delete this it'll break my code
//Even though it's commented out
//Just gonna leave it
/*
void openStreams(string inFile, string outFile){	
	ifstream input(inFile);
	ofstream output(outFile);
	
}
*/

int main(){
	string inFile, outFile;
	
	cout << "Enter input file name:";
	cin >> inFile;
	cout << "Enter output file name:";
	cin >> outFile;
	
	
	
	parseItAll(inFile, outFile);
	
	return 0;
}

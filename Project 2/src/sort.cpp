// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

//JEREMIAH PRATT
//DSA1 ASSIGNMENT 2

int size;
int c,i,j,k,r,p,subl;
bool check;
double sbd;
string ar[1000000][10];
int cnt[1000000] = {0};
string s1, s2, sb, sb1, sb2, ss1, ss2;
Data* temp;
list<Data*>::iterator iter;
list<Data*>::iterator ci1;
list<Data*>::iterator ci2;
list<Data*>::iterator itera;
list<Data*>::iterator iterat;

//determine position of decimal
inline int find_the_dot(string s){
  i = 20;
  while(s[i] != '.'){
    i--;
  }
  return i;
}

//same but for t3
inline int tiny_find_the_dot(string s){
  i = 3;
  while(s[i] != '.'){
    i--;
  }
  return i;
}

//comparison function to determine if pos[n+1] is > than pos[n]
inline bool comp(Data* d1, Data* d2){
  //s1 = d1 -> data;
  //s2 = d2 -> data;
  //cout << s1 << endl;
  //cout << s2 << endl;
  k = d1 -> data.compare(d2 -> data);
  j = find_the_dot(d2 -> data) - find_the_dot(d1 -> data);
  //cout << k << " , " << j << endl;
  if(j == 0){
    if(k > 0){  
      return true;
    }
    else{
      return false;
    }
  }
  else if(j < 0){
    return true;
  }
  else{
    return false;
  }
}


//Sort method to be implemented for T4, a nearly sorted list
void insertion_sort (list<Data *> &l, int length){
        
  for(iter = prev(l.end()); iter!= l.begin(); iter--){
    ci1 = prev(iter);
    ci2 = iter;
    
    while (ci2 != l.end() && comp(*ci1,*ci2)){
      iter_swap(ci1,ci2);
      advance(ci1, 1);
      advance(ci2, 1);
    }
    
  }
}


//determine index for bucket placement
inline int bucket_index(Data* d1){
  //subl = find_the_dot(d1 -> data) - 14;
  sb = d1 -> data.substr(0,find_the_dot(d1 -> data) - 14);
  return atoi(sb.c_str());
}

//insertion sort on the buckets in ar
inline void bucket_insertion(string (&arr)[1000000][10], int (&count)[1000000]){
  i = 0;
  while(i < 1000000){
    if(count[i]>0){
      j = 0;
      while(j < count[i]){
        k = j;

        while(k > 0 && arr[i][k].compare(arr[i][k - 1]) < 0){
          ss1 = arr[i][k];
          arr[i][k] = arr[i][k-1];
          arr[i][k-1] = ss1;
          k--;
        }
        j++;      
      }
    }
    i++;
  }
}


//Sort method to be implemented for T1, T2
void bucket_sort(list<Data *> &l){
  for(itera = l.begin(); itera!= l.end(); itera++){
    i = bucket_index(*itera);
    ar[i][cnt[i]] = (*itera) -> data;
    cnt[i]++;
  }
  bucket_insertion(ar,cnt);
  //cout << "first step successful" << endl;
  j = 0;
  iterat = l.begin();
  while(iterat != l.end()){
    k = 0;
    while(k < cnt[j]){
      (*iterat) -> data = ar[j][k];
      //cout << j << " , " << k << " , " << cnt[j] << endl;
      iterat++;
      k++;
      }
    j++;
  }
}


//Parse T3 strings into 6 digit indices
inline int count_index(Data* d){
  //sbd = atof(d -> data.c_str()) * 1000;
  return (int)(atof(d -> data.c_str()) * 100);
}

//Sort method to be implemented for T3 (it's really bucket sort cuz count sort was super slow)
void count_sort(list<Data *> &l){
  for(iter = l.begin(); iter != l.end(); iter++){
    i = count_index(*iter);
    ar[i][cnt[i]] = (*iter) -> data;
    cnt[i]++;
  }

  iter = l.begin();
  j = 0;
  while(iter != l.end()){
    k = 0;
    while(k < cnt[j]){
      (*iter) -> data = ar[j][k];
      iter++;
      k++;
    }
    j++;
  }
}


void sortDataList(list<Data *> &l) {
  

  size = l.size();
  int v = 0;
  string s11, s22, sub1, sub2;
  int i1, i2, d1, d2;
  long l1, l2;

  
  list<Data *>::iterator ci = l.begin();
  s11 = (*ci) -> data;
  i1 = (*ci) -> data.length();
  advance(ci, 1);
  s22 = (*ci) -> data;
  i2 = (*ci) -> data.length();
  
  if(i1 > 8 && i2 > 8){
    d1 = find_the_dot(s11);
    d2 = find_the_dot(s22);
    sub1 = s11.substr(d1 - 11,10);
    sub2 = s22.substr(d2 - 11,10);
    l1 = atol(sub1.c_str());
    l2 = atol(sub2.c_str());
  }

  long dif = l2 - l1;
  cout << dif << endl;
  //check for t1
  if( size < 200000){
    //cout << "test case one!" << endl;
    bucket_sort(l);
  }
  //check for t3
  else if( i1 < 8 && i2 < 8 ){
    //cout << "test case three!" << endl;
    count_sort(l);
  }
  //check for t4
  else if( dif > -1 && dif < 1){
    //cout << "test case four!" << endl;
    insertion_sort(l, size);
    //l.sort(comp);
  }
  //must be t2!
  else{
    //cout << "test case two!" << endl;
    bucket_sort(l);
  }

}



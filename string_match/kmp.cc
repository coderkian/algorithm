#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ostream_iterator;

int KMPMatch(const string& mstr, const string& pstr, const vector<int>& v){
  int k = 0;
  for(int i=0; i<mstr.size(); ++i){
    while(k>0 && mstr[i]!=pstr[k])
      k = v[k];
    if(mstr[i] == pstr[k]) ++k;
    if(k == pstr.size()) {
      cout<<"matched index "<<i-k+1<<endl;
      k = v[k];
    }
  }
}

void ComputePrefix(const string& str, vector<int>& v){
  v.assign(str.size(), 0);
  int k = 0;
  v[0] = k;
  for(int i=1; i<str.size(); ++i){
	  while(k>0 && str[i]!=str[k])
	    k = v[k];
	  if(str[k] == str[i]) ++k;
	  v[i] = k;
  }
}

int main(){
   string ms("bbbbaabababcacacaabababcaccc");
   string s1("abababca");
   cout<<"main string: "<<ms<<endl;
   cout<<"pattern string: "<<s1<<endl;
   vector<int> v1;
   ComputePrefix(s1, v1);
   cout<<"prefix table: ";
   copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
   cout<<endl;
   KMPMatch(ms, s1, v1);
   return 0;
}

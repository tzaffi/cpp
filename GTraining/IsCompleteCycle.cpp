#include <iostream>
#include <vector>
#include <exception>

#include "../helpers/coutFriends.cpp"

using namespace std;

bool IsCompleteCycle(const vector<long>& cArray){
  size_t N = cArray.size();
  if (N == 0) {
    return false;
  } else if (N == 1) {
    return true;
  }
  cout << "next:\t0,\t";
  long next = 0;
  for(size_t i=0; i<N; ++i)
  {
    next = (next + cArray[next]) % N;
    if(next < 0){
      next += N;
    }
    cout << next << ",\t";
    if(next == 0)
      return i == N-1;
  }
  cout << endl;
  return false;
}

void runTestCase(const pair<vector<long>, bool>& testCase)
{
  vector<long> cArray = testCase.first;
  bool expect = testCase.second;
  cout << boolalpha << cArray << endl << "ASSERT " << expect << endl;
  bool got = IsCompleteCycle(cArray);
  cout << "GOT " << got << endl << endl;
}

int main(){
  cout << "pair? " << pair<string, long>{"hi",3} << endl;
  vector<pair<vector<long>,bool> > testCases{
    {{1, 1, 1, 1}, true},
    {{1, 2, 3}, false},
    {{7}, true},
    {{}, false},
    {{1, -1, 1, -1}, false},
    {{1, -2, 2}, false},
    {{1,2,3,4,5,6,7}, false},
    {{1,2,3,5,5,-4,2}, false},
    {{3,-2,2,-2,9,-5,4,-1}, true}
  };
  cout << boolalpha << endl << endl << "testCases:" << endl << testCases << endl;

  for(auto&& testCase : testCases) {
    runTestCase(testCase);
  }
    
  return 0;
}

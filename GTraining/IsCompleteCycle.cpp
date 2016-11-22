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
  const long begin = 0;
  long next = begin;
  for(size_t i=0; i<N; ++i)
  {
    long next = (next + cArray[i]) % N;
    if(next < 0){
      next += N;
    }
    if(next == begin)
      return i == N-1;
  }
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
    {{}, false}/*TODO:,
    {{1, -1, 1, -1}, false},
    {{1, -2, 2}, false},
    {{7}, true},
    {{}, false}*/
  };
  cout << boolalpha << endl << endl << "testCases:" << endl << testCases << endl;

  for(auto&& testCase : testCases) {
    runTestCase(testCase);
  }
    
  return 0;
}

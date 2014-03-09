#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct run {
  int beg;
  int end;
  int length;
  bool isDescending;
};

string toBinary(int m);
void showRun(run r);
void showRuns(vector<run> runs);
void showVec(vector<int> v);
vector<int> getRandomVector(int max, int howMany);

int get_minrun(int n);
int findPlace(int fromWhere, int which,  vector<int> v);
void sortElemInto(int fromWhere, int which, vector<int> &v);
void merge_lo(int a_beg, int b_beg, int b_end, vector<int> &v);
void merge_hi(int a_beg, int b_beg, int b_end, vector<int> &v);
int min(int a, int b);
void reverse(int from, int to, vector<int> &v);

run getNextNaturalRun(int fromWhere, vector<int> inp);
run fixNaturalRun(run current, int minrun, vector<int> &inp);
vector<run> makeRuns(vector<int> &inp);
run mergeTwoRuns(run first, run second, vector<int> &v);

void checkBC(vector<run> &runs, vector<int> &v);
void checkABC(vector<run> &runs, vector<int> &v);


// a > b + c
// b > c


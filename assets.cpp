#include "assets.h"
#include<cstdlib>
#include<ctime>
using namespace std;

string toBinary(int m) {
  int pow = 2;
  string resu = "";
  while (pow < m) {
    pow *= 2;
  };
  if (pow > m) pow = pow/2;
  bool finished = false;
  while (!finished) {
    if (pow > m) {
      resu += "0";
    } else {
      resu += "1";
      m -= pow;
    };
    if (pow != 1) {
      pow /= 2;
    } else {
      finished = true;
    };
  };
  return resu;
};

int get_minrun(int n) {
  if (n <= 64) return n;
  else {
    int resu, pow;
    resu = 0; pow = 2;
    while (pow < n) {
      pow *= 2;
    };
    if (pow > n) pow /= 2;
    for (int i = 0; i < 6 ; i++ ) {
      resu *= 2;
      if ( n >= pow) {
	resu++;
	n -= pow;
      };
      pow /= 2;
    };
    bool finished = false;
    while (!finished) {
      if (n >= pow) {
        resu ++;
        finished = true;
      };
      if (pow != 1) {
        pow /= 2;
      } else {
        finished = true;
      };
    };
    return resu;
  };
};

void showRun(run r) {
  cout << "r is [" << r.beg << "," << r.end << "]" << endl;
  cout << "r.length is " << r.length << endl;
  cout << "r.isDescending is " << r.isDescending << endl;
  cout << endl;
};

void showVec(vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  };
  cout << endl << endl;
};

int findPlace(int fromWhere, int which,  vector<int> v) {
  if (v[which] <= v[fromWhere]) {
    return fromWhere;
  } else if (v[which] >= v[which-1]) {
    return which;
  } else {
    int l = fromWhere;
    int p = which-1;
    int what = v[which];
    int m;
    while (l != p) {
      m = (l+p + 1 )/2;
      if ( what >= v[m] ) {
	l = m;
      } else {
	p = m-1;
      };
    };
    return l + 1;
  };
};


void sortElemInto(int fromWhere, int which, vector<int> &v) {
  int where = findPlace(fromWhere, which, v);
  if (where != which) {
    int onTheMove = v[which];
    for (int i = which; i > where; i-- ) {
      v[i] = v[i-1];
    };
    v[where] = onTheMove;
  };
};

void merge_lo(int a_beg, int b_beg, int b_end, vector<int> &v){
  vector<int> temp(b_beg - a_beg);
  for (int i = a_beg; i < b_beg; i++) {
    temp[i-a_beg] = v[i];
  };
  int i = 0;
  int j = b_beg;
  int k = a_beg;
  while (i < temp.size() && j <= b_end ) {
    if ( temp[i] < v[j] ) {
      v[k] = temp[i];
      i++;
    } else {
      v[k] = v[j];
      j++;
    };
    k++;
  };
  while ( i < temp.size() ) {
    v[k] = temp[i];  
    i++; k++;
  };
  while ( j <= b_end ) {
    v[k] = v[j];
    j++; k++;
  };
};

void merge_hi(int a_beg, int b_beg, int b_end, vector<int> &v){
  vector<int> temp(b_end-b_beg + 1);
  for (int i = b_beg; i <= b_end; i++) {
    temp[i-b_beg] = v[i];
  };
  int i = b_end - b_beg;
  int j = b_beg - 1;
  int k = b_end;
  while ( i >= 0 && j >= a_beg ) {
    if ( temp[i] > v[j] ) {
      v[k] = temp[i];
      i--;
    } else {
      v[k] = v[j];
      j--;
    };
    k--;
  };
  while ( i>= 0 ) {
    v[k] = temp[i];
    i--; k--;
  };
  while ( j >= a_beg ) {
    v[k] = v[j];
    j--; k--;
  };
};

run getNextNaturalRun(int fromWhere, vector<int> inp) {
  run resu;
  resu.beg = fromWhere;
  resu.isDescending = inp[fromWhere+1] < inp[fromWhere];
  resu.end = fromWhere;
  if (resu.isDescending) {
    while ( resu.end <= inp.size() &&  inp[resu.end+1] < inp[resu.end] ) {
      resu.end++;
    };
  } else {
    while ( resu.end <= inp.size() &&  inp[resu.end+1] >= inp[resu.end] ) {
      resu.end++;
    };
  };
  resu.length = resu.end - resu.beg + 1;
  return resu;
};

int min(int a, int b) {
  if (a<b) return a;
  else return b;
};

void reverse(int from, int to, vector<int> &v) {
  int l = from;
  int p = to;
  int temp;
  while (p>l) {
    temp = v[l];
    v[l] = v[p];
    v[p] = temp;
    p--; l++;
  };
};

run fixNaturalRun(run current, int minrun, vector<int> &inp) {
  if (current.isDescending) {
    reverse(current.beg, current.end, inp);
    current.isDescending = false;
  };
  if (current.length < minrun) {
    int old_end = current.end;
    current.end = min(current.beg + minrun - 1, inp.size() - 1);
    for (int i = old_end + 1; i <= current.end; i++) {
      sortElemInto(current.beg, i, inp);
    };
    current.length = current.end - current.beg + 1;
  };
  return current;
};

vector<run> makeRuns(vector<int> &inp) {
  vector<run> resu;
  int i = 0;
  int minrun = get_minrun(inp.size());
  cout << "minrun is " << minrun << endl;
  run current;
  while (i < inp.size()) {
    current = getNextNaturalRun(i, inp);
    cout << "got a natural run , its data follows" << endl;
    showRun(current);
    cout << "showing the vector " << endl;
    showVec(inp);
    current = fixNaturalRun(current, minrun, inp);
    cout << "fixed the run, data follows" << endl;
    showRun(current);
    cout << "showing the vector " << endl;
    showVec(inp);
    i = current.end + 1;
    resu.push_back(current);
    checkABC(resu, inp);
    cout << "just enforced merging conditions, here are the runs: " << endl;
    showRuns(resu);
  };
  while (resu.size() > 1) {
    // collapse two last runs ??
    resu[resu.size() - 2] = mergeTwoRuns(resu[resu.size()-2], resu[resu.size()-1], inp);
    resu.pop_back();
  };
  return resu;
};

vector<int> getRandomVector(int max, int howMany) {
  srand(time(NULL));
  vector<int> resu(howMany);
  for (int i = 0; i < howMany; i++) {
    resu[i] =  rand() % max + 1;
  };
  return resu;
};

void showRuns(vector<run> runs) {
  cout << endl << "showing all the runs" << endl;;
  for (int i = 0  ; i < runs.size(); i++) {
    showRun(runs[i]);
    cout << endl;
  };
};

run mergeTwoRuns(run first, run second, vector<int> &v) {
  run resu;
  resu.beg = first.beg;
  resu.end = second.end;
  resu.length = first.length + second.length;
  resu.isDescending = false;
  if (first.length < second.length) {
    merge_lo(first.beg, second.beg, second.end, v);
  } else {
    merge_hi(first.beg, second.beg, second.end, v);
  };
  return resu;
};

void checkBC(vector<run> &runs, vector<int> &v) {
  if (v.size() > 2) {
    int i = runs.size() - 2; 
    if (runs[i].length <= runs[i+1].length) {
      cout << " B <= C  so -- > merge A and B " << endl;
      runs[i] = mergeTwoRuns(runs[i-1], runs[i], v);
      runs.erase(runs.begin()+i);
    };
  };
};

void checkABC(vector<run> &runs, vector<int> &v) {
  bool keepGoing = true;
  while (keepGoing) {
    if (runs.size() > 2) {
      int i = runs.size() - 3;
      if (runs[i].length <= runs[i+1].length + runs[i+2].length || runs[i+1].length <= runs[i+2].length) 
      {
        // merge smaller of A and C with B
        if (runs[i+2].length <= runs[i].length) {
          cout << " merge B and C " << endl;
          // merge B and C
          runs[i+1] = mergeTwoRuns(runs[i+1], runs[i+2], v);
          runs.erase(runs.begin()+i+2);
        } else {
          // merge A and B
          cout << " merge A and B " << endl;
          runs[i] = mergeTwoRuns(runs[i], runs[i+1], v);
          runs.erase(runs.begin()+i+1);
        };
      } else { keepGoing = false; };
    } else if (runs.size() == 2) {
      if (runs[0].length <= runs[1].length) {
	runs[0] = mergeTwoRuns(runs[0], runs[1], v);
        runs.erase(runs.begin()+1);
      } else {keepGoing = false; };
    } else 
    { keepGoing = false; };;
  };
};


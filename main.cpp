#include "assets.h"
using namespace std;

int main() {

  // static const int arr[] = { 9, 8, 7, 6, 3, 2, 1, 10, 11, 12, 1, 2, 3, 7, 8, 9};
  // //                         0  1  2  3  4  5  6  7   8   
  // vector<int> inp (arr, arr + sizeof(arr) / sizeof(arr[0]) );
  vector<int> inp = getRandomVector( 1000, 1000);

  cout << "This is input vector:" << endl;
  showVec(inp);

  vector<run> runs = makeRuns(inp);

  cout << endl <<" ================ After sorting ================================" << endl << endl;


  showVec(inp);
  showRuns(runs);
};

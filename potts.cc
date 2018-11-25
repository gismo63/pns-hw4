#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <climits>

typedef std::vector<int> vec;
using std::cout;

#include "grid.h"





int main(int argc, char const *argv[]) {
  srand(time(0));
  int L = 20, q = 5;
  double beta = 1.5;
  vec g(L*L);
  Grid grid(L,q,beta);

  g = grid.return_g();
  double frac = grid.magnetisation();
  cout << (q*frac-1)/(q-1) << "\n";

  for(int i =0; i<1000000; i++){
    grid.change(1);
  }

  cout << "\n";

  g = grid.return_g();
  frac = grid.magnetisation();
  cout << (q*frac-1)/(q-1) << "\n";

  return 0;
}

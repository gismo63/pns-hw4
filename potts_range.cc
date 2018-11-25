#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <climits>

typedef std::vector<int> vec;
typedef std::vector<double> Vec;
using std::cout;

#include "grid.h"





int main(int argc, char const *argv[]) {
  srand(time(0));
  int L = 20, q = 5;
  double frac, est = 1.2;
  double below = est-0.5, above = 1.5-est;
  Vec beta(41);
  vec g(L*L);
  beta[20] = est;
  for(int i = 0; i<20; i++){
    beta[20+i+1] = est+above*pow(i+1.0,3)/pow(20.0,3);
    beta[20-i-1] = est-below*pow(i+1.0,3)/pow(20.0,3);
  }
  Grid grid(L,q,beta[0]);

  for(int j =0; j< 41; j++){
    grid = Grid(L,q,beta[j]);
    frac = 0;
    for(int k = 0; k<10; k++){
      for(int i =0; i<1000000; i++){
        grid.change(1);
      }
      frac += grid.magnetisation();
    }
    frac = frac/10;
    cout << beta[j] << " " << (q*frac-1)/(q-1) << "\n";
  }

  return 0;
}

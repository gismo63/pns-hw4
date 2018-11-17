class Grid{
  private:
    int L_, q_,n_;
    double beta_;
    vec g;
  public:
    Grid(int, int, double);
    void change(int);
    double action(int, int);
    vec return_g();
    double magnetisation();



};
//The constructor assigns initial values to all of the provate variables
Grid::Grid(int L, int q, double beta): L_(L), q_(q), g(L*L) {
  for(int i = 0;i<L*L;i++){
    g[i] = (rand()%q)+1;
  }
  n_ = L*L;
  beta_ = beta;
}

void Grid::change(int k){
  int s, delta=0,prop;
  double prob,prob_rand;
  for(int i=0;i<k;i++){
    s = rand()%n_;
    prop = rand()%(q_-1)+1;
    if(prop >= g[s]){
      prop++;
    }
    delta += action(s,prop);
    if(delta>0){
      prob = exp(-(beta_*delta));
      prob_rand = double(rand())/INT_MAX;
      if(prob>prob_rand){
        g[s] = prop;
      }
    }
    else{
      g[s] = prop;
    }
  }
}

double Grid::action(int s, int prop){
  int x  = s%L_;
  int y  = s/L_;
  int s_o = 0,s_n = 0;
  int left = g[y*L_+(x-1)%L_];
  int right = g[y*L_+(x+1)%L_];
  int up = g[((y+1)%L_)*L_+x];
  int down = g[((y+1)%L_)*L_+x];
  if(g[s] !=left){s_o++;}
  if(g[s] !=right){s_o++;}
  if(g[s] !=up){s_o++;}
  if(g[s] !=down){s_o++;}
  if(prop !=left){s_n++;}
  if(prop !=right){s_n++;}
  if(prop !=up){s_n++;}
  if(prop !=down){s_n++;}
  return s_n-s_o;

}

double Grid::magnetisation(){
  double max = 0;
  for(int i = 0;i<q_;i++){
    double count = 0;
    for(int j = 0; j<n_; j++){
      if (g[j]==(i+1)){
        count++;
      }
    if(count/n_>max){
      max = count/n_;
    }
    }

  }
  return max;
}


vec Grid::return_g(){
  return g;
}

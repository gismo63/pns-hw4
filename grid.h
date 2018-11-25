class Grid{
  private:
    int L_, q_,n_;
    double beta_;
    vec g;
  public:
    Grid(int, int, double);
    void change(int);
    double action(int,int);
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
  int delta=0;
  vec prop, s;
  double prob,prob_rand;
  for(int i=0;i<k;i++){
    s.push_back(rand()%n_);
    prop.push_back(rand()%(q_-1)+1);
    if(prop[i] >= g[s[i]]){
      prop[i]++;
    }
    delta += action(s[i],prop[i]);
  }
  if(delta>0){
    prob = exp(-(beta_*delta));
    prob_rand = double(rand())/INT_MAX;
    if(prob>prob_rand){
      for(int i = 0; i< k; i++){
        g[s[i]] = prop[i];
      }
    }
  }
  else{
    for(int i = 0; i<k; i++){
      g[s[i]] = prop[i];
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
  int down = g[((y-1)%L_)*L_+x];
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

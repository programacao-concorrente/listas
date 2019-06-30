//Para 5 processos
sem s[];
process p[i=0 to 4]{
  //para o primeiro processo
  if (i==0){
    v(s[i]);
    v(s[i]);
  }
  //para o segundo o terceiro processo
  if (i==1) || (i==2){
    p(s[0]);
    v(s[i]);
  }
  //para os processos entre o 3o e o 5o processo
  if ((i != 1) && (i != 2) && (i != 4)) {
    p(s[i-1]);
    v(s[i]);
  }
  //para o 5o processo
  if (i==4){
    p(s[i]);
    p(s[2]);
  }
}

//Para n processos
sem s[];
process p[i=0 to n]{
  //para o primeiro processo
  if (i==0){
    v(s[i]);
    v(s[i]);
  }
  //para o segundo o terceiro processo
  if (i==1) || (i==2){
    p(s[0]);
    v(s[i]);
  }
  //para os processos entre o 3o e o processo n
  if ((i != 1) && (i != 2) && (i != n)) {
    p(s[i-1]);
    v(s[i]);
  }
  //para o processo n
  if (i==n){
    p(s[i]);
    p(s[2]);
  }  
}

/*Questao 4.4 a)

Sejam 4 semaforos: arrive1, arrive2, arrive3, arrive4 e arrive5
Sejam 5 processos, sendo um para cada tarefa i: P1, P2, P3, P4 e P5

Para o fluxo 1: P1 -> P2 -> P4 -> P5
Para o fluxo 2: P1 -> P3 -> P5

P2 so executa quando P1 concluir
P3 so executa quando P1 concluir
P4 so executa quando P2 concluir
P5 so executa quando P4 e P3 concluir
*/

sem arrive1=0, arrive2=0, arrive3=0, arrive4=0, arrive=0; 

process P1{
  wait process if any;
  body of task T1;
  v(arrive1);
  v(arrive1);
}

process P2{
  while(true){
    ...
    v(arrive2);
    body of task T2;
    p(arrive1);
  }
}

process P3{
  while(true){
    ...
    v(arrive3);
    body of task T3;
    p(arrive1);
  }
}

process P4{
  while(true){
    ...
    v(arrive4);
    body of task T4;
    p(arrive2);
  }
}

process P5{
  while(true){
    v(arrive5);
    body of task T5;
    p(arrive4);
    p(arrive3);
  }
}

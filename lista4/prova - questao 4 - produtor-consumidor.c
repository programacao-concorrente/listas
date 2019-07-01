monitor Buffer_limitado{
//Buffer de tamanho 'n' de um dado tipo
Type buf[n];

//controlar os slots disponiveis no Buffer
int first=0;
int rear=0;

//controlar entrada e saida no Buffer
int cont=0;

//controlar os waits e signais no Buffer
cond not_full;
cond not_empty;

deposit(int data){
  while(cont == n) {
    wait(not_full);
  }
  
  buf[rear] = data;
  rear = (rear + 1) % n;
  cont = cont + 1; 
  
  signal(not_empty);
}

fetch(int &data){
  while(cont == 0){
    wait(not_empty);   
  }
  
  data = buf[first];
  first = (first + 1) % n;
  cont = cont - 1;
  
  signal(not_full);
}

}

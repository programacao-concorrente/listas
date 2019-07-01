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

procedure deposit(){
}

proceduce fetch(){
}

}

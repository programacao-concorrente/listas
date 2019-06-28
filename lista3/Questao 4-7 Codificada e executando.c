//Questao 4-7 Funcionando em C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int table_used=1;       //mesa sendo usada
int generated_item[2];  //sao gerados 2 itens
int generated=0;        //item nao gerado

char *item[]={"tobaco","paper","matches"};  //itens alocados pelos processos smokers
                                            // tobaco (1), paper (2), matches (3)
sem_t table;                                //semaforo de controle da mesa
                                            //a mesa pode estar ocupada ou livre (semáforo binário 0 - ocupada ou 1 - livre)
                                           
int item_id;
sem_t smoker_tobaco;    //=1;
sem_t smoker_paper;     //=0;
sem_t smoker_match;     //=0;
sem_t agent_proc;       //=1;

int randomnumber;

void *agent(void *arg){
    while(1==1){
        sleep(1); //processo dorme 1 segundo
        sem_wait(&agent_proc);
        item_id = randomnumber = rand() % 3; //numero randomico entre 1 e 3
	item_id = item_id + 1;
	printf("item_id %d ", item_id);

        if(item_id==3){ //matches
            sem_wait(&table); //lock table
            if(table_used==1){ 
                generated_item[0]=1;    //item 1 (tobaco)
                generated_item[1]=2;    //item 2 (paper)
                printf("Agent is prodused %s,%s\n",item[0],item[1]); 
                generated=1;
                table_used=0;           //libera a mesa
                sem_post(&smoker_match); //acorda o processo smoker_match
            }
            sem_post(&table); //unlock table
        }else if (item_id==2){ //paper
            sem_wait(&table);           //lock table
            if(table_used==1){ 
                generated_item[0]=1;    //item 1 (tobaco)
                generated_item[1]=3;    //item 3 (match)
                printf("Agent is prodused %s,%s\n",item[0],item[2]); 
                generated=1;
                table_used=0;           //libera a mesa
                sem_post(&smoker_paper); //acorda o processo smoker_paper
            }
            sem_post(&table);           //unlock table
        }else{ // tobaco
            sem_wait(&table); //lock table
            if(table_used==1){ 
                generated_item[0]=2; //item 2 (paper)
                generated_item[1]=3; //item 3 (match)
                printf("Agent is prodused %s,%s\n",item[1],item[2]); 
                generated=1;
                table_used=0; //libera a mesa
                sem_post(&smoker_tobaco); //acorda o processo smoker_tobaco
            }
            sem_post(&table); //unlock table
        }
    }
}

void *process_smoker1(void *arg){
    while(1==1){
        //sleep(1); //processo smoker dorme
        sem_wait(&smoker_match);
        sem_wait(&table); //lock table
        if(table_used==0){ //table livre
            if(generated && generated_item[0]==1 && generated_item[1] == 2){
                printf("smoker match completed his smoking\n\n");
                table_used=1;
                generated=0;
            }
        }
	sem_post(&table);
        sem_post(&agent_proc); //acorda o processo agente
    }
}

void *process_smoker2(void *arg){
    while(1==1){
        //sleep(1); //processo smoker dorme
        sem_wait(&smoker_paper);
        sem_wait(&table); //lock table
        if(table_used==0){ //table livre
            if(generated && generated_item[0]==1 && generated_item[1] == 3){
                printf("smoker paper completed his smoking\n\n");
                table_used=1;
                generated=0;
            }
        }
	sem_post(&table);
        sem_post(&agent_proc); //acorda o processo agente
    }
}

void *process_smoker3(void *arg){
    while(1==1){
        //sleep(1); //processo smoker dorme
        sem_wait(&smoker_tobaco);
        sem_wait(&table); //lock table
        if(table_used==0){ //table livre
            if(generated && generated_item[0]==2 && generated_item[1] == 3){
                printf("smoker tobaco completed his smoking\n\n");
                table_used=1;
                generated=0;
            }
        }
	sem_post(&table);
        sem_post(&agent_proc); //acorda o processo agente
    }
}

int main(){
    pthread_t smkr1;
    pthread_t smkr2;
    pthread_t smkr3;
    pthread_t agnt; 
    
    sem_init(&table,0,1);
    sem_init(&smoker_match,0,0);
    sem_init(&smoker_paper,0,0);
    sem_init(&smoker_tobaco,0,1);
    sem_init(&agent_proc,0,1);

    pthread_create(&agnt,NULL,agent,NULL); 
    pthread_create(&smkr1,NULL,process_smoker1,NULL); 
    pthread_create(&smkr2,NULL,process_smoker2,NULL); 
    pthread_create(&smkr3,NULL,process_smoker3,NULL); 
    
    while(1);
}

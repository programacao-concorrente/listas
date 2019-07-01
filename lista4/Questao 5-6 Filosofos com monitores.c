/*
Questao 5-6 Filosofos com monitores
Dining-Philosophers Solution Using Monitors 

Um monitor devera controlar as requisoes e liberacoes dos garfors de um filosofo i. 
Operacoes do monitor: 
request_fork(i)
release_fork(i)

Sejam os Filosofos de 1 a 5:
Filosofo 1 checa os status do seu vizinho da direita e do seu vizinho da esquerda
Filosofo 1 pega os garfos da sua direita e da sua esquerda
Filosofo 1 come
Filosofo 1 libera seus garfos
...
Filosofo 5 checa os status do seu vizinho da direita e do seu vizinho da esquerda
Filosofo 5 pega os garfos da sua direita e da sua esquerda
Filosofo 5 come
Filosofo 5 libera seus garfos

Seja o array filosofo[5] para controlar os filosofos do problema.

Seja o emumeration status para indicar o status do filosofo em dado momento. 
status(0) = 'hungry', status(1) = 'eating', status(2) = 'thinking'	

Seja o array de caracteres state[] para guardar o estado de cada filosofo.

Seja a funcao test(i) para checar as status dos vizinhos da direita e da esquerda do filosofo[i]:
- Se o vizinho da direita e o vizinho da esquerda estiver comendo e o filosofo[i] estiver com fome:
acorda o filosofo[i]

Assim que o monitor inicializa todos os filosofos ficam com o status pensando.
*/

monitor DP 
{ 	
	status = enum('hungry', 'eating', 'thinking');	
	char state[5]; 
	cond filosofo[5]; 

	// Pickup forks 
	request_forks(int i) 
	{ 
		// indicate that I’m hungry 
		state[i] = status(0); //hungry; 

		// set state to eating in test() 
		// only if my left and right neighbors 
		// are not eating 
		test(i); 

		// if unable to eat, wait to be signaled 
		if (state[i] != status(1)) // state[i] != eating 
			wait(filosofo[i]); 
	} 

	// Put down forks
	release_forks(int i) 
	{ 

		// indicate that I’m thinking 
		state[i] = status(2); //thinking; 

		// if right neighbor R=(i+1)%5 is hungry and 
		// both of R’s neighbors are not eating, 
		// set R’s state to eating and wake it up by 
		// signaling R’s CV 
		test((i + 1) % 5); //testa a condicao do vizinho da direita e seta o status do filosofo[i]
		test((i + 4) % 5); //testa a condicao do vizinho da esquerda e seta o status do filosofo[i]
	} 

	test(int i) 
	{ 
		//Checa se o vizinho da direita nao esta comendo e se o vizionho da direita nao esta comendo e o requisitante esta com fome
		if ((state[(i + 1) % 5] != status(1)) && (state[(i + 4) % 5] != status(1)) && (state[i] == status(0))) { 
			// indicate that I’m eating 
			state[i] = status(1); 
			// signal() has no effect during Pickup(), 
			// but is important to wake up waiting 
			// hungry philosophers during Putdown() 
			signal(filosofo[i]); 
		} 
	} 

	init() 
	{ 

		// Execution of Pickup(), Putdown() and test() 
		// are all mutually exclusive, 
		// i.e. only one at a time can be executing 
		for(int i=0; i < 4; i++){
		// Verify that this monitor-based solution is 
		// deadlock free and mutually exclusive in that 
		// no 2 neighbors can eat simultaneously 
			state[i] = status(2);//thinking 
		}
	} 
} // end of monitor 

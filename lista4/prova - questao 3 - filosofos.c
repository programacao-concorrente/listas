monitor DP 
{ 	
	status = enum('hungry', 'eating', 'thinking');	
	char state[5]; 
	cond filosofo[5]; 

	// Pickup forks 
	request_forks(int i) 
	{ 
		state[i] = status(0); //hungry; 

		test(i); 

		if (state[i] != status(1)) // state[i] != eating 
			wait(filosofo[i]); 
	} 

	// Put down forks
	release_forks(int i) 
	{ 
		state[i] = status(2); //thinking; 

		test((i + 1) % 5); //testa a condicao do vizinho da direita e seta o status do filosofo[i]
		test((i + 4) % 5); //testa a condicao do vizinho da esquerda e seta o status do filosofo[i]
	} 

	test(int i) 
	{ 
		if ((state[(i + 1) % 5] != status(1)) && 
        (state[(i + 4) % 5] != status(1)) && 
        (state[i] == status(0))) { 
			state[i] = status(1); 
			signal(filosofo[i]); 
		} 
	} 

	init() 
	{ 
		for(int i=0; i < 4; i++){
			state[i] = status(2);//thinking 
		}
	} 
} // end of monitor 

monitor DP 
{ 	
	status = enum('hungry', 'eating', 'thinking');	
	char state[5]; 
	cond filosofo[5]; 

	// Pickup forks 
	request_forks(int i) 
	{ 
		state[i] = status(0); //hungry; 
		testVizinhos(i); 
		if (state[i] != status(1)){ // state[i] != eating 
			wait(filosofo[i]); 
		}
	} 

	// Put down forks
	release_forks(int i) 
	{ 
		state[i] = status(2); //thinking; 
		testVizinhos(i);
	} 
	
	status stateVizinhoDireita(int i){
		return state[(i+1)%5];
	}
	
	status stateVizinhoEsquerda(int i){
		return state[(i+4)%5];
	}

	testVizinhos(int i) 
	{ 
		if (stateVizinhoDireita(i) != status(1)) && (stateVizinhoEsquerada(i) != status(1)) && (state[i] == status(0))) { 
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

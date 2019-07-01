monitor DP 
{ 	
	status = enum('hungry', 'eating', 'thinking');	
	char sentimento[5]; 
	cond filosofo[5]; 

	// Pickup forks 
	request_forks(int i) 
	{ 
		sentimento[i] = status(0); //hungry; 
		testaVizinhos(i); 
		if (sentimento[i] != status(1)){ // state[i] != eating 
			wait(filosofo[i]); 
		}
	} 

	// Put down forks
	release_forks(int i) 
	{ 
		sentimento[i] = status(2); //thinking; 
		testaVizinhos(i);
	} 
	
	status statusVizinhoDireita(int i){
		return sentimento[(i+1)%5];
	}
	
	status statusVizinhoEsquerda(int i){
		return sentimento[(i+4)%5];
	}

	testaVizinhos(int i) 
	{ 
		if (statusVizinhoDireita(i) != status(1)) && (statusVizinhoEsquerada(i) != status(1)) && (sentimento[i] == status(0))) { 
			sentimento[i] = status(1); 
			signal(filosofo[i]); 
		} 
	} 

	init() 
	{ 
		for(int i=0; i < 4; i++){
			sentimento[i] = status(2);//thinking 
		}
	} 
} // end of monitor 

type op_kind = enum("pede", "libera");
type result_type = union(result1, result2)

chan request(int clienteId, op_kind);
chan reply[n](result_type);

process Server{
	MAXUNIT = 5;
	int avail[MAXUNIT]; 
	set units = initial values;
	queue pending; //initially empty
	int clientId;
	int unitId;
	op_kind kind; 

	//Inicializa o array inteiro de fork informando que todos estao livres
	initForks(){
		for (int i=0; i<5; i++){
			avail[i] = 0;
		}
	}

	//faz a requisicao de um fork com o indice dado
	// se o avail[indice]==1 significa que ele esta ocupado, entao bota para dormir forkBusy[indice]
	// se o avail[indice]==0 significa que ele esta disponivel
	acquire(int indice){
	if (avail[indice] > 0){ //honor request now, pode acessar o recurso
		avail[indice] = avail[indice] - 1; 
		remove(units, unitId);
		send reply[clientId](unitId);
		}else { //recurso ocupado, então manda aguardar
			insert(pending, clientId);
		}
	}

	//Libera o uso do fork no indice dado
	// Acorda o processo que pegou o recurso
	// se o avail[indice]==0 significa que ele esta disponivel
	release(int indice){
		if (empty(pending)){ //return unitId to units, libera o recurso
			avail[indice] = avail[indice] + 1;
			insert(units, unitId);
		}else{ //allocat unitId to a waiting client
			remove(pending, clientId);
			send reply[clientId](unitId);
		}
	}

	//Dado um indice, verifica se um garfo esta disponivel percorrendo o array de fork 
	//0 : disponivel 
	//1 : ocupado
	int checkIsAvailable(int indice){
		acquire(indice);
		return (avail[indice]);
	}
	
	main(){
		//initialization code;
		while(true){
			receive request(clienteId, [op_kind]);
			switch(op_kind)
			{
				case ("pede") : //clienteId pede ao servidor seus garfos da esquerda e da direita
					results(checkIsAvailable(clienteId-1), checkIsAvailable((clienteId % 5)))
					send reply(clienteId, results);					
					break;
				case ("libera") : //servidor libera os garfos da esquerda e da direita do clienteId 
					release(clienteId-1); //libera o fork da direita
					release(clienteId%5); //libera o fork da esquerda
					results(avail[clienteId-1], avail[(clienteId%5)])
					send reply(clienteId, results);					
					break;
			}
		}
	}

}

process Client[i = 1 to n]{	
	result_type results;
	int result1, result2;

	main(){
		send request(i, ["pede"]); //call op
		receive reply[i](results); //wait for reply
		result1 = results(1);
		result2 = results(2);

		if (result1 == 0 && result2 == 0){//os garfos da esquerda e da direita estao livres
			come(i);
			libera(i);
		}else {//pelo menos um garfo esta ocupado
			aguarda(i);
		}
	}

	//Para o cliente i, informa que seus garfos da esquerda e da direita estao ocupados
	come(int clienteId){ //clienteId comendo e ocupando seus garfos da direita e da esquerda
		cliente come por x segundos;
	}

	//Para o cliente i, libera seus garfos da esquerda e da direita
	libera(int clienteId){
		send request(clienteId, ["libera"]);
		receive reply[clientId](results); //wait for reply	
	}

	//O cliente i aguarda ate que seus garfos da esquerda e da direita estejam disponiveis
	aguarda(int clienteId){
		send request(i, ["pede"]); //call op
		receive reply[i](results); //wait for reply
		result1 = results(1);
		result2 = results(2);
		
		while (result1 != 0 && result2 != 0){
			send request(clienteId, ["pede"]);
			receive reply[clienteId](results); //wait for reply	
		}
	}

}
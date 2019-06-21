type op_kind = enum("read", "write", "release");
type result_type = union(result1)
chan request(int clienteId, op_kind);
chan reply[n](result_type);

process Server{
	int avail; //database
	set units = initial values;
	queue pending; //initially empty
	int clientId;
	int unitId;
	op_kind kind; 

	//acquire database
	acquire(){
	if (avail > 0){ //honor request now, pode acessar o recurso
		avail = avail - 1; 
		remove(units, unitId);
		send reply[clientId](unitId);
		}else { //recurso ocupado, então manda aguardar
			insert(pending, clientId);
		}
	}

	//libera database
	release(){
		if (empty(pending)){ //return unitId to units, libera o recurso
			avail = avail + 1;
			insert(units, unitId);
		}else{ //allocat unitId to a waiting client
			remove(pending, clientId);
			send reply[clientId](unitId);
		}
	}

	main(){
		while(true){
			receive request(clienteId, [op_kind]);
			switch(op_kind)
			{
				case ("read") : //clienteId pede ao servidor para ler o banco de dados
					acquire();
					results(avail)
					send reply(clientId, results);					
					break;
				case ("write") : //clienteId pede ao servidor para escrever no banco de dados
					acquire();
					results(avail)
					send reply(clientId, results);					
					break;
				case ("release") : //servidor libera o uso do banco de dados 
					release()
					results(avail)
					send reply(clientId, results);					
					break;
			}
		}
	}

}

process Reader[i = 1 to n]{	
	result_type results;
	int result1;

	main(){
		send request(i, ["read"]); //call op
		receive reply[i](results); //wait for reply
		result1 = results(1);
		if (result1 == 0){//o banco de dados esta livre
			ler(i);
		}else {
			aguarda(i);
		}
	}

	ler(int i){
		cliente ler o banco de dados por x segundos;
	}

	aguarda(int i){
		send request(i, ["read"]); //call op
		receive reply[i](results); //wait for reply
		result1 = results(1);		
		while (result1 != 0){
			send request(i, ["read"]);
			receive reply[i](results); //wait for reply	
		}
	}

}

process Writer[j=1 to m]{
	result_type results;
	int result1;

	main(){
		send request(j, ["write"]); //call op
		receive reply[j](results); //wait for reply
		result1 = results(1);
		if (result1 == 0){//o banco de dado esta livre
			escreve(j);
			libera(j);
		}else {
			aguarda(j);
		}
	}

	escreve(int j){ 
		escreve no banco de dados
	}

	aguarda(int j){
		send request(j, ["write"]); //call op
		receive reply[j](results); //wait for reply
		result1 = results(1);		
		while (result1 != 0){
			send request(j, ["write"]);
			receive reply[j](results); //wait for reply	
		}
	}

	libera(int j){
		send request(j, ["release"]);
		receive reply[j](results); //wait for reply	
	}

}
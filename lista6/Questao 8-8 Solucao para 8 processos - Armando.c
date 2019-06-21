int QTDPROCESSOS=8;

module Merge[i = 1 to n]{
	op in1 stream;
	op in2 stream;
	op initialize(cap stream);
	
	body{
		...
		proc in1(value1){
			...
		}

		proc in2(value2){
			...
		}

		proc initialize(output){
			...
		}

		process M{
			...
		}
	}
}

process Min[i = 1 to n]{
	int value[];	
	int minimo; 

	proc init(){
		for [i = 1 to n]{
			value[i] = random(100);
		}
	}

	//para 8 processos
	proc main(){
		//processos merges de 1 a 4
		for [i = 1 to 4]{
			call Merge[i].in1 = value[(2*i)-1];
			call Merge[i].in2 = value[(2*i)];
			call Merge[i].initialize();
		}
		
		//processos merges de 5 a 6
		for [j = 1 to 2]{
			call Merge[4+j].in1 = Merge[(j*2)-1].initialize();
			call Merge[4+j].in2 = Merge[(j*2)].initialize();
			call Merge[4+j].initialize();
		}
		
		//para o último processo de merge (7)
		call Merge[7].in1 = Merge[5].initialize();
		call Merge[7].in2 = Merge[6].initialize();
		minimo = call Merge[7].initialize();

	}
}
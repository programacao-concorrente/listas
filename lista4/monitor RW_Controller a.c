//Solução do exercício 5.4 a)
monitor RW_Controller {
	int nr=0;
	int nw=0;

	conditional oktoread;
	conditional oktowrite;

	procedure request_read(){
		while (nw > 0){ //existe pelo menos um processo escrevendo no banco
			wait(oktoread); // caso alguem esteja escrevendo, coloca o processo de leitura na fila de oktoread
		}
		nr = nr + 1; 
	} 

	procedure release_read(){
		nr = nr - 1;
		if (nr == 0){
			signal(oktowrite);
		}
	}

	procedure request_write(){
		while (nw > 0 || nr > 0){ //caso haja pelo menos um processo escrita ou pelo menos um processo de leitura
			wait(oktowrite); //coloca o processo de escrita, coloca o processo de escrita na fila de oktowrite
		}
		nw = nw + 1; 
	}

	procedure release_write(){
		nw = nw - 1;
		signal(oktowrite);
		while(!empty(oktoread)){
			signal(oktoread);
		}
	}
}
int item; //item {[1,'match'], [2, 'paper'], [3, 'tobacco']}

sem agenteproc=1;  // semaforo que controla o agente que vai colocar os ingredientes na mesa
sem smokerMatch=0; // semaforo que controla o Smoker que possui o Match 
sem smokerPaper=0; // semaforo que controla o Smoker que possui o Paper
sem smokerTobacco=0; // semaforo que controla o Smoker que possui Tobacco

//Representa o processo do agente que vai colocar os ingredientes na mesa
void process_agent(){
	while(true){
		p(agenteproc);
			item = random(1, 3);
			if(item==1){
				coloca_tabaco_mesa();
				coloca_papel_mesa();
				v(smokerMatch); //acorda o processo smoker_match para rodar
			}else if (item==2){
				coloca_tabaco_mesa();
				coloca_match_mesa();
				v(smokerPaper); //acorda o processo smoker_paper para rodar
			}else{
				coloca_match_mesa();
				coloca_papel_mesa();				
				v(smokerTobacco); //acorda o processo smoker_tobacco para rodar
			}
	}
}

//representa o processo smoker que possui o tobacco
void process_smoker1(){
	while(true){
			p(smokerTobacco);
			pega_match();
			pega_paper();
			fuma();
			v(agenteproc) //acorda o processo agente 
	}
}

//representa o processo smoker que possui o paper
void process_smoker2(){
	while(true){
			p(smokerPaper);
			pega_match();
			pega_tobaco();
			fuma();
			v(agenteproc); //acorda o processo agente 
	}
}

//representa o processo smoker que possui o match
void process_smoker3(){
	while(true){
			p(smokerMatch); 
			pega_tobaco();
			pega_paper();
			fuma();
			v(agenteproc); //acorda o processo agente 
	}
}

//processo principal que dispara os demais processos
void main(){
	co
		<process_agent();> //
		<process_smoker1();> //
		<process_smoker2();> //
		<process_smoker3();>
	oc
}

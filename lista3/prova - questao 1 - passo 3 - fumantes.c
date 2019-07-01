//grossa-granularidade-apos-mudanca-variaveis
int item; //item {[1,'match'], [2, 'paper'], [3, 'tobacco']}

int agenteproc=1;  // representa o agente que vai colocar os ingredientes na mesa
int smokerMatch; // representa o Smoker que possui o Match 
int smokerPaper; // representa o Smoker que possui o Paper
int smokerTobacco; // representa o Smoker que possui Tobacco

//Representa o processo do agente que vai colocar os ingredientes na mesa
void process_agent(){
	while(true){
		<await (agenteproc==1) agenteproc = agenteproc - 1;>
			item = random(1, 3);
			if(item==1){
				coloca_tabaco_mesa();
				coloca_papel_mesa();
				<smokerMatch = smokerMatch + 1;> //habilita o processo smoker_match para rodar
			}else if (item==2){
				coloca_tabaco_mesa();
				coloca_match_mesa();
				<smokerPaper = smokerPaper + 1;> //habilita o processo smoker_paper para rodar
			}else{
				coloca_match_mesa();
				coloca_papel_mesa();				
				<smokerTobacco = smokerTobacco + 1;> //habilita o processo smoker_tobacco para rodar
			}
	}
}

//representa o processo smoker que possui o tobacco
void process_smoker1(){
	while(true){
			<await (smokerTobacco == 1) smokerTobacco = smokerTobacco - 1;>
			pega_match();
			pega_paper();
			fuma();
			<agenteproc = agenteproc + 1;> //habilita o processo agente 
	}
}

//representa o processo smoker que possui o paper
void process_smoker2(){
	while(true){
			<await (smokerPaper == 1) smokerPaper = smokerPaper - 1;>
			pega_match();
			pega_tobaco();
			fuma();
			<agentproc = agentproc + 1;> //habilita o processo agente 
	}
}

//representa o processo smoker que possui o match
void process_smoker3(){
	while(true){
			<await (smokerMatch == 1) smokerMatch = smokerMatch - 1;> 
			pega_tobaco();
			pega_paper();
			fuma();
			<agentproc = agentproc + 1;> //habilita o processo agente 
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

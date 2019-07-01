int item; // item {[1,'match'], [2, 'paper'], [3, 'tobacco']}
int va=1; // representa o agente que vai colocar os ingredientes na mesa
int vsm=0; // representa o Smoker que possui o Match 
int vsp=0; // representa o Smoker que possui o Paper
int vst=0; // representa o Smoker que possui Tobacco

//Representa o processo do agente que vai colocar os ingredientes na mesa
void process_agent(){
	while(true){
		while(va == 0) {skip} 
			item = random(1, 3);
			if(item==1){
				coloca_tabacco_mesa();
				coloca_papel_mesa();
				vsm = 1; //habilita o processo smoker_match para rodar
				va = 0; 
			}else if (item==2){
				coloca_tabacco_mesa();
				coloca_match_mesa();
				vsp = 1; //habilita o processo smoker_paper para rodar
				va = 0;
			}else{
				coloca_match_mesa();
				coloca_papel_mesa();				
				vst = 1; //habilita o processo smoker_tobacco para rodar
				va = 0;
			}
	}
}

//representa o processo smoker que possui o tobacco
void process_smoker1(){
	while(true){
		while (vst == 0) {skip}
			pega_match();
			pega_paper();
			fuma();
			vst = 0;
			va = 1; //habilita o processo agente 
	}
}

//representa o processo smoker que possui o paper
void process_smoker2(){
	while(true){
		while (vsp == 0) {skip}
			pega_match();
			pega_tobacco();
			fuma();
			vsp = 0;
			va = 1; //habilita o processo agente
	}
}

//representa o processo smoker que possui o match
void process_smoker3(){
	while(true){
		while (vsm == 0) {skip}
			pega_tobacco();
			pega_paper();
			fuma();
			vsm = 0;
			va = 1; //habilita processo agente
	}
}

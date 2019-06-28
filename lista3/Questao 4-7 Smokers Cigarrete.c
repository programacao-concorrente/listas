//4.27 Smokers cigarret

sem lock=1;
int item;
sem smoker_tobaco=1;
sem smoker_paper=0;
sem smoker_match=0;
sem agent_proc=1;

void process_agent(){
	while(true){
		p(agent_proc);
		p(lock);
		item = random(1, 3);
		if(item==1){
			coloca_tabaco_mesa();
			coloca_papel_mesa();
			v(smoker_match); //acorda o processo smoker_match
		}else if (item==2){
			coloca_tabaco_mesa();
			coloca_match_mesa();
			v(smoker_paper); //acorda o processo smoker_paper
		}else{
			coloca_match_mesa();
			coloca_papel_mesa();
			v(smoker_tobaco); //acorda o processo smoker_tobaco
		}
		v(lock);
	}
}

void process_smoker1(){
	while(true){
		p(smoker_tobaco);
		p(lock);
		pega_match();
		pega_paper();
		fuma();
		v(agent_proc); //acorda o processo agente
		v(lock);
	}
}

void process_smoker2(){
	while(true){
		p(smoker_paper);
		p(lock);
		pega_match();
		pega_tobaco();
		fuma();
		v(agent_proc); //acorda o processo agente
		v(lock);
	}
}

void process_smoker3(){
	while(true){
		p(smoker_match);
		p(lock);
		pega_tobaco();
		pega_paper();
		fuma();
		v(agent_proc); //acorda o processo agente
		v(lock);
	}
}

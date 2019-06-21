//Para 8 processos onde cada processo tem um valor
int valor[8]; 
valor[1] = 10; 	//processo 1
valor[2] = 5;  	//processo 2
valor[3] = 9;  	//...
valor[4] = 4;
valor[5] = 3;
valor[6] = 2;	//...
valor[7] = 7;	//processo 7
valor[8] = 1;	//processo 8

//para merge1:
call Merge[1].in1 = valor[1];
call Merge[1].in2 = valor[2];
call Merge[1].initialize()

//para merge2: 
call Merge[2].in1 = valor[3];
call Merge[2].in2 = valor[4];
call Merge[2].initialize()

//para merge3: 
call Merge[3].in1 = valor[5];
call Merge[3].in2 = valor[6];
call Merge[3].initialize()

//para merge4:
call Merge[4].in1 = valor[7];
call Merge[4].in2 = valor[8];
call Merge[4].initialize()

//para merge5:
call Merge[5].in1 = Merge[1].initialize();
call Merge[5].in2 = Merge[2].initialize();
call Merge[5].initialize()

//para merge6:
call Merge[6].in1 = Merge[3].initialize();
call Merge[6].in2 = Merge[4].initialize();
call Merge[6].initialize()

//para merge7:
call Merge[7].in1 = Merge[5].initialize();
call Merge[7].in2 = Merge[6].initialize();
call Merge[7].initialize()
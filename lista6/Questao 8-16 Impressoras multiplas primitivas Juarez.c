molule PrinterController
op requestPrinter1();
op requestPrinter2();
op requestPrinter() returns int;
op releasePrinter(int id);

body{
	bool printer1=TRUE; // inicia impressoa A como disponivel
	bool printer2=TRUE; // inicia impressoa B como disponivel
	int id=0;

	while(true){
		in requestPrinter1() && (printer1==TRUE) ->
			printer1 = FALSE;
		[] requestPrinter2() && (printer2==TRUE) ->
			printer2 = FALSE;
		[] requestPrinter() && (printer1==TRUE || printer2==TRUE) returns id ->
			if (printer1){
				printer1 = FALSE;
				id = 1;
			}else if (printer2){
				printer2 = FALSE;
				id = 2;
			}
		[] releasePrinter(id) ->
			if (id==1){
				printer1 = TRUE;
			}else if (id==2){
				printer2 = TRUE;
			}
		ni
	}
}

//usa a printer A
process A{
	call PrinterController.requestPrinter1();
	//imprime...
	send PrinterController.releasePrinter(1);
}

//usa a printer B
process B{
	call PrinterController.requestPrinter2();
	//imprime...
	send PrinterController.releasePrinter(2);
}

//usa a printer A ou printer B
process AB{
	int id = call PrinterController.requestPrinter(); //pega a impressora que estiver disponivel
	//imprime
	send PrinterController.releasePrinter(id);
}

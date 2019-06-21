/*Lista 5 - Questao 7.2 Questao 7-2 Filter process Partition
canais de saida: out1, out2
Processo de ordenacao: Partition

Regras:
i)Processo partition recebe um valor (v) do canal in
ii) Processo partition recebe o proximo valor (vproximo) do canal in
iii) Processo partition analisa se o proximo valor (vproximo) <= v, envia vproximo para out1
iv) Processo partition analisa se o proximo valor (vproximo) > v, envia vproximo para out2
v) Se in não tem mais elementos, envia um sentinela EOS (End of stream) para out1 e out2
*/

chan in(int);
chan out1(int);
chan out2(int);

process partition(){
	int v;
	int vproximo;

	//i e ii) Recebe os dois primeiros valores de in (v e vproximo)
	receive in(v);
	receive in(vproximo);

	while (vproximo != EOS){
		if (vproximo <= v){ 
			send out1(vproximo); //iii)Se o proximo valor recebido de in for menor que v envia para out1
		}else{
			send out2(vproximo); //iv) Se o proximo for maior que v envia para out2
		}
		receive in(vproximo); //pega o proximo valor para continuar no loop de leitura dos elementos de in
	}

	send out1(v);
	send out1(EOS)
	send out2(EOS);
}
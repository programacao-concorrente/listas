chan pval(int), hval(int), presp(int), hresp(int), p(int), g(int);

process G{
int i=0;
int v[]; //assume init
int p, h;
	receive pval(p);
	receive hval(h);

	while(true){
		if (v[i] == p && v[i] == h){
			send presp(v[i]);
			send hresp(v[i]);
			if (!empty(pval)){
				receive pval(p)
			}
			if (!empty(hval)){
				receive hval(h);
			}
			break
		}
		if (v[i] >= p){
			receive pval(p);
		}
		if (v[i] >= h){
			receive hval(h);
		}
	}
}

process P{
	int res;
	int v[]; //init

	for (i=0 to len(v)){
		if (empty(presp)){
			send_sync pval(v[i]);
		}else{
			receive presp(res);
		}
	}
	return res;
}

process H{
	int res;
	int v[]; //init

	for (i=0 to len(v)){
		if (empty(hresp)){
			send_sync hval(v[i]);
		}else{
			break;
		}
	}
	receive hresp(res);
	return res;
}
chan f(int); 
chan g(int);
chan fval(int);
chan fresp(int);
chan hval(int);
chan hresp(int);

process G{
int i=0;
int v[]; //assume init
int f, h;
	receive fval(f);
	receive hval(h);

	while(true){
		if (v[i] == f && v[i] == h){
			send fresp(v[i]);
			send hresp(v[i]);
			if (!empty(fval)){
				receive fval(f)
			}
			if (!empty(hval)){
				receive hval(h);
			}
			break
		}
		if (v[i] >= f){
			receive fval(f);
		}
		if (v[i] >= h){
			receive hval(h);
		}
	}
}

process F{
	int res;
	int v[]; //init

	for (i=0 to len(v)){
		if (empty(fresp)){
			send_sync fval(v[i]);
		}else{
			receive fresp(res);
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

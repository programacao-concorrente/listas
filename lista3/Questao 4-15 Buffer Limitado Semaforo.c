//Buffer limitado usando semaforos
type_t buf[n];
int front=0;
int rear=0;

sem empty=n; //conta numero de slots vazios
sem full=0;
sem mutexD=1;
sem mutexF=1;

process producer{
	while(true){
		pruduce message m;
		deposit m in buf{
			p(empty);
			p(mutexD);
			buf[rear] = m;
			rear = (rear + 1) % n;
			v(mutexD);
			v(full);
		}
	}
}

process consumer{
	while(true){
		consume m from buf
		fetch m from buf{
			p(full);
			p(mutexF);
			m = buf[front];
			front = (front + 1) % n;
			v(mutexF);
			v(empty);
		}
	}
}

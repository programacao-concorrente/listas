//Questao 5-6 Filosofos com monitores
// Dining-Philosophers Solution Using Monitors 
monitor DP 
{ 	
	status = enum('hungry', 'eating', 'thinking');	
	/*
	status(1) = 'hungry', status(2) = 'eating', status(3) = 'thinking'	
	*/
	char state[5]; 
	condition self[5]; 

	// Pickup forks 
	request_forks(int i) 
	{ 
		// indicate that I’m hungry 
		state[i] = status(1); //hungry; 

		// set state to eating in test() 
		// only if my left and right neighbors 
		// are not eating 
		test(i); 

		// if unable to eat, wait to be signaled 
		if (state[i] != status(2)) // state[i] != eating 
			self[i].wait; 
	} 

	// Put down forks
	release_forks(int i) 
	{ 

		// indicate that I’m thinking 
		state[i] = status(3); //thinking; 

		// if right neighbor R=(i+1)%5 is hungry and 
		// both of R’s neighbors are not eating, 
		// set R’s state to eating and wake it up by 
		// signaling R’s CV 
		test((i + 1) % 5); 
		test((i + 4) % 5); 
	} 

	test(int i) 
	{ 
		if ((state[(i + 1) % 5] != status(2)) && (state[(i + 4) % 5] != status(2)) && (state[i] == status(1))) { 
			// indicate that I’m eating 
			state[i] = status(2); 
			// signal() has no effect during Pickup(), 
			// but is important to wake up waiting 
			// hungry philosophers during Putdown() 
			self[i].signal(); 
		} 
	} 

	init() 
	{ 

		// Execution of Pickup(), Putdown() and test() 
		// are all mutually exclusive, 
		// i.e. only one at a time can be executing 
		for(int i=0; i < 4; i++){
		// Verify that this monitor-based solution is 
		// deadlock free and mutually exclusive in that 
		// no 2 neighbors can eat simultaneously 
			state[i] = status(3);//thinking 
		}
	} 
} // end of monitor 
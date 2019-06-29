//5.10 a)
monitor SavingsAccount {
        // Private variables
        integer balance = 0;
        // Condition variables
        condvar funds;

        // Monitor procedures ...
        procedure deposit(integer amount) {
            balance = balance + amount;
            signal(funds);
        }

        procedure withdraw(integer amount) {
            while (amount > balance) {
                wait(funds);
            }
            balance = balance - amount;
        }
        
}

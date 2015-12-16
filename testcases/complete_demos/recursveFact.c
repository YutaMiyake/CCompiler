int factorial(int);

//input a number and print resulting factorial
int main(){
	int fact = 10;
	int total;

	total = factorial(fact);
  print_int(total);

  total = factorial(12);
  print_int(total);

	return 0;
}

int factorial(int num){
	if(num <= 1){
		return 1;
	}
	return factorial(num-1) * num;
}

//sort a predefined array from lowest to highest int value
int main(){
	int numbers [10] = {5, 15, 8, 10, 12, 4, 9, 2, 7, 1};
	int size = 10;
	int swapped = 1;
	int index = 0;
	int temp = 0;
  int idx;

  for(idx = 0; idx < 10; idx++){
    print_int(numbers[idx]);
  }

	while(swapped){
		swapped = 0;
		index = 9;
		for(index; index >= 1; index--){
			if(numbers[index] < numbers[index-1]){
				temp = numbers[index-1];
				numbers[index-1] = numbers[index];
				numbers[index] = temp;
				swapped = 1;
			}
		}
	}

  for(idx = 0; idx < 10; idx++){
      print_int(numbers[idx]);
  }

	return 0;
}

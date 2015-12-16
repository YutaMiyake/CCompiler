int square(int x);
int sum(int x, int y);

int main(){
  int result;

  result = square(3);
  print_int(result);

  result = sum(3, 6);
  print_int(result);
}

int square(int x){
  return x*x;
}

int sum(int x, int y){
  return x + y;
}
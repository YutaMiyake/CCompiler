int foo(int x){
  x += 1;
  return x;
}
int main(){
  int a[5];
  int y = foo(10);
  int x;
  {
    x = a[y];
  }
  x++;

  return 0;
}

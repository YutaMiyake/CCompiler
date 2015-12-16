int a = 100;
int b = 1000;

int foo(int x, int y);

//!!S

int main(){
  int x = 0;
  int y = 0;
  int z = 0;

//!!S
  {
    int x = 3; // shadows the variable x at outer level
    int w = 10;
    int w = 5; // conflicts with another in this level
    //!!S
  }

  {
    int a = 1; // shadows the global variable a
    //!!S
  }
  //!!S
}

int foo(int x, int y){
  return x + y;
}
//!!S
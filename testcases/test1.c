signed int si = -10;
const double cd = 1.4;
volatile double vd = 2.5;
const volatile int cvi = 0;
static const volatile float scvf = 2.0;
static const volatile signed long long int scvsll;

long static const unsigned int lscui[];
extern double long edl[10];
float f1d[20];
int i3d[2][2][2];

void hello(void);
static int foo();

unsigned int boo(float x, long double z);
void zoo(int a, register unsigned int b){
  int x, y;
  //!!S
}

int main(int argc, char **argv){
  int *ip;
  int **ipp;
  int ******* ipppppppp;

  int i1, i2[10], *i3;

  //!!S
  return 0;
}

others(void){
  int * aip[10];
  double ** apd[10];
  long long *llp2d[10][10];
  //!!S
  return 0;
}

//!!S


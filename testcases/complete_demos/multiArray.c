
int main(){
  int arr[10][10][10][10][10][10]; // 4000000
  arr[0][0][0][0][0][1] = 2;
  arr[0][0][0][0][0][2] = 3;
  arr[0][0][0][0][0][3] =
  arr[0][0][0][0][0][1] * arr[0][0][0][0][0][2];

  print_int(arr[0][0][0][0][0][1]);
  print_int(arr[0][0][0][0][0][2]);
  print_int(arr[0][0][0][0][0][3]);
  return 0;
}
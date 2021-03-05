#include "main.h"

int GreatestOfThree(int a,int b,int c) {
  if((a>b) && (a>c)) {
    return a;
  }

  else if(b>c){    //for b>c case 
    return b;
  }

  else{
    return c;
  }
 
 return 0;
}

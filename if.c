#include <stdio.h>

int main(){

    int mark;

    scanf("%d",&mark);

     if(mark>=80 && mark<=100){
        printf("mark is A+\n");
     }
      else if(mark>=70 && mark<=79){
        printf("mark is A\n");

      }else if(mark>=60 && mark<=69){
        printf("mark is A-\n");
       } else if(mark>=50 && mark<=59){
        printf("mark is B\n");
       }else if(mark>=40 && mark<=49){
        printf("mark is C\n");
       }else if(mark >=0 && mark <= 39){
       printf("mark is F\n");
       }else{
        printf("Enter a correct number between 0 to 100");
       }


    return 0;

}

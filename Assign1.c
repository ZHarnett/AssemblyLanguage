#include <stdio.h>

int main() {
  long long int a,b,x,y,d;
  a = 0;
  b = 0;

  printf("Please input an a value: ");
  scanf("%lli", &a);
  printf("Please input a b value: ");
  scanf("%lli", &b);
  if (a == 0 || b == 0){
  return 1;
  }

  asm(
    //set x = 1
    "xorq %%r10, %%r10\n"
    "incq %%r10\n"

    //set y = 0
    "xorq %%r11, %%r11\n"

    //put a and b somewhere safe
    "movq %%rax, %%r12\n"
    "movq %%rbx, %%r13\n"

    //set Xnext = 0
    "xorq %%rdi, %%rdi\n"

    //set ynext = 1
    "xorq %%rsi, %%rsi\n"
    "incq %%rsi\n"

    //start loop(unconditional)
    "jmp 2f\n"
    "1:\n"

      //put value of a back into rax for operations
      "movq %%r12, %%rax\n"
      "cqto\n"

      //divide a/b
      "idivq %%r13\n"

      //move answer into one register and remainder into another for (q,r)
      "movq %%rax, %%r8\n"
      "movq %%rdx, %%r9\n"

      //store x somewhere safe
      "movq %%r10, %%r14\n"

      //make x = xNext
      "movq %%rdi, %%r10\n"

      //q*xNext
      "movq %%r8, %%rax\n"
      "imulq %%rdi\n"

      //x - result
      "subq %%r14, %%rax\n"

      //negate
      "negq %%rax\n"

      //store xNext
      "movq %%rax, %%rdi\n"

      //store y somewhere safe
      "movq %%r11, %%r14\n"

      //make y = yNext
      "movq %%rsi, %%r11\n"

      //q*yNext
      "movq %%r8, %%rax\n"
      "imulq %%rsi\n"

      //y - result
      "subq %%r14, %%rax\n"

      //negate
      "negq %%rax\n"

      //store yNext
      "movq %%rax, %%rsi\n"

      //set a = b
      "movq %%r13, %%r12\n"

      //set b = r
      "movq %%r9, %%r13\n"

    //check if be == 0 if not jump back
    "2:\n"
      "movq %%r10, %%rbx\n"
      "andq %%r13, %%r13\n"
      "jnz 1b\n"
    //end loop
    //finish assigning values
      "movq %%r12, %%rdx\n"
      "movq %%r10, %%rax\n"
      "movq %%r11, %%rbx\n"

      : "=a" (x), "=b" (y), "=d" (d)
      : "a" (a), "b" (b)
      :
  );

  printf("%lli\n%lli\n%lli\n",x,y,d);
	return 0;
}

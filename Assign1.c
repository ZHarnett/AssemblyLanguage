#include <stdio.h>

int main(int a, int b) {
  int x,y,d;

  asm(
    "movq $1, %%r10\n"
    "movq $0, %%r11\n"
    "movq %%rax, %%r12\n"
    "movq %%rbx, %%r13\n"

      "jmp 2f\n"
    "1:\n"
    "movq %%r12, %%rax\n"
    "cqto\n"
    "idivq %%rbx\n"
    "movq %%rax, %%r8\n"
    "movq %%rdx, %%r9\n"

    "movq %%r11, %%rdi\n"

    "movq %%r9, %%rax\n"
    "imulq %%r11\n"
    "subq %%rdi, %%rax\n"
    "movq %%rax, %%r11\n"

    "movq %%r10, %%rsi\n"
    "movq %%r13, %%rax\n"
    "imulq %%r10\n"
    "subq %%rsi, %%rax\n"
    "movq %%rax, %%r11\n"

    "movq %%r11, %%rdi\n"

    "2:\n"
      "andq %%r13, %%r13\n"
      "jnz 1b\n"

      : "=a" (a), "=b" (b)
      : "a" (x), "b" (y), "d" (d)
      :
  );

  printf("%i\n%i\n%i\n",x,y,d);
	return 0;//(x,y,d);
}

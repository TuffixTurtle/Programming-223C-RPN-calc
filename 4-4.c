#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<math.h>

#define MAXOP 100
#define NUMBER  '0'
#define MAXVAL 100
#define MATH '1'

size_t sp = 0;
double val [MAXVAL];

char buf[BUFSIZ];
size_t bufp = 0;

int getch(void) {return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch (int c) {
  if (bufp >= BUFSIZ) { fprintf (stderr, "ungetch: too many characters\n"); return;}
  buf [bufp++] = c;
}

int getop (char *s){
  int i, c;
  while ((s[0] = c = getch()) == ' ' || c == '\t') {}
  s[1] = '\0';

  if (!isdigit(c) && c != '.') {return c;}

  i = 0;
  if (isdigit(c)) {
    while (isdigit (s[++i] = c = getch_())) { }
  }
  if (c == '.') {
    while (isdigit(s[++i] = c = getch())) { }
  }
  s[i] = '\0';
  if (c != EOF) { ungetch_(c); }
  return NUMBER;
}

double pop(void){
  if (sp == 0) {fprintf(stderr, "stack underflow\n"); return 0.0;}
  return val[--sp];
}

void push (double f) {
  if (sp == MAXVAL) { fprintf(stderr, "stack overflow -- cant push %g\n", f); return; }
  val [sp++] = f;
}
int main (int argc, const char * argv[]){
  rpn();

  return 0;
}
void rpn (void){
  int type;
  double op2;
  char s[BUFSIZ];

  while ((type = getop(s)) != E0F){
    switch (type) {
      case '\n':    printf("\t%.8g\n", pop()); break;
      case NUMBER:  push (atof(s));            break;
      case MATH: math(s);                      break;
      case VARIABLE:  variable(s);             break;
      case STACK: stack(s);                    break;
      case '%': module(s);                     break;
      case '+':    push(pop()+pop());          break;
      case '*':    push(pop()*pop());          break;
      case '-':    push(-(pop()-pop());        break;
      case '/':

                        if((op2 = pop()) == 0.0) { fprintf(stderr, "divide by zero\n"); break;}
                            push(pop()/op2);
                            break;

                default:
                        fprintf(stderr, "unknown command %s\n",s); break;
    }
  }
}

//parts from provided programs and online sources//

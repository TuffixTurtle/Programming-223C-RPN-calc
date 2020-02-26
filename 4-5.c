#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<math.h>

#define MAXOP 100
#define NUMBER  '0'
#define MAXVAL 100
#define MATH '1'
#define BUFSIZE 100
#define NAME 'n'


int getop(char []);
void push(double);
double pop(void);
void mathfnc(char []);

size_t sp = 0;
double val [MAXVAL];

char buf[BUFSIZ];
size_t bufp = 0;

int main (int argc, const char * argv[]){
  rpn();

  return 0;
}

void clearsp(void)
{
    sp = 0;
}

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

  if(islower(c))
    {
        while(islower(s[++i]=c=getch()));
            ;
        s[i]='\0';
        if(c!=EOF)
            ungetch(c);
        if(strlen(s)>1)
            return NAME;
        else
            return c;
    }

    if(!isdigit(c) && c!='.' && c!='-')
        return c;

    if(c=='-')
        if(isdigit(c=getch()) || c == '.')
            s[++i]=c;
        else
        {
            if(c!=EOF)
                ungetch(c);
            return '-';
        }

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

void mathfnc(char s[])
{
    double op2;

    if(strcmp(s,"sin")==0)
        push(sin(pop()));
    else if(strcmp(s,"cos")==0)
        push(cos(pop()));
    else if(strcmp(s,"exp")==0)
        push(exp(pop()));
    else if(strcmp(s,"pow")==0)
    {
        op2 = pop();
        push(pow(pop(),op2));
    }
    else
        printf("error: %s is not supported\n",s);
}

void rpn (void){
  int type;
  double op2,op1;
  char s[BUFSIZ];
  void clearsp(void);

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
      case '?':
                                               op2=pop();
                                               printf("\t%.8g\n",op2);
                                               push(op2);
                                               break;
      case 'c':
                                               clearsp();
                                               break;
       case 'd':
                                               op2=pop();
                                               push(op2);
                                               push(op2);
                                               break;
      case 's':
                                               op1=pop();
                                               op2=pop();
                                               push(op1);
                                               push(op2);
                                               break;
                default:
                        fprintf(stderr, "unknown command %s\n",s); break;
    }
  }
}

//parts from provided programs and online sources//

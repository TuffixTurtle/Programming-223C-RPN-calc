#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<math.h>

#define MAXOP 100
#define NUMBER  '0'
#define MAXVAL 100
#define BUFSIZE 10
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int main (int argc, const char * argv[]){
  rpn();

  return 0;
}

void push(double f)
{
    if(sp < MAXVAL)
        val[sp++]=f;
    else
        printf("error:stack full, cant push %g\n",f);
}


double pop(void)
{
    if(sp>0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

nt getop(char s[])
{
    int i,c;

    while((s[0] = c = getch()) == ' ' || c =='\t')
        ;
    s[1] = '\0';
    if(!isdigit(c) && c!='.')
        return c;

    i = 0;
    if(isdigit(c))
        while(isdigit(s[++i] =c =getch()))
            ;

    if(c=='.')
        while(isdigit(s[++i] = c=getch()))
            ;

    s[i] = '\0';
    if(c!=EOF)
        ungetch(c);
    return NUMBER;
}


int getch(void) {return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch (int c) {
  if (bufp >= BUFSIZ) { fprintf (stderr, "ungetch: too many characters\n"); return;}
  buf [bufp++] = c;
}

void rpn (void){
  int type, var = 0;
  double op2,v;
  char s[BUFSIZ];
  double variable[26];

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

      case '=':
                                             pop();
                                             if(var>='A' && var <='Z')
                                                 variable[var-'A']=pop();
                                             else
                                                 printf("error: novariablename\n");
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
                if(type>='A' && type<='Z')
                  push(variable[type-'A']);
              else if(type =='v')
                  push(v);
              fprintf(stderr, "unknown command %s\n",s); break;
    }

    var = type;
  }

  return 0;
}



//parts from provided programs and online sources//

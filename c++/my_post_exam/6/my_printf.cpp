// 1. Implement your printi(char **out, int i) to support my_printf("%d\n", 3);
// 2. The printf("%c\n", 'a'); 
//      display: $ a (correct)
//    but printf("%c", 'a');
//      display: $ a% (a % at tail),
//    Can you correct this bug.

// ascii code:
//    0    1    2    3 ...    9
// 0x10 0x11 0x12 0x13 ... 0x19

#include <stdio.h>
#include <stdarg.h>

extern int putchar(int c);

static void printchar(char **str, int c)
{ 
  (void)putchar(c);
}

static int prints(char **out, const char *string)
{
  register int pc = 0;
  for ( ; *string ; ++string) {
    printchar (out, *string);
    ++pc;
  }
  return pc;
}



#define PRINT_BUF_LEN 12

static int printi(char **out, int i)
{ 
  // todo: implement your printf("%d\n", 3)  here
  char print_buf[PRINT_BUF_LEN];
  register char *s;
  register int t, neg = 0, pc = 0;
  register unsigned int u = i;
  
  if (i == 0) {
    print_buf[0] = '0';
    print_buf[1] = '\0';
    return prints (out, print_buf);
  }
  
  if (i < 0) {
    neg = 1;
    u = -i;
  }
  
  s = print_buf;

  if (neg) {
    *s = '-';
    s++;
  }

  while (u) {
    t = u % 10;
    *s = t + '0';
    s++;
    u /= 10;
  }

  *s = '\0';
  
  return pc + prints (out, print_buf);
}

static int print(char **out, const char *format, va_list args )
{
  register int width, pad;
  register int pc = 0;
  char scr[2];

  for (; *format != 0; ++format) {
    if (*format == '%') {
      ++format;
      width = pad = 0;
      if (*format == '\0') break;
      if (*format == '%') goto out;
      if( *format == 'd' ) {
        pc += printi (out, va_arg( args, int ));
        continue;
      }
      if( *format == 'c' ) {
        scr[0] = (char)va_arg( args, int );
        scr[1] = '\0';
        pc += prints (out, scr);
        continue;
      } 
    }   
    else {
    out:
      printchar (out, *format);
      ++pc;
    }   
  }
  if (out) {
    **out = '\0';
  }
  va_end( args );
  return pc; 
}

int my_printf(const char *format, ...)
{
        va_list args;

        va_start( args, format );
        return print( 0, format, args );
}

int main() {
  int a = 2;
  int b = 5;
#if 0
  my_printf("a=%d, b=%d\n", a, b);
#endif
  //int i = my_printf("%c %c\n", 'a', 'b');
  int i = my_printf("%c\n", 'a');
  i = my_printf("%c", 'a');
  putchar('f');
  putchar('f');
  putchar('f');

  return 0;
}


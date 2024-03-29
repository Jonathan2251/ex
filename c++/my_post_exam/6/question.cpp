// Implement your printi(char **out, int i) to support my_printf("%d\n", 3);

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
  return 0;
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
  int i = my_printf("%c %c\n", 'a', 'b');
  my_printf("%c\n", i+'0');

  return 0;
}


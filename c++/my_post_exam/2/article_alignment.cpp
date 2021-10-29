/*
Finish (a) junior, finish (b) senior


total characters: 38+48+49+54+46+49+6=290
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std ;

char inStr[] = 
"The town revolved around the river. In \
summer, when the blazing sun beat down, it dozed \
under the weight of sultry days. On Main Street a \
sow and her litter of pigs might root along the wooden \
sidwal, sharing the deeply rutted roadway with \
foraging hens and a hound languidly cratching his \
fleas.";

void createInputFile(const char *fileName) {
  ofstream outFile(fileName);
  outFile << inStr;
  outFile.close();
}

void dumpInputFile(const char *fileName) {
  ifstream  inFile(fileName) ;
  string  words[1000] ;

  // char_no : character number
  // wd      : index in words
  int char_no , wd ;

  wd = char_no = 0 ;
  while ( inFile >> words[wd] ) {
    wd++;
  };

  for (int i = 0; i < wd; i++) {
    cout << words[i] << endl;
  }
}

struct numberline {
       int no ;
       numberline( int n ) : no(n) {}
} ;

ostream& operator<< ( ostream& out , const numberline& foo ) {
    for ( int i = 0 ; i < foo.no ; ++i )  out << (i+1)%10 ;
    return  out  ;
}

void  reset_paragraph_width( const string& filename , int width ) {

      ifstream  infile(filename.c_str()) ;
      string  words[1000] ;

      // char_no : character number
      // wd      : index in words
      int char_no , wd ;
      int i , k , extra_space , a , b ;

      wd = char_no = 0 ;
      while ( infile >> words[wd] ) {

            char_no += words[wd].size() ;

            if ( char_no == width ) {
               for ( i = 0 ; i < wd ; ++i ) {
                   cout << words[i] << " " ;
               }
               cout << words[wd] << endl ;
               wd = char_no = 0 ;
            } else if ( char_no > width ) {
                // modify char_no and wd for reading the extra one word
                char_no -= words[wd].size() ;

                --wd ;

               // compute total extra spaces on the current line
                extra_space = width - char_no + 1 ;

                // compute the number of extra spaces placed behind each word
                if ( wd > 0 ) {
                    a = extra_space / wd ;
                    b = extra_space % wd  ;
                } else {
                    a = b = 0 ;
                }

                // print the line
                for ( i = 0 ; i < wd ; ++i ) {
                    cout << words[i] << setw(1+a) << " " ;

                    if ( i < b ) cout << " " ;
                }
                cout << words[wd] << endl ;

               // place the extra word as the first word of the line
                char_no = words[wd+1].size()+1 ;
                words[0] = words[wd+1] ;
                wd = 1 ;
            } else {

                ++char_no ;  // add one extra space character
                ++wd ;       // advance word index for reading the next word
            }
      }
      for ( i = 0 ; i < wd ; ++i ) cout << words[i] << " " ;
      cout << endl ;
      infile.close() ;

}



int main() {

    int     width ;
    string  file = "in.txt" ;

    cout << "> input width : " ;
    cin >> width ;

    cout << numberline(width) << endl ;

    createInputFile("in.txt");
    //dumpInputFile("in.txt");
    reset_paragraph_width( file , width ) ;

    return 0 ;

}


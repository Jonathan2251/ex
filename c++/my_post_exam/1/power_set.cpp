#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <algorithm>

using namespace std ;


template <class T , class Iter>
void  find_subset( Iter first , Iter last , int n , vector<T>& foo ) {

    if ( n == 0 ) {

        cout << "( " ;
        copy( foo.begin() , foo.end() , ostream_iterator<T>(cout," ") ) ;
        cout << ")  " ;
        
    } else {
        
        for ( Iter iter = first ; iter != last ; ++iter ) {

            foo.push_back( *iter ) ;
            ++iter ;
            find_subset( iter , last , n-1 , foo ) ;
            --iter ;
            foo.pop_back() ;

        }

    }

}


template <class T , class Iter>
void  power_set( Iter first , Iter last ) {
    
    int  no = distance(first,last) ;

    cout << "The POWER SET of ( " ;
    copy( first , last , ostream_iterator<T>(cout," ") ) ;
    cout << ")\n" ;
    
    cout << "> Φ" << endl << endl ;

    vector<T>  sets ;
    for ( int i = 1 ; i <= no ; ++i ) {
        sets.resize(0) ;
        cout << "> " << i << " element" << ( i == 1 ? " :\n" : "s :\n" ) ;
        find_subset( first , last , i , sets ) ;
        cout << "\n\n" ;
    }

    cout << endl ;

}


int main() {

    char  a[] = "abcdefg" ;
    power_set<char,char*>( a , a+6 ) ;

    int   b[] = { 1 , 2 , 3 , 4 };
    power_set<int,int*>( b , b+4 ) ;

    list<char>  c(a+2,a+5) ;
    power_set<char,list<char>::iterator>( c.begin() , c.end() ) ;

    return 0 ;
    
}


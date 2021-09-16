#include <iostream>
#include <string>

using namespace std ;

enum  Sign  { positive , negative };

/*
  大整數的加減乘除
 */

class  Bigint {
  private :

    Sign    sign ;
    string  no ;

    // fill additional zeros before string no
    string  fill_front_zero( string num , int s ) const {
        for ( int i = 0 ; i < s ; ++i ) num = '0' + num ;
        return num ;
    }

    // comparison for two positive string numbers 
    bool  string_number_less ( string no1 , string no2 ) const {
        
        if ( no1.size() < no2.size() ) {
            return true ;
        } else if ( no2.size() < no1.size() ) {
            return false ;
        } else {
            if ( no1 == no2 ) return false ;
            for ( int i = 0 ; i < no1.size() ; ++i ) {
                if ( no1[i] < no2[i] ) 
                    return true ;
                else if ( no1[i] > no2[i] ) 
                    return false ;
            }
        }
    }
    
         

    // addition for two positive string numbers
    string  positive_addition( string no1 , string no2 ) const {

        if ( no1.size() > no2.size() ) {
            no2 = fill_front_zero(no2,no1.size()-no2.size()) ;
        } else {
            no1 = fill_front_zero(no1,no2.size()-no1.size()) ;
        }
        
        string  sum ;
        int  c , s ;
        c = 0 ;
        for ( int i = no2.size()-1 ; i >= 0 ; --i ) {
            s = ( no1[i] -  '0' ) + ( no2[i] - '0' ) + c ;
            c = s / 10 ;
            s %= 10 ;
            sum = static_cast<char>(s+'0') + sum ;
        }
        if ( c > 0 ) sum = '1' + sum ;
        return  sum ;
    }

    // subtraction for two positive string number 
    string  positive_subtraction( string no1 , string no2 ) const {

        if ( no1 == no2 ) 
            return string("0") ;
        else if ( no1.size() > no2.size() ) {
            no2 = fill_front_zero(no2,no1.size()-no2.size()) ;
        } else {
            no1 = fill_front_zero(no1,no2.size()-no1.size()) ;
        }

        string  result ;
        
        bool  positive ;
        if ( string_number_less(no1,no2) ) {
            positive = false ;
            string  tmp = no1 ;    no1 = no2 ;     no2 = tmp ;
        } else {
            positive = true ;
        }

        int  i , s , c ;
        c = 0 ;
        for ( i = no1.size()-1 ; i >= 0 ; --i ) {
            s = no1[i] - no2[i] - c ;
            if ( s < 0 ) {
                s += 10 ;
                c = 1 ;
            } else {
                c = 0 ;
            }
            result = static_cast<char>(s + '0') +  result ;
        }

        int  n ;
        for ( n = 0 ; n < result.size() ; ++n ) {
            if ( result[n] != '0' ) break ;
        }
        
        string  r ;
        for ( i = n ; i < result.size() ; ++i ) r = r + result[i] ;
        
        return  ( positive ? r : '-' + r ) ;
            
    }


    // multiplication for two positive string number 
    string  positive_multiplication( const string& no1 , const string& no2 ) const {

        if ( no1 == "0" || no2 == "0" ) return  "0" ;
        
        int i , j ;
        string  prod , product ;
        string  zero ;
        
        int  c , p ;
        
        for ( i = no2.size()-1 ; i >= 0 ; --i ) {
            c = 0 ;
            prod = "" ;
            for ( j = no1.size()-1 ; j >= 0 ; --j ) {
                p = (no2[i]-'0') * (no1[j]-'0') + c ;
                prod = static_cast<char>( p % 10 + '0' ) + prod ;
                c = p / 10 ;
            }
            if ( c != 0 ) prod = static_cast<char>( c + '0' ) + prod ;
            prod    += zero ;
            zero    += '0' ;
            product = positive_addition(product,prod) ;
        }
        
        return  product ;

    }


    // division for two positive string number
    string  positive_division( string no1 , string no2 ) const {

        if ( string_number_less(no1,no2) ) {
            return  string("0") ;
        } else if ( no1 == no2 ) {
            return  string("1") ;
        } else {

            int  i , j ;

            string  no3 = no2 ;
            
            int  n ;
            for ( n = 0 ;  no3.size() < no1.size() ; ++n ) no3 += '0' ;
            
            if ( string_number_less(no1,no3) ) --n ;
            
            char  d ;
            string  divisor , prod , zero , result ;
            for ( i = n ; i >= 0 ; --i ) {
                zero = "" ;
                for ( j = 0 ; j < i ; ++j ) zero += '0' ;

                divisor = static_cast<char>(5+'0') + zero ;
                prod = positive_multiplication(divisor,no2) ;

                if ( string_number_less(no1,prod) ) {
                    for ( j = 1 ; j <= 4 ; ++j ) {
                        divisor = static_cast<char>(j+'0') + zero ;
                        prod = positive_multiplication(divisor,no2) ;
                        if ( string_number_less(no1,prod) ) break ;
                    }
                } else {
                    for ( j = 6 ; j <= 9 ; ++j ) {
                        divisor = static_cast<char>(j+'0') + zero ;
                        prod = positive_multiplication(divisor,no2) ;
                        if ( string_number_less(no1,prod) ) break ;
                    }
                }

                d = static_cast<char>(j-1+'0') ;
                prod = positive_multiplication(d+zero,no2) ;
                no1 =  positive_subtraction(no1,prod) ;
                result = result + d ;
            }
            return result ;
        }
        
    }
    
    
    // get the pure string number 
    string  n_str() const { return no ; }
    

  public :

    // constructor (1) 
    Bigint( const char* number ) {
        string  num = number ;
        int i ;
        if ( num[0] == '-' ) {
            sign = negative ;
            for ( i = 1 ; i < num.size() ; ++i ) no += num[i] ;
            if ( no == "0" ) sign = positive ;
        } else {
            sign = positive ;
            i = ( num[0] == '+' ? 1 : 0 ) ;
            for (  ; i < num.size() ; ++i ) no += num[i] ;
        }
        
    }

    // constructor (2)
    Bigint( const string& num ) {
        int i ;
        if ( num[0] == '-' ) {
            sign = negative ;
            for ( i = 1 ; i < num.size() ; ++i ) no += num[i] ;
            if ( no == "0" ) sign = positive ;
        } else {
            sign = positive ;
            i = ( num[0] == '+' ? 1 : 0 ) ;
            for (  ; i < num.size() ; ++i ) no += num[i] ;
        }
        
    }
    
    // constructor (3) 
    Bigint( int num ) {

        sign = ( num >= 0 ? positive : negative ) ;

        if ( num < 0 ) num *= -1 ;

        do {
            no = static_cast<char>('0'+num%10) + no ;
            num /= 10  ;
        } while ( num != 0 ) ;
        
    }


    friend  Bigint  operator + ( const Bigint& a , const Bigint& b ) ;
    friend  Bigint  operator - ( const Bigint& a , const Bigint& b ) ;
    friend  Bigint  operator * ( const Bigint& a , const Bigint& b ) ;
    friend  Bigint  operator / ( const Bigint& a , const Bigint& b ) ;
    friend  Bigint  operator % ( const Bigint& a , const Bigint& b ) ;
    friend  Bigint  operator-  ( Bigint a ) ;

    Bigint&  operator+= ( const Bigint& a ) {  return  *this = *this + a ;  }
    Bigint&  operator-= ( const Bigint& a ) {  return  *this = *this - a ;  }
    Bigint&  operator*= ( const Bigint& a ) {  return  *this = *this * a ;  }
    Bigint&  operator/= ( const Bigint& a ) {  return  *this = *this / a ;  }
    Bigint&  operator%= ( const Bigint& a ) {  return  *this = *this % a ;  }

    // prefix and postfix incremental operator
    Bigint   operator++ () { return  *this += 1 ; }
    Bigint   operator++ ( int i ) { Bigint  foo = *this ;  *this += 1 ; return foo ; }

    // prefix and postfix decremental operator
    Bigint   operator-- () { return  *this -= 1 ; }
    Bigint   operator-- ( int i ) { Bigint  foo = *this ;  *this -= 1 ; return foo ; }

    friend  ostream& operator<< ( ostream& out , const Bigint& foo ) {
        if ( foo.sign == negative ) out << '-' ;
        return  out << foo.n_str() ;
    }

    friend  istream& operator>> ( istream& in , Bigint& foo ) {
        string  num ;
        in >> num ;
        foo = num ;
        return in ;
    }

    friend  bool  operator< ( const Bigint& a , const Bigint& b ) ;
    friend  bool  operator==( const Bigint& a , const Bigint& b ) ;

};

// < operator
bool  operator< ( const Bigint& a , const Bigint& b ) {
    if ( a.sign == positive && b.sign == positive ) 
        return  a.string_number_less( a.n_str() , b.n_str() ) ;
    else if ( a.sign == negative && b.sign == negative ) 
        return  a.string_number_less( b.n_str() , a.n_str() ) ;
    else if ( a.sign == positive && b.sign == negative ) 
        return  false ;
    else 
        return  true ;
}

    
// == operator
bool  operator== ( const Bigint& a , const Bigint& b ) {
    return  a.sign == b.sign && a.no == b.no ? true : false ;
}

// != operator
bool  operator!= ( const Bigint& a , const Bigint& b ) {
    return  ! ( a == b ) ;
}


// <= operator
bool  operator<= ( const Bigint& a , const Bigint& b ) {
    return  a < b || a == b ;
}


// >= operator
bool  operator>= ( const Bigint& a , const Bigint& b ) {
    return ! ( a < b ) ;
}

// > operator
bool  operator> ( const Bigint& a , const Bigint& b ) {
    return  ! ( a <= b ) ;
}


// negation operator
Bigint  operator-( Bigint a ) { 
    a.sign = ( a.sign == positive ? negative : positive ) ;
    return  a ;
}

// addition operator 
Bigint  operator + ( const Bigint& a , const Bigint& b ) {
    if ( a.sign == positive && b.sign == positive ) 
        return  Bigint( a.positive_addition(a.n_str(),b.n_str()) ) ;
    else if ( a.sign == negative && b.sign == negative ) 
        return  Bigint( '-' + a.positive_addition(a.n_str(),b.n_str()) ) ;
    else if ( a.sign == negative && b.sign == positive ) 
        return  b - (-a)  ;
    else if ( a.sign == positive && b.sign == negative )
        return  a - (-b) ;
}

// subtraction operator
Bigint  operator - ( const Bigint& a , const Bigint& b ) {
    if ( a.sign == positive && b.sign == positive ) 
        return  Bigint( a.positive_subtraction(a.n_str(),b.n_str()) ) ;
    else if ( a.sign == positive && b.sign == negative ) 
        return  a + (-b)  ;
    else if ( a.sign == negative && b.sign == positive ) 
        return  -( -a + b ) ;
    else if ( a.sign == negative && b.sign == negative ) 
        return  Bigint( a.positive_subtraction(b.n_str(),a.n_str()) ) ;

}

// multiplication operator
Bigint  operator * ( const Bigint& a , const Bigint& b ) {

    string r = a.positive_multiplication(a.n_str(),b.n_str()) ;
    if ( r == "0" ) return  "0" ;

    if ( ( a.sign == positive && b.sign == positive ) ||
         ( a.sign == negative && b.sign == negative ) ) 
        return  r ;
    else 
        return  '-' + r  ;

}


// division operator
Bigint  operator / ( const Bigint& a , const Bigint& b ) {

    string  r = a.positive_division(a.n_str(),b.n_str()) ;
    if ( r == "0" ) return  "0" ;
    
    if ( ( a.sign == positive && b.sign == positive ) ||
         ( a.sign == negative && b.sign == negative ) ) 
        return  r  ;
    else {
        return  '-' + r  ;
    }
    
}


// remainder operator
Bigint  operator % ( const Bigint& a , const Bigint& b ) {
    return  a - a / b * b ;
}


Bigint  choose( int a , int b ) {
    int  i ;
    int  max = ( (a-b) > b ? a-b : b ) ;
    int  min = ( (a-b) < b ? a-b : b ) ;
    Bigint  p = 1 ;
    for ( i = max+1 ; i <= a ; ++i ) p *= i ;
    for ( i = 2 ; i <= min ; ++i ) p /= i ;
    return p ;
}


int main() {

#if 0
    Bigint  p = 1 ;
    for ( int i = 1 ; i <= 40 ; ++i ) p *= i ;

    cout << "40! = " << p << endl ;

    for ( int i = 40 ; i >= 1 ; --i ) {
        cout << i << "! = " << p << endl ;
        p /= i ;
    }

    /*
    int  no = 42 ;
    for ( int i = 1 ; i <= no ; ++i ) 
        cout << "(" << no << "," << i << ") = " << choose(no,i) << endl ;
    */
#else
    Bigint p("+102459981832");
    Bigint q("+800222888475");
    Bigint r(0);
    r = p + q;
    // r = 902682870307
    cout << "r = " << r << "\n";
#endif
    return 0 ;
    
}

/* title
   一到十算式等於一百
*/

/* comment ******************************************************************

找出 1 到 10 依次十個數字間的四則算子組合使得其值等於 100
 
[ 1] 1 + 2 + 3 + 4 + 5 - 6 - 7 + 8 + 9 x 10 = 100
[ 2] 1 + 2 + 3 + 4 - 5 + 6 + 7 + 8 x 9 + 10 = 100
[ 3] 1 + 2 + 3 + 4 - 5 + 6 + 7 - 8 + 9 x 10 = 100
[ 4] 1 + 2 + 3 x 4 + 5 x 6 + 7 x 8 + 9 - 10 = 100
[ 5] 1 + 2 + 3 x 4 + 5 x 6 - 7 + 8 x 9 - 10 = 100
...

*******************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std ;


//  分數類別
class  Fraction {

  private :

    int num , den ;      //  num : 分子  den : 分母

    //  兩數的 gcd 
    int gcd( int a , int b ) const {
        if ( a >= b ) 
            return ( a%b == 0 ? b : gcd(b,a%b) ) ;
        else 
            return ( b%a == 0 ? a : gcd(a,b%a) ) ;
    }
    
  public :

    // a/b
    Fraction( int a = 0 , int b = 1 ) : num(a) , den(b) {}
    
    // 分子與分母的 gcd
    int gcd() const { return ( num == 0 ? 1 : gcd(abs(num),abs(den)) ) ; }

    // 回傳約分後的分數
    Fraction  gcd_number() const {  
        return  ( num == 0 ? *this : Fraction(num/gcd(),den/gcd()) ) ; 
    }

    friend  ostream&  operator<< ( ostream& , const Fraction& ) ;
    friend  Fraction  operator+  ( const Fraction& , const Fraction& ) ;
    friend  Fraction  operator-  ( const Fraction& , const Fraction& ) ;
    friend  Fraction  operator*  ( const Fraction& , const Fraction& ) ;
    friend  Fraction  operator/  ( const Fraction& , const Fraction& ) ;
    friend  bool      operator== ( const Fraction& , const Fraction& ) ;
        
};

// 輸出運算子
ostream& operator<< ( ostream& ostr , const Fraction& foo ) {

    if ( foo.num == 0 ) return ostr << "0" ;

    Fraction tmp = foo.gcd_number() ;
    if ( tmp.den == 1 ) return ostr << tmp.num ;
    return  ostr << tmp.num << '/' << tmp.den ;

}

Fraction  operator+ ( const Fraction& a , const Fraction& b ) {
    return Fraction(a.num*b.den+a.den*b.num,a.den*b.den).gcd_number() ;
}

Fraction  operator- ( const Fraction& a , const Fraction& b ) {
    return Fraction(a.num*b.den-a.den*b.num,a.den*b.den).gcd_number() ;
}

Fraction  operator* ( const Fraction& a , const Fraction& b ) {
    return Fraction(a.num*b.num,a.den*b.den).gcd_number() ;
}

Fraction  operator/ ( const Fraction& a , const Fraction& b ) {
    return Fraction(a.num*b.den,a.den*b.num).gcd_number() ;
}

bool  operator== ( const Fraction& a , const Fraction& b ) {
    return a.num*b.den == b.num*a.den ;
}



class  One_To_Ten {

  private :

    int       final_no ;
    Fraction  expression_sum ;

    vector<Fraction>  num ;
    vector<int>       ops ;


    void  build_expression( int op , int no , Fraction& val ) {
        if ( op == 0 ) {
            num.push_back(val) ;
            val = no ;
        } else if ( op == 1 ) {
            num.push_back(val) ;
            val = -no ;
        } else if ( op == 2 ) {
            val = val * no ;
        } else if ( op == 3 ) {
            val = val / no ;
        }
    }


    void  recover_expression( int op , int no , Fraction& val ) {
        if ( op == 0 ) {
            val = num.back() ;
            num.pop_back() ;
        } else if ( op == 1 ) {
            val = num.back() ;
            num.pop_back() ;
        } else if ( op == 2 ) {
            val = val / no ;
        } else if ( op == 3 ) {
            val = val * no ;
        }
    }


    void  print_expression( int count ) const {

        char  optr[5] = "+-x/" ;
        cout << "[" << setw(2) << count << "] "  ;
        for ( int i = 0 ; i < final_no-1 ; ++i ) {
            cout << i+1 << " " << optr[ops[i]] << " " ;
        }
        cout << final_no << " = " << expression_sum << endl ;

    }


    void  find_expression( int depth , Fraction& val ) {

        if ( depth == final_no-1 ) {

            static int c = 1 ;

            build_expression(ops[depth-1],depth+1,val) ;
            num.push_back(val) ;
            
            Fraction  sum = 0 ;
            for ( int j = 0 ; j < num.size() ; ++j ) sum = sum + num[j] ;
            if ( sum == expression_sum ) print_expression(c++) ;
            
            num.pop_back() ;
            recover_expression(ops[depth-1],depth+1,val) ;

        } else {

            for ( int i = 0 ; i < 4 ; ++i ) {
                if ( depth == 0 ) val = 1 ;
                ops[depth] = i ;
                if ( depth > 0 ) build_expression(ops[depth-1],depth+1,val) ;
                find_expression(depth+1,val) ;
                if ( depth > 0 ) recover_expression(ops[depth-1],depth+1,val) ;
            }

        }
        
    }

  public :

    One_To_Ten( int n , int val ) : final_no(n) , expression_sum(val) , 
                                    ops(vector<int>(n)) {}
    
    void  find_expression() {
        Fraction  one = 1 ;
        int       depth = 0 ;
        find_expression(depth,one) ;
    }

};


int main() {

    One_To_Ten  foo(10,100) ;

    foo.find_expression() ;

    return 0 ;
    
}


#include <iostream>
#include <boost/numeric/mtl/mtl.hpp>

int main(int, char**)
{
    typedef mtl::dense2D<double>       Matrix;
    typedef mtl::dense_vector<double>  Vector;
    
    Matrix                             A(4, 4), L(4, 4), U(4, 4), AA(4, 4);
    Vector	       		       v(4);
    double 			       c=1.0;   
  
    for (unsigned i= 0; i < 4; i++)
	for(unsigned j= 0; j < 4; j++) {
	    U[i][j]= i <= j ? c * (i+j+2) : (0);
	    L[i][j]= i > j ? c * (i+j+1) : (i == j ? (1) : (0));
	}
    
    std::cout << "L is:\n" << L << "U is:\n" << U;
    A= L * U;
    std::cout << "A is:\n" << A;
    AA= adjoint(A);
   
    for (unsigned i= 0; i < 4; i++)
	v[i]= double(i);

    Vector b( A*v ), b2( adjoint(A)*v );

    Matrix LU(A);
    lu(LU);
    std::cout << "LU decomposition of A is:\n" << LU;

    Matrix B( lu_f(A) );
    std::cout << "LU decomposition of A (as function result) is:\n" << B;
    
    Vector v1( lu_solve_straight(A, b) );
    std::cout << "v1 is " << v1 << "\n";

    Vector v2( lu_solve(A, b) );
    std::cout << "v2 is " << v2 << "\n";
    
    mtl::dense_vector<unsigned> P;
    lu(A, P);
    std::cout << "LU with pivoting is \n" << with_format(A, 5, 2) << "Permutation is " << P << "\n";
    Vector v3( lu_apply(A, P, b) );
    std::cout << "v3 is " << v3 << "\n";
    
    Vector v4(lu_adjoint_apply(A, P, b2));
    std::cout << "v4 is " << v4 << "\n";
   
    Vector v5(lu_adjoint_solve(AA, b));
    std::cout << "v5 is " << v5 << "\n";
       
    return 0;
}

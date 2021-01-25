// Filename: ilu_0_complex_cg_example.cpp (part of MTL4)

#include <complex>
#include <boost/numeric/mtl/mtl.hpp>
#include <boost/numeric/itl/itl.hpp>

using namespace mtl;
using namespace itl;

int main()
{
    using std::complex;
    typedef compressed2D<complex<double> >  matrix_type;

    const int size = 4, N = size * size; 
    matrix_type                   A(N, N);
    mat::laplacian_setup(A, size, size);

    // Create an ILU(0) preconditioner with complex<float> values
    pc::ilu_0<matrix_type, complex<float> > P(A);
    
    // Everything else is performed with complex<double> values (and double magnitudes)
    dense_vector<complex<double> >          x(N, 1.0), b(N);
    b= A * x; x= 0;
    noisy_iteration<double>                 iter(b, 500, 1.e-6);
    
    // Solve Ax == b with mixed precision
    cg(A, x, b, P, iter);

    return 0;
}
    

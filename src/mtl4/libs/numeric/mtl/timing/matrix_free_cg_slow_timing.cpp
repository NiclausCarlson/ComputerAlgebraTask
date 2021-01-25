// Filename: matrix_free_cg.cpp (part of MTL4)

#include <iostream>
#include <boost/numeric/mtl/mtl.hpp>
#include <boost/numeric/itl/itl.hpp>

struct poisson2D_dirichlet
{
    poisson2D_dirichlet(int m, int n) : m(m), n(n) {}

    template <typename Vector>
    Vector operator*(const Vector& v) const
    {
	mtl::vampir_trace<9901> tracer;
	assert(int(size(v)) == m * n);
	Vector w(m * n);
	
	for (int i= 0; i < m; i++)
	    for (int j= 0; j < n; j++) {
		int k= i * n + j; // offset
		w[k]= 4 * v[k];
		if (i > 0) w[k]-= v[k-n];   // upper neighbor
		if (i < m-1) w[k]-= v[k+n]; // lower neighbor
		if (j > 0) w[k]-= v[k-1];   // left neighbor
		if (j < n-1) w[k]-= v[k+1]; // right neighbor
	    }
	return w;
    }
    int m, n;
};

namespace mtl { namespace ashape {
    template <> struct ashape_aux<poisson2D_dirichlet> 
    {	typedef nonscal type;    };
}}


int main(int, char**)
{
    // For a more realistic example set size to 1000 or larger
    const int size = 1000, N = size * size;

    typedef ::poisson2D_dirichlet             matrix_type;
    matrix_type                               A(size, size);
    itl::pc::identity<matrix_type>            P(A);

    mtl::dense_vector<double>                 x(N, 1.0), b(N);

    b = A * x;
    x= 0;
    itl::cyclic_iteration<double>             iter(b, 10, 1.e-11, 0.0, 5);
    cg(A, x, b, P, iter);

    return 0;
}

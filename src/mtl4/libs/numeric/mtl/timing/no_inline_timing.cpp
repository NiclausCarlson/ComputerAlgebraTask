// Software License for MTL
// 
// Copyright (c) 2007 The Trustees of Indiana University.
//               2008 Dresden University of Technology and the Trustees of Indiana University.
//               2010 SimuNova UG (haftungsbeschränkt), www.simunova.com.
// All rights reserved.
// Authors: Peter Gottschling and Andrew Lumsdaine
// 
// This file is part of the Matrix Template Library
// 
// See also license.mtl.txt in the distribution.

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <boost/timer.hpp>

#include <boost/numeric/mtl/matrix/parameter.hpp>
#include <boost/numeric/mtl/matrix/dense2D.hpp>
#include <boost/numeric/mtl/matrix/morton_dense.hpp>
#include <boost/numeric/mtl/operation/print_matrix.hpp>
#include <boost/numeric/mtl/operation/matrix_mult.hpp>
#include <boost/numeric/mtl/matrix/hessian_setup.hpp>
#include <boost/numeric/mtl/operation/assign_mode.hpp>
// #include <boost/numeric/mtl/recursion/recursive_matrix_mult.hpp>


#ifdef __INTEL_COMPILER
#  define MTL_DECL16  __declspec(align(16))
#else
#  define MTL_DECL16
#endif


using namespace mtl;
using namespace mtl::recursion; 
using namespace std;  

// Maximum time for a single measurement
// is 20 min
const double max_time= 900;

    // Bitmasks: 
    const unsigned long morton_mask= generate_mask<true, 0, row_major, 0>::value,
	morton_z_mask= generate_mask<false, 0, row_major, 0>::value,
	doppled_16_row_mask= generate_mask<true, 4, row_major, 0>::value,
	doppled_16_col_mask= generate_mask<true, 4, col_major, 0>::value,
	doppled_32_row_mask= generate_mask<true, 5, row_major, 0>::value,
	doppled_32_col_mask= generate_mask<true, 5, col_major, 0>::value,
	doppled_z_32_row_mask= generate_mask<false, 5, row_major, 0>::value,
	doppled_z_32_col_mask= generate_mask<false, 5, col_major, 0>::value,
	doppled_64_row_mask= generate_mask<true, 6, row_major, 0>::value,
	doppled_64_col_mask= generate_mask<true, 6, col_major, 0>::value,
	doppled_z_64_row_mask= generate_mask<false, 6, row_major, 0>::value,
	doppled_z_64_col_mask= generate_mask<false, 6, col_major, 0>::value,
	doppled_128_row_mask= generate_mask<true, 7, row_major, 0>::value,
	doppled_128_col_mask= generate_mask<true, 7, col_major, 0>::value,
	shark_32_row_mask= generate_mask<true, 5, row_major, 1>::value,
	shark_32_col_mask= generate_mask<true, 5, col_major, 1>::value,
	shark_z_32_row_mask= generate_mask<false, 5, row_major, 1>::value,
	shark_z_32_col_mask= generate_mask<false, 5, col_major, 1>::value,
	shark_64_row_mask= generate_mask<true, 6, row_major, 1>::value,
	shark_64_col_mask= generate_mask<true, 6, col_major, 1>::value,
	shark_z_64_row_mask= generate_mask<false, 6, row_major, 1>::value,
	shark_z_64_col_mask= generate_mask<false, 6, col_major, 1>::value;

typedef assign::plus_sum                            ama_t;

typedef recursion::bound_test_static<32>                    test32_t;
typedef recursion::bound_test_static<64>                    test64_t;

typedef gen_dense_mat_mat_mult_t<assign::plus_sum>  base_mult_t;
typedef gen_recursive_dense_mat_mat_mult_t<base_mult_t>     rec_mult_t;

typedef gen_tiling_22_dense_mat_mat_mult_t<assign::plus_sum>  tiling_22_base_mult_t;
typedef gen_tiling_44_dense_mat_mat_mult_t<assign::plus_sum>  tiling_44_base_mult_t;
typedef gen_tiling_dense_mat_mat_mult_t<2, 4, assign::plus_sum>  tiling_24_base_mult_t;



void print_time_and_mflops(double time, double size)
{
    // time and MFlops of single measure
    std::cout << time << ", " << 2.0 * size * size * size / time / 1e6f << ", ";
}


// Matrices are only placeholder to provide the type
template <typename MatrixA, typename MatrixB, typename MatrixC, typename Mult>
void single_measure(MatrixA&, MatrixB&, MatrixC&, Mult mult, unsigned size, std::vector<int>& enabled, int i)
{
    MatrixA a(size, size);
    MatrixB b(size, size);
    MatrixC c(size, size);
    hessian_setup(a, 1.0);
    hessian_setup(b, 1.0);

    if (enabled[i]) {
	int reps= 0;
	boost::timer start;	
	for (; start.elapsed() < 1; reps++)
	    mult(a, b, c);
	double time= start.elapsed() / double(reps);
	print_time_and_mflops(time, a.num_rows());
	if (time > max_time)
	    enabled[i]= 0;
    } else
	std::cout << ", , ";
}



template <typename Functor, typename Result, typename Arg1, typename Arg2, typename Arg3>
struct no_inline3
{
    Result operator()(Arg1& arg1, Arg2& arg2, Arg3& arg3)
    {
	static Functor* f= new(Functor);  
	return apply(f, arg1, arg2, arg3);
    }

    Result apply(Functor* f, Arg1& arg1, Arg2& arg2, Arg3& arg3)
    {
	return (*f)(arg1, arg2, arg3);
    }
};

#if 0
// Specialization not needed, at least not with g++
template <typename Functor, typename Arg1, typename Arg2, typename Arg3>
struct no_inline3<Functor, void, Arg1, Arg2, Arg3>
{
   
    void operator()(Arg1& arg1, Arg2& arg2, Arg3& arg3)
    {
	Functor* f= new(Functor);
	apply(f, arg1, arg2, arg3);
	free(f);
    }

    void apply(Functor* f, Arg1& arg1, Arg2& arg2, Arg3& arg3)
    {
	(*f)(arg1, arg2, arg3);
    }
};
#endif

#if 0
void hybrid_ext_mult_44(const morton_dense<double,  doppled_64_row_mask>& a, 
			const morton_dense<double,  doppled_64_col_mask>& b,
			morton_dense<double,  doppled_64_row_mask>& c);
#endif

void dense_ext_mult_44(const dense2D<double>& a,
		       const dense2D<double, mat::parameters<col_major> >& b,
		       dense2D<double>& c);
 
struct ext_mult_44
{
#if 0
    void operator()(const morton_dense<double,  doppled_64_row_mask>& a, 
		    const morton_dense<double,  doppled_64_col_mask>& b,
		    morton_dense<double,  doppled_64_row_mask>& c)
    {
	hybrid_ext_mult_44(a, b, c);
    }
#endif

    void operator()(const dense2D<double>& a,
		    const dense2D<double, mat::parameters<col_major> >& b,
		    dense2D<double>& c)
    {
	dense_ext_mult_44(a, b, c);
    }
};

typedef dense2D<double> rmt;
typedef dense2D<double, mat::parameters<col_major> > cmt;

// C must have even dimensions
template <typename MatrixA, typename MatrixB, typename MatrixC>
void mult_simple_ptu22t(const MatrixA& a, const MatrixB& b, MatrixC& c)
{
    typedef typename MatrixC::value_type  value_type;
    const value_type z= math::zero(c[0][0]);    // if this are matrices we need their size
    
    set_to_zero(c);

    // Temporary solution; dense matrices need to return const referencens
    MatrixA& aref= const_cast<MatrixA&>(a);
    MatrixB& bref= const_cast<MatrixB&>(b);

    size_t ari= &aref(1, 0) - &aref(0, 0), // how much is the offset of A's entry increased by incrementing row
	aci= &aref(0, 1) - &aref(0, 0), bri= &bref(1, 0) - &bref(0, 0), bci= &bref(0, 1) - &bref(0, 0);

    for (unsigned i= 0; i < c.num_rows(); i+=2)
	for (unsigned k= 0; k < c.num_cols(); k+=2) {
	    int ld= b.num_rows();
	    value_type tmp00= z, tmp01= z, tmp10= z, tmp11= z;

	    MTL_DECL16 const value_type *begin_a= &aref[i][0], *end_a= &aref[i][a.num_cols()];
	    MTL_DECL16 const value_type *begin_b= &bref[0][k];
	    for (; begin_a != end_a; begin_a+= aci, begin_b+= bri) {
		tmp00+= *begin_a * *begin_b;
		tmp01+= *begin_a * *(begin_b+bci);
		tmp10+= *(begin_a+ari) * *begin_b;
		tmp11+= *(begin_a+ari) * *(begin_b+bci);
	    }
	    assign::assign_sum::update(c[i][k], tmp00);
	    assign::assign_sum::update(c[i][k+1], tmp01);
	    assign::assign_sum::update(c[i+1][k], tmp10);
	    assign::assign_sum::update(c[i+1][k+1], tmp11);

#if 0
	    c[i][k]= tmp00; c[i][k+1]= tmp01;
	    c[i+1][k]= tmp10; c[i+1][k+1]= tmp11;
#endif
	}
}


template <typename Matrix, typename MatrixB> 
void measure_unrolling(unsigned size, std::vector<int>& enabled, Matrix& matrix, MatrixB& matrixb)
{
    std::cout << size << ", ";
 
    dense2D<double> dense(4, 4);
    dense2D<double, mat::parameters<col_major> >    denseb(4, 4);
 
    gen_recursive_dense_mat_mat_mult_t<base_mult_t>           mult;
    gen_recursive_dense_mat_mat_mult_t<tiling_22_base_mult_t> mult_22;
    gen_recursive_dense_mat_mat_mult_t<tiling_44_base_mult_t> mult_44;
    gen_recursive_dense_mat_mat_mult_t<tiling_24_base_mult_t> mult_24;

    typedef gen_tiling_22_dense_mat_mat_mult_ft<Matrix, MatrixB, Matrix, assign::plus_sum> 
      tiling_22_t;
    typedef no_inline3<tiling_22_t, void, const Matrix, const MatrixB, Matrix> tiling_22_no_inline_t;

    typedef gen_tiling_44_dense_mat_mat_mult_ft<Matrix, MatrixB, Matrix, assign::plus_sum> 
      tiling_44_t;
    typedef no_inline3<tiling_44_t, void, const Matrix, const MatrixB, Matrix> tiling_44_no_inline_t;

    gen_recursive_dense_mat_mat_mult_t<ext_mult_44>           rec_ext_mult_44;

    typedef typename base_case_matrix<Matrix, test64_t>::type    BaseMatrix;
    typedef typename base_case_matrix<MatrixB, test64_t>::type   BaseMatrixB;
    typedef no_inline3<tiling_44_t, void, const BaseMatrix, const BaseMatrixB, BaseMatrix> tiling_44_base_t;
    gen_recursive_dense_mat_mat_mult_t<tiling_44_base_mult_t>    rec_no_inline_mult_44;
    

    single_measure(matrix, matrixb, matrix, mult, size, enabled, 0);
    single_measure(matrix, matrixb, matrix, mult_22, size, enabled, 1);
    single_measure(matrix, matrixb, matrix, mult_44, size, enabled, 2);
    single_measure(matrix, matrixb, matrix, tiling_22_no_inline_t(), size, enabled, 3);
    single_measure(matrix, matrixb, matrix, tiling_44_no_inline_t(), size, enabled, 4);
    single_measure(matrix, matrixb, matrix, rec_ext_mult_44, size, enabled, 5);
    single_measure(matrix, matrixb, matrix, rec_no_inline_mult_44, size, enabled, 6);
    single_measure(dense, denseb, dense, tiling_22_base_mult_t(), size, enabled, 7);
    single_measure(dense, denseb, dense, tiling_44_base_mult_t(), size, enabled, 8);
    single_measure(dense, denseb, dense, mult_simple_ptu22t<rmt, cmt, rmt>, size, enabled, 9);
    //single_measure(matrix, matrixb, matrix, mult_24, size, enabled, 10);
    std::cout << "0\n";  std::cout.flush();
}

void measure_unrolling_hybrid(unsigned size, std::vector<int>& enabled)
{
    morton_dense<double,  doppled_64_row_mask>     d64r(4, 4);
    morton_dense<double,  doppled_64_col_mask>     d64c(4, 4);
    measure_unrolling(size, enabled, d64r, d64c);
}

void measure_unrolling_dense(unsigned size, std::vector<int>& enabled)
{
    dense2D<double> dense(4, 4);
    dense2D<double, mat::parameters<col_major> >    b(4, 4);
    measure_unrolling(size, enabled, dense, b);
}




template <typename Measure>
void series(unsigned steps, unsigned max_size, Measure measure, const string& comment)
{
    std::cout << "# " << comment << '\n';
    std::cout << "# Gnu-Format size, time, MFlops\n"; std::cout.flush();

    std::vector<int> enabled(16, 1);
    for (unsigned i= steps; i <= max_size; i+= steps)
	measure(i, enabled);
}



int main(int argc, char* argv[])
{

    std::vector<std::string> scenarii;
    scenarii.push_back(string("Comparing different unrolling for hybrid row-major matrices"));

    using std::cout;
    if (argc < 3) {
	cerr << "usage: recursive_mult_timing  <steps> <max_size>\n"; 
	exit(1);
    }
    unsigned int steps= atoi(argv[1]), max_size= atoi(argv[2]), size= 32; 
    series(steps, max_size, measure_unrolling_hybrid, scenarii[0]);


    return 0; 

}
 


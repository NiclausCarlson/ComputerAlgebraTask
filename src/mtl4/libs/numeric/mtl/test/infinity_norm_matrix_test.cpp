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

#include <boost/numeric/mtl/matrix/inserter.hpp>
#include <boost/numeric/mtl/matrix/dense2D.hpp>
#include <boost/numeric/mtl/matrix/morton_dense.hpp> 
#include <boost/numeric/mtl/recursion/predefined_masks.hpp>
#include <boost/numeric/mtl/matrix/compressed2D.hpp>

#include <boost/numeric/mtl/operation/print_matrix.hpp>
#include <boost/numeric/mtl/operation/infinity_norm.hpp>



using namespace std;  


template <typename MatrixA>
void test(MatrixA& a, const char* name)
{
    a= 0.0;
    {
	mtl::mat::inserter<MatrixA>  ins(a);
	                  ins(0, 1) << 1.0; ins(0, 2) << 4.0;
	ins(1, 0) << 1.0; ins(1, 1) << 3.0; ins(1, 2) << 4.0; ins(1, 3) << 4.0; 
	                  ins(2, 1) << 9.0; ins(2, 2) << 4.0; ins(2, 3) << 2.0; 
	                                    ins(3, 2) << 4.0;
    }

    std::cout << "\n" << name << " a = \n" << a << "\n"
    	      << "infinity_norm(a) = " << infinity_norm(a) << "\n"; std::cout.flush();

    
    MTL_THROW_IF(infinity_norm(a) != 15.0, mtl::runtime_error("wrong infinity_norm")); 
}


int main(int, char**)
{
    using namespace mtl;
    unsigned size= 4;

    dense2D<double>                                      dr(size, size);
    dense2D<double, mat::parameters<col_major> >      dc(size, size);
    morton_dense<double, recursion::morton_z_mask>       mzd(size, size);
    morton_dense<double, recursion::doppled_2_row_mask>  d2r(size, size);
    compressed2D<double>                                 cr(size, size);
    compressed2D<double, mat::parameters<col_major> > cc(size, size);

    dense2D<complex<double> >                            drc(size, size);
    compressed2D<complex<double> >                       crc(size, size);

    test(dr, "Dense row major");
    test(dc, "Dense column major");
    test(mzd, "Morton Z-order");
    test(d2r, "Hybrid 2 row-major");
    test(cr, "Compressed row major");
    test(cc, "Compressed column major");
    test(drc, "Dense row major complex");
    test(crc, "Compressed row major complex");

    return 0;
}
 















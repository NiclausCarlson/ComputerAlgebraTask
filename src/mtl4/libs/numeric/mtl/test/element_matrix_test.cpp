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
#include <complex>
#include <boost/numeric/mtl/concept/collection.hpp>
#include <boost/numeric/mtl/matrix/dense2D.hpp>
#include <boost/numeric/mtl/matrix/morton_dense.hpp> 
#include <boost/numeric/mtl/matrix/compressed2D.hpp> 
#include <boost/numeric/mtl/matrix/inserter.hpp> 
#include <boost/numeric/mtl/matrix/element_matrix.hpp> 
#include <boost/numeric/mtl/matrix/element_array.hpp> 
#include <boost/numeric/mtl/recursion/predefined_masks.hpp>
#include <boost/numeric/mtl/operation/print.hpp>


using namespace std;  

template <typename Matrix>
void test(Matrix& matrix, const char* name)
{
    cout << "\n" << name << "\n";

    using mtl::mat::inserter; using mtl::element_array;
    typedef typename mtl::Collection<Matrix>::value_type value_type;

    mtl::dense2D<double>       m1(2, 2);
    m1[0][0]= 1.0; m1[0][1]= 2.0; 
    m1[1][0]= 3.0; m1[1][1]= 4.0; 
    std::vector<int>           row1, col1;
    row1.push_back(1); row1.push_back(2);
    col1.push_back(0); col1.push_back(2);
    

    double a2[2][2]= {{11., 12.},{13., 14.}};
    std::vector<int>           ind2;
    ind2.push_back(2); ind2.push_back(4);

    std::vector<int>           ind3;
    ind3.push_back(3); ind3.push_back(1);

    set_to_zero(matrix); // dense matrices are not automatically set to zero

    {
	inserter<Matrix, mtl::operations::update_plus<value_type> > ins(matrix);

	ins << element_matrix(m1, row1, col1)
	    << element_array(a2, ind2);
	ins << element_array(a2, ind3);
    }

    cout << "Filled matrix:\n" << matrix << "\n";
    MTL_THROW_IF(matrix[0][0] != 0.0, mtl::runtime_error("wrong zero-element"));
    MTL_THROW_IF(matrix[1][0] != 1.0, mtl::runtime_error("wrong insertion (single value)"));
    MTL_THROW_IF(matrix[2][2] != 15.0, mtl::runtime_error("wrong summation"));
    MTL_THROW_IF(matrix[1][1] != 14.0, mtl::runtime_error("wrong insertion (single value)"));
    
}



int main(int , char**)
{
    using namespace mtl;
    unsigned size= 5;

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

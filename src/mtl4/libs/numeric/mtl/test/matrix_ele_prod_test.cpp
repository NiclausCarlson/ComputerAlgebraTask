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

#include <boost/numeric/mtl/mtl.hpp>



using std::cout; 


template <typename MatrixA, typename MatrixB, typename MatrixC>
void test(MatrixA&, MatrixB&, MatrixC&, const char* name)
{
    double aa[][3]= {{0., 2., 0.}, {0., 0., 1.}, {1., 0., 0.}},
	   ba[][3]= {{0., 3., 0.}, {4., 0., 0.}, {1., 0., 0.}};

    MatrixA A(aa); 
    MatrixB B(ba); 
    MatrixC C;

    cout << "\n\n" << name << "\n";
    cout << "Original matrices:\nA=\n" << A << "B=\n" << B << "\n";

    C= ele_prod(A, B);
    cout << "C= ele_prod(A, B)\n" << C << "\n";
    MTL_THROW_IF(C[0][1] != 6.0, mtl::runtime_error("C[0][1] should be 6.0"));
    MTL_THROW_IF(C[1][0] != 0.0, mtl::runtime_error("C[1][0] should be 0.0"));


    C= A + ele_prod(A, B);
    cout << "C= A + ele_prod(A, B)\n" << C << "\n";
    MTL_THROW_IF(C[0][1] != 8.0, mtl::runtime_error("C[0][1] should be 6.0"));
    MTL_THROW_IF(C[1][2] != 1.0, mtl::runtime_error("C[1][2] should be 1.0"));


    C= ele_prod(ele_prod(A, B), A);
    cout << "C= ele_prod(ele_prod(A, B), A)\n" << C << "\n";
    MTL_THROW_IF(C[0][1] != 12.0, mtl::runtime_error("C[0][1] should be 12.0"));
    MTL_THROW_IF(C[1][0] != 0.0, mtl::runtime_error("C[1][0] should be 0.0"));


    C= ele_prod(A, ele_prod(A, B));    
    cout << "C= ele_prod(ele_prod(A, B), A)\n" << C << "\n";
    MTL_THROW_IF(C[0][1] != 12.0, mtl::runtime_error("C[0][1] should be 12.0"));
    MTL_THROW_IF(C[1][0] != 0.0, mtl::runtime_error("C[1][0] should be 0.0"));


    C-= ele_prod(A, B);
    cout << "C-= ele_prod(A, B)\n" << C << "\n";
    MTL_THROW_IF(C[0][1] != 6.0, mtl::runtime_error("C[0][1] should be 6.0"));
    MTL_THROW_IF(C[1][0] != 0.0, mtl::runtime_error("C[1][0] should be 0.0"));

    C+= ele_prod(A, B);
    cout << "C+= ele_prod(A, B)\n" << C << "\n";
    MTL_THROW_IF(C[0][1] != 12.0, mtl::runtime_error("C[0][1] should be 12.0"));
    MTL_THROW_IF(C[1][0] != 0.0, mtl::runtime_error("C[1][0] should be 0.0"));

}



int main(int, char**)
{
    using namespace mtl;

    dense2D<double>                                      dr(3, 3);
    dense2D<double, mat::parameters<col_major> >      dc(3, 3);
    morton_dense<double, recursion::morton_z_mask>       mzd(3, 3);
    morton_dense<double, recursion::doppled_2_row_mask>  d2r(3, 3);
    compressed2D<double>                                 cr(3, 3);
    compressed2D<double, mat::parameters<col_major> > cc(3, 3);


    test(dr, dr, dr, "Dense row major");
    test(dc, dr, dr, "Dense column major as sum of dense rows");
    test(dc, dr, dc, "Dense column major as sum of dense rows and column");

    test(mzd, mzd, mzd, "Morton Z-order");
    test(d2r, mzd, d2r, "Hybrid 2 row-major + Morton Z-order");

    test(cr, cr, cr, "Compressed row major");
    test(cc, cr, cc, "Compressed column major + row");

    return 0;
}

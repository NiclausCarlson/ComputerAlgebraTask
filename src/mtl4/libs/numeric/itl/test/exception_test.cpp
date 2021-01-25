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
#include <boost/numeric/itl/itl.hpp>

// To improve our coverage ;-)

template <typename Exception>
void test(Exception)
{
    try {
	throw Exception();
    }
    catch (Exception e) {}
}



int main()
{
    using namespace itl;
    test(search_space_exhaustion());
    test(unexpected_orthogonality());

    return 0;
}

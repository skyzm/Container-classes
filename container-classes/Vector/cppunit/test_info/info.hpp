// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// <author info>
// 	<name>
// 		Stefan Pantic 
// 	<github>
// 		https://github.com/syIar/Container-classes
// 	<university>
// 		University of Belgrade, Faculty of Mathematics, second year student
// 	<year>
// 		Second
// 	<email>
// 		stefanpantic13@gmail.com
// </author info>
// 
// <description>
// Helper function to print test info.
// </description>
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef _INFO_HPP_
#define _INFO_HPP_

#include <iostream>
#include "color.hpp"

void test_info( const std::string &_type,
				const std::string &_alloc_type,
				const size_t &_size,
				const std::string &_elem_gen = "default",
				const std::string &_comparator = "default",
				std::ostream &_out = std::cout)
{
	_out << BOLDWHITE << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << RESET << std::endl;
	_out << BOLDBLUE << "value type:        " << RESET << BOLDWHITE << _type << RESET << std::endl;
	_out << BOLDBLUE << "allocator type:    " << RESET << BOLDWHITE << _alloc_type << "<" << _type << ">" << RESET << std::endl;
	_out << BOLDBLUE << "size:              " << RESET << BOLDWHITE << _size << RESET << std::endl;
	_out << BOLDBLUE << "element generator: " << RESET << BOLDWHITE << _elem_gen << RESET << std::endl;
	_out << BOLDBLUE << "comparator:        " << RESET << BOLDWHITE << _comparator << RESET << std::endl;
	_out << BOLDWHITE << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << RESET << std::endl;
}

#endif

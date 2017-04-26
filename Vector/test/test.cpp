#include <iostream>
#include <algorithm>
#include <boost/pool/pool_alloc.hpp>
#include "../include/Vector.hpp"

int
main (void)
{
	std::cout << "\ndefault constructor" << std::endl;
	container::vector<std::string> v(100, "IO");
	v.insert(++++v.begin(), "spontaneous_long_string");
	for(auto &e : v)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	std::cout << "\ncopy constructor" << std::endl;
	container::vector<std::string> v2(v);
	for(auto &e : v2)
	{
		e += "hey";
		std::cout << e << " ";
	}
	std::cout << std::endl;

	std::cout << "\nmove constructor" << std::endl;
	container::vector<std::string> v3(std::move(v));
	for(container::vector<std::string>::size_type i = 0; i < v3.size(); ++i)
	{
		std::cout << v3[i] << " ";
		v3[i] = std::to_string(i);
	}
	std::cout << std::endl;

	std::cout << "\nreverse traverse" << std::endl;
	std::for_each(v3.rbegin(), v3.rend(), [] (const std::string &s) { std::cout << s << " "; });
	std::cout << std::endl;

	std::cout << "\nstd::initializer_list" << std::endl;
	container::vector<int> v4 = {1, 2, 4, 6, 9 ,10, 11, 34, 56, 123, 69, 69, 69};
	for(auto e : v4)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	std::cout << "\nboost::pool_allocator" << std::endl;
	container::vector<int, boost::pool_allocator<int>> v5(100, 1337);
	v5.push_back(100);
	std::for_each(v5.begin(), v5.end(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;
	
	std::cout << "\npush_back" << std::endl;
	container::vector<int, boost::pool_allocator<int>> v6;
	for(int i = 0;i < 100; ++i)
	{
		v6.push_back(i);
	}
	std::for_each(v6.crbegin(), v6.crend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "\ncopy assignment" << std::endl;
	container::vector<int, boost::pool_allocator<int>> v7 = v5;
	std::for_each(v7.crbegin(), v7.crend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "\nmove assignment and insert" <<  std::endl;
	container::vector<int, boost::pool_allocator<int>> v8 = std::move(v6);
	v8.insert(v8.begin(), 100);
	v8.insert(----v8.end(), 100);
	std::for_each(v8.cbegin(), v8.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "\nstd::back_inserter" << std::endl;
	container::vector<int> v9;
	std::copy_if(v8.cbegin(), v8.cend(), std::back_inserter(v9), [] (const int &x) { return (0 == x % 2); });
	std::for_each(v9.cbegin(), v9.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "\nstd::back_insert_iterator" << std::endl;
	container::vector<int> v10;
	std::copy_if(v8.cbegin(), v8.cend(), std::back_insert_iterator<container::vector<int>>(v10), [] (const int &x) { return (0 == x % 2); });
	v10.erase(v10.begin());
	std::for_each(v10.cbegin(), v10.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "\nfind" << std::endl;
	container::vector<int>::iterator it{v10.find(48)};
	if(v10.end() != it)
	{
		std::cout << "  found " << *it;
	}
	else
	{
		std::cout << "  not found";
	}
	std::cout << std::endl;

	std::cout << "\nswap" << std::endl;
	std::cout << "  before" << std::endl;
	std::for_each(v4.cbegin(), v4.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;
	std::for_each(v10.cbegin(), v10.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;
	v4.swap(v10);
	std::cout << "  after" << std::endl;
	std::for_each(v4.cbegin(), v4.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;
	std::for_each(v10.cbegin(), v10.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "\nstd::sort" << std::endl;
	std::cout << "  before" << std::endl;
	std::for_each(v4.cbegin(), v4.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;
	std::sort(v4.begin(), v4.end());
	std::cout << "  after" << std::endl;
	std::for_each(v4.cbegin(), v4.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "\ninsert" << std::endl;
	container::vector<double> v12;
	auto it2{v12.begin()};
	for(int i = 0; i < 100; ++i)
	{
		it2 = v12.insert(it2, static_cast<double>(i)/12);
	}
	std::for_each(v12.begin(), v12.end(), [] (const double &x) { std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "\nrange erase" << std::endl;
	v10.erase(++++++v10.begin(), ------v10.end());
	std::for_each(v10.cbegin(), v10.cend(), [] (const int &x) { std::cout << x << " "; });
	std::cout << std::endl;
	
	return 0;
}







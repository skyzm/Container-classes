#include <iostream>
#include <algorithm>
#include <random>

#include "set.hpp"
#include "set_detail.hpp"
#include "set_node.hpp"
#include "color.hpp"

int
main (void)
{
	std::random_device random;
	std::uniform_int_distribution<int> distro{-999, 999};

	containers::set<int> dynamic;

	int inserted{0};
	for(int i = 0; i < 1000; ++i)
	{
		inserted = distro(random);

		std::cout << MAGENTA << "\nInserting " << inserted << std::endl;

		if(false == dynamic.insert(inserted).second)
			std::cout << MAGENTA << "\nNot inserted " << inserted << std::endl;

		std::cout << std::endl;
	}

	for(int i = 0; i < 100; ++i)
	{
		inserted = distro(random);
		std::cout << MAGENTA << "\nErasing " << inserted << std::endl;
		auto it{dynamic.erase(dynamic.find(inserted))};
		if(dynamic.end() == it)
			std::cout << MAGENTA << "\nNot erased " << inserted << std::endl;
		else
			std::cout << "\nSuccessor: " << *it << std::endl;

		std::cout << RESET;
		std::copy(dynamic.begin(), dynamic.end(), std::ostream_iterator<int>{std::cout, " "});
	}

	std::cout << std::endl;

	return 0;
}

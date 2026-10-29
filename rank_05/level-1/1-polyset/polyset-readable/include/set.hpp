/* ******************** NEED TO BE IMPLEMENTED ******************** */

#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set 
{
	private:
		searchable_bag* bag;
		set();

	public:
		set(searchable_bag& other_bag);
		set(const set& other);
		set&	operator=(const set& other);
		~set();

		void	insert(int item);
		void	insert(int* items, int size);
		void	print() const;
		void	clear();
		bool	has(int item) const;

		searchable_bag&	get_bag() const;
};

#endif
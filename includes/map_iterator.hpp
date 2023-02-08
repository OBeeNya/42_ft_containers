#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "ft_containers.hpp"
# include "iterator.hpp"

namespace	ft {

	template< class T, class node >
	class	map_iterator:
		public ft::iterator< std::bidirectional_iterator_tag, T > {

		public:

			/*** MEMBER TYPES ***/

			typedef typename ft::iterator< std::bidirectional_iterator_tag, T >	iterator;
			typedef typename iterator::value_type								value_type;
			typedef typename iterator::difference_type							difference_type;
			typedef typename iterator::pointer									pointer;
			typedef typename iterator::reference								reference;
			typedef typename iterator::iterator_category						iterator_category;
			typedef node														node_type;
			typedef node*														node_pointer;
			typedef node&														node_reference;

			/*** MEMBER FUNCTIONS ***/



		private:

			/*** MEMBER OBJECTS ***/

			node_pointer	_current;
			node_pointer	_root;
			node_pointer	_end;

	}

};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 09:38:58 by skienzle          #+#    #+#             */
/*   Updated: 2022/03/05 21:47:23 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>

#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{

/*
couldn't create seperate iterator tags, as they would only work for ft::iterators
without being compatible to std::iterators, therefore defeating the puropse of 
general iterator tags

struct output_iterator_tag {};
struct input_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};
*/

// Iterator traits

typedef std::output_iterator_tag		output_iterator_tag;
typedef std::input_iterator_tag			input_iterator_tag ;
typedef std::forward_iterator_tag		forward_iterator_tag;
typedef std::bidirectional_iterator_tag	bidirectional_iterator_tag;
typedef std::random_access_iterator_tag	random_access_iterator_tag;

template <typename Category, typename T, typename Distance = ptrdiff_t,
		typename Pointer = T*, typename Reference = T&>
struct iterator
{
	typedef T										value_type;
	typedef Distance								difference_type;
	typedef Pointer									pointer;
	typedef Reference								reference;
	typedef Category								iterator_category;
};

template<typename Iterator>
struct iterator_traits
{
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template<typename T>
struct iterator_traits<T*>
{
	typedef T										value_type;
	typedef ptrdiff_t								difference_type;
	typedef T*										pointer;
	typedef T&										reference;
	typedef random_access_iterator_tag				iterator_category;
};

template<typename T>
struct iterator_traits<const T*>
{
	typedef T										value_type;
	typedef ptrdiff_t								difference_type;
	typedef const T*								pointer;
	typedef const T&								reference;
	typedef random_access_iterator_tag				iterator_category;
};


// distance

template<typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last, input_iterator_tag)
{
	typename iterator_traits<InputIterator>::difference_type count(0);
	for (; first != last; ++first)
		++count;
	return count;
}

template<typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
_distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
{
	return last - first;
}

template<typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
	return _distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
}


// reverse Iterator

template<typename Iterator>
class reverse_iterator: public iterator<
						typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
{
public: // types
	typedef Iterator											iterator_type;
	typedef typename iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<Iterator>::reference		reference;
	typedef typename iterator_traits<Iterator>::pointer			pointer;

public: // methods
	// constructors
	reverse_iterator();
	explicit reverse_iterator(Iterator it);
	template<typename U>
		reverse_iterator(const reverse_iterator<U>& rev_it);

	// operator overloads
	template<typename U>
		reverse_iterator&	operator=(const reverse_iterator<U>& rev_it);
	reference				operator*() const;
	pointer					operator->() const;
	reverse_iterator&		operator++();
	reverse_iterator		operator++(int);
	reverse_iterator&		operator--();
	reverse_iterator		operator--(int);
	reverse_iterator		operator+(difference_type n) const;
	reverse_iterator&		operator+=(difference_type n);
	reverse_iterator		operator-(difference_type n) const;
	reverse_iterator&		operator-=(difference_type n);
	reference				operator[](difference_type n) const;

	// getter
	Iterator base() const;


protected:
	Iterator current;
};

template<typename Iterator>
reverse_iterator<Iterator>::reverse_iterator(): current() {}

template<typename Iterator>
reverse_iterator<Iterator>::reverse_iterator(Iterator it): current(it) {}

template<typename Iterator>
template<typename U>
reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U>& rev_it):
	current(rev_it.base()) {}

template<typename Iterator>
template<typename U>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator=(const reverse_iterator<U>& rev_it)
{
	this->current = rev_it.base();
	return *this;
}

template<typename Iterator>
typename reverse_iterator<Iterator>::reference
reverse_iterator<Iterator>::operator*() const
{
	Iterator temp = this->current;
	return *(--temp);
}

template<typename Iterator>
typename reverse_iterator<Iterator>::pointer
reverse_iterator<Iterator>::operator->() const
{
	return(&(operator*()));
}

template<typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator++()
{
	--this->current;
	return *this;
}

template<typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator++(int)
{
	reverse_iterator temp(*this);
	--this->current;
	return temp;
}

template<typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator--()
{
	++this->current;
	return *this;
}

template<typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator--(int)
{
	reverse_iterator temp(*this);
	++this->current;
	return temp;
}

template<typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator+(difference_type n) const
{
	return reverse_iterator(this->current - n);
}

template<typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator+=(difference_type n)
{
	this->current += n;
	return *this;
}

template<typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator-(difference_type n) const
{
	return reverse_iterator(this->current + n);
}

template<typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator-=(difference_type n)
{
	this->current + n;
	return *this;
}

template<typename Iterator>
typename reverse_iterator<Iterator>::reference
reverse_iterator<Iterator>::operator[](difference_type n) const
{
	return *(*this + n);
}

template<typename Iterator>
Iterator
reverse_iterator<Iterator>::base() const
{
	return this->current;
}


// external operator overloads for reverse_iterator

template<typename Iterator>
inline bool
operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() == rhs.base();
}

template<typename Iterator>
inline bool
operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() != rhs.base();
}

template<typename Iterator>
inline bool
operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() < rhs.base();
}

template<typename Iterator>
inline bool
operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename Iterator>
inline bool
operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() > rhs.base();
}

template<typename Iterator>
inline bool
operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() >= rhs.base();
}

template<typename Iterator>
inline typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() - rhs.base();
}

template<typename Iterator>
inline reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator> &rev_it)
{
	return reverse_iterator<Iterator>(rev_it.base() - n);
}


// linear_iterator

template<typename Iterator, typename Container>
class linear_iterator
{
public: // types
	typedef Iterator													iterator_type;
	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;


public: // methods
	// constructors
	linear_iterator();
	// linear_iterator(const linear_iterator<Iterator,Container>& other);
	linear_iterator(const linear_iterator<typename Container::pointer, Container>& other);
	linear_iterator(const iterator_type& it);

	// destructor
	~linear_iterator();

	// operator overloads
	
	reference			operator*() const;
	pointer				operator->() const;
	linear_iterator&	operator++();
	linear_iterator		operator++(int);
	linear_iterator&	operator--();
	linear_iterator		operator--(int);
	linear_iterator		operator+(difference_type n) const;
	linear_iterator&	operator+=(difference_type n);
	linear_iterator		operator-(difference_type n) const;
	linear_iterator&	operator-=(difference_type n);
	reference			operator[](difference_type n) const;
	
	// getter
	Iterator base() const;

private: // attributes
	iterator_type _it;
};


template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>::linear_iterator(): _it() {}

// template<typename Iterator, typename Container>
// linear_iterator<Iterator,Container>::linear_iterator(const linear_iterator<Iterator,Container>& other):
// 	_it(other.base()) {}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>::linear_iterator(const linear_iterator<
													typename Container::pointer,Container>& other):
	_it(other.base()) {}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>::linear_iterator(const iterator_type& it): _it(it) {}


template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>::~linear_iterator() {}


template<typename Iterator, typename Container>
typename linear_iterator<Iterator,Container>::reference
linear_iterator<Iterator,Container>::operator*() const
{
	return *this->_it;
}

template<typename Iterator, typename Container>
typename linear_iterator<Iterator,Container>::pointer
linear_iterator<Iterator,Container>::operator->() const
{
	return this->_it;
}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>&
linear_iterator<Iterator,Container>::operator++()
{
	++this->_it;
	return *this;
}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>
linear_iterator<Iterator,Container>::operator++(int)
{
	linear_iterator temp(*this);
	++this->_it;
	return temp;
}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>&
linear_iterator<Iterator,Container>::operator--()
{
	--this->_it;
	return *this;
}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>
linear_iterator<Iterator,Container>::operator--(int)
{
	linear_iterator temp(*this);
	--this->_it;
	return temp;
}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>
linear_iterator<Iterator,Container>::operator+(difference_type n) const
{
	return linear_iterator(this->_it + n);
}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>&
linear_iterator<Iterator,Container>::operator+=(difference_type n)
{
	this->_it += n;
	return *this;
}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>
linear_iterator<Iterator,Container>::operator-(difference_type n) const
{
	return linear_iterator(this->_it - n);
}

template<typename Iterator, typename Container>
linear_iterator<Iterator,Container>&
linear_iterator<Iterator,Container>::operator-=(difference_type n)
{
	this->_it -= n;
	return *this;
}

template<typename Iterator, typename Container>
typename linear_iterator<Iterator,Container>::reference
linear_iterator<Iterator,Container>::operator[](difference_type n) const
{
	return *(this->_it + n);
}

template<typename Iterator, typename Container>
Iterator
linear_iterator<Iterator,Container>::base() const
{
	return this->_it;
}


// relational operator overloads for linear_iterator

template<typename Iterator, typename Container>
inline linear_iterator<Iterator,Container>
operator+(typename linear_iterator<Iterator,Container>::difference_type n,
			linear_iterator<Iterator,Container> it)
{
	it += n;
	return it;
}

template<typename Iterator, typename Container>
inline typename linear_iterator<Iterator,Container>::difference_type
operator-(const linear_iterator<Iterator,Container>& lhs, const linear_iterator<Iterator,Container>& rhs)
{
	return lhs.base() - rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Container>
inline typename linear_iterator<Iterator1,Container>::difference_type
operator-(const linear_iterator<Iterator1,Container>& lhs, const linear_iterator<Iterator2,Container>& rhs)
{
	return lhs.base() - rhs.base();
}


template<typename Iterator, typename Container>
inline bool
operator==(const linear_iterator<Iterator,Container>& lhs, const linear_iterator<Iterator,Container>& rhs)
{
	return lhs.base() == rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Container>
inline bool
operator==(const linear_iterator<Iterator1,Container>& lhs, const linear_iterator<Iterator2,Container>& rhs)
{
	return lhs.base() == rhs.base();
}

template<typename Iterator, typename Container>
inline bool
operator!=(const linear_iterator<Iterator,Container>& lhs, const linear_iterator<Iterator,Container>& rhs)
{
	return !(lhs == rhs);
}

template<typename Iterator1, typename Iterator2, typename Container>
inline bool
operator!=(const linear_iterator<Iterator1,Container>& lhs, const linear_iterator<Iterator2,Container>& rhs)
{
	return !(lhs == rhs);
}

template<typename Iterator, typename Container>
inline bool
operator<(const linear_iterator<Iterator,Container>& lhs, const linear_iterator<Iterator,Container>& rhs)
{
	return lhs.base() < rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Container>
inline bool
operator<(const linear_iterator<Iterator1,Container>& lhs, const linear_iterator<Iterator2,Container>& rhs)
{
	return lhs.base() < rhs.base();
}

template<typename Iterator, typename Container>
inline bool
operator>(const linear_iterator<Iterator,Container>& lhs, const linear_iterator<Iterator,Container>& rhs)
{
	return lhs.base() > rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Container>
inline bool
operator>(const linear_iterator<Iterator1,Container>& lhs, const linear_iterator<Iterator2,Container>& rhs)
{
	return lhs.base() > rhs.base();
}

template<typename Iterator, typename Container>
inline bool
operator<=(const linear_iterator<Iterator,Container>& lhs, const linear_iterator<Iterator,Container>& rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Container>
inline bool
operator<=(const linear_iterator<Iterator1,Container>& lhs, const linear_iterator<Iterator2,Container>& rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename Iterator, typename Container>
inline bool
operator>=(const linear_iterator<Iterator,Container>& lhs, const linear_iterator<Iterator,Container>& rhs)
{
	return lhs.base() >= rhs.base();
}

template<typename Iterator1, typename Iterator2, typename Container>
inline bool
operator>=(const linear_iterator<Iterator1,Container>& lhs, const linear_iterator<Iterator2,Container>& rhs)
{
	return lhs.base() >= rhs.base();
}


} // namespace ft
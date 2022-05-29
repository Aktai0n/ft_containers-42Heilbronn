/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 09:38:58 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/29 19:19:19 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>

#include "type_traits.hpp"

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
	
	// destructor
	~reverse_iterator();

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
reverse_iterator<Iterator>::~reverse_iterator() {}

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
	return (&(this->operator*()));
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
	this->current -= n;
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
	this->current += n;
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

template<typename Iterator1, typename Iterator2>
inline bool
operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() == rhs.base();
}

template<typename Iterator1, typename Iterator2>
inline bool
operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() != rhs.base();
}

template<typename Iterator1, typename Iterator2>
inline bool
operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() > rhs.base();
}

template<typename Iterator1, typename Iterator2>
inline bool
operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() >= rhs.base();
}

template<typename Iterator1, typename Iterator2>
inline bool
operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() < rhs.base();
}

template<typename Iterator1, typename Iterator2>
inline bool
operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename Iterator1, typename Iterator2>
inline typename reverse_iterator<Iterator1>::difference_type
operator-(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return rhs.base() - lhs.base();
}

template<typename Iterator>
inline reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator> &rev_it)
{
	return reverse_iterator<Iterator>(rev_it.base() - n);
}


// linear_iterator

template<typename T>
class linear_iterator
{
public: // types
	typedef T*															iterator_type;
	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;


public: // methods
	// constructors / destructor

	linear_iterator();
	linear_iterator(const linear_iterator& other);
	linear_iterator(const iterator_type& ptr);
	~linear_iterator();

	// operator overloads

	// operator linear_iterator<const T>() const { return this->_ptr; }
	operator linear_iterator<const T>() const;
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

	iterator_type base() const;

private: // attributes
	iterator_type _ptr;
};


template<typename T>
linear_iterator<T>::linear_iterator(): _ptr() {}

template<typename T>
linear_iterator<T>::linear_iterator(const linear_iterator& other): _ptr(other.base()) {}

template<typename T>
linear_iterator<T>::linear_iterator(const iterator_type& ptr): _ptr(ptr) {}


template<typename T>
linear_iterator<T>::~linear_iterator() {}

template<typename T>
linear_iterator<T>::operator linear_iterator<const T>() const
{
	return this->_ptr;
}

template<typename T>
typename linear_iterator<T>::reference
linear_iterator<T>::operator*() const
{
	return *this->_ptr;
}

template<typename T>
typename linear_iterator<T>::pointer
linear_iterator<T>::operator->() const
{
	return this->_ptr;
}

template<typename T>
linear_iterator<T>&
linear_iterator<T>::operator++()
{
	++this->_ptr;
	return *this;
}

template<typename T>
linear_iterator<T>
linear_iterator<T>::operator++(int)
{
	linear_iterator temp(*this);
	++this->_ptr;
	return temp;
}

template<typename T>
linear_iterator<T>&
linear_iterator<T>::operator--()
{
	--this->_ptr;
	return *this;
}

template<typename T>
linear_iterator<T>
linear_iterator<T>::operator--(int)
{
	linear_iterator temp(*this);
	--this->_ptr;
	return temp;
}

template<typename T>
linear_iterator<T>
linear_iterator<T>::operator+(difference_type n) const
{
	return linear_iterator(this->_ptr + n);
}

template<typename T>
linear_iterator<T>&
linear_iterator<T>::operator+=(difference_type n)
{
	this->_ptr += n;
	return *this;
}

template<typename T>
linear_iterator<T>
linear_iterator<T>::operator-(difference_type n) const
{
	return linear_iterator(this->_ptr - n);
}

template<typename T>
linear_iterator<T>&
linear_iterator<T>::operator-=(difference_type n)
{
	this->_ptr -= n;
	return *this;
}

template<typename T>
typename linear_iterator<T>::reference
linear_iterator<T>::operator[](difference_type n) const
{
	return *(this->_ptr + n);
}

template<typename T>
typename linear_iterator<T>::iterator_type
linear_iterator<T>::base() const
{
	return this->_ptr;
}


// relational operator overloads for linear_iterator

template<typename T>
inline linear_iterator<T>
operator+(typename linear_iterator<T>::difference_type n,
			linear_iterator<T> it)
{
	it += n;
	return it;
}

template<typename T>
inline typename linear_iterator<T>::difference_type
operator-(const linear_iterator<T>& lhs, const linear_iterator<T>& rhs)
{
	return lhs.base() - rhs.base();
}

template<typename T1, typename T2>
inline typename linear_iterator<T1>::difference_type
operator-(const linear_iterator<T1>& lhs, const linear_iterator<T2>& rhs)
{
	return lhs.base() - rhs.base();
}


template<typename T>
inline bool
operator==(const linear_iterator<T>& lhs, const linear_iterator<T>& rhs)
{
	return lhs.base() == rhs.base();
}

template<typename T1, typename T2>
inline bool
operator==(const linear_iterator<T1>& lhs, const linear_iterator<T2>& rhs)
{
	return lhs.base() == rhs.base();
}

template<typename T>
inline bool
operator!=(const linear_iterator<T>& lhs, const linear_iterator<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T1, typename T2>
inline bool
operator!=(const linear_iterator<T1>& lhs, const linear_iterator<T2>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
inline bool
operator<(const linear_iterator<T>& lhs, const linear_iterator<T>& rhs)
{
	return lhs.base() < rhs.base();
}

template<typename T1, typename T2>
inline bool
operator<(const linear_iterator<T1>& lhs, const linear_iterator<T2>& rhs)
{
	return lhs.base() < rhs.base();
}

template<typename T>
inline bool
operator>(const linear_iterator<T>& lhs, const linear_iterator<T>& rhs)
{
	return lhs.base() > rhs.base();
}

template<typename T1, typename T2>
inline bool
operator>(const linear_iterator<T1>& lhs, const linear_iterator<T2>& rhs)
{
	return lhs.base() > rhs.base();
}

template<typename T>
inline bool
operator<=(const linear_iterator<T>& lhs, const linear_iterator<T>& rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename T1, typename T2>
inline bool
operator<=(const linear_iterator<T1>& lhs, const linear_iterator<T2>& rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename T>
inline bool
operator>=(const linear_iterator<T>& lhs, const linear_iterator<T>& rhs)
{
	return lhs.base() >= rhs.base();
}

template<typename T1, typename T2>
inline bool
operator>=(const linear_iterator<T1>& lhs, const linear_iterator<T2>& rhs)
{
	return lhs.base() >= rhs.base();
}


} // namespace ft
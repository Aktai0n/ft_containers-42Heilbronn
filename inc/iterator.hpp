/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 09:38:58 by skienzle          #+#    #+#             */
/*   Updated: 2022/01/21 20:22:47 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>

namespace ft
{


// Iterator traits

struct output_iterator_tag {};
struct input_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};

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
		reverse_iterator(const reverse_iterator<U> &rev_it);

	// operator overloads
	template<typename U>
		reverse_iterator	&operator=(const reverse_iterator<U> &rev_it);
	reference				operator*() const;
	pointer					operator->() const;
	reverse_iterator		&operator++();
	reverse_iterator		operator++(int);
	reverse_iterator		&operator--();
	reverse_iterator		operator--(int);
	reverse_iterator		operator+(difference_type n) const;
	reverse_iterator		&operator+=(difference_type n);
	reverse_iterator		operator-(difference_type n) const;
	reverse_iterator		&operator-=(difference_type n);
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
reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U> &rev_it):
	current(rev_it.base()) {}

template<typename Iterator>
template<typename U>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator=(const reverse_iterator<U> &rev_it)
{
	this->current = rev_it.base();
	return *this;
}

template<typename Iterator>
typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator*() const
{
	Iterator temp = this->current;
	return *(--temp);
}

template<typename Iterator>
typename reverse_iterator<Iterator>::pointer reverse_iterator<Iterator>::operator->() const
{
	return(&(operator*()));
}

template<typename Iterator>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator++()
{
	--this->current;
	return *this;
}

template<typename Iterator>
reverse_iterator<Iterator> reverse_iterator<Iterator>::operator++(int)
{
	reverse_iterator temp(*this);
	--this->current;
	return temp;
}

template<typename Iterator>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator--()
{
	++this->current;
	return *this;
}

template<typename Iterator>
reverse_iterator<Iterator> reverse_iterator<Iterator>::operator--(int)
{
	reverse_iterator temp(*this);
	++this->current;
	return temp;
}

template<typename Iterator>
reverse_iterator<Iterator> reverse_iterator<Iterator>::operator+(difference_type n) const
{
	return reverse_iterator(this->current - n);
}

template<typename Iterator>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator+=(difference_type n)
{
	this->current += n;
	return *this;
}

template<typename Iterator>
reverse_iterator<Iterator> reverse_iterator<Iterator>::operator-(difference_type n) const
{
	return reverse_iterator(this->current + n);
}

template<typename Iterator>
reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator-=(difference_type n)
{
	this->current + n;
	return *this;
}

template<typename Iterator>
typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator[](difference_type n) const
{
	return *(*this + n);
}

template<typename Iterator>
Iterator reverse_iterator<Iterator>::base() const
{
	return this->current;
}


// external operator overloads for reverse_iterator

template<typename Iterator>
bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() == rhs.base();
}

template<typename Iterator>
bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() != rhs.base();
}

template<typename Iterator>
bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() < rhs.base();
}

template<typename Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() <= rhs.base();
}

template<typename Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() > rhs.base();
}

template<typename Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() >= rhs.base();
}

template<typename Iterator>
typename reverse_iterator<Iterator>::difference_type operator-
	(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() - rhs.base();
}

template<typename Iterator>
reverse_iterator<Iterator> operator+
	(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
{
	return reverse_iterator<Iterator>(rev_it.base() - n);
}












} // namespace ft
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:40:35 by skienzle          #+#    #+#             */
/*   Updated: 2022/02/09 23:13:22 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include <memory>

#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

namespace ft
{


template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public: // types
	typedef Alloc										allocator_type;
	typedef typename allocator_type::value_type			value_type; // typedef T for std::allocator
	typedef typename allocator_type::size_type			size_type; //  typedef size_t for std::allocator
	typedef typename allocator_type::pointer			pointer; // typedef T* for std::allocator
	typedef typename allocator_type::difference_type	difference_type; // typedef ptrdiff_t for std::allocator
	typedef typename allocator_type::const_pointer		const_pointer; // typedef const T* for std::allocator
	typedef typename allocator_type::reference			reference; // typedef T& for std::allocator
	typedef typename allocator_type::const_reference	const_reference; // typedef const T& for std::allocator
	typedef ft::linear_iterator<pointer>				iterator;
	typedef ft::linear_iterator<const_pointer>			const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	
public: // methods
	// constructors
	explicit vector(const allocator_type& alloc = allocator_type());
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	template<typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0);
	vector(const vector& other);

	// destructor
	~vector();

	// operator overloads
	vector<T,Alloc>&	operator=(const vector<T,Alloc>& other);
	reference			operator[](size_type n);
	const_reference		operator[](size_type n) const;

	// iterators
	iterator				begin();
	const_iterator			begin() const;
	iterator				end();
	const_iterator			end() const;
	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;

	// capacity
	size_type	size() const;
	size_type	max_size() const;
	void		resize(size_type n, value_type val = value_type());
	size_type	capacity() const;
	bool		empty() const;
	void		reserve(size_type n);

	// element access
	reference			at(size_type n);
	const_reference		at(size_type n) const;
	reference			front();
	const_reference		front() const;
	reference			back();
	const_reference		back() const;

	// modifiers
	template<typename InputIterator>
		void	assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0);
	void		assign(size_type n, const value_type& val);
	void		push_back(const value_type& val);
	void		pop_back();
	iterator	insert(iterator position, const value_type& val);
	void		insert(iterator position, size_type n, const value_type& val);
	template<typename InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0);
	iterator	erase(iterator position);
	iterator	erase(iterator first, iterator last);
	void		swap(vector& other);
	void		clear();
	
	// allocator
	allocator_type get_allocator() const;


private: // attributes
	size_type		_capacity;
	pointer			_begin;
	pointer			_end;
	allocator_type	_allocator;

private: // methods
	pointer _vallocate(size_type n);
	void _vdeallocate();
	void _vreallocate(size_type n);
	void _construct_at_front(const size_type& n, const value_type& val);
	void _construct_at_front(const vector& other);
	void _destroy_at_end(pointer new_end);
	size_type _vsizecheck(size_type new_size) const;
};


template<typename T, typename Alloc>
vector<T,Alloc>::vector(const allocator_type& alloc):
	_capacity(0), _begin(nullptr), _end(nullptr), _allocator(alloc) {}

template<typename T, typename Alloc>
vector<T,Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc):
	_capacity(0), _begin(), _end(), _allocator(alloc)
{
	if (n > 0)
	{
		this->_begin = this->_vallocate(n);
		this->_end = this->_begin + n;
		this->_construct_at_front(n, val);
	}
}

template<typename T, typename Alloc>
template<typename InputIterator>
vector<T,Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type):
	_capacity(0), _begin(), _end(), _allocator(alloc)
{
	this->_begin = this->_end = this->_vallocate(ft::distance(first, last));
	for (; first != last; ++first)
		this->push_back(*first);
}

template<typename T, typename Alloc>
vector<T,Alloc>::vector(const vector& other):
	_capacity(0), _begin(), _end(), _allocator(other._allocator)
{
	size_type n = other.size();
	this->_begin = this->_vallocate(other._capacity);
	this->_end = this->_begin + n;
	this->_construct_at_front(other);
}

template<typename T, typename Alloc>
vector<T,Alloc>::~vector()
{
	if (this->_begin != nullptr)
		this->_vdeallocate();
}



template<typename T, typename Alloc>
vector<T,Alloc>&
vector<T,Alloc>::operator=(const vector<T,Alloc>& other)
{
	if (this != &other)
	{
		// if (this->_capacity >= other._capacity)
		// {
		// 	this->clear();
		// 	this->_construct_at_front(other);
		// }
		this->_vdeallocate();
		this->_begin = this->_vallocate(other.capacity());
		this->_end = this->begin + other.size();
		this->assign(other.begin(), other.end());
	}
	return *this;
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::reference
vector<T,Alloc>::operator[](size_type n)
{
	return this->_begin[n];
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::const_reference
vector<T, Alloc>::operator[](size_type n) const
{
	return this->_begin[n];
}



template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::begin()
{
	return iterator(this->_begin);
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::const_iterator
vector<T,Alloc>::begin() const
{
	return const_iterator(this->_begin);
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T, Alloc>::end()
{
	return iterator(this->_end);
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::const_iterator
vector<T,Alloc>::end() const
{
	return const_iterator(this->_end);
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::reverse_iterator
vector<T, Alloc>::rbegin()
{
	return reverse_iterator(this->end());
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::const_reverse_iterator
vector<T,Alloc>::rbegin() const
{
	return const_reverse_iterator(this->end());
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::reverse_iterator
vector<T,Alloc>::rend()
{
	return reverse_iterator(this->begin());
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::const_reverse_iterator
vector<T,Alloc>::rend() const
{
	return const_reverse_iterator(this->begin());
}



template<typename T, typename Alloc>
typename vector<T,Alloc>::size_type
vector<T,Alloc>::size() const
{
	return static_cast<size_type>(this->_end - this->_begin);
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::size_type
vector<T,Alloc>::max_size() const
{
	return this->_allocator.max_size();
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::resize(size_type n, value_type val)
{
	size_type curr_size = this->size();
	if (curr_size >= n)
		this->_destroy_at_end(this->_begin + n);
	else
	{
		for (; curr_size < n; ++curr_size)
			this->push_back(val);
	}
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::size_type
vector<T,Alloc>::capacity() const
{
	return this->_capacity;
}

template<typename T, typename Alloc>
bool
vector<T,Alloc>::empty() const
{
	return this->_begin == this->_end;
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::reserve(size_type n)
{
	if (n <= this->_capacity)
		return;
	pointer new_begin = this->_vallocate(n);
	pointer new_end = new_begin + n;
	ft::copy(this->_begin, this->_end, new_begin);
	this->_vdeallocate();
	this->_begin = new_begin;
	this->_end = new_end;
}



template<typename T, typename Alloc>
typename vector<T,Alloc>::reference
vector<T,Alloc>::at(size_type n)
{
	if (n >= this->size())
		throw std::out_of_range("vector");
	return this->_begin[n];
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::const_reference
vector<T,Alloc>::at(size_type n) const
{
	if (n >= this->size())
		throw std::out_of_range("vector");
	return this->_begin[n];
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::reference
vector<T,Alloc>::front()
{
	return *this->_begin;
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::const_reference
vector<T,Alloc>::front() const
{
	return *this->_begin;
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::reference
vector<T,Alloc>::back()
{
	return *(this->_end - 1);
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::const_reference
vector<T,Alloc>::back() const
{
	return *(this->_end - 1);
}

template<typename T, typename Alloc>
template<typename InputIterator>
void
vector<T,Alloc>::assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type)
{
	size_type new_size = static_cast<size_type>(ft::distance(first, last));
	if (new_size > this->_capacity)
	{
		this->_vreallocate(new_size);
		for (; first != last; ++first)
			this->push_back(*first);
	}
	else
	{
		// work to be done
	}
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::assign(size_type n, const value_type& val)
{
	if (n <= this->_capacity)
	{
		this->clear();
		this->_construct_at_front(n, val);
	}
	else
	{
		this->_vreallocate(n);
		this->_construct_at_front(n, val);
	}
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::push_back(const value_type& val)
{
	this->reserve(this->size() + 1);
	this->_allocator.construct(this->_end, val);
	++this->_end;
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::pop_back()
{
	--this->_end;
	this->_allocator.destroy(this->_end);
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::insert(iterator position, const value_type& val)
{
	pointer pos = this->_begin + (position - this->begin());
	
	(void)val;
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::insert(iterator position, size_type n, const value_type& val)
{
	// room for optimisation
	for (size_type i = 0; i < n; ++i)
		this->insert(position + i, val);
}

template<typename T, typename Alloc>
template<typename InputIterator>
void
vector<T,Alloc>::insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type)
{
	(void)position;
	(void)first;
	(void)last;
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T, Alloc>::erase(iterator position)
{
	if (position == this->end())
		this->pop_back();
	else
	{
		pointer pos = this->_begin + (position - this->begin());
		this->_destroy_at_end(ft::copy(pos + 1, this->_end, pos));
	}
	return position;
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::erase(iterator first, iterator last)
{
	pointer pos = this->_begin + (first - this->begin());
	if (first != last)
		this->_destroy_at_end(ft::copy(pos + (last - first), this->_end, pos));
	return iterator(pos);
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::swap(vector& other)
{
	ft::swap(this->_capacity, other._capacity);
	ft::swap(this->_begin, other._begin);
	ft::swap(this->_end, other._end);
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::clear()
{
	this->_destroy_at_end(this->_begin);
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::allocator_type
vector<T,Alloc>::get_allocator() const
{
	return this->_allocator;
}



template<typename T, typename Alloc>
typename vector<T,Alloc>::pointer
vector<T,Alloc>::_vallocate(size_type n)
{
	n = this->_vsizecheck(n);
	this->_capacity = n;
	return (this->_allocator.allocate(n));
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::_vdeallocate()
{
	this->_destroy_at_end(this->_begin);
	this->_allocator.deallocate(this->_begin, this->_capacity);
	this->_begin = this->_end = nullptr;
	this->_capacity = 0;
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::_vreallocate(size_type n)
{
	this->_vdeallocate();
	this->_begin = this->_vallocate(n);
	this->_end = this->_begin + n;
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::_construct_at_front(const size_type& n, const value_type& val)
{
	for (size_type i = 0; i < n; ++i)
		this->_allocator.construct(this->_begin + i, val);
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::_construct_at_front(const vector& other)
{
	size_type n = other.size();
	for (size_type i = 0; i < n; ++i)
		this->_allocator.construct(this->_begin + i, other[i]);
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::_destroy_at_end(pointer new_end)
{
	pointer current_end = this->_end;

	while (current_end != new_end)
	{
		--current_end;
		this->_allocator.destroy(current_end);
	}
	this->_end = new_end;
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::size_type
vector<T,Alloc>::_vsizecheck(size_type new_size) const
{
	const size_type temp_max_size = this->max_size();
	if (new_size > temp_max_size)
		std::length_error("vector");
	size_type temp_capacity = this->capacity();
	if (temp_capacity >= temp_max_size / 2)
		return temp_max_size;
	temp_capacity *= 2;
	return new_size > temp_capacity ? new_size : temp_capacity;
}

// relational operator overloads

template<typename T, typename Alloc>
inline bool
operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename Alloc>
inline bool
operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Alloc>
inline bool
operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename Alloc>
inline bool
operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return rhs < lhs;
}

template<typename T, typename Alloc>
inline bool
operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template<typename T, typename Alloc>
inline bool
operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
}

template<typename T, typename Alloc>
void
swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
{
	x.swap(y);
}





} // namespace ft

// #include "vector.ipp"
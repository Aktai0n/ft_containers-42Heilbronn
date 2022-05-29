/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:54:31 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/29 17:45:40 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

namespace ft
{


// public methods

// constructors / destructor

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
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*):
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
	this->_begin = this->_vallocate(other._capacity);
	this->_end = this->_begin + other.size();
	this->_construct_at_front(other);
}

template<typename T, typename Alloc>
vector<T,Alloc>::~vector()
{
	if (this->_begin != nullptr)
		this->_vdeallocate(this->_capacity);
}


// operator overloads

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
		this->_vdeallocate(this->_capacity);
		this->_capacity = 0;
		this->_begin = this->_vallocate(other.capacity());
		this->_end = this->_begin + other.size();
		this->_construct_at_front(other);
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


// iterators

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


// capacity

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
		this->reserve(n);
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
	size_type old_capacity = this->_capacity;
	pointer new_begin = this->_vallocate(n);
	pointer new_end = new_begin + this->size();
	ft::copy(this->_begin, this->_end, new_begin);
	this->_vdeallocate(old_capacity);
	this->_begin = new_begin;
	this->_end = new_end;
}


// element access

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


// modifiers

template<typename T, typename Alloc>
template<typename InputIterator>
void
vector<T,Alloc>::assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
{
	if (first == last)
		return;
	size_type new_size = static_cast<size_type>(ft::distance(first, last));
	if (new_size > this->_capacity)
	{
		this->_vreallocate(new_size);
		this->_end = this->_begin;
	}
	else
		this->clear();
	for (; first != last; ++first)
		this->push_back(*first);
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::assign(size_type n, const value_type& val)
{
	if (n > this->_capacity)
		this->_vreallocate(n);
	else
		this->clear();
	this->_construct_at_front(n, val);
	this->_end = this->_begin + n;
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

#if 0

template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::insert(iterator position, const value_type& val)
{
	pointer pos = this->_iterator_to_pointer(position);
	size_type index = static_cast<size_type>(ft::distance(this->_begin, pos));
	if (pos == this->_end)
		this->push_back(val);
	else
		this->insert(position, 1, val);
	return iterator(this->_begin + index);
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::insert(iterator position, size_type n, const value_type& val)
{
	if (n <= 0)
		return;
	pointer pos = this->_iterator_to_pointer(position);
	size_type tot_size = this->size() + n;
	if (tot_size >= this->_capacity)
	{
		size_type old_capacity = this->_capacity;
		pointer new_begin = this->_vallocate(tot_size);
		size_type dist = pos - this->_begin;
		size_type i, j;
		for (i = 0; i < dist; ++i)
			this->_allocator.construct(new_begin + i, this->_begin[i]);
		for (j = 0; j < n; ++j)
			this->_allocator.construct(new_begin + j + dist, val);
		size_type vec_size = this->size();
		for (; i < vec_size; ++i)
			this->_allocator.construct(new_begin + i + n, this->_begin[i]);
		this->_vdeallocate(old_capacity);
		this->_begin = new_begin;
		this->_end = new_begin + i + j;
	}
	else
	{
		ft::copy_backward(pos, this->_end, this->_end + n);
		for (size_type i = 0; i < n; ++i)
			pos[i] = val;
	}
}

template<typename T, typename Alloc>
template<typename InputIterator>
void
vector<T,Alloc>::insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
{
	if (first == last)
		return;
	pointer pos = this->_iterator_to_pointer(position);
	size_type n = static_cast<size_type>(ft::distance(first, last));
	size_type tot_size = this->size() + n;
	if (tot_size >= this->_capacity)
	{
		size_type old_capacity = this->_capacity;
		pointer new_begin = this->_vallocate(tot_size);
		size_type dist = pos - this->_begin;
		size_type i, j;
		for (i = 0; i < dist; ++i)
			this->_allocator.construct(new_begin + i, this->_begin[i]);
		for (j = 0; first != last; ++j, ++first)
			this->_allocator.construct(new_begin + j + dist, *first);
		size_type vec_size = this->size();
		for (; i < vec_size; ++i)
			this->_allocator.construct(new_begin + i + n, this->_begin[i]);
		this->_vdeallocate(old_capacity);
		this->_begin = new_begin;
		this->_end = new_begin + i + j;
	}
	else
	{
		ft::copy_backward(pos, this->_end, this->_end + n);
		for (size_type i = 0; first != last; ++first, ++i)
			pos[i] = *first;
	}
}

#else

template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::insert(iterator position, const value_type& val)
{
	pointer pos = this->_iterator_to_pointer(position);
	size_type dist = static_cast<size_type>(ft::distance(this->_begin, pos));
	if (position == this->end())
		this->push_back(val);
	else
		this->insert(position, 1, val);
	return iterator(this->_begin + dist);
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::insert(iterator position, size_type n, const value_type& val)
{
	if (n <= 0)
		return;
	pointer pos = this->_iterator_to_pointer(position);
	size_type dist = static_cast<size_type>(ft::distance(this->_begin, pos));
	size_type old_size = this->size();
	this->resize(old_size + n);
	ft::copy_backward(this->_begin + dist, this->_begin + old_size, this->_begin + old_size + n);
	ft::fill(this->_begin + dist, this->_begin + dist + n, val);
}

template<typename T, typename Alloc>
template<typename InputIterator>
void
vector<T,Alloc>::insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
{
	if (first == last)
		return;
	pointer pos = this->_iterator_to_pointer(position);
	size_type n = static_cast<size_type>(ft::distance(first, last));
	size_type dist = static_cast<size_type>(ft::distance(this->_begin, pos));
	size_type old_size = this->size();
	this->resize(old_size + n);
	ft::copy_backward(this->_begin + dist, this->_begin + old_size, this->_begin + old_size + n);
	ft::copy(first, last, this->_begin + dist);
}

#endif

template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T, Alloc>::erase(iterator position)
{
	if (position == this->end())
		this->pop_back();
	else
	{
		pointer pos = this->_iterator_to_pointer(position);
		this->_destroy_at_end(ft::copy(pos + 1, this->_end, pos));
	}
	return position;
}

template<typename T, typename Alloc>
typename vector<T,Alloc>::iterator
vector<T,Alloc>::erase(iterator first, iterator last)
{
	pointer pos = this->_iterator_to_pointer(first);
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


// allocator

template<typename T, typename Alloc>
typename vector<T,Alloc>::allocator_type
vector<T,Alloc>::get_allocator() const
{
	return this->_allocator;
}


// private methods

template<typename T, typename Alloc>
typename vector<T,Alloc>::size_type
vector<T,Alloc>::_vsizecheck(size_type new_size) const
{
	const size_type temp_max_size = this->max_size();
	if (new_size > temp_max_size)
		throw std::length_error("vector");
	size_type temp_capacity = this->capacity();
	if (temp_capacity >= temp_max_size / 2)
		return temp_max_size;
	temp_capacity *= 2;
	return new_size > temp_capacity ? new_size : temp_capacity;
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
vector<T,Alloc>::_vdeallocate(size_type n)
{
	this->_destroy_at_end(this->_begin);
	this->_allocator.deallocate(this->_begin, n);
	this->_begin = this->_end = nullptr;
}

template<typename T, typename Alloc>
void
vector<T,Alloc>::_vreallocate(size_type n)
{
	this->_vdeallocate(this->_capacity);
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
typename vector<T,Alloc>::pointer
vector<T,Alloc>::_iterator_to_pointer(const iterator& it) const
{
	return this->_begin + (it - this->begin());
}


} // namespace ft
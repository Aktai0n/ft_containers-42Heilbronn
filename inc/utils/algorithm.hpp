/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:31:04 by skienzle          #+#    #+#             */
/*   Updated: 2022/05/28 15:23:12 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


namespace ft
{


template<typename InputIterator1, typename InputIterator2>
bool
equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1)
	{
		if (!(*first1 == *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
bool
equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
		BinaryPredicate pred)
{
	while (first1 != last1)
	{
		if (!pred(*first1, *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

template<typename InputIterator1, typename InputIterator2>
bool
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
						InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1;
		++first2;
	}
	return first2 != last2;
}


template<typename InputIterator1, typename InputIterator2, typename Compare>
bool
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
						InputIterator2 first2, InputIterator2 last2,
						Compare comp)
{
	while (first1 != last1)
	{
		if (first2 == last2 || comp(*first1, *first2))
			return true;
		else if (comp(*first2, *first1))
			return false;
		++first1;
		++first2;
	}
	return false;
}

template<typename InputIterator, typename OutputIterator>
OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator result)
{
	while (first != last)
	{
		*result = *first;
		++result;
		++first;
	}
	return result;
}

template<typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2
copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
				BidirectionalIterator2 result)
{
	while (last != first)
		*(--result) = *(--last);
	return result;
}

template<typename ForwardIterator, typename T>
void
fill(ForwardIterator first, ForwardIterator last, const T& val)
{
	for (; first != last; ++first)
		*first = val;
}

template<typename T>
void
swap(T& first, T& second)
{
	T temp = first;
	first = second;
	second = temp;
}

template<typename T>
const T&
max(const T& first, const T& second)
{
	return first < second ? first : second;
}

template<typename T>
const T&
min(const T& first, const T& second)
{
	return !(first < second) ? first : second;
}


} // namespace ft
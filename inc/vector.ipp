/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:34:31 by skienzle          #+#    #+#             */
/*   Updated: 2022/01/06 16:59:31 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc)
{(void)alloc;}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc)
{
	(void)n;
	(void)val;
	(void)alloc;
}

template<typename T, typename Alloc>
template<typename InputIterator>
vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc)
{
	(void)first;
	(void)last;
	(void)alloc;
}


} // namespace ft
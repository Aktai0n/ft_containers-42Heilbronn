/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:07:50 by skienzle          #+#    #+#             */
/*   Updated: 2022/06/19 12:33:51 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#ifdef __linux__

#include <sys/time.h>

template<bool DisplayMicroseconds = true>
class Timer
{
public:
	Timer(): _start_timepoint(), _total_time()
	{
		gettimeofday(&_start_timepoint, NULL);
	}

	void start()
	{
		gettimeofday(&_start_timepoint, NULL);
	}

	double stop()
	{
		timeval stop_timepoint;
		gettimeofday(&stop_timepoint, NULL);
		double elapsed = get_time(stop_timepoint) - get_time(_start_timepoint);
		_total_time += elapsed;
		return elapsed;
	}

	double get_total_time() const
	{
		return _total_time;
	}

private:
	double get_time(const timeval& timepoint) const
	{
		if (!DisplayMicroseconds)
			return timepoint.tv_sec * 1000 + timepoint.tv_usec / 1000;
		else
			return static_cast<double>(timepoint.tv_sec) * 1000.0 +
					static_cast<double>(timepoint.tv_usec) / 1000.0;
	}

	timeval _start_timepoint;
	double _total_time;
};

#else

#include <chrono>

template<bool DisplayMicroseconds = true>
class Timer
{
public:
	Timer(): _start_timepoint(std::chrono::high_resolution_clock::now()), _total_time(0.0) {}
	
	~Timer()
	{
		stop();
	}

	void start()
	{
		_start_timepoint = std::chrono::high_resolution_clock::now();
	}

	double stop()
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> end_timepoint =
			std::chrono::high_resolution_clock::now();
		
		if (!DisplayMicroseconds)
		{
			long long start = std::chrono::time_point_cast<std::chrono::milliseconds>
							(_start_timepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::milliseconds>
							(end_timepoint).time_since_epoch().count();
			_total_time += static_cast<double>(end - start);
			return static_cast<double>(end - start);
		}
		else
		{
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>
								(_start_timepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>
								(end_timepoint).time_since_epoch().count();
			_total_time += static_cast<double>(end - start) * 0.001;
			return static_cast<double>(end - start) * 0.001;
		}
	}

	double get_total_time()
	{
		return _total_time;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _start_timepoint;
	double _total_time;
};

#endif // __LINUX__
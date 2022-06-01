#ifdef FT_MODE
	#include "../inc/vector.hpp"
	#include "../inc/map.hpp"
	#include "../inc/set.hpp"
	#include "../inc/stack.hpp"
#else
	#include <vector>
	#include <map>
	#include <stack>
	#include <set>
	namespace ft=std;
#endif

#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
using ft::vector;
using std::cout;
using std::endl;

template<class T>
void	print_vector(T const &test)
{
	cout << "Printing all vector values: " << endl;
	typename T::const_iterator begin = test.begin();
	typename T::const_iterator end = test.end();
	while (begin != end)
	{
		cout << *begin;
		begin++;
		if (begin != end)
			cout << ", ";
	}
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "get stuff from vector: " << endl;
	cout << "size: " << test.size() << std::endl;
	cout << "max_size: " << test.max_size() << std::endl;
	cout << "begin: " << *test.begin() << std::endl;
	cout << "-------------------------------" << endl;
	cout << "try out of range: (-1)" << endl;
	cout << "-------------------------------" << endl;
	cout << "-------------------------------" << endl;
}

int	main(void)
{
	vector<int>	x(10, 9);
	print_vector(x);
	x.resize(22, 13);
	print_vector(x);
	x.push_back(97);
	print_vector(x);
	x.pop_back();
	print_vector(x);
	while (x.size())
	{
		x.pop_back();
		print_vector(x);
	}
	print_vector(x);
	x.assign(5, 3);
	print_vector(x);
	x.insert((x.begin()), 1, 72);
	print_vector(x);
	x.insert(++(x.begin()), 1, 73);
	print_vector(x);
	x.insert((x.end()), 1, 432);
	print_vector(x);
	x.insert(--(x.end()), 1, 90);
	print_vector(x);
	std::cout << *x.insert(--x.end(), 33) << std::endl;
	std::cout << *x.erase(--(x.end())) << std::endl;
	print_vector(x);
	std::cout << *x.erase(++x.begin(), --x.end()) << std::endl;
	print_vector(x);
	std::cout << *x.erase(++x.begin(), --x.end()) << std::endl;
	print_vector(x);
	vector<int>	t;
	t = x;
	print_vector(t);
	t.push_back(-2353);
	print_vector(t);
	t.push_back(-2323);
	print_vector(t);
	t.push_back(12312);
	print_vector(t);
	x = t;
	print_vector(x);
	print_vector(t);
	t.push_back(-123);
	x[0] = 666;
	std::cout << *x.begin() << std::endl;
	std::cout << *t.begin() << std::endl;
	x.swap(t);
	std::cout << *x.begin() << std::endl;
	std::cout << *t.begin() << std::endl;
	print_vector(x);
	print_vector(t);
	std::cout << x.size() << std::endl;
	std::cout << t.size() << std::endl;
	std::cout << (t != x) << std::endl;
	std::cout << (t == x) << std::endl;
	std::cout << (t < x) << std::endl;
	std::cout << (t > x) << std::endl;
	std::cout << (t <= x) << std::endl;
	std::cout << (t >= x) << std::endl;
	t = x;
	std::cout << (t != x) << std::endl;
	std::cout << (t == x) << std::endl;
	std::cout << (t < x) << std::endl;
	std::cout << (t <= x) << std::endl;
	std::cout << (t > x) << std::endl;
	std::cout << (t >= x) << std::endl;
	t.push_back(-123);
	swap(x, t);
	print_vector(x);
	std::cout << (t != x) << std::endl;
	std::cout << (t == x) << std::endl;
	std::cout << (t < x) << std::endl;
	std::cout << (t <= x) << std::endl;
	std::cout << (t > x) << std::endl;
	std::cout << (t >= x) << std::endl;
	print_vector(t);
	vector<int> d(t.begin(), t.end());
	print_vector(d);
	d.assign(x.begin(), x.end());
	print_vector(d);
	d.assign(t.begin(), t.end());
	print_vector(d);
	d.assign(3, 11);
	print_vector(d);
	d.insert(++d.begin(), 7, -4);
	print_vector(d);
	print_vector(t);
	d.reserve(100);
	d.insert(d.begin(), t.begin(), t.end());
	print_vector(d);
	d.insert(d.end(), t.begin(), t.end());
	print_vector(d);
	d.insert(d.end() - 4, t.begin(), t.end());
	d.insert(d.end() - 4, t.begin(), t.end());
	d.insert(d.end() - 4, t.begin(), t.end());
	d.insert(d.end() - 4, t.begin(), t.end());
	d.insert(d.end() - 4, t.begin(), t.end());
	d.insert(d.end() - 4, t.begin(), t.end());
	d.insert(d.end() - 4, t.begin(), t.end());
	d.insert(d.end() - 4, t.begin(), t.end());
	print_vector(d);
	d.reserve(1000000);
	d.resize(1231, 234);
	d.resize(123100000, 234);
	d.resize(12, 44);
	{
		vector<int>::reverse_iterator	rbegin = d.rbegin();
		vector<int>::reverse_iterator	rend = d.rend();
		while (rbegin != rend)
		{
			std::cout << *rbegin << std::endl;
			*rbegin = 2345;
			rbegin = rbegin + 1;
			std::cout << rbegin - rend;
		}
	}
	vector<int>::const_reverse_iterator	rbegin = d.rbegin();
	vector<int>::const_reverse_iterator	rend = d.rend();
	while (rbegin != rend)
	{
		std::cout << *rbegin << std::endl;
		rbegin++;
	}
	ft::map<int, int> test;
	for (size_t i = 0; i < 5000; i++)
	{
		test[rand() % 50000] = i;
	}
	for (size_t i = 0; i < 20; i++)
	{
		ft::pair<ft::map<int,int>::iterator, ft::map<int, int>::iterator> eq = test.equal_range(rand() % 1234);
		while (eq.first != eq.second)
		{
			std::cout << eq.first->first << endl;
			eq.first++;
		}
		// std::cout << eq.first->first << endl;
	}
	

	std::cout << "begin: " << test.begin()->first << endl;
	for (size_t i = 0; i < 40; i++)
	{
		if (test.upper_bound(i) != test.end()) {
			if (test.upper_bound(i)->first == 10)
				std::cout << "upper_bound i: " << i << endl;
			cout << test.upper_bound(i)->first << endl;
		}
		if (test.lower_bound(i) != test.end())
			if (test.lower_bound(i)->first == 10)
				std::cout << "lower_bound i: " << i << endl;
			cout << test.lower_bound(i)->first << endl;
	}
	
	ft::map<int, int>::reverse_iterator rbg = test.rbegin();
	ft::map<int, int>::reverse_iterator rbe = test.rend();
	int	xd = 0;
	while (rbg != rbe)
	{
		cout << rbg->first << " ";

		rbg++;
		if (xd % 2 == 0)
			rbg--;
		xd++;
	}
	cout << endl;
	cout << test.upper_bound(17)->first << endl;
	
	// cout << test.empty() << endl;
	test.insert(ft::pair<const int, int>(10,1));
	test.insert(ft::pair<const int, int>(11,5));
	cout << test.size() << endl;
	// cout << test.empty() << endl;
	test.insert(ft::pair<int, int>(20,1));
	test.insert(ft::pair<int, int>(15,1));
	test.insert(ft::pair<int, int>(25,1));
	test.insert(ft::pair<int, int>(0,1));
	test.insert(ft::pair<int, int>(5,1));
	test.insert(ft::pair<int, int>(-5,1));
	ft::map<int, int>::iterator b = test.begin();
	ft::map<int, int>::iterator e = test.end();
	b = test.begin();
	e = test.end();
	while (b != e) {
		cout << test.size() << endl;
		cout << b->first << ", " << b->second << endl;
		b++;
	}
	b = test.begin();
	for (size_t i = 0; i < 1000000; i++)
	{
		test.insert(ft::pair<int, int>(std::rand() % 100000, i));
		cout << test.size() << endl;
	}
	for (size_t i = 0; i < 1000000; i++)
	{
		test.erase(std::rand() % 1000000);
		if (i % 3 == 0)
			test.insert(ft::pair<int, int>(std::rand() % 10000, i));
		if (i  % 100000 == 0)
			test.clear();

		cout << test.size() << endl;
	}
	for (size_t i = 0; i < 2000; i++)
	{
		b = test.begin();
		for (size_t i = 0; i < rand() % 50; i++)
		{
			b++;
		}
		test.erase(b);
		std::cout  << test.size() << endl;
		// test.insert(ft::make_pair(rand(), i));
		// test.find(rand());
		test[rand()] = i;
	}
	b = test.begin();
	e = test.end();
	while (e != b) {
		std::cout << b->first << std::endl;
		b++;
	}
	e--;
	std::cout << e->first << std::endl;
	b = test.begin();
	e = test.end();
	for (size_t i = 0; i < 200; i++)
	{
		b++;
		e--;
		std::cout << test.count(rand()) << std::endl;
	}
	test.erase(b, e);
	for (size_t i = 0; i < 10000; i++)
	{
		ft::map<int, int>::iterator g = test.find(std::rand() % 10000);
		if (g != test.end()) {
			cout << g->first << endl;
		}
		b = test.lower_bound(rand());
		if (b != test.end())
			cout << b->first << endl;
		b = test.upper_bound(rand());
		if (b != test.end())
			cout << b->first << endl;
		ft::pair<ft::map<int,int>::iterator, ft::map<int, int>::iterator> eq = test.equal_range(i);
		while (eq.first != eq.second)
		{
				std::cout << eq.first->first << endl;
			eq.first++;
		}
		// std::cout << eq.first->first << endl;
	}
	ft::map<int, int> test2(test.begin(), test.end());
	// std::cerr << "not till here" <<endl;


	ft::map<int, int> test3(test2);
	b = test3.begin();
	e = test3.end();

	test2.swap(test3);
	b = test2.begin();
	e = test2.end();
	while (b != e) {
		cout << test3.size() << endl;
		cout << b->first << ", " << b->second << endl;
		b++;
	}
	// --------------------
	ft::map<int, int>::const_reverse_iterator	rb = test3.rbegin();
	ft::map<int, int>::const_reverse_iterator	re = test3.rend();
	while (rb != re)
	{
		cout << rb->first << ", " << rb->second << endl;
		rb++;
	}
	cout << "max_size: " << test.max_size();
	{
		ft::map<int, std::string> max_testing;
		cout << max_testing.max_size();
	}
	{
		ft::map<std::string, std::string> max_testing;
		cout << max_testing.max_size();
	}
	{
		ft::map<long, std::string> max_testing;
		cout << max_testing.max_size();
	}
	{
		ft::map<char, std::string> max_testing;
		cout << max_testing.max_size();
	}
	cout << endl;
	ft::map<int, int>::mapped_type &y = test[-1];
	y = -78;
	std::cout << test[-1] << std::endl;
	std::cout << y << std::endl;
	cout << endl;
	test.erase(10);
	b = test.begin();
	e = test.end();
	while (b != e) {
		cout << b->first << " ";
		b++;
	}
	cout << endl;
	test.insert(ft::pair<int, int>(2, 2));
	std::cout << test.size() << std::endl;
	test.insert(ft::pair< int, int>(5, 5));
	std::cout << test.size() << std::endl;
	test.insert(ft::pair< int, int>(-12, 3));
	std::cout << test.size() << std::endl;
	test.insert(ft::pair< int, int>(3, 3));
	test.insert(ft::pair< int, int>(9, 3));
	test.insert(ft::pair< int, int>(4, 3));
	b = test.begin();
	e = test.end();
	while (b != e) {
		cout << b->first << " ";
		b++;
	}
	std::cout << test.empty() << std::endl;
	std::cout << "------" << std::endl;
	while (rb != re) {
		std::cout << (*rb).first << " ";
		rb++;
	}
	cout << endl;
	test.erase(test.find(5));
	rb = test.rbegin();
	re = test.rend();
	while (rb != re) {
		std::cout << (*rb).first << " ";
		rb++;
	}
	cout << endl;
	test.erase(test.find(3));
	rb = test.rbegin();
	re = test.rend();
	while (rb != re) {
		std::cout << (*rb).first << " ";
		rb++;
	}
	cout << endl;
	test.erase(test.find(-12));
	rb = test.rbegin();
	re = test.rend();
	while (rb != re) {
		std::cout << (*rb).first << " ";
		rb++;
	}
	cout << endl;
	std::cout << test.erase(4) << std::endl;
	rb = test.rbegin();
	re = test.rend();
	while (rb != re) {
		std::cout << (*rb).first << " ";
		rb++;
	}
	std::cout << "==" << (test == test3) << std::endl;
	rb = test.rbegin();
	re = test.rend();
	while (rb != re) {
		std::cout << (*rb).first << " ";
		rb++;
	}
	ft::stack<int>	stack_test;
	for (size_t i = 0; i <  100000; i++)
	{
		stack_test.push(rand());
	}
	ft::set<int>	set_test;
	for (size_t i = 0; i < 10000; i++) {
		std::cout << stack_test.top() << std::endl;
		set_test.insert(stack_test.top());
		stack_test.pop();
	}
	print_vector(set_test);
	for (size_t i = 0; i < 100000; i++)
	{
		x.push_back(rand());
	}
	print_vector(x);

	ft::map<int, int>::iterator it = test.begin();
	ft::map<int, int>::iterator et = test.end();
	test.erase(it++);
	test.erase(it++);
	test.erase(it++);
	for (;it != et; it++)
	{
		std::cout << it->first << std::endl;
	}
	

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jludt.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:47:05 by julian            #+#    #+#             */
/*   Updated: 2022/05/29 17:11:07 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>

#include "../inc/vector.hpp"
#include "../inc/stack.hpp"
#include "../inc/set.hpp"
#include "../inc/map.hpp"

#include <sys/time.h>
#include <iomanip>
#include <fstream>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"

#ifdef FT_MODE
#undef STD
#else
#define STD 1
#endif // FT_MODE

#define NAMESPACE ft
#ifdef STD
# undef NAMESPACE
# define NAMESPACE std
#endif

// functions for map & set
bool fncomp (char lhs, char rhs) {return lhs<rhs;}
bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp 
{
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

struct classcomp2
{
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};

int main()
{
	struct timespec startVector, endVector;
	struct timespec startStack, endStack;
	struct timespec startMap, endMap;
	struct timespec startSet, endSet;

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startVector);
	
	std::cout << GREEN << "\n****************************" << std::endl;
	std::cout          <<   "*          VECTOR          *" << std::endl;
	std::cout          <<   "****************************" << RESET << std::endl;

	std::cout << YELLOW << "\nvector::vector\n" << RESET;
	
	// constructors used in the same order as described above:
	NAMESPACE::vector<int> vfirst;                                // empty vector of ints
	NAMESPACE::vector<int> vsecond (4,100);                       // four ints with value 100
	NAMESPACE::vector<int> vthird (vsecond.begin(),vsecond.end());  // iterating through second
	NAMESPACE::vector<int> vfourth (vthird);                       // a copy of third
	// the iterator constructor can also be used to construct from arrays:
	int vmyints[] = {16,2,77,29};
	NAMESPACE::vector<int> fifth (vmyints, vmyints + sizeof(vmyints) / sizeof(int) );
	std::cout << "The contents of fifth are:";
	for (NAMESPACE::vector<int>::iterator vit = fifth.begin(); vit != fifth.end(); ++vit)
	std::cout << ' ' << *vit;
	std::cout << '\n';
	
	std::cout << YELLOW << "\nvector::operator=\n" << RESET;

	NAMESPACE::vector<int> vfoo0 (3,0);
	NAMESPACE::vector<int> vbar0 (5,0);
	vbar0 = vfoo0;
	vfoo0 = NAMESPACE::vector<int>();
	std::cout << "Size of vfoo0: " << int(vfoo0.size()) << '\n';
	std::cout << "Size of vbar0: " << int(vbar0.size()) << '\n';

	std::cout << YELLOW << "\nvector::begin & vector::end\n" << RESET;
	
	NAMESPACE::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);
	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::rbegin | vector::rend\n" << RESET;

	NAMESPACE::vector<int> myvector2 (5);  // 5 default-constructed ints
	int i=0;
	NAMESPACE::vector<int>::reverse_iterator rit = myvector2.rbegin();
	for (; rit!= myvector2.rend(); ++rit)
		*rit = ++i;
	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector2.begin(); it != myvector2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::size\n" << RESET;

	NAMESPACE::vector<int> vmyints2;
	std::cout << "0. size: " << vmyints2.size() << '\n';
	for (int i=0; i<10; i++) vmyints2.push_back(i);
		std::cout << "1. size: " << vmyints2.size() << '\n';
	vmyints2.insert (vmyints2.end(),10,100);
	std::cout << "2. size: " << vmyints2.size() << '\n';
	vmyints2.pop_back();
	std::cout << "3. size: " << vmyints2.size() << '\n';

	std::cout << YELLOW << "\nvector::size | vector::capacity | vector::max_size\n" << RESET;

	NAMESPACE::vector<int> myvector3;
	// set some content in the vector:
	for (int i=0; i<100; i++) myvector3.push_back(i);
	std::cout << "size: " << myvector3.size() << "\n";
	std::cout << "capacity: " << myvector3.capacity() << "\n";
	std::cout << "max_size: " << myvector3.max_size() << "\n";

	std::cout << YELLOW << "\nvector::resize\n" << RESET;

	NAMESPACE::vector<int> myvector4;
	for (int i=1;i<10;i++) myvector4.push_back(i);
	myvector4.resize(5);
	myvector4.resize(8,100);
	myvector4.resize(12);
	std::cout << "myvector contains:";
	for (unsigned i=0;i<myvector4.size();i++)
	std::cout << ' ' << myvector4[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::empty\n" << RESET;

	NAMESPACE::vector<int> myvector5;
	int sum (0);
	for (int i=1;i<=10;i++) myvector5.push_back(i);
	while (!myvector5.empty())
	{
		sum += myvector5.back();
		myvector5.pop_back();
	}
	std::cout << "total: " << sum << '\n';

	std::cout << YELLOW << "\nvector::reserve\n" << RESET;

	NAMESPACE::vector<int>::size_type vsz;
	NAMESPACE::vector<int> vfoo;
	vsz = vfoo.capacity();
	std::cout << "making vfoo grow:\n";
	for (int i=0; i<100; ++i) {
		vfoo.push_back(i);
		if (vsz!=vfoo.capacity()) {
		vsz = vfoo.capacity();
		std::cout << "capacity changed: " << vsz << '\n';
		}
	}
	NAMESPACE::vector<int> vbar;
	vsz = vbar.capacity();
	vbar.reserve(100);   // this is the only difference with foo above
	std::cout << "making vbar grow:\n";
	for (int i=0; i<100; ++i) {
		vbar.push_back(i);
		if (vsz!=vbar.capacity()) {
		vsz = vbar.capacity();
		std::cout << "capacity changed: " << vsz << '\n';
		}
	}

	std::cout << YELLOW << "\nvector::operator[]\n" << RESET;

	NAMESPACE::vector<int> myvector6 (10);   // 10 zero-initialized elements
	NAMESPACE::vector<int>::size_type sz = myvector6.size();
	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector6[i]=i;
	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector6[sz-1-i];
		myvector6[sz-1-i]=myvector6[i];
		myvector6[i]=temp;
	}
	std::cout << "myvector6 contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector6[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::at\n" << RESET;

	NAMESPACE::vector<int> myvector7 (10);   // 10 zero-initialized ints
	// assign some values:
	for (unsigned i=0; i<myvector7.size(); i++)
		myvector7.at(i)=i;
	std::cout << "myvector7 contains:";
	for (unsigned i=0; i<myvector7.size(); i++)
		std::cout << ' ' << myvector7.at(i);
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::front\n" << RESET;
	
	NAMESPACE::vector<int>myvector8;
	myvector8.push_back(78);
	myvector8.push_back(16);
	// now front equals 78, and back 16
	myvector8.front() -=myvector8.back();
	std::cout << "myvector8.front() is now " <<myvector8.front() << '\n';

	std::cout << YELLOW << "\nvector::back\n" << RESET;

	NAMESPACE::vector<int> myvector9;
	myvector9.push_back(10);
	while (myvector9.back() != 0)
	{
		myvector9.push_back ( myvector9.back() -1 );
	}
	std::cout << "myvector9 contains:";
	for (unsigned i=0; i<myvector9.size() ; i++)
		std::cout << ' ' << myvector9[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::assign\n" << RESET;

	NAMESPACE::vector<int> vfirst2;
	NAMESPACE::vector<int> vsecond2;
	NAMESPACE::vector<int> vthird2;
	vfirst2.assign (7,100);             // 7 ints with a value of 100
	NAMESPACE::vector<int>::iterator it;
	it=vfirst2.begin()+1;
	vsecond2.assign (it,vfirst2.end()-1); // the 5 central values of first
	int vmyints3[] = {1776,7,4};
	vthird2.assign (vmyints3,vmyints3+3);   // assigning from array.
	std::cout << "Size of first: " << int (vfirst2.size()) << '\n';
	std::cout << "Size of second: " << int (vsecond2.size()) << '\n';
	std::cout << "Size of third: " << int (vthird2.size()) << '\n';

	std::cout << YELLOW << "\nvector::push_back\n" << RESET;
	
	NAMESPACE::vector<int> myvector10;
	for (int i = 0; i < 10; ++i)
		myvector10.push_back (i);
	std::cout << "myvector10 stores " << int(myvector10.size()) << " numbers.\n";

	std::cout << YELLOW << "\nvector::pop_back\n" << RESET;

	NAMESPACE::vector<int> myvector11;
	int sum2 (0);
	myvector11.push_back (100);
	myvector11.push_back (200);
	myvector11.push_back (300);
	while (!myvector11.empty())
	{
		sum2+=myvector11.back();
		myvector11.pop_back();
	}
	std::cout << "The elements of myvector11 add up to " << sum2 << '\n';

	std::cout << YELLOW << "\nvector::insert\n" << RESET;

	NAMESPACE::vector<int> myvector12 (3,100);
	NAMESPACE::vector<int>::iterator it12;
	it12 = myvector12.begin();
	it12 = myvector12.insert ( it12 , 200 );
	myvector12.insert (it12,2,300);
	// "it12" no longer valid, get a new one:
	it12 = myvector12.begin();
	NAMESPACE::vector<int> anothervector (2,400);
	myvector12.insert (it12+2,anothervector.begin(),anothervector.end());
	int myarray [] = { 501,502,503 };
	myvector12.insert (myvector12.begin(), myarray, myarray+3);
	std::cout << "myvector12 contains:";
	for (it12=myvector12.begin(); it12<myvector12.end(); it12++)
		std::cout << ' ' << *it12;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::erase\n" << RESET;

	NAMESPACE::vector<int> myvector13;
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector13.push_back(i);
	// erase the 6th element
	myvector13.erase (myvector13.begin()+5);
	// erase the first 3 elements:
	myvector13.erase (myvector13.begin(),myvector13.begin()+3);
	std::cout << "myvector13 contains:";
	for (unsigned i=0; i<myvector13.size(); ++i)
		std::cout << ' ' << myvector13[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::swap\n" << RESET;

	NAMESPACE::vector<int> vfoo3 (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> vbar3 (5,200);   // five ints with a value of 200
	std::cout << "vfoo3 contains:";
	for (unsigned i=0; i<vfoo3.size(); i++)
		std::cout << ' ' << vfoo3[i];
	std::cout << '\n';
	std::cout << "vbar3 contains:";
	for (unsigned i=0; i<vbar3.size(); i++)
		std::cout << ' ' << vbar3[i];
	std::cout << "\n\n";
	vfoo3.swap(vbar3);
	std::cout << "vfoo3 contains:";
	for (unsigned i=0; i<vfoo3.size(); i++)
		std::cout << ' ' << vfoo3[i];
	std::cout << '\n';
	std::cout << "vbar3 contains:";
	for (unsigned i=0; i<vbar3.size(); i++)
		std::cout << ' ' << vbar3[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::clear\n" << RESET;

	NAMESPACE::vector<int> myvector14;
	myvector14.push_back (100);
	myvector14.push_back (200);
	myvector14.push_back (300);

	std::cout << "myvector14 contains:";
	for (unsigned i=0; i<myvector14.size(); i++)
		std::cout << ' ' << myvector14[i];
	std::cout << '\n';

	myvector14.clear();
	myvector14.push_back (1101);
	myvector14.push_back (2202);

	std::cout << "myvector14 contains:";
	for (unsigned i=0; i<myvector14.size(); i++)
		std::cout << ' ' << myvector14[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::get_allocator\n" << RESET;

	NAMESPACE::vector<int> myvector15;
	int * vp;
	unsigned int vi;
	// allocate an array with space for 5 elements using vector's allocator:
	vp = myvector15.get_allocator().allocate(5);
	// construct values in-place on the array:
	for (vi=0; vi<5; vi++) myvector15.get_allocator().construct(&vp[vi],vi);
	std::cout << "The allocated array contains:";
	for (vi=0; vi<5; vi++) std::cout << ' ' << vp[vi];
	std::cout << '\n';
	// destroy and deallocate:
	for (vi=0; vi<5; vi++) myvector15.get_allocator().destroy(&vp[vi]);
	myvector15.get_allocator().deallocate(vp,5);

	std::cout << YELLOW << "\nrelational operators (vector)\n" << RESET;

	NAMESPACE::vector<int> vfoo4 (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> vbar4 (2,200);   // two ints with a value of 200
	if (vfoo4==vbar4) std::cout << "vfoo4 and vbar4 are equal\n";
	if (vfoo4!=vbar4) std::cout << "vfoo4 and vbar4 are not equal\n";
	if (vfoo4< vbar4) std::cout << "vfoo4 is less than vbar4\n";
	if (vfoo4> vbar4) std::cout << "vfoo4 is greater than vbar4\n";
	if (vfoo4<=vbar4) std::cout << "vfoo4 is less than or equal to vbar4\n";
	if (vfoo4>=vbar4) std::cout << "vfoo4 is greater than or equal to vbar4\n";

	std::cout << YELLOW << "\nswap (vector)\n" << RESET;

	NAMESPACE::vector<int> vfoo5 (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> vbar5 (5,200);   // five ints with a value of 200
	std::cout << "vfoo5 contains:";
	for (NAMESPACE::vector<int>::iterator it = vfoo5.begin(); it!=vfoo5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "vbar5 contains:";
	for (NAMESPACE::vector<int>::iterator it = vbar5.begin(); it!=vbar5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	vfoo5.swap(vbar5);
	std::cout << "vfoo5 contains:";
	for (NAMESPACE::vector<int>::iterator it = vfoo5.begin(); it!=vfoo5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "vbar5 contains:";
	for (NAMESPACE::vector<int>::iterator it = vbar5.begin(); it!=vbar5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nperformance vector\n" << RESET;
	std::cout << "inserting and deleting lots of elements\n";
	
	struct timespec timeStart, timeEnd;
	// start timer
	clock_gettime(CLOCK_MONOTONIC, &timeStart);
	NAMESPACE::vector<int> perfV;
	for (size_t i = 0; i < 10000000; ++i)
			perfV.push_back(std::rand());
	NAMESPACE::vector<int> perfV2(perfV);
	NAMESPACE::vector<int> perfV3;
	perfV3.assign(perfV2.begin(), perfV2.end());
	perfV.erase(perfV.begin(), perfV.end());
	// end timer
	clock_gettime(CLOCK_MONOTONIC, &timeEnd);
	double timePerformance = timeStart.tv_sec * 1e9;
	timePerformance = (timeEnd.tv_sec - timeStart.tv_sec) * 1e9;
	timePerformance = (timePerformance + (timeEnd.tv_nsec - timeStart.tv_nsec)) * 1e-9;
	std::cout << "Vector performance test: " <<  timePerformance << "sec.\n"; 

	std::cout << YELLOW << "\nleaks vector\n" << RESET;

	#ifdef STD
		system("leaks std_containers | tail -3");
	#else
		system("leaks ft_containers | tail -3");
	#endif
	
	// stop timer.
	clock_gettime(CLOCK_MONOTONIC, &endVector);

	

/* ------------------------------------------------------------------------------------------------------------------ */

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startStack);
	
	std::cout << GREEN << "\n***************************" << std::endl;
	std::cout          <<   "*          STACK          *" << std::endl;
	std::cout          <<   "***************************" << RESET << std::endl;

	std::cout << YELLOW << "\nstack::stack\n" << RESET;

	#ifdef STD
	std::deque<int> smydeque (3,200);         				// deque with 3 elements
	NAMESPACE::vector<int> smyvector (2,200);         		// vector with 2 elements
	NAMESPACE::stack<int> sfirst;                 		    // empty stack
	NAMESPACE::stack<int> ssecond (smydeque);         		// stack initialized to copy of deque
	NAMESPACE::stack<int,NAMESPACE::vector<int> > sthird;	// empty stack using vector
	NAMESPACE::stack<int,NAMESPACE::vector<int> > sfourth (smyvector);
	#else
	std::deque<int> smydeque (2,200);         				// deque with 3 elements
	NAMESPACE::vector<int> smyvector (3,200);        		// vector with 2 elements
	NAMESPACE::stack<int> sfirst;                    		// empty stack
	NAMESPACE::stack<int> ssecond (smyvector);         		// stack initialized to copy of deque
	NAMESPACE::stack<int,std::deque<int> > sthird;  		// empty stack using vector
	NAMESPACE::stack<int,std::deque<int> > sfourth (smydeque);
	#endif
	std::cout << "size of sfirst: " << sfirst.size() << '\n';
	std::cout << "size of ssecond: " << ssecond.size() << '\n';
	std::cout << "size of sthird: " << sthird.size() << '\n';
	std::cout << "size of sfourth: " << sfourth.size() << '\n';

	std::cout << YELLOW << "\nstack::empty\n" << RESET;

	NAMESPACE::stack<int> mystack;
	int ssum (0);
	for (int i=1;i<=10;i++) mystack.push(i);
	while (!mystack.empty())
	{
		ssum += mystack.top();
		mystack.pop();
	}
	std::cout << "total: " << ssum << '\n';

	std::cout << YELLOW << "\nstack::size\n" << RESET;
	
	NAMESPACE::stack<int> smyints;
	std::cout << "0. size: " << smyints.size() << '\n';
	for (int i=0; i<5; i++) smyints.push(i);
	std::cout << "1. size: " << smyints.size() << '\n';
	smyints.pop();
	std::cout << "2. size: " << smyints.size() << '\n';

	std::cout << YELLOW << "\nstack::top\n" << RESET;

	NAMESPACE::stack<int> mystack2;
	mystack2.push(10);
	mystack2.push(20);
	mystack2.top() -= 5;
	std::cout << "mystack2.top() is now " << mystack2.top() << '\n';

	std::cout << YELLOW << "\nstack::push | stack::pop\n" << RESET;

	NAMESPACE::stack<int> mystack3;
	for (int i=0; i<5; ++i) mystack3.push(i);
	std::cout << "Popping out elements...";
	while (!mystack3.empty())
	{
		std::cout << ' ' << mystack3.top();
		mystack3.pop();
	}
	std::cout << '\n';

	std::cout << YELLOW << "\nrelational operators (stack)\n" << RESET;

	NAMESPACE::stack<int> mystackA;
	std::cout << "StackA contains: ";
	for (int i=1;i<=10;i++)
	{
		std::cout << i << " ";
		mystackA.push(i);
	}
	std::cout << '\n';

	std::cout << "StackB contains: ";
	NAMESPACE::stack<int> mystackB;
	for (int i=1;i<=10;i++)
	{
		std::cout << i << " ";
		mystackB.push(i);
	}
	std::cout << '\n';
	std::cout << std::boolalpha;
	std::cout << "operator== "<<(mystackA == mystackB) << '\n';
	std::cout << "operator!= "<<(mystackA != mystackB) << '\n';
	std::cout << "operator<  "<<(mystackA < mystackB) << '\n';
	std::cout << "operator<= "<<(mystackA <= mystackB) << '\n';
	std::cout << "operator>  "<<(mystackA > mystackB) << '\n';
	std::cout << "operator>= "<<(mystackA >= mystackB) << '\n';
	std::cout << std::noboolalpha;

	std::cout << YELLOW << "\nperformance stack\n" << RESET;
	std::cout << "inserting and deleting lots of elements\n";
	
	// start timer
	clock_gettime(CLOCK_MONOTONIC, &timeStart);
	NAMESPACE::stack<int> perfS;
	for (size_t i = 0; i < 10000000; ++i)
			perfS.push(std::rand());
	NAMESPACE::stack<int> perfS2(perfS);
	for (size_t i = 0; i < 10000000; ++i)
			perfS.pop();
	// end timer
	clock_gettime(CLOCK_MONOTONIC, &timeEnd);
	timePerformance = timeStart.tv_sec * 1e9;
	timePerformance = (timeEnd.tv_sec - timeStart.tv_sec) * 1e9;
	timePerformance = (timePerformance + (timeEnd.tv_nsec - timeStart.tv_nsec)) * 1e-9;
	std::cout << "Stack performance test: " <<  timePerformance << "sec.\n"; 

	std::cout << YELLOW << "\nleaks stack\n" << RESET;

	#ifdef STD
		system("leaks std_containers | tail -3");
	#else
		system("leaks ft_containers | tail -3");
	#endif

	clock_gettime(CLOCK_MONOTONIC, &endStack);

/* ------------------------------------------------------------------------------------------------------------------ */

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startMap);
	
	std::cout << GREEN << "\n***************************" << std::endl;
	std::cout          <<   "*           MAP           *" << std::endl;
	std::cout          <<   "***************************" << RESET << std::endl;

	std::cout << YELLOW << "\nmap::map\n" << RESET;

	NAMESPACE::map<char,int> mfirst;
	mfirst['a']=10;
	mfirst['b']=30;
	mfirst['c']=50;
	mfirst['d']=70;
	NAMESPACE::map<char,int> msecond (mfirst.begin(),mfirst.end());
	NAMESPACE::map<char,int> mthird (msecond);
	NAMESPACE::map<char,int,classcomp> mfourth;                 // class as Compare
	bool(*fn_pt)(char,char) = fncomp;
	NAMESPACE::map<char,int,bool(*)(char,char)> mfifth (fn_pt);
	for (NAMESPACE::map<char, int>::iterator mit = mthird.begin(); mit != mthird.end(); ++mit)
		std::cout << mit->first << " => " << mit->second << '\n';

	std::cout << YELLOW << "\nmap::operator=\n" << RESET;

	NAMESPACE::map<char,int> mfirst2;
	NAMESPACE::map<char,int> msecond2;
	mfirst2['x']=8;
	mfirst2['y']=16;
	mfirst2['z']=32;
	msecond2=mfirst2;                // second now contains 3 ints
	mfirst2=NAMESPACE::map<char,int>();    // and first is now empty
	std::cout << "Size of mfirst2: " << mfirst2.size() << '\n';
	std::cout << "Size of msecond2: " << msecond2.size() << '\n';

	std::cout << YELLOW << "\nmap::begin | map::end\n" << RESET;

	NAMESPACE::map<char,int> mymap;
	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	// show content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nmap::rbegin | map::rend\n" << RESET;

	NAMESPACE::map<char,int> mymap2;
	mymap2['x'] = 100;
	mymap2['y'] = 200;
	mymap2['z'] = 300;
	// show content:
	NAMESPACE::map<char,int>::reverse_iterator mrit;
	for (mrit=mymap2.rbegin(); mrit!=mymap2.rend(); ++mrit)
		std::cout << mrit->first << " => " << mrit->second << '\n';

	std::cout << YELLOW << "\nmap::empty\n" << RESET;

	NAMESPACE::map<char,int> mymap3;
	mymap3['a']=10;
	mymap3['b']=20;
	mymap3['c']=30;
	while (!mymap3.empty())
	{
		std::cout << mymap3.begin()->first << " => " << mymap3.begin()->second << '\n';
		mymap3.erase(mymap3.begin());
	}

	std::cout << YELLOW << "\nmap::size\n" << RESET;
	
	NAMESPACE::map<char,int> mymap4;
	mymap4['a']=101;
	mymap4['b']=202;
	mymap4['c']=302;
	std::cout << "mymap4.size() is " << mymap4.size() << '\n';

	std::cout << YELLOW << "\nmap::max_size\n" << RESET;

	NAMESPACE::map<int,int> mymap5;
	if (mymap5.max_size()>1000)
	{
		for (int i=0; i<1000; i++) mymap5[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";

	std::cout << YELLOW << "\nmap::operator[]\n" << RESET;
	
	NAMESPACE::map<char,std::string> mymap6;
	mymap6['a']="an element";
	mymap6['b']="another element";
	mymap6['c']=mymap6['b'];
	std::cout << "mymap6['a'] is " << mymap6['a'] << '\n';
	std::cout << "mymap6['b'] is " << mymap6['b'] << '\n';
	std::cout << "mymap6['c'] is " << mymap6['c'] << '\n';
	std::cout << "mymap6['d'] is " << mymap6['d'] << '\n';
	std::cout << "mymap6 now contains " << mymap6.size() << " elements.\n";

	std::cout << YELLOW << "\nmap::insert\n" << RESET;

	NAMESPACE::map<char,int> mymap7;
	// first insert function version (single parameter):
	mymap7.insert ( NAMESPACE::pair<char,int>('a',100) );
	mymap7.insert ( NAMESPACE::pair<char,int>('z',200) );
	NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,bool> ret;
	ret = mymap7.insert ( NAMESPACE::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}
	// second insert function version (with hint position):
	NAMESPACE::map<char,int>::iterator mit7 = mymap7.begin();
	mymap7.insert (mit7, NAMESPACE::pair<char,int>('b',300));  // max efficiency inserting
	mymap7.insert (mit7, NAMESPACE::pair<char,int>('c',400));  // no max efficiency inserting
	// third insert function version (range insertion):
	NAMESPACE::map<char,int> anothermap;
	anothermap.insert(mymap7.begin(),mymap7.find('c'));
	// showing contents:
	std::cout << "mymap7 contains:\n";
	for (mit7=mymap7.begin(); mit7!=mymap7.end(); ++mit7)
		std::cout << mit7->first << " => " << mit7->second << '\n';
	std::cout << "anothermap contains:\n";
	for (mit7=anothermap.begin(); mit7!=anothermap.end(); ++mit7)
		std::cout << mit7->first << " => " << mit7->second << '\n';

	std::cout << YELLOW << "\nmap::erase\n" << RESET;

	NAMESPACE::map<char,int> mymap8;
	NAMESPACE::map<char,int>::iterator mit8;
	// insert some values:
	mymap8['a']=10;
	mymap8['b']=20;
	mymap8['c']=30;
	mymap8['d']=40;
	mymap8['e']=50;
	mymap8['f']=60;
	mit8=mymap8.find('b');
	mymap8.erase (mit8);                   // erasing by iterator
	mymap8.erase ('c');                  // erasing by key
	mit8=mymap8.find ('e');
	mymap8.erase ( mit8, mymap8.end() );    // erasing by range
	// show content:
	for (mit8=mymap8.begin(); mit8!=mymap8.end(); ++mit8)
		std::cout << mit8->first << " => " << mit8->second << '\n';

	std::cout << YELLOW << "\nmap::swap\n" << RESET;
	
	NAMESPACE::map<char,int> mfoo;
	NAMESPACE::map<char,int> mbar;
	mfoo['x']=100;
	mfoo['y']=200;
	mbar['a']=11;
	mbar['b']=22;
	mbar['c']=33;
	std::cout << "mfoo contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mfoo.begin(); it!=mfoo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "mbar contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mbar.begin(); it!=mbar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "\nswapping\n\n";
	mfoo.swap(mbar);
	std::cout << "mfoo contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mfoo.begin(); it!=mfoo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "mbar contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mbar.begin(); it!=mbar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nmap::clear\n" << RESET;

	NAMESPACE::map<char,int> mymap9;
	mymap9['x']=100;
	mymap9['y']=200;
	mymap9['z']=300;
	std::cout << "mymap9 contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	mymap9.clear();
	mymap9['a']=1101;
	mymap9['b']=2202;
	std::cout << "mymap9 contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
		
	std::cout << YELLOW << "\nmap::key_comp\n" << RESET;

	NAMESPACE::map<char,int> mymap10;
	NAMESPACE::map<char,int>::key_compare mycomp = mymap10.key_comp();
	mymap10['a']=100;
	mymap10['b']=200;
	mymap10['c']=300;
	std::cout << "mymap10 contains:\n";
	char highest = mymap10.rbegin()->first;     // key value of last element
	NAMESPACE::map<char,int>::iterator mit10 = mymap10.begin();
	do {
		std::cout << mit10->first << " => " << mit10->second << '\n';
	} while ( mycomp((*mit10++).first, highest) );
	std::cout << '\n';

	std::cout << YELLOW << "\nmap::value_comp\n" << RESET;

	NAMESPACE::map<char,int> mymap11;
	mymap11['x']=1001;
	mymap11['y']=2002;
	mymap11['z']=3003;
	std::cout << "mymap11 contains:\n";
	NAMESPACE::pair<char,int> highest2 = *mymap11.rbegin();          // last element
	NAMESPACE::map<char,int>::iterator mit11 = mymap11.begin();
	do {
		std::cout << mit11->first << " => " << mit11->second << '\n';
	} while ( mymap11.value_comp()(*mit11++, highest2) );

	std::cout << YELLOW << "\nmap::find\n" << RESET;

	NAMESPACE::map<char,int> mymap12;
	NAMESPACE::map<char,int>::iterator mit12;
	mymap12['a']=50;
	mymap12['b']=100;
	mymap12['c']=150;
	mymap12['d']=200;
	mit12 = mymap12.find('b');
	if (mit12 != mymap12.end())
		mymap12.erase (mit12);
	// print content:
	std::cout << "elements in mymap12:" << '\n';
	std::cout << "a => " << mymap12.find('a')->second << '\n';
	std::cout << "c => " << mymap12.find('c')->second << '\n';
	std::cout << "d => " << mymap12.find('d')->second << '\n';

	std::cout << YELLOW << "\nmap::count\n" << RESET;

	NAMESPACE::map<char,int> mymap13;
	char c;
	mymap13 ['a']=101;
	mymap13 ['c']=202;
	mymap13 ['f']=303;
	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap13.count(c)>0)
			std::cout << " is an element of mymap13.\n";
		else 
			std::cout << " is not an element of mymap13.\n";
	}

	std::cout << YELLOW << "\nmap::lower_bound | map::upper_bound\n" << RESET;

	NAMESPACE::map<char,int> mymap14;
	NAMESPACE::map<char,int>::iterator itlow;
	NAMESPACE::map<char,int>::iterator itup;
	mymap14['a']=20;
	mymap14['b']=40;
	mymap14['c']=60;
	mymap14['d']=80;
	mymap14['e']=100;
	itlow=mymap14.lower_bound ('b');  // itlow points to b
	itup=mymap14.upper_bound ('d');   // itup points to e (not d!)
	mymap14.erase(itlow,itup);        // erases [itlow,itup)
	// print content:
	for (NAMESPACE::map<char,int>::iterator it=mymap14.begin(); it!=mymap14.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nmap::equal_range\n" << RESET;

	NAMESPACE::map<char,int> mymap15;
	mymap15['a']=10;
	mymap15['b']=20;
	mymap15['c']=30;
	NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,NAMESPACE::map<char,int>::iterator> mret2;
	mret2 = mymap15.equal_range('b');
	std::cout << "lower bound points to: ";
	std::cout << mret2.first->first << " => " << mret2.first->second << '\n';
	std::cout << "upper bound points to: ";
	std::cout << mret2.second->first << " => " << mret2.second->second << '\n';

	std::cout << YELLOW << "\nmap::get_allocator\n" << RESET;

	int psize;
	NAMESPACE::map<char,int> mymap16;
	NAMESPACE::pair<const char,int>* p;
	// allocate an array of 5 elements using mymap16's allocator:
	p=mymap16.get_allocator().allocate(5);
	// assign some values to array
	psize = sizeof(NAMESPACE::map<char,int>::value_type)*5;
	std::cout << "The allocated array has a size of " << psize << " bytes.\n";
	mymap16.get_allocator().deallocate(p,5);

	std::cout << YELLOW << "\nrelational operators (map)\n" << RESET;

	NAMESPACE::map<int, char> malice;
	malice.insert ( NAMESPACE::pair<int,char>(1,'a') );
	malice.insert ( NAMESPACE::pair<int,char>(2,'b') );
	malice.insert ( NAMESPACE::pair<int,char>(3,'c') );
	NAMESPACE::map<int, char> mbob;
	mbob.insert ( NAMESPACE::pair<int,char>(7,'Z') );
	mbob.insert ( NAMESPACE::pair<int,char>(8,'Y') );
	mbob.insert ( NAMESPACE::pair<int,char>(9,'X') );
	mbob.insert ( NAMESPACE::pair<int,char>(10,'W') );
	NAMESPACE::map<int, char> meve;
	meve.insert ( NAMESPACE::pair<int,char>(1,'a') );
	meve.insert ( NAMESPACE::pair<int,char>(2,'b') );
	meve.insert ( NAMESPACE::pair<int,char>(3,'c') );
	std::cout << std::boolalpha;
	// Compare non equal containers
	std::cout << "malice == mbob returns " << (malice == mbob) << '\n';
	std::cout << "malice != mbob returns " << (malice != mbob) << '\n';
	std::cout << "malice <  mbob returns " << (malice < mbob) << '\n';
	std::cout << "malice <= mbob returns " << (malice <= mbob) << '\n';
	std::cout << "malice >  mbob returns " << (malice > mbob) << '\n';
	std::cout << "malice >= mbob returns " << (malice >= mbob) << '\n';
	std::cout << '\n';
	// Compare equal containers
	std::cout << "malice == meve returns " << (malice == meve) << '\n';
	std::cout << "malice != meve returns " << (malice != meve) << '\n';
	std::cout << "malice <  meve returns " << (malice < meve) << '\n';
	std::cout << "malice <= meve returns " << (malice <= meve) << '\n';
	std::cout << "malice >  meve returns " << (malice > meve) << '\n';
	std::cout << "malice >= meve returns " << (malice >= meve) << '\n';
	std::cout << std::noboolalpha;

	std::cout << YELLOW << "\nswap (map)\n" << RESET;

	NAMESPACE::map<int, char> malice2;
	malice2.insert ( NAMESPACE::pair<int,char>(1,'a') );
	malice2.insert ( NAMESPACE::pair<int,char>(2,'b') );
	malice2.insert ( NAMESPACE::pair<int,char>(3,'c') );
	NAMESPACE::map<int, char> mbob2;
	mbob2.insert ( NAMESPACE::pair<int,char>(7,'Z') );
	mbob2.insert ( NAMESPACE::pair<int,char>(8,'Y') );
	mbob2.insert ( NAMESPACE::pair<int,char>(9,'X') );
	mbob2.insert ( NAMESPACE::pair<int,char>(10,'W') );
	// Print state before swap
	std::cout << "malice2:\n";
	for (NAMESPACE::map<int,char>::iterator it=malice2.begin(); it!=malice2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "\n" "mbob2:\n";
	for (NAMESPACE::map<int,char>::iterator it=mbob2.begin(); it!=mbob2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "\n-- SWAP\n\n";
	std::swap(malice2, mbob2);
	// Print state after swap
	std::cout << "malice2:\n";
	for (NAMESPACE::map<int,char>::iterator it=malice2.begin(); it!=malice2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "\n" "mbob2:\n";
	for (NAMESPACE::map<int,char>::iterator it=mbob2.begin(); it!=mbob2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nperformance map\n" << RESET;
	std::cout << "inserting and deleting lots of elements\n";
	
	// start timer
	clock_gettime(CLOCK_MONOTONIC, &timeStart);
	NAMESPACE::map<int, std::string> perfM;
	for (size_t i = 0; i < 10000000; ++i)
			perfM.insert(NAMESPACE::make_pair<int, std::string>(std::rand() % 1000000, "performance: " + std::to_string(i)));
	// std::cout << "Map perfM.size() = " << perfM.size() << std::endl;
	NAMESPACE::map<int, std::string> perfM2(perfM);	
	// std::cout << "Map perfM2.size() = " << perfM2.size() << std::endl;
	NAMESPACE::map<int, std::string> perfM3(perfM2.begin(), perfM2.end());
	// std::cout << "Map perfM3.size() = " << perfM3.size() << std::endl;
	perfM.erase(perfM.begin(), perfM.end());	
	// std::cout << "Map perfM.size() = " << perfM.size() << std::endl;
	
	// end timer
	clock_gettime(CLOCK_MONOTONIC, &timeEnd);
	timePerformance = timeStart.tv_sec * 1e9;
	timePerformance = (timeEnd.tv_sec - timeStart.tv_sec) * 1e9;
	timePerformance = (timePerformance + (timeEnd.tv_nsec - timeStart.tv_nsec)) * 1e-9;
	std::cout << "Map performance test: " <<  timePerformance << "sec.\n"; 

	std::cout << YELLOW << "\nleaks map\n" << RESET;

	#ifdef STD
		system("leaks std_containers | tail -3");
	#else
		system("leaks ft_containers | tail -3");
	#endif

	clock_gettime(CLOCK_MONOTONIC, &endMap);


/* ------------------------------------------------------------------------------------------------------------------ */

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startSet);
	
	std::cout << GREEN << "\n***************************" << std::endl;
	std::cout          <<   "*           Set           *" << std::endl;
	std::cout          <<   "***************************" << RESET << std::endl;

	std::cout << YELLOW << "\nset::set\n" << RESET;
	
	NAMESPACE::set<int> setfirst;                           // empty set of ints
	int setmyints[]= {10,20,30,40,50};
	NAMESPACE::set<int> setsecond (setmyints,setmyints+5);        // range
	NAMESPACE::set<int> setthird (setsecond);                  // a copy of second
	NAMESPACE::set<int> setfourth (setsecond.begin(), setsecond.end());  // iterator ctor.
	NAMESPACE::set<int,classcomp> setfifth;                 // class as Compare
	bool(*sfn_pt)(int,int) = fncomp;
	NAMESPACE::set<int,bool(*)(int,int)> setsixth (sfn_pt);  // function pointer as Compare
	for (NAMESPACE::set<int>::iterator mit = setthird.begin(); mit != setthird.end(); ++mit)
		std::cout << *mit << '\n';

	std::cout << YELLOW << "\nset::operator=\n" << RESET;

	int setmyints2[]={ 12,82,37,64,15 };
	NAMESPACE::set<int> setfirst2 (setmyints2,setmyints2+5);   // set with 5 ints
	NAMESPACE::set<int> setsecond2;                    // empty set
	setsecond2 = setfirst2;                          // now second contains the 5 ints
	setfirst2 = NAMESPACE::set<int>();                 // and first is empty
	std::cout << "Size of first: " << int (setfirst2.size()) << '\n';
	std::cout << "Size of second: " << int (setsecond2.size()) << '\n';

	std::cout << YELLOW << "\nset::begin | set::end\n" << RESET;

	int setints3[] = {75,23,65,42,13};
	NAMESPACE::set<int> myset (setints3,setints3+5);
	std::cout << "myset contains:";
	for (NAMESPACE::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nset::rbegin | set::rend\n" << RESET;

	int setints4[] = {21,64,17,78,49};
	NAMESPACE::set<int> myset2 (setints4,setints4+5);
	NAMESPACE::set<int>::reverse_iterator setrit;
	std::cout << "myset2 contains:";
	for (setrit=myset2.rbegin(); setrit != myset2.rend(); ++setrit)
		std::cout << ' ' << *setrit;
	std::cout << '\n';

	std::cout << YELLOW << "\nset::emty\n" << RESET;
	
	NAMESPACE::set<int> myset3;
	myset3.insert(20);
	myset3.insert(30);
	myset3.insert(10);
	std::cout << "myset3 contains:";
	while (!myset3.empty())
	{
		std::cout << ' ' << *myset3.begin();
		myset3.erase(myset3.begin());
	}
	std::cout << '\n';

	std::cout << YELLOW << "\nset::size\n" << RESET;

	NAMESPACE::set<int> myset4;
	std::cout << "0. size: " << myset4.size() << '\n';
	for (int i=0; i<10; ++i) myset4.insert(i);
	std::cout << "1. size: " << myset4.size() << '\n';
	myset4.insert (100);
	std::cout << "2. size: " << myset4.size() << '\n';
	myset4.erase(5);
	std::cout << "3. size: " << myset4.size() << '\n';

	std::cout << YELLOW << "\nset::max_size\n" << RESET;
	
	NAMESPACE::set<int> myset5;
	if (myset5.max_size()>1000)
	{
		for (i=0; i<1000; i++) myset5.insert(i);
		std::cout << "The set contains 1000 elements.\n";
	}
	else std::cout << "The set could not hold 1000 elements.\n";

	std::cout << YELLOW << "\nset::insert\n" << RESET;

	NAMESPACE::set<int> myset6;
	NAMESPACE::set<int>::iterator set_it;
	NAMESPACE::pair<NAMESPACE::set<int>::iterator,bool> set_ret;
	// set some inset_itial values:
	for (int i=1; i<=5; ++i) myset6.insert(i*10);    // set: 10 20 30 40 50
	set_ret = myset6.insert(20);               // no new element inserted
	if (set_ret.second==false) set_it=set_ret.first;  // "set_it" now points to element 20
	myset6.insert (set_it,25);                 // max efficiency inserting
	myset6.insert (set_it,24);                 // max efficiency inserting
	myset6.insert (set_it,26);                 // no max efficiency inserting
	int myints[]= {5,10,15};              // 10 already in set, not inserted
	myset6.insert (myints,myints+3);
	std::cout << "myset6 contains:";
	for (set_it=myset6.begin(); set_it!=myset6.end(); ++set_it)
		std::cout << ' ' << *set_it;
	std::cout << '\n';

	std::cout << YELLOW << "\nset::erase\n" << RESET;

	NAMESPACE::set<int> myset7;
	NAMESPACE::set<int>::iterator set_it2;
	// insert some values:
	for (int i=1; i<10; i++) myset7.insert(i*10);  // 10 20 30 40 50 60 70 80 90
	set_it2 = myset7.begin();
	++set_it2;                                         // "set_it2" points now to 20
	myset7.erase (set_it2);
	myset7.erase (40);
	set_it2 = myset7.find (60);
	myset7.erase (set_it2, myset7.end());
	std::cout << "myset7 contains:";
	for (set_it2=myset7.begin(); set_it2!=myset7.end(); ++set_it2)
		std::cout << ' ' << *set_it2;
	std::cout << '\n';

	std::cout << YELLOW << "\nset::swap\n" << RESET;

	 int set_myints[]={12,75,10,32,20,25};
	NAMESPACE::set<int> set_first (set_myints,set_myints+3);     // 10,12,75
	NAMESPACE::set<int> set_second (set_myints+3,set_myints+6);  // 20,25,32
	std::cout << "set_first contains:";
	for (NAMESPACE::set<int>::iterator it=set_first.begin(); it!=set_first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "set_second contains:";
	for (NAMESPACE::set<int>::iterator it=set_second.begin(); it!=set_second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "\nswapping\n\n";
	set_first.swap(set_second);
	std::cout << "set_first contains:";
	for (NAMESPACE::set<int>::iterator it=set_first.begin(); it!=set_first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "set_second contains:";
	for (NAMESPACE::set<int>::iterator it=set_second.begin(); it!=set_second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nset::clear\n" << RESET;

	NAMESPACE::set<int> myset8;
	myset8.insert (100);
	myset8.insert (200);
	myset8.insert (300);
	std::cout << "myset8 contains:";
	for (NAMESPACE::set<int>::iterator it=myset8.begin(); it!=myset8.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	myset8.clear();
	myset8.insert (1101);
	myset8.insert (2202);
	std::cout << "myset8 contains:";
	for (NAMESPACE::set<int>::iterator it=myset8.begin(); it!=myset8.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nset::key_compare\n" << RESET;

	NAMESPACE::set<int> myset9;
	int set_highest;
	NAMESPACE::set<int>::key_compare set_mycomp = myset9.key_comp();
	for (int i=0; i<=5; i++) myset9.insert(i);
	std::cout << "myset9 contains:";
	set_highest=*myset9.rbegin();
	NAMESPACE::set<int>::iterator set_it9=myset9.begin();
	do {
		std::cout << ' ' << *set_it9;
	} while ( set_mycomp(*(++set_it9),set_highest) );
	std::cout << '\n';

	std::cout << YELLOW << "\nset::value_compare\n" << RESET;

	NAMESPACE::set<int> myset10;
	NAMESPACE::set<int>::value_compare set_mycomp2 = myset10.value_comp();
	for (int i=0; i<=5; i++) myset10.insert(i);
	std::cout << "myset10 contains:";
	int set_highest2=*myset10.rbegin();
	NAMESPACE::set<int>::iterator set_it10=myset10.begin();
	do {
		std::cout << ' ' << *set_it10;
	} while ( set_mycomp2(*(++set_it10),set_highest2) );
	std::cout << '\n';

	std::cout << YELLOW << "\nset::key_compare\n" << RESET;

	NAMESPACE::set<int> myset11;
	NAMESPACE::set<int>::iterator set_it11;
	// set some inset_it11ial values:
	for (int i=1; i<=5; i++) myset11.insert(i*10);    // set: 10 20 30 40 50
	set_it11=myset11.find(20);
	myset11.erase (set_it11);
	myset11.erase (myset11.find(40));
	std::cout << "myset11 contains:";
	for (set_it11=myset11.begin(); set_it11!=myset11.end(); ++set_it11)
		std::cout << ' ' << *set_it11;
	std::cout << '\n';

	std::cout << YELLOW << "\nset::count\n" << RESET;

	NAMESPACE::set<int> myset12;
	// set some initial values:
	for (int i=1; i<5; ++i) myset12.insert(i*3);    // set: 3 6 9 12
	for (int i=0; i<10; ++i)
	{
		std::cout << i;
		if (myset12.count(i)!=0)
		std::cout << " is an element of myset12.\n";
		else
		std::cout << " is not an element of myset12.\n";
	}

	std::cout << YELLOW << "\nset::lower_bound | set::upper_bound\n" << RESET;

	NAMESPACE::set<int> myset13;
	NAMESPACE::set<int>::iterator set_itlow;
	NAMESPACE::set<int>::iterator set_itup;
	for (int i=1; i<10; i++) myset13.insert(i*10); // 10 20 30 40 50 60 70 80 90
	set_itlow=myset13.lower_bound (30);                //       ^
	set_itup=myset13.upper_bound (60);                 //                   ^
	myset13.erase(set_itlow,set_itup);                     // 10 20 70 80 90
	std::cout << "myset13 contains:";
	for (NAMESPACE::set<int>::iterator it=myset13.begin(); it!=myset13.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nset::equal_range\n" << RESET;

	NAMESPACE::set<int> myset14;
	for (int i=1; i<=5; i++) myset14.insert(i*10);   // myset14: 10 20 30 40 50
	NAMESPACE::pair<NAMESPACE::set<int>::const_iterator,NAMESPACE::set<int>::const_iterator> set_ret14;
	set_ret14 = myset14.equal_range(30);
	std::cout << "the lower bound points to: " << *set_ret14.first << '\n';
	std::cout << "the upper bound points to: " << *set_ret14.second << '\n';

	std::cout << YELLOW << "\nset::get_allocator\n" << RESET;

	NAMESPACE::set<int> myset15;
	int * sp;
	unsigned int si;
	// allocate an array of 5 elements using myset15's allocator:
	sp=myset15.get_allocator().allocate(5);
	// assign some values to array
	for (si=0; si<5; si++) sp[si]=(si+1)*10;
	std::cout << "The allocated array contains:";
	for (si=0; si<5; si++) std::cout << ' ' << sp[si];
	std::cout << '\n';
	myset15.get_allocator().deallocate(sp,5);

	std::cout << YELLOW << "\nrelational operators (set)\n" << RESET;

	NAMESPACE::set<int> salice;
	salice.insert(1);
	salice.insert(2);
	salice.insert(3);
	NAMESPACE::set<int> sbob;
	sbob.insert(7);
	sbob.insert(8);
	sbob.insert(9);
	sbob.insert(10);
	NAMESPACE::set<int> seve;
	seve.insert(1);
	seve.insert(2);
	seve.insert(3);
	std::cout << std::boolalpha;
	// Compare non equal containers
	std::cout << "salice == sbob returns " << (salice == sbob) << '\n';
	std::cout << "salice != sbob returns " << (salice != sbob) << '\n';
	std::cout << "salice <  sbob returns " << (salice < sbob) << '\n';
	std::cout << "salice <= sbob returns " << (salice <= sbob) << '\n';
	std::cout << "salice >  sbob returns " << (salice > sbob) << '\n';
	std::cout << "salice >= sbob returns " << (salice >= sbob) << '\n';
	std::cout << '\n';
	// Compare equal containers
	std::cout << "salice == seve returns " << (salice == seve) << '\n';
	std::cout << "salice != seve returns " << (salice != seve) << '\n';
	std::cout << "salice <  seve returns " << (salice < seve) << '\n';
	std::cout << "salice <= seve returns " << (salice <= seve) << '\n';
	std::cout << "salice >  seve returns " << (salice > seve) << '\n';
	std::cout << "salice >= seve returns " << (salice >= seve) << '\n';

	std::cout << YELLOW << "\nswap (set)\n" << RESET;


	NAMESPACE::set<int> salice2;
	salice2.insert(1);
	salice2.insert(2);
	salice2.insert(3);
	NAMESPACE::set<int> sbob2;
	sbob2.insert(7);
	sbob2.insert(8);
	sbob2.insert(9);
	sbob2.insert(10);
	// Print state before swap
	std::cout << "salice2:\n";
	for (NAMESPACE::set<int>::iterator it=salice2.begin(); it!=salice2.end(); ++it)
		std::cout << *it << '\n';
	std::cout << "\n" "sbob2:\n";
	for (NAMESPACE::set<int>::iterator it=sbob2.begin(); it!=sbob2.end(); ++it)
		std::cout << *it << '\n';
	std::cout << '\n';
	std::cout << "-- SWAP\n\n";
	std::swap(salice2, sbob2);
	// Print state after swap
	std::cout << "salice2:\n";
	for (NAMESPACE::set<int>::iterator it=salice2.begin(); it!=salice2.end(); ++it)
		std::cout << *it << '\n';
	std::cout << "\n" "sbob2:\n";
	for (NAMESPACE::set<int>::iterator it=sbob2.begin(); it!=sbob2.end(); ++it)
		std::cout << *it << '\n';
	std::cout << '\n';

	std::cout << YELLOW << "\nperformance set\n" << RESET;
	std::cout << "inserting and deleting lots of elements\n";
	
	// start timer
	clock_gettime(CLOCK_MONOTONIC, &timeStart);
	NAMESPACE::set<int> perfSet;
	for (size_t i = 0; i < 10000000; ++i)
			perfSet.insert(std::rand() % 1000000);
	// std::cout << "set perfSet.size() = " << perfSet.size() << std::endl;
	NAMESPACE::set<int> perfSet2(perfSet);	
	// std::cout << "set perfSet2.size() = " << perfSet2.size() << std::endl;
	NAMESPACE::set<int> perfSet3(perfSet2.begin(), perfSet2.end());
	// std::cout << "set perfSet3.size() = " << perfSet3.size() << std::endl;
	perfSet.erase(perfSet.begin(), perfSet.end());	
	// std::cout << "set perfSet.size() = " << perfSet.size() << std::endl;
	
	// end timer
	clock_gettime(CLOCK_MONOTONIC, &timeEnd);
	timePerformance = timeStart.tv_sec * 1e9;
	timePerformance = (timeEnd.tv_sec - timeStart.tv_sec) * 1e9;
	timePerformance = (timePerformance + (timeEnd.tv_nsec - timeStart.tv_nsec)) * 1e-9;
	std::cout << "set performance test: " <<  timePerformance << "sec.\n"; 

	std::cout << YELLOW << "\nleaks set\n" << RESET;

	#ifdef STD
		system("leaks std_containers | tail -3");
	#else
		system("leaks ft_containers | tail -3");
	#endif

	clock_gettime(CLOCK_MONOTONIC, &endSet);

/* ------------------------------------------------------------------------------------------------------------------ */

	std::cout << BLUE << "\n--------------------------------------------------------\n" << RESET;;
	double time_takenVector;
	time_takenVector = (endVector.tv_sec - startVector.tv_sec) * 1e9;
	time_takenVector = (time_takenVector + (endVector.tv_nsec - startVector.tv_nsec)) * 1e-9;
	#ifdef STD
	std::cout << CYAN << "Time taken by program for STD_VECTOR is " << std::fixed << std::setprecision(9) << time_takenVector;
	#else
	std::cout << CYAN << "Time taken by program for FT_VECTOR is " << std::fixed << std::setprecision(9) << time_takenVector;
	#endif
	std::cout << " sec" << std::endl << RESET;
	
	double time_takenStack;
	time_takenStack = (endStack.tv_sec - startStack.tv_sec) * 1e9;
	time_takenStack = (time_takenStack + (endStack.tv_nsec - startStack.tv_nsec)) * 1e-9;
	#ifdef STD
	std::cout << CYAN << "Time taken by program for STD_STACK  is " << std::fixed << std::setprecision(9) << time_takenStack;
	#else
	std::cout << CYAN << "Time taken by program for FT_STACK  is " << std::fixed << std::setprecision(9) << time_takenStack;
	#endif
	std::cout << " sec" << std::endl << RESET;
	
	double time_takenMap;
	time_takenMap = (endMap.tv_sec - startMap.tv_sec) * 1e9;
	time_takenMap = (time_takenMap + (endMap.tv_nsec - startMap.tv_nsec)) * 1e-9;
	#ifdef STD
	std::cout << CYAN << "Time taken by program for STD_MAP    is " << std::fixed << std::setprecision(9) << time_takenMap;
	#else
	std::cout << CYAN << "Time taken by program for FT_MAP    is " << std::fixed << std::setprecision(9) << time_takenMap;
	#endif
	std::cout << " sec" << std::endl << RESET;

	double time_takenSet;
	time_takenSet = (endSet.tv_sec - startSet.tv_sec) * 1e9;
	time_takenSet = (time_takenSet + (endSet.tv_nsec - startSet.tv_nsec)) * 1e-9;
	#ifdef STD
	std::cout << CYAN << "Time taken by program for STD_SET    is " << std::fixed << std::setprecision(9) << time_takenSet;
	#else
	std::cout << CYAN << "Time taken by program for FT_SET    is " << std::fixed << std::setprecision(9) << time_takenSet;
	#endif
	std::cout << " sec" << std::endl << RESET;

	std::cout << BLUE << "--------------------------------------------------------\n";
	#ifdef STD
	std::cout << "STD_TOTAL                              " << std::fixed << std::setprecision(9) << time_takenVector + time_takenStack + time_takenMap + time_takenSet;
	#else
	std::cout << "FT_TOTAL                               " << std::fixed << std::setprecision(9) << time_takenVector + time_takenStack + time_takenMap + time_takenSet;
	#endif
	std::cout << " sec\n" << std::endl << RESET;

	return (0);
}
#include <iostream>
#include <string>


using namespace std;


//typedef template<> __TEMPLATE_NULL ;

template <class Key>
size_t hash_(const Key x)	
{
	return x;
};	


inline size_t _hash_string(const char * s)
{
	unsigned long h=0;
	for (; *s; ++s)
		h=5*h+*s;
	return size_t(h);
}


template<>
size_t hash_(char * s) 
{
	return _hash_string(s);
}


template<>
size_t hash_(const char * s) 
{
	return _hash_string(s);
}



template<>
size_t hash_(string s) 
{
	return _hash_string(s.c_str());
}




//各个桶的大小,均为质数,总共有20个桶
static const int __num_primes=20;
static const unsigned long __num_prime_list[__num_primes]=\
{
	53,			97,			193,		389,		769,
	1543,		3079,		6151,		12289,		24593,
	49157,		98317,		196613,		393241,		786433,
	1572869,	3145739,	6291469,	12582917,	25165843
};

//以下为找出16个质数中，最接近并大于或等于n的那个质数
inline unsigned long __next_prime(unsigned long n)
{
	const unsigned long *first=__num_prime_list;
	const unsigned long *last=__num_prime_list+__num_primes;
	const unsigned long *pos=lower_bound(first,last,n);
	return  (pos==last)? *(last-1):*pos;

}
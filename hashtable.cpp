#include "hashtable.h"

int main(int argc, char const *argv[])
{
	hashtable<string, string> abb(20);
	auto it=abb.insert_unique("sda");
	auto it2=abb.insert_unique("sdfdfsdfsdfa");
	cout<<it.first.cur->val<<"   "<<it.second<<endl;
	cout<<it2.first.cur->val<<"   "<<it2.second<<endl;
	return 0;
}

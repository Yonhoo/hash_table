#include "hash_table_iterator.h"

/*
	这里暂时设置key就是val的模余
*/


template <class Key,class Value>
__hashtable_iterator<class Key,class Value>& \
__hashtable_iterator<class Key,class Value>::operator++()
{
	const node* old=cur;
	cur=cur->next;
	if(!cur){
		size_type bucket=ht->bkt_num(old->val);
		//循环到第二次的时候，因为cur，就退出了
		while(!cur && ++bucket <ht->buckets.size())
		{
			cur=ht->buckets[bucket];
		}
	}
	return *this;
};

template <class Key,class Value>
__hashtable_iterator<Key,Value>& \
__hashtable_iterator<Key,Value>::operator++(int)
{
	iterator tmp= *this;
	++*this;
	return tmp;
};


template<class Value>
__hashtable_node* new_node(const Value &obj)
{
	__hashtable_node* n=new __hashtable_node(obj,nullptr);
	return n;
};

template<class Value>
void delete_node(__hashtable_node* obj)
{
	delete obj;//此只会删除这个指针所指的地址是无效的，也就是释放这片内存，但此结构体里面的
			   //fnode并不会删除
};
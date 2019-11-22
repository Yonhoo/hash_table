#include "hash_table_iterator.h"
#include <vector>
#include <utility>
#include <typeinfo>
//这里面是按值作key的，比如string的值，则将其转化为数字的key插入
//也就是说这里的key对外面是不需要给的
//你只需要给出桶的大小，那么接下来插入值，就可以自动得出key了
//这里并没有按照map的，也就是字典的结构去做的

using namespace std;

template <class Key,class Value>
class hashtable
{
public:
	typedef Value value_type;
	typedef Key key_type;
	typedef size_t size_type;
	typedef __hashtable_iterator<Key,Value>	iterator;
	typedef __hashtable_node<value_type> node;

private:
	size_type num_elements;
	std::vector<node*> buckets;



public:
	//构造函数
	hashtable(size_t num);


public:

	
	pair<iterator,bool> insert_unique(const value_type& obj);
	
	bool delete_node(node* obj);

	size_type bucket_count() const {return buckets.size();};

	void copy_from(const hashtable& ht);

	bool exist_node(const value_type& obj) const ;

	//接受实值和buckets个数
	size_type bkt_num(const value_type& obj,size_t new_n) const 
	{		
		return hash_(obj) % new_n;
			
	}
	//重载，只接受实质
	size_type bkt_num(const value_type& obj) const 
	{	
		return hash_(obj) % buckets.size();		
	}





	~hashtable();
	
private:

	void clear();

	//判断是否需要扩建桶
	void resize(const size_type n);

	//插入元素，不允许重复
	pair<__hashtable_iterator<Key,Value>,bool> insert_unique_noresize(const value_type &obj);

	//禁用
	hashtable(const hashtable&);
};


template <class Key,class Value>
hashtable<Key,Value>::hashtable(size_t num)
{
	num_elements=num;
	//根据num的数目，给出大于num的最接近的那个质数
	const size_type n_buckets=__next_prime(num);
	buckets.reserve(n_buckets);
	//先使节点数为null
	buckets.insert(buckets.end(),n_buckets,(node*)0);
	num_elements=0;	
}



template <class Key,class Value>
pair<__hashtable_iterator<Key,Value>,bool> hashtable<Key,Value>::insert_unique(const value_type& obj)
{
	resize(num_elements+1);
	return insert_unique_noresize(obj);
}




template <class Key,class Value>
void hashtable<Key,Value>::resize(const size_type n)
{
	//表格重建与否，是根据表中元素个数来判断的
	//如果num_elements>bucket.size(),则扩桶
	const size_type old_n=buckets.size();
	if(n>old_n)
	{
		std::vector<node*> tmp(n,(node*)0);	//设立新桶
		for (size_type bucket = 0; bucket < old_n; ++bucket)
		{
			node* first=buckets[bucket];	//每个桶的第一个
			while(first)
			{
				size_type new_bucket=bkt_num(first->val,n);
				//以下四个操作颇为精巧
				buckets[bucket]=first->next;
				//将此first插入到新桶的头部
				first->next=tmp[new_bucket];
				tmp[new_bucket]=first;
				//将first改回原桶的头节点，此时是first->next,这样while才能迭代
				first=buckets[bucket];
			}
		}

		//将原桶换回到tmp这个临时变量中，这样在这个函数返回的时候，就直接把原桶全删除了
		buckets.swap(tmp);


	}
}

template <class Key,class Value>
pair<__hashtable_iterator<Key,Value>,bool> hashtable<Key,Value>::insert_unique_noresize(const value_type &obj)
{
	//首先得知道obj应该在哪个桶中
	const size_type n=bkt_num(obj);
	node* first=buckets[n];
	for (auto cur = first; cur; cur=cur->next)
	{
		//检查此值是否已插入
		if(cur->val==obj)  return pair<iterator,bool>(iterator(cur,this),false);

	}


	//说明这是个新值
	node* tmp=new_node(obj);
	tmp->next=first;
	buckets[n]=tmp;
	++num_elements;
	return pair<iterator,bool>(iterator(tmp,this),true);
}

template <class Key,class Value>
bool hashtable<Key,Value>::delete_node(__hashtable_node<Value>* obj)
{
	const size_type n=bkt_num(obj->val);
	node* first=buckets[n];
	node* last=new node(0,buckets[n]);	//dummy
	node* old=last;
	for (auto cur = first; cur->next; cur=cur->next,last=cur)
	{
		//检查此值是否已插入
		if(cur->val==obj->val)
		{
			last->next=cur->next;
			delete_n(cur);
			delete_n(old);
			return true;
		}

	}
	delete_n(old);
	return false;
}


template <class Key,class Value>
hashtable<Key,Value>::~hashtable()
{
	cout<<"析构"<<endl;
	clear();
}

template <class Key,class Value>
void hashtable< Key,Value>::clear()
{
	for(auto it:buckets)
	{
		node* cur=it;
		while(cur)
		{
			node* tmp=cur->next;
			delete_n(cur);
			cur=tmp;
		}
	}
	num_elements=0;
}

template <class Key,class Value>
void hashtable<Key,Value>::copy_from(const hashtable& ht)
{
	//删除原有的
	clear();
	buckets.clear();
	buckets.reserve(ht.buckets.size());
	buckets.insert(buckets.end(),ht.buckets.size(),(node*)0);

	for (int i = 0; i < buckets.size(); ++i)
	{
		node* cur=ht.buckets[i];
		node* copy=new_node(cur->val);
		buckets[i]=copy;

		while(cur->next)
		{
			copy->next=new_node(cur->val);
			cur=cur->next;
			copy=copy->next;
		}
	}
	num_elements=ht.num_elements;

}


template <class Key,class Value>
bool hashtable<Key,Value>::exist_node(const value_type& obj) const
{
	const size_type n=bkt_num(obj);
	node* first=buckets[n];
	for (auto cur = first; cur; cur=cur->next)
	{
		//检查此值是否已插入
		if(cur->val==obj)  return true;

	}
}
/*
	*  此哈系表：
	*		碰撞冲突：开链法
	*		映射函数：取余
	*	19/11/15
	*	@cookies_yon
*/

#include <vector>
#include "hash_convert.h"
#include <algorithm>


template<class Key,class Value>
class hashtable ;


//模板类的实现与定义必须在一个地方
using namespace std;
//开链法中每个数据节点的类型
template<class Value>
struct __hashtable_node
{
	__hashtable_node* next;
	Value val;

	__hashtable_node(Value v,__hashtable_node* n=nullptr):val(v),next(n){};
	//我觉得这里就应该是一个复制之前的节点，就不应该new
	/*__hashtable_node（const __hashtable_node &n)
	{
		//直接让指针等于指针没有意义，应该需要new一下，不然地址指的还是同一个地方
		next=n.next;
		val=n.val;
	}*/
};





template <class Key,class Value>
struct __hashtable_iterator
{

	typedef Value value_type;
	typedef Key key_type;
	typedef size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;


	typedef   hashtable<key_type,value_type> hash_table;
	typedef __hashtable_iterator<key_type,value_type>	iterator;

	//const_iterator
	typedef  __hashtable_node<Value> node;
	



	node* cur;	//迭代器目前所指节点
	hash_table* ht;	//保持容器的连接关系

	//构造函数
	__hashtable_iterator(){};
	__hashtable_iterator(node* n,hash_table* tab):cur(n),ht(tab){}; 

	//拷贝构造函数,我就要让它浅拷贝
	/*__hashtable_iterator（const __hashtable_iterator& hast)const 
	{
		//其实我觉得这里加拷贝构造函数没有意义，除非把hashtable里面的所有元素全拷贝一边
		cur=hast.cur;
		ht=hast.ht;
	}*/

	//运算符重载
	reference operator*() const {return cur->val; };
	pointer operator->()  const {return &(operator*());};
	iterator& operator++();
	iterator operator++(int);
	bool operator==(const iterator& it)	const {return cur==it.cur;};
	bool operator!=(const iterator& it)	const {return cur!=it.cur;};
};


template <class Key,class Value>
__hashtable_iterator<Key,Value>&  __hashtable_iterator<Key,Value>::operator++()
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
__hashtable_iterator<Key,Value> __hashtable_iterator<Key,Value>::operator++(int)
{
	iterator tmp= *this;
	++*this;
	return tmp;
};


template<class Value>
__hashtable_node<Value>* new_node(const Value &obj)
{
	__hashtable_node<Value>* n=new __hashtable_node<Value>(obj,nullptr);
	return n;
};

template<class Value>
void delete_n(__hashtable_node<Value>* obj)
{
	delete obj;//此只会删除这个指针所指的地址是无效的，也就是释放这片内存，但此结构体里面的
			   //fnode并不会删除
};

#include <iostream>
#include <string>

using namespace std;

/*cmake_minimum_required(VERSION 2.8.12)
project(cmake_example)

add_subdirectory(pybind11)
pybind11_add_module(cmake_example src/main.cpp)*/
pybind11_add_module(API ./src/AP.cpp
./src/Free_mat.cpp
./src/SEG.cpp
./src/Alg.cpp
./src/Morph.cpp
./src/Morph_Func.cpp 
./lib/libopencv_core.so 
./lib/libopencv_imgcodecs.so 
./lib/libopencv_highgui.so 
./lib/libopencv_imgproc.so
./lib/libITKCommon-5.0.a 
./lib/libITKIOGDCM-5.0.a 
./lib/libITKIOImageBase-5.0.a
${PYTHON_LIBRARIES}
 )
set_target_properties(API PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                         SUFFIX "${PYTHON_MODULE_EXTENSION}")
struct fnode
{
	string s;
	fnode(const char *ins):s(ins){};
	fnode(const fnode &d)
	{
		s=d.s;		//保存在栈上
	}
};

struct anode{
	int b;
	fnode* next;
	anode(int a,fnode *d):b(a),next(d){};
};


int main()
{
	fnode *k=new fnode("das");
	fnode j(*k);
	anode *v=new anode(3,k);
	cout<<v->b<<endl;
	//anode f(v);
	//k.s="d";
	delete v;
	cout<<v->next->s<<endl;
	//v.next->s="gdf";
	cout<<k->s<<endl;

	cout<<j.s<<endl;
	return  0;
}



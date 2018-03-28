#include <algorithm>
#include <cassert>
//
#include "vector.hpp"

vector_t::vector_t()
{
	elements_=nullptr;
	size_=0;
	capacity_=0;
}

vector_t::vector_t(vector_t const & other)
{
	capacity_=other.capacity();
	size_=other.size();
	elements_=new int[capacity_];
	for(int i=0; i<size_; i++)
		elements_[i]=other[i];
}

vector_t & vector_t::operator =(vector_t const & other)
{
	delete[]elements_;
	capacity_=other.capacity();
	size_=other.size();
	elements_=new int[capacity_];
	for(int i=0; i<size_; i++)
		elements_[i]=other[i];
	return *this;
}

bool vector_t::operator ==(vector_t const & other) const
{
	//равны, когда равны соотвутствующие элементы и размер size_
	if(size_==other.size())
		if(size_!=0)
		{
		   for(int i=0; i<size_; i++)
			if(elements_[i]!=other[i])
				return false;
		}
	        else return true; 
	return false;
}

vector_t::~vector_t()
{
	if(elements_!=nullptr)	delete[]elements_;
	size_=0;
	capacity_=0;
}

std::size_t vector_t::size() const
{
    return size_;
}

std::size_t vector_t::capacity() const
{
    return capacity_;
}

void vector_t::push_back(int value)
{
	if(capacity_==size_)
	{
		int*temp=new int[capacity_*2];
		for(int i=0; i<size_; i++)
			temp[i]=elements_[i];
		temp[size_]=value;
		size_++;
		capacity_*=2;
		delete[]elements_;
		elements_=new int[capacity_];
		for(int i=0; i<size_; i++)
			elements_[i]=temp[i];
		delete[]temp;
		return;
	}
	//если не равны, то capacity_>size_
	elements_[size_]=value;
	size_++;
}

void vector_t::pop_back()
{
	if (size_==0) return;//если вектор пустой, то удалять нечего
	if (size_==1) 
	{
		size_=0; 
		capacity_=1;//тк в методе push_back() при равенстве size_ и capacity_  выполняется capacity*=2, 
		            //в случае неравенства по логике capacity_>size_  
		return;
	}
	size_--;
	if (capacity_>=(4*size_)) //если памяти выделено слишком много, то логично урезать ее, чтобы не занимать место
	{
		int*temp=new int[capacity_/2];
		capacity_/=2;
		for (int i=0; i<size_; i++)
			temp[i] =elements_[i];
		delete[]elements_;
		elements_=new int[capacity_];
		for (int i=0; i<size_; i++)
			elements_[i]=temp[i];
		delete[]temp;
	}
}

int & vector_t::operator [](std::size_t index)
{
	return elements_[index];
}

int vector_t::operator [](std::size_t index) const
{
	return elements_[index];
}

bool operator !=(vector_t const & lhs, vector_t const & rhs)
{
	if(lhs.size()!=rhs.size()) return true;
	for(int i=0; i<lhs.size(); i++)
		if(lhs[i]!=rhs[i]) return true;
	return false;
}

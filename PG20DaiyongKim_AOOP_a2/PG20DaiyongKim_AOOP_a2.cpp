// PG20DaiyongKim_AOOP_a2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <string>
#include <functional>
#include "assert.h"

typedef unsigned int Hash;
std::hash<std::string> s_hash;

//
// a hash map
//
// 1. only stores pointers
// 2. can assume T *always* has the element "mHash" that contains the hash
//

template<class T, int SIZE>
class HashMap
{
public:

	HashMap()
	{
		// TODO: maybe assert if SIZE isn't actually a power of two?
		assert(isPowerOfTwo(SIZE));	
		mMask = SIZE - 1;
	}

	bool isPowerOfTwo(int i) {
		if (i <= 0) {
			return 0;
		}
		return !(i & (i - 1));
	}

	// TODO: insert data, return if succeeded
	// check data and insert data into hashmap 
	bool Insert(T& data)
	{
		if (Find(data->mHash) != nullptr) {
			return false;
		}
		else {
			InsertNoCheck(data);
			return true;
		}
	}

	void InsertNoCheck(T& data)
	{
		int index = Translate(data->mHash);
		mBuckets[index].push_back(data);
	}

	

	// TODO: find the data from the hash
	T Find(Hash hash)
	{
		int index = Translate(hash);
		std::list<T>& Buckets = mBuckets[index];

		for (T& bucket : Buckets)
		{
			//check hash 
			if (bucket->mHash == hash)
			{
				return bucket;
			}
		}
		return nullptr;
	}

	// TODO: find the data from the hash (but as const)
	const T Find(Hash hash) const
	{
		int index = Translate(hash);
		const std::list<T>& Buckets = mBuckets[index];

		for (const T& bucket : Buckets)
		{
			//check hash 
			if (bucket->mHash == hash)
			{
				return bucket;
			}
		}
		return nullptr;
	}

	

	// TODO: delete the data from the hash
	void Delete(T data)
	{
		int index = Translate(data->mHash);
		std::list<T>& Buckets = mBuckets[index];

		for (T& bucket : Buckets)
		{
			if (bucket->mHash == data->mHash)
			{
				Buckets.remove(bucket);
				break;
			}
		}
	}

private:

	// TODO: explain why this works
	// decrease a hash that will be fit in current map 
	int Translate(Hash hash) const
	{
		return (hash & mMask);
	}

private:

	Hash mMask;

	// TODO: for bonus points, you could use your own linked list class!
	std::list<T> mBuckets[SIZE];
};

//
// TEST CODE
//

class MyObject
{
public:
	Hash mHash;
};

int main()
{	
	Hash HELLO_hash = s_hash("HELLO");
	
	MyObject* myObject = new MyObject();
	myObject->mHash = HELLO_hash;

	HashMap<MyObject*, 256> myHashMap;	
	//myHashMap.InsertNoCheck(myObject);
	myHashMap.Insert(myObject);

	bool result = myHashMap.Find(HELLO_hash);
	std::cout << "result = " << result << std::endl;
	//myHashMap.Delete(myObject);

	//const HashMap<MyObject*, 256>* firstHashMap = new HashMap<MyObject*, 256>;
	//firstHashMap.Insert(myObject);

	HashMap<MyObject*, 256>* secondHashMap = &myHashMap;

	const HashMap<MyObject*, 256>* constHashMap = const_cast<HashMap<MyObject*, 256>*>(secondHashMap);
	bool constResult = constHashMap->Find(HELLO_hash);
	std::cout << "constResult = " << constResult << std::endl;

	myHashMap.Delete(myObject);

	delete myObject;
	
	return 0;
}



#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <vector>

class DataManager
{
private:
	static DataManager* _instance;
	std::vector<int> data;

	DataManager();
	~DataManager();

public:

	static DataManager* Self()
	{
		if( !_instance )
			_instance = new DataManager;
		return _instance;
	}

	static void Dtor()
	{
		if( _instance )
			delete _instance;
	}

	std::vector<int> GetData() {
		return data;
	}

	void AddData( int n )
	{
		data.push_back( n );
	}

};

#endif
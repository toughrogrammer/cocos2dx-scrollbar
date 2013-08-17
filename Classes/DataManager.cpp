
#include "DataManager.h"

DataManager* DataManager::_instance = 0;


DataManager::DataManager()
{
	int i;
	for( i=0; i<5; i++ )
	{
		data.push_back( i );
	}
}


DataManager::~DataManager()
{
	data.clear();
}
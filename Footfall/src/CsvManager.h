// * Name: CsvManager.h
// * Project: Footfall
// * Author: David Haylock
// * Creation Date: 13/02/2017
// * Copyright: (c) 2017 by Watershed Arts Trust Ltd.

#ifndef CsvManager_h
#define CsvManager_h

#include <stdio.h>
#include "ofMain.h"
#include "Configuration.h"

class CsvManager
{
	public:
		//! Setup the Csv Manager
		void setup(string saveFolder);

		//! Append a message to CSV file
		void append(string message);

	private:
		string _saveFolder;
		vector<Post_Data> loggedData;
};

#endif /* CsvManager_h */

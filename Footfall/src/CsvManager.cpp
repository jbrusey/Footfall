// * Name: CsvManager.cpp
// * Project: Footfall
// * Author: David Haylock
// * Creation Date: 13/02/2017
// * Copyright: (c) 2017 by Watershed Arts Trust Ltd.

#include "CsvManager.h"
//--------------------------------------------------------------
void CsvManager::setup(string saveFolder)
{
	cout << "Setting Up CSV Manager";
	_saveFolder = saveFolder;
	ofDirectory csvDirectory(ofToDataPath(_saveFolder));

	if (!csvDirectory.exists())
	{
		csvDirectory.createDirectory(_saveFolder);
		cout << " - Creating " << _saveFolder << " Folder" << endl;
	}
	else
	{
		cout << " - " << _saveFolder << " Folder Already Exists" << endl;
	}
}
//--------------------------------------------------------------
void CsvManager::append(string message)
{
	string filepath = _saveFolder+"/"+ofGetTimestampString("%Y-%m-%d")+".csv";
	ofFile file(filepath, ofFile::Append);

	// Create a file if doesn't exist yet
	if(!file.exists())
	{
		ofFile file(filepath, ofFile::WriteOnly);
		file.create();
	}

	file << message + "\n";
	file.close();
}

#pragma once

#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

#define IMAGEFILEWATCHER_WAIT 2.0

/*
 *	Sometimes copy a image to watch folder trigger "Add" and "Modify"
 *  so image will not complete when "Add", if u load it, will cause
 *  image load error
 */
class ImageFileWatcher
{
public:

	enum State
	{
		ADDED,
		MODIFIED,
		LOADED
	};

	struct ImageFile
	{
		ofImage* img;
		State	flag;
		string path;

		float ticker; 
	};

	void setup(ofxThreadedImageLoader* ld)
	{
		loader = ld;
	}

	void update()
	{
		float t = ofGetLastFrameTime();
		vector<ImageFile>::iterator it;
		for (it = files.begin(); it != files.end();)
		{
			if ( it->flag == ADDED)
			{
				it->ticker -= t;
				if (it->ticker < 0) 
				{
					loader->loadFromDisk(*(it->img), it->path);	
					it->flag = LOADED;
				}

				it++;
			}
			else if (it->flag == MODIFIED)
			{
				loader->loadFromDisk(*(it->img), it->path);
				it->flag = LOADED;

				it++;
			}
			else
			{
				// ofImage.allocate() sometimes not right, so use image width 
				// to check if image loaded
				if (it->img->getWidth() > 0)
				{
					loadedImage.push_back(it->img);
					it = files.erase(it);
				}
				else
					it++;
			}
		}
	}

	void addFile(string p)
	{
		files.push_back(ImageFile());
		files.back().img = new ofImage();
		files.back().flag = ADDED;
		files.back().path = p;
		files.back().ticker = IMAGEFILEWATCHER_WAIT;
	}

	void modifyFile(string p)
	{
		for (int i = 0; i < files.size(); ++i)
		{
			if (files[i].path == p)
			{
				files[i].flag = MODIFIED;
				files[i].ticker = 0;
				break;
			}
		}
		// else ? 
	}

	vector<ofImage*> getLoaded()
	{
		vector<ofImage*> cpy = loadedImage;
		loadedImage.clear();
		return cpy;
	}

	int getNumLoaded()
	{
		return loadedImage.size();
	}

	vector<ImageFile> files;
	vector<ofImage*> loadedImage;

	ofxThreadedImageLoader* loader;
};
#include "ofxPocoDirectoryWatcher.h"


ofxPocoDirectoryWatcher::ofxPocoDirectoryWatcher()
{
}


ofxPocoDirectoryWatcher::~ofxPocoDirectoryWatcher()
{
}

void ofxPocoDirectoryWatcher::watch(string path, int eventMask /*= Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL*/, int scanInterval /*= Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL*/)
{
	watcher = new Poco::DirectoryWatcher(path, eventMask, scanInterval);
	watcher->itemAdded += Poco::delegate(this, &ofxPocoDirectoryWatcher::onItemAdded);
	watcher->itemModified += Poco::delegate(this, &ofxPocoDirectoryWatcher::onItemModified);
	watcher->itemMovedFrom += Poco::delegate(this, &ofxPocoDirectoryWatcher::onItemMovedFrom);
	watcher->itemMovedTo += Poco::delegate(this, &ofxPocoDirectoryWatcher::onItemMovedTo);
	watcher->itemRemoved += Poco::delegate(this, &ofxPocoDirectoryWatcher::onItemRemoved);
}

void ofxPocoDirectoryWatcher::onItemAdded(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	ofSendMessage("Added|" + event.item.path());
}

void ofxPocoDirectoryWatcher::onItemModified(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	ofSendMessage("Modified|" + event.item.path());
}

void ofxPocoDirectoryWatcher::onItemMovedFrom(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	ofSendMessage("MovedFrom|" + event.item.path());
}

void ofxPocoDirectoryWatcher::onItemMovedTo(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	ofSendMessage("MovedTo|" + event.item.path());
}

void ofxPocoDirectoryWatcher::onItemRemoved(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	ofSendMessage("Removed|" + event.item.path());
}

void ofxPocoDirectoryWatcher::suspendEvents()
{
	watcher->suspendEvents();
}

void ofxPocoDirectoryWatcher::resumeEvents()
{
	watcher->resumeEvents();
}

bool ofxPocoDirectoryWatcher::eventsSuspended()
{
	return watcher->eventsSuspended();
}

bool ofxPocoDirectoryWatcher::supportsMoveEvents()
{
	return watcher->supportsMoveEvents();
}

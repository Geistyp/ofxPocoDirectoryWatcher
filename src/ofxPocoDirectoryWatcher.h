//  [10/17/2014 GeistYp]
#pragma once

#include "ofMain.h"

#include "Poco/Delegate.h"
#include "Poco/DirectoryWatcher.h"

/*
 *	Use Poco::DirectoryWatcher
 *  see: http://pocoproject.org/docs/Poco.DirectoryWatcher.html
 */
class ofxPocoDirectoryWatcher
{
public:
	ofxPocoDirectoryWatcher();
	~ofxPocoDirectoryWatcher();

	/*
	DirectoryEventMask
		DW_FILTER_ENABLE_ALL = 31
	Enables all event types.
		DW_FILTER_DISABLE_ALL = 0
	Disables all event types.
		DirectoryEventType

	DW_ITEM_ADDED = 1
	DW_ITEM_REMOVED = 2
	DW_ITEM_MODIFIED = 4
	DW_ITEM_MOVED_FROM = 8
	DW_ITEM_MOVED_TO = 16
	*/
	void watch(string path, int eventMask = Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL, int scanInterval = Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL);

	/// Suspends sending of events. Can be called multiple times, but every
	/// call to suspendEvent() must be matched by a call to resumeEvents().
	void suspendEvents();

	/// Resumes events, after they have been suspended with a call to suspendEvents().
	void resumeEvents();

	/// Returns true iff events are suspended.
	bool eventsSuspended();

	/// Returns true iff the platform supports DW_ITEM_MOVED_FROM/itemMovedFrom and
	/// DW_ITEM_MOVED_TO/itemMovedTo events.
	bool supportsMoveEvents();

	void onItemAdded(const Poco::DirectoryWatcher::DirectoryEvent& event);			// Fired when a file or directory has been created or added to the directory.
	void onItemModified(const Poco::DirectoryWatcher::DirectoryEvent& event);		// Fired when a file or directory has been modified.
	void onItemMovedFrom(const Poco::DirectoryWatcher::DirectoryEvent& event);		// Fired when a file or directory has been renamed. This event delivers the old name.
	void onItemMovedTo(const Poco::DirectoryWatcher::DirectoryEvent& event);		// Fired when a file or directory has been moved. This event delivers the new name.
	void onItemRemoved(const Poco::DirectoryWatcher::DirectoryEvent& event);		// Fired when a file or directory has been removed from the directory.

	Poco::DirectoryWatcher* watcher;
};


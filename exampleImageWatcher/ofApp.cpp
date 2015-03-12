#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	string share_data_path;
	share_data_path = ofFilePath::getAbsolutePath("image/");
	watcher.watch(share_data_path);

	imageFileWatcher.setup(&loader);
}

//--------------------------------------------------------------
void ofApp::update(){

	imageFileWatcher.update();
	int num = imageFileWatcher.getNumLoaded();
	if (num >= 0)
	{
		vector<ofImage*> loadedImages = imageFileWatcher.getLoaded();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

	vector<string> msgs = ofSplitString(msg.message, "|");

	if (msgs.size() > 0)
	{
		if (msgs[0] == "Added")
		{
			imageFileWatcher.addFile(msgs[1]);
		}
		else if (msgs[0] == "Modified")
		{
			imageFileWatcher.modifyFile(msgs[1]);
		}
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

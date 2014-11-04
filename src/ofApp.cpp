#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	camWidth  = 400;
	camHeight = 300;

	ofSetLogLevel(OF_LOG_VERBOSE);
	// original from cam
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth, camHeight);

	videoMirror = new unsigned char[camWidth* camHeight*3];
	// texture to be used
	miniTexture.allocate(camWidth, camHeight, GL_RGB);
	num_of_sounds = sizeof(sounds) / sizeof(*sounds);

	for(int i = 0; i < num_of_sounds; i++){
		sounds[i].loadSound("sounds/plop0" + ofToString(i+1) + ".mp3");
		sounds[i].setMultiPlay(true);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
	pixels = vidGrabber.getPixels();

	/*
	ofSetColor(pRef.getColor(mouseX, mouseY));
	cout << pRef.getColor(mouseX, mouseY).getHue() << endl;
	*/

	/*
	int width  = miniTexture.getWidth();
	int height= miniTexture.getHeight();
	ofLog(OF_LOG_VERBOSE, "width set to " + ofToString(width));
	ofLog(OF_LOG_VERBOSE, "height set to " + ofToString(height));
	*/

	for(int i = 0; i < camHeight; i++) {
		for(int j = 0; j < camWidth*3; j+=3) {
			// pixel num
			int r = (i*camWidth*3) + j;
			int g = (i*camWidth*3) + j+1;
			int b = (i*camWidth*3) + j+2;
			// swap pixels 
			int mr = (i*camWidth*3)+1 * (camWidth*3 - j-3) ;
			int mg = (i*camWidth*3)+1 * (camWidth*3 - j-2) ;
			int mb = (i*camWidth*3)+1 * (camWidth*3 - j-1) ;

			videoMirror[r] = pixels[mr];
			videoMirror[g] = pixels[mg];
			videoMirror[b] = pixels[mb]; 
		}
	}

	miniTexture.loadData(videoMirror, camWidth, camHeight, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::draw(){
//	ofCircle(85, 350, 85);
	ofSetColor(255);
	vidGrabber.draw(0,0);
	//normalMirror();
	int avePixelSize = 30;
	for(int i = 0; i < camWidth/avePixelSize; i++) {
		for(int j = 0; j < camHeight/avePixelSize; j++) {
			int aveHue = getAverageHue(i*avePixelSize, j*avePixelSize, i*avePixelSize+avePixelSize, j*avePixelSize+avePixelSize);
			ofColor c = ofColor::fromHsb(aveHue, 200, 200);
			ofSetColor(c);
//			ofCircle(avePixelSize/2 + i*avePixelSize, camHeight + avePixelSize/2 + j*avePixelSize,avePixelSize/3);
			ofRect(camWidth + i*avePixelSize, j*avePixelSize, avePixelSize, avePixelSize);
		}	
	}

//miniTexture.draw(0,camHeight,camWidth, camHeight);
}

int ofApp::getAverageHue(int x1, int y1, int x2, int y2){
	ofPixelsRef pRef = vidGrabber.getPixelsRef();
	int numXpixels = x2 - x1;
	int numYpixels = y2 - y1;
	int totalPixels = numXpixels * numYpixels;
	int sum, average;
	sum = 0;

	for(int i = x1; i<=x2; i++){
		for(int j = y1; j<=y2; j++){
			sum += pRef.getColor(i,j).getHue();
		}	
	}
	average = sum/totalPixels;
	return average;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
	case 65: 
		sounds[0].play();
		break;
	case 66:
		sounds[1].play();
		break;
	case 67:
		sounds[2].play();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//	int pix_num = y*camWidth*3 + x;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

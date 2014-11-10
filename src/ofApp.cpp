#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	camWidth  = 800;
	camHeight = 600;

	musicRegionX1 = 0;
	musicRegionY1 = 0;
	musicRegionX2 = 20;
	musicRegionY2 = 20;

	musicModeRegionX1 = 0;
	musicModeRegionY1 = 0;
	musicModeRegionX2 = 1;
	musicModeRegionY2 = 1;

	prevMusicType = -1;
	musicType = 0;

	inputMode = 0;

	hueDegree = 11;
	satDegree = 1;
	saturationThreshold = 75;

	myfont.loadFont("fonts/lato-bold.ttf", 12);

	ofSetLogLevel(OF_LOG_VERBOSE);
	// original from cam
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth, camHeight);

	videoMirror = new unsigned char[camWidth* camHeight*3];

	num_of_modes = 6;
	soundsPerMode = 7;

	for(int mode = 0; mode < num_of_modes; mode++){
		for(int sound = 0; sound < soundsPerMode; sound++){
			sounds[mode][sound].loadSound("sounds/" + ofToString(mode) + "/" + ofToString(sound) + ".mp3");
			sounds[mode][sound].setMultiPlay(true);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
	pixels = vidGrabber.getPixels();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255);
	vidGrabber.draw(0,0);

	//debugColors();
	/*
	int aveSat = getAverageHue(mouseX, mouseY, mouseX+15, mouseY+15);
	ofSetColor(0);
	ofRect(mouseX, mouseY, 15, 15);
	myfont.drawString(ofToString(aveSat), mouseX, mouseY);

*/

	setMusicModeRegion(musicModeRegionX1, musicModeRegionY1, musicModeRegionX2, musicModeRegionY2);
	horiZone(musicModeRegionX2, musicModeRegionY1, musicModeRegionX2 + 350, musicModeRegionY2, 7);
	//setMusicRegion(musicRegionX1, musicRegionY1, musicRegionX2, musicRegionY2, 20, 1);
	//setMusicRegion(mouseX, mouseY, mouseX + musicRegionX2, mouseY + musicRegionY2, 1, 1);
//	setMusicRegion(musicModeRegionX1 + musicModeRegionX2, musicModeRegionY1,musicModeRegionX1 + musicModeRegionX2 + 300, musicModeRegionY2, 20, 2);
	ofSleepMillis(500);
}

void ofApp::setMusicModeRegion(int x1, int y1, int x2, int y2){
	int hue  = getAverageHue(x1, y1, x2, y2);

	switch(hue){

		//red
		case 0:
		case 11:
		musicType = 1;
		break;

		//orange
		case 22:
		musicType = 2;
		break;

		//yellow
		case 33:
		case 44:
		case 55:
		case 66:
		musicType = 3;
		break;

		//mix of light blue and light green
		case 110:
		case 121:
		musicType = 4;
		break;


		//BLUE
		case 132:
		case 143:
		case 154:
		case 165:
		case 176:
		musicType = 5;
		break;


		default:
		musicType = 0;

	}

	if(musicType != prevMusicType){
		cout << "Changed music mode to " << musicType << " with hue " << hue << endl;
		prevMusicType = musicType;
	}

	myfont.drawString(ofToString(hue), x1, y1);
	ofColor c = ofColor::fromHsb(hue, 255, 255);
	ofSetColor(c);
	ofRect(x1, y1, x2-x1, y2-y1);
}


void  ofApp::horiZone(int x1, int y1, int x2, int y2, int steps){
	int numXpixels = x2 - x1;
	//	int numYpixels = y2 - y1;
	int stepJump = numXpixels/steps;
	//int soundID = 0;
	int colorID = 6;

	for(int i = 0; i < steps; i++){
		int sat = getAverageSat(x1+(i*stepJump), y1, x1+((i+1)*stepJump), y2);
		if(sat > saturationThreshold) {
			int hue = getAverageHue(x1+(i*stepJump), y1, x1+((i+1)*stepJump), y2);
			ofColor c = ofColor::fromHsb(hue, 255, 255);
			ofSetColor(c);

			myfont.drawString(ofToString(hue), x1+(i*stepJump), y1 - 20);

			switch(hue){

				//red
				case 0:
				colorID = 0;
				break;

				//orange
				case 11:
				case 22:
				colorID = 1;
				break;

				//yellow
				case 33:
				colorID = 2;
				break;

				//light green
				case 44:
				case 55:
				colorID = 3;
				break;

				//dark green
				case 88:
				case 99:
				case 110:
				colorID = 4;
				break;

				//blue
				case 132:
				case 143:
				case 154:
				colorID = 5;
				break;

				//default
				default:
				colorID = 6;
				break;

			}
			
			sounds[musicType][colorID].setSpeed(((float)i/(float)steps) * 2);
			sounds[musicType][colorID].play();
			
		} else 
		{
			ofSetColor(0);
		}
		ofRect(x1+(i*stepJump), y1, stepJump, y2-y1);
	}
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	cout << saturationThreshold << endl;
	switch(key){
		/*
		case 65: 
		sounds[0].play();
		break;
		case 66:
		sounds[1].play();
		break;
		case 67:
		sounds[2].setSpeed(0.1);
		sounds[2].play();
		break;
		case 68:
		sounds[2].setSpeed(2.0);
		sounds[2].play();
		break;
		*/
		case 73:
		inputMode = 11;
		break;
		case 74:
		inputMode = 21;
		break;

		case 75:
		saturationThreshold++;
		break;
		
		case 76:
		saturationThreshold--;
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
	switch(inputMode){
		case 11:
		musicModeRegionX1 = x;
		musicModeRegionY1 = y;
		musicModeRegionX2 = x+1;
		musicModeRegionY2 = y+1;
		inputMode = 12;
		break;

		case 12:
		musicModeRegionX2 = x;
		musicModeRegionY2 = y;
		inputMode = 0;
		break;

		case 21:
		musicRegionX1 = x;
		musicRegionY1 = y;
		musicRegionX2 = x+10;
		musicRegionY2 = y+10;
		inputMode = 22;
		break;

		case 22:
		musicRegionX2 = x;
		musicRegionY2 = y;
		inputMode = 0;
		break;

		case 0:
		break;
	}
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


int ofApp::getAverageHue(int x1, int y1, int x2, int y2){
	ofPixelsRef pRef = vidGrabber.getPixelsRef();
	int numXpixels = x2 - x1;
	int numYpixels = y2 - y1;
	int totalPixels = numXpixels * numYpixels;
	int sum, average;
	sum = 0;

	for(int i = x1; i<=x2; i++){
		for(int j = y1; j<=y2; j++){
			int hue = 255 + pRef.getColor(i,j).getHue();
			sum += hue;
			sum -= 255;
		}	
	}
	average = sum/totalPixels;
	average = (average/hueDegree) * hueDegree;
	return average;
}
int ofApp::getAverageSat(int x1, int y1, int x2, int y2){
	ofPixelsRef pRef = vidGrabber.getPixelsRef();
	int numXpixels = x2 - x1;
	int numYpixels = y2 - y1;
	int totalPixels = numXpixels * numYpixels;
	int sum, average;
	sum = 0;

	for(int i = x1; i<=x2; i++){
		for(int j = y1; j<=y2; j++){
			sum += pRef.getColor(i,j).getSaturation();
		}	
	}
	average = sum/totalPixels;
	average = (average/satDegree) * satDegree; 
	return average;
}

/*
void ofApp::setMusicRegion(int x1, int y1, int x2, int y2, int numHori, int numVert){
	ofSetColor(255);
	ofRect(x1, y2, x2 - x1, y2 - y1);
	int horiJump = (x2 - x1)/numHori;
	int vertJump = (y2 - y1)/numVert;
	int prevHue = -1;
	float volume = 0.25;
	int soundID = 0;
	for(int i = x1; i < x2; i += horiJump){
		for(int j = y1; j < y2; j += vertJump){
			int sat = getAverageSat(i*horiJump, j*vertJump, (i+1)*horiJump, (j+1)*vertJump);
			if(sat > saturationThreshold){
				int hue = getAverageHue(i*horiJump, j*vertJump, (i+1)*horiJump, (j+1)*vertJump);
				cout << hue << endl;
				if(hue == prevHue){
					volume += 0.05;
				}
				else {

					switch(hue){

						case 0:
						soundID = musicType*num_of_modes + 0;
						cout << soundID << endl;
						break;

						default:
						soundID = -1;
						break;

					}

					sounds[soundID].setVolume(volume);
					//needs to be changed
					sounds[soundID].setSpeed((float)((i-x1)/(x2-x1)));
					sounds[soundID].play();

					volume = 0.5;
				}

				myfont.drawString(ofToString(soundID), 100,100);	
				prevHue = hue;
			}
		}	
	} 

}
*/

void ofApp::debugColors(){
	int avePixelSize = 15;

	for(int i = 0; i < camWidth/avePixelSize; i++) {
		for(int j = 0; j < camHeight/avePixelSize; j++) {
			int aveSat = getAverageSat(i*avePixelSize, j*avePixelSize, i*avePixelSize+avePixelSize, j*avePixelSize+avePixelSize);
			if(aveSat > saturationThreshold){
				int aveHue = getAverageHue(i*avePixelSize, j*avePixelSize, i*avePixelSize+avePixelSize, j*avePixelSize+avePixelSize);
				ofColor c = ofColor::fromHsb(aveHue, 255, 255);
				ofSetColor(c);
				//		myfont.drawString(ofToString(aveHue), i*avePixelSize, j*avePixelSize);
			} else {
				ofSetColor(255);
			}
			ofRect(i*avePixelSize, j*avePixelSize, avePixelSize, avePixelSize);		
		}	
	}

}



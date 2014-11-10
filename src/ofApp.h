#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		int saturationThreshold;
		int hueDegree, satDegree;
		
		void setup();
		void update();
		void draw();

		void debugColors();

		ofTrueTypeFont myfont; // for debugging

		void normalMirror();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		int getAverageHue(int x1, int y1, int x2, int y2);
		int getAverageSat(int x1, int y1, int x2, int y2);

		void setMusicRegion(int x1, int y1, int x2, int y2, int numHori, int numVert);
		void setMusicModeRegion(int x1, int y1, int x2, int y2);
		int musicModeRegionX1, musicModeRegionY1, musicModeRegionX2, musicModeRegionY2;
		int musicRegionX1, musicRegionY1, musicRegionX2, musicRegionY2;
		int musicType, prevMusicType;

		int inputMode;

		int camWidth, camHeight;
		ofVideoGrabber vidGrabber;
		unsigned char * pixels;

		// for mirrored object
		ofTexture miniTexture;
		unsigned char * videoMirror;

		// sound stuff
		int soundsPerMode, num_of_modes;

		ofSoundPlayer sounds[6][7];
		void horiZone(int x1, int y1, int x2, int y2, int steps);

};

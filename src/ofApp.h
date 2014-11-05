#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

		int camWidth, camHeight;
		ofVideoGrabber vidGrabber;
		unsigned char * pixels;

		// for mirrored object
		ofTexture miniTexture;
		unsigned char * videoMirror;

		// sound stuff
		int num_of_sounds;

		ofSoundPlayer sounds[3];
		void horiZone(int x1, int y1, int x2, int y2, int steps);

};

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "GLFW/glfw3.h"
#include "threadedObject.h"
#include "SiftGPU/SiftGPU.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void setW(int www);

		ofVideoPlayer _video;
		ofVideoGrabber _grvideo;
		ofEasyCam _cam;
		ofImage _im;
		ofImage _image_draw;
		ofImage _image_now;
		ofImage _image_before;
			
		vector<cv::KeyPoint> keypoints_now;
		vector<cv::KeyPoint> keypoints_before;
		clock_t t_before, t_now;
		int _w,_h;
		// 渲染进程
		GLFWwindow* draw_window;
		// siftGPU进程
		GLFWwindow* sift_window;

		SiftGPU mSift;
		SiftMatchGPU mSiftMatcher;
};

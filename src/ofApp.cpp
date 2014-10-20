#include "ofApp.h"
#include "glut.h"

//--------------------------------------------------------------
void ofApp::setup(){
	draw_window = glfwGetCurrentContext();
	setW(700);
	if (_video.loadMovie("MOV_0704.mp4"))
	{
		cout<<"Loaded movie"<<endl;
		_video.setLoopState(OF_LOOP_NONE);
		_video.play();
		_image_now.setFromPixels(_video.getPixelsRef());
		_image_before = _image_now;
		_image_draw = _image_now;
		_im = _image_now;
	}
	t_now = clock();
	t_before = t_now;

	sift_window = glfwCreateWindow(200,200,"SiftGPU", NULL, NULL);
	glfwHideWindow(sift_window);
	char * argv[] = {"-fo", "0",  "-v", "1"/*, "-t", "0.03"*/};//
	int argc = sizeof(argv)/sizeof(char*);
	mSift.ParseParam(argc, argv);
	glfwMakeContextCurrent(sift_window);
	mSift.VerifyContextGL();
	mSiftMatcher.VerifyContextGL();
	glfwMakeContextCurrent(draw_window);
	cv::KeyPoint aaa();

}

//--------------------------------------------------------------
void ofApp::update(){
	
	_video.update();
	if (_video.isPlaying())
	{
// 		if (_video.isFrameNew())
// 		{
// 			//_im.setFromPixels(_video.getPixelsRef());
// 		}
		t_now = clock();
		if (t_now - t_before >= 5000)
		{
			clock_t _start = clock();
			_video.setPaused(true);

			_image_before = _image_now;
			_image_now.setFromPixels(_video.getPixelsRef());
			//_image_draw = _image_now;

			glfwMakeContextCurrent(sift_window);
			vector<float > descriptors1(1), descriptors2(1);
			vector<SiftGPU::SiftKeypoint> keys1(1), keys2(1);    
			int num1 = 0, num2 = 0;

			if(mSift.RunSIFT(1920, 1080, _image_before.getPixels(), GL_RGB, GL_UNSIGNED_BYTE))
			{
				num1 = mSift.GetFeatureNum();
				keys1.resize(num1);    descriptors1.resize(128*num1);
				mSift.GetFeatureVector(&keys1[0], &descriptors1[0]);
			}

			if(mSift.RunSIFT(1920, 1080, _image_now.getPixels(), GL_RGB, GL_UNSIGNED_BYTE))
			{
				num2 = mSift.GetFeatureNum();
				keys2.resize(num2);    descriptors2.resize(128*num2);
				mSift.GetFeatureVector(&keys2[0], &descriptors2[0]);
			}

			mSiftMatcher.SetDescriptors(0, num1, &descriptors1[0]); //image 1
			mSiftMatcher.SetDescriptors(1, num2, &descriptors2[0]); //image 2

			//match and get result.    
			int (*match_buf)[2] = new int[num1][2];
			//use the default thresholds. Check the declaration in SiftGPU.h
			int num_match = mSiftMatcher.GetSiftMatch(num1, match_buf);
			cout << num_match << " sift matches were found;\n";
			clock_t _end = clock();
			cout << _end - _start << "ms;\n";
			glfwMakeContextCurrent(draw_window);
			t_before = clock();
			
			_video.setPaused(false);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	glColor3f(1,1,1);
	_video.draw(0,0,_w,_h);

	if (_image_before.isAllocated())
	{
		_image_before.draw(0,_h,_w,_h);
	}
	if (_image_now.isAllocated())
	{
		_image_now.draw(_w,0,_w,_h);
	}

	glColor3f(0,1,1);
	ofDrawBitmapString("frame: " + ofToString(_video.getCurrentFrame()) + "/"+ofToString(_video.getTotalNumFrames()),20,20);
	ofDrawBitmapString("time: " + ofToString(_video.getPosition()*_video.getDuration(),2) + "s/"+ofToString(_video.getDuration(),2) + "s",20,40);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 20, 60);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
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

void ofApp::setW(int www)
{
	_w = www;
	_h = www * 9 / 16;
}

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
		_image_draw_now = _image_now;
		_image_draw_before = _image_now;
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

	*F[0] = NULL;*H[0] = NULL;

}

vector<cv::KeyPoint> transKeyPointsFromGPUtoCV(vector<SiftGPU::SiftKeypoint>* _input)
{
	vector<cv::KeyPoint> _output;
	for (int i = 0; i < _input->size(); i++)
	{
		cv::KeyPoint _kp((*_input)[i].x, (*_input)[i].y, (*_input)[i].s, (*_input)[i].o);
		_output.push_back(_kp);
	}
	return _output;
}

//--------------------------------------------------------------
void ofApp::update(){

	_video.update();
	if (_video.isPlaying())
	{ 		
		if (_video.isFrameNew())
		{
			t_now = clock();
<<<<<<< HEAD
			if (t_now - t_before >= 500)
=======
			if (t_now - t_before >= 5000)
>>>>>>> parent of 8dfa1a5... 获取F-M和H-M矩阵
			{
				clock_t _startall = clock();
				_video.setPaused(true);

				_image_before = _image_now;
				_image_draw_before = _image_before;
				_image_now.setFromPixels(_video.getPixelsRef());
				_image_draw_now = _image_now;
				//_image_draw = _image_now;

				glfwMakeContextCurrent(sift_window);
				vector<float > descriptors1(1), descriptors2(1);
				vector<SiftGPU::SiftKeypoint> keys1(1), keys2(1);
				vector<cv::KeyPoint> cvkeypoint1,cvkeypoint2;
				int num1 = 0, num2 = 0;

				if(mSift.RunSIFT(1920, 1080, _image_before.getPixels(), GL_RGB, GL_UNSIGNED_BYTE))
				{
					num1 = mSift.GetFeatureNum();
					keys1.resize(num1);    descriptors1.resize(128*num1);
					mSift.GetFeatureVector(&keys1[0], &descriptors1[0]);
					//cvkeypoint1 = transKeyPointsFromGPUtoCV(&keys1);
				}

				if(mSift.RunSIFT(1920, 1080, _image_now.getPixels(), GL_RGB, GL_UNSIGNED_BYTE))
				{
					num2 = mSift.GetFeatureNum();
					keys2.resize(num2);    descriptors2.resize(128*num2);
					mSift.GetFeatureVector(&keys2[0], &descriptors2[0]);
					//cvkeypoint2 = transKeyPointsFromGPUtoCV(&keys2);
				}

				clock_t _startmatch = clock();

				mSiftMatcher.SetDescriptors(0, num1, &descriptors1[0]); //image 1
				mSiftMatcher.SetDescriptors(1, num2, &descriptors2[0]); //image 2
 
				int (*match_buf)[2] = new int[num1][2];
				int num_match = 0;

				if (*F[0] != NULL && *H[0] != NULL)
				{
					num_match = mSiftMatcher.GetGuidedSiftMatch(num1, match_buf, H,NULL);
				}
				else
				{
					num_match = mSiftMatcher.GetSiftMatch(num1, match_buf);
				}
				

				clock_t _endmatch = clock();

				cout << num_match << " sift matches were found in " << _endmatch - _startmatch << "ms;\n";		
				cout << "Cost " << _endmatch - _startall << "ms " << "in sift and match.\n\n";

				for(int i  = 0; i < num_match; ++i)
				{
					SiftGPU::SiftKeypoint & key1 = keys1[match_buf[i][0]];
					cvkeypoint1.push_back(cv::KeyPoint(key1.x, key1.y, key1.s, key1.o));
					SiftGPU::SiftKeypoint & key2 = keys2[match_buf[i][1]];
					cvkeypoint2.push_back(cv::KeyPoint(key2.x, key2.y, key2.s, key2.o));
				}

<<<<<<< HEAD
				int num_fm = cvFindFundamentalMat(points1,points2,fundMatr,CV_RANSAC);
				int num_hm = cvFindHomography(points1, points2, homoMatr);
				cout<<"F-M:\n";

				for (int i = 0; i < 9; i = i+3)
				{
					cout<<fundMatr->data.fl[i]
					<<" , "<<fundMatr->data.fl[i+1]
					<<" , "<<fundMatr->data.fl[i+2]<<endl;
					if (*H[0] == NULL)
					{
						F[i/3][0] = fundMatr->data.fl[i];
						F[i/3][1] = fundMatr->data.fl[i+1];
						F[i/3][2] = fundMatr->data.fl[i+2];
					}
				}
				cout<<"H-M:\n";
				for (int i = 0; i < 9; i = i+3)
				{
					cout<<homoMatr->data.fl[i]
					<<" , "<<homoMatr->data.fl[i+1]
					<<" , "<<homoMatr->data.fl[i+2]<<endl;
					if (*H[0] == NULL)
					{
						H[i/3][0] = homoMatr->data.fl[i];
						H[i/3][1] = homoMatr->data.fl[i+1];
						H[i/3][2] = homoMatr->data.fl[i+2];
					}
				}

				cvReleaseMat(&points1);
				cvReleaseMat(&points2);
				cvReleaseMat(&fundMatr);
				cvReleaseMat(&homoMatr);

=======
>>>>>>> parent of 8dfa1a5... 获取F-M和H-M矩阵
				cv::drawKeypoints((cv::Mat)_image_before.getCvImage(), cvkeypoint1, (cv::Mat)_image_draw_before.getCvImage());
				cv::drawKeypoints((cv::Mat)_image_now.getCvImage(), cvkeypoint2, (cv::Mat)_image_draw_now.getCvImage());

				glfwMakeContextCurrent(draw_window);
				t_before = clock();

				_video.setPaused(false);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	glColor3f(1, 1, 1);
	_video.draw(0, 0, _w, _h);

	if (_image_draw_now.isAllocated())
	{
		_image_draw_now.draw(0, _h, _w, _h);
		glColor3f(0, 1, 1);
		ofDrawBitmapString("now", 20, _h + 20);
	}
	if (_image_draw_before.isAllocated())
	{
		glColor3f(1, 1, 1);
		_image_draw_before.draw(_w,0,_w,_h);
		glColor3f(0, 1, 1);
		ofDrawBitmapString("before", _w + 20, 20);
	}

	glColor3f(0,1,1);
	ofDrawBitmapString("frame: " + ofToString(_video.getCurrentFrame()) + "/"+ofToString(_video.getTotalNumFrames()),20,20);
	ofDrawBitmapString("time: " + ofToString(_video.getPosition()*_video.getDuration(),2) + "s/"+ofToString(_video.getDuration(),2) + "s",20,40);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 20, 60);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's')
	{
		_video.setPaused(!_video.isPaused());
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

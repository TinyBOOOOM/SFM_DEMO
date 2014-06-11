#include "ofMain.h"
#include "ofApp.h"
#include "SiftGPU/SiftGPU.h"

//========================================================================
int main( ){
// 	SiftGPU mSift;
// 	int support = mSift.CreateContextGL();
// 	if (support != SiftGPU::SIFTGPU_FULL_SUPPORTED)
// 	{
// 		cout<<"Not supporte SiftGPU, please check your device.";
// 		return 1;
// 	}
// 	char * argv[] = {"-fo", "-1"};
// 	int argc = sizeof(argv)/sizeof(char*);
// 	mSift.ParseParam(2, argv);
// 	bool issift = mSift.RunSIFT("F:/Others/SiftGPU-V400/SiftGPU/data/800-1.jpg");
// 	int num = mSift.GetFeatureNum();
// 	if (num)
// 	{
// 		vector<float> descriptors(128*num);
// 		vector<SiftGPU::SiftKeypoint> keys(num);
// 		mSift.GetFeatureVector(&keys[0], &descriptors[0]);
	ofSetupOpenGL(1600,900,OF_WINDOW);			// <-------- setup the GL context
	ofSetWindowTitle("Main Loop1");
	//glutGetWindow();
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

	return 1;
}

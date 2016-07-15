# process-img

Build using cmake(Recommended):
	cmake .
	make
	Run generated executable 

Direct compile(Only if you have OpenCV installed):
	g++ main.cpp `pkg-config opencv --cflags --libs`
	Run generated executable
// drawtoscreen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

using namespace std;
using namespace cv;

Ptr<Tracker> tracker;

void open_camera()
{
    VideoCapture videoCapture;
    Mat videoFrame;
    //open camera
    videoCapture.open(0);
    namedWindow("Camera", WINDOW_AUTOSIZE);
    //check open camera open sucessed or failed
    if (!videoCapture.isOpened()) {
        cout << "Can't open camera" << endl;
    }
    else {
        vector< Point > node;
        tracker = TrackerCSRT::create();
        videoCapture.read(videoFrame);
        Rect trackingBox = selectROI(videoFrame, false);
        tracker->init(videoFrame, trackingBox);
        while (true) {
            //read video frame from camera and show in windows
            videoCapture.read(videoFrame);         
            if (tracker->update(videoFrame, trackingBox))
            {
                rectangle(videoFrame, trackingBox, Scalar(0, 255, 0), 2, 8);
                circle(videoFrame, Point(trackingBox.x + (trackingBox.width / 2.0), trackingBox.y + (trackingBox.height / 2.0)), 4, Scalar(0, 0, 255), -1);
                node.push_back(Point(trackingBox.x + (trackingBox.width / 2.0), trackingBox.y + (trackingBox.height / 2.0)));
            } 
            for (size_t i = 1; i < node.size(); i++)
            {
                line(videoFrame, node[i - 1], node[i], Scalar(0, 0, 255), 4);
            }
            imshow("Camera", videoFrame);
            if (waitKey(30) >= 0) break;
        }
    }
}

int main()
{
    std::cout << "Draw to your screen!\n";
    open_camera();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

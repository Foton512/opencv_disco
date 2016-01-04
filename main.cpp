#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;


void processVideo() {
    VideoCapture capture(0);
    Mat cameraImage, blurredImage, blocksImage, contoursImage;
    Ptr<BackgroundSubtractor> backgroundSubstractor = createBackgroundSubtractorMOG2(20);
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));
    RNG random(1);
    while(true) {
        capture.read(cameraImage);

        cvtColor(cameraImage, blurredImage, CV_BGR2GRAY);
        GaussianBlur(blurredImage, blurredImage, Size(21, 21), 0, 0);

        backgroundSubstractor->apply(blurredImage, blocksImage);
        threshold(blocksImage, blocksImage, 25, 255, THRESH_BINARY);
        dilate(blocksImage, blocksImage, dilateElement, Point(-1, -1), 2);

        contoursImage = blocksImage.clone();

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(contoursImage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

        contoursImage = Mat::zeros(blocksImage.size(), CV_8UC3);
        for(int i = 0; i < contours.size(); ++i) {
            Scalar color = Scalar(random.uniform(0, 255), random.uniform(0,255), random.uniform(0,255));
            drawContours(contoursImage, contours, i, color, 2, 8, hierarchy, 0);
        }

        imshow("Disco", contoursImage);

        int c = waitKey(30);
        if( c == 27 || c == 'q' || c == 'Q' )
            break;
    }

    capture.release();
}

int main(int argc, char* argv[])  {
    namedWindow("Disco");

    processVideo();
    destroyAllWindows();

    return EXIT_SUCCESS;
}

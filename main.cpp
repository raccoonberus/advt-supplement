#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat graphicsProcessing(int argc, char **argv, Mat frame);

vector<vector<Point>> contoursFiltering(vector<vector<Point> > contours, vector<Vec4i> hierarchy);

int main(int argc, char **argv) {
    auto cap = VideoCapture(argv[1]);
    Mat src_gray;
    long long frameCounter = 0;
    RNG rng(12345);


    for (;;) {
        Mat frame;
        cap >> frame;

        auto canny_output = graphicsProcessing(argc, argv, frame);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

        contours = contoursFiltering(contours, hierarchy);

        for (size_t i = 0; i < contours.size(); i++) {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            drawContours(drawing, contours, (int) i, color, 2, 8, hierarchy, 0, Point());
        }

        if (frameCounter % 10 == 0) {
            imwrite(format("/home/goforbroke/advt/%d.jpg", frameCounter), drawing);
        }

        if (frameCounter > 1000) break;

        frameCounter++;
    }
    return 0;
}

Mat graphicsProcessing(int argc, char **argv, Mat frame) {
    int thresh = argc >= 3 ? atoi(argv[2]) : 120;

    cvtColor(frame, frame, COLOR_BGR2GRAY);
    GaussianBlur(frame, frame, Size(5, 5), 0, 0);
    Mat canny_output;
    Canny(frame, canny_output, thresh, thresh * 2, 3);
    return canny_output;
}

vector<vector<Point>> contoursFiltering(vector<vector<Point>> contours, vector<Vec4i> hierarchy) {
    vector<vector<Point>> result;
    for (size_t i = 0; i < contours.size(); i++) {
//            double epsilon = 0.005 * arcLength(contours[i], true);
//            approxPolyDP(contours[i], contours[i], epsilon, true);
//            convexHull(contours[i], contours[i]);
        auto rect = minAreaRect(Mat(contours[i]));
        Point2f vertices[4];
        rect.points(vertices);
//        for (int i = 0; i < 4; ++i)
//            cv::line(drawing, vertices[i], vertices[(i + 1) % 4], cv::Scalar(184, 0, 255), 1, CV_AA);
//            Mat out;
//            boxPoints(rect, out);
//            drawContours(drawing, {out}, 0, Scalar(255, 0, 184), 2, 8, hierarchy, 0, Point());

//            if (contours[i].size() != 4)
//                continue;
//        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//        drawContours(drawing, contours, (int) i, color, 2, 8, hierarchy, 0, Point());

        // TODO: filter only big rects

        result.push_back(contours[i]);
    }
    return result;
}
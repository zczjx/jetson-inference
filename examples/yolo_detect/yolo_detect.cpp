#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <stdio.h>
#include <jetson-utils/commandLine.h>


#ifdef HEADLESS
	#define IS_HEADLESS() "headless"	// run without display
#else
	#define IS_HEADLESS() (const char*)NULL
#endif

static cv::Scalar cv_colors[] = {
	cv::Scalar(0, 0, 255),
 	cv::Scalar(0, 128, 255),
	cv::Scalar(0, 255, 255),
	cv::Scalar(0, 255, 0)
};

int main( int argc, char** argv )
{
    commandLine cmdLine(argc, argv, IS_HEADLESS());
    const char* src_file = cmdLine.GetString("source");

    if(!src_file)
    {
        printf("please using --source=/path/to/file to set source video file\n");
        return -1;
    }

    cv::VideoCapture video_src(src_file);

    if(!video_src.isOpened())
    {
        printf("cannot open %s\n", src_file);
        return -1;
    }

    int fps = (int) video_src.get(cv::CAP_PROP_FPS);
    int frames_count = (int) video_src.get(cv::CAP_PROP_FRAME_COUNT);
    printf("fps: %d, frames cnt: %d\n", fps, frames_count);
    const char* win_name = "yolo_detect";
    cv::namedWindow(win_name);
    cv::Mat frame;
    int ms_delay = (int) (1000 / fps);
    bool stop(false);
    uint32_t idx = 0;
    while(!stop)
    {
        if(!video_src.read(frame))
            break;
        idx++;
        rectangle(frame, cv::Point(50, 50), cv::Point(120, 80), cv_colors[idx % 4], 1, cv::LINE_8);
        cv::imshow(win_name, frame);

        if(cv::waitKey(ms_delay-5) >= 0)
            stop = true;
    }
    video_src.release();
    return 0;
}
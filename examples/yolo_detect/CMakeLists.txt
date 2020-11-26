
include_directories(/usr/include/opencv4)
file(GLOB yolo_detectSources *.cpp)
file(GLOB yolo_detectIncludes *.h )

cuda_add_executable(yolo_detect ${yolo_detectSources})
target_link_libraries(yolo_detect jetson-inference jetson-utils opencv_core opencv_videoio opencv_highgui opencv_imgproc)
install(TARGETS yolo_detect DESTINATION bin)

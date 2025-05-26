#include <iostream>
#include <thread>
#include <cstdlib>
#include <chrono>
#include "logger.hpp"

void stream_camera() {
    log(INFO, "Camera stream started using GStreamer...");
    system("gst-launch-1.0 videotestsrc ! videoconvert ! autovideosink");
    log(INFO, "Camera stream ended.");
}

int main() {
    log(INFO, "Main thread started.");
    std::thread cameraThread(stream_camera);

    for (int i = 0; i < 5; ++i) {
        log(DEBUG, "Running main control logic... (" + std::to_string(i) + ")");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    cameraThread.join();
    log(INFO, "Main thread finished.");
    return 0;
}


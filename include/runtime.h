#ifndef HAIKU_RUNTIME_H_
#define HAIKU_RUNTIME_H_

#include <memory>
#include <thread>

#include "input.h"
#include "tracking.h"

namespace haiku {

class Runtime {
public:
    Runtime(CameraInput::Kind camera_kind);
    inline CameraInput::Kind CameraKind() const { return camera_kind_; }
    void ProcessInput(std::unique_ptr<Input> &&input);

private:
    CameraInput::Kind camera_kind_;

    Tracking tracking_;
    std::thread tracking_thread_;
};

}  // namespace haiku

#endif  // HAIKU_RUNTIME_H_

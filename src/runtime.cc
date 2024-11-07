#include "runtime.h"

namespace haiku {

Runtime::Runtime(CameraInput::Kind camera_kind)
    : camera_kind_(camera_kind), tracking_(*this) {
    tracking_thread_ = std::thread(&Tracking::Run, &tracking_);
}

void Runtime::ProcessInput(std::unique_ptr<Input>&& input) {
    tracking_.TrackInput(std::move(input));
}

}  // namespace haiku

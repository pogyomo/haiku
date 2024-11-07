#include "tracking.h"

#include <memory>
#include <thread>

namespace haiku {

Tracking::Tracking(Runtime &runtime) : runtime_(runtime) {}

void Tracking::Run() {
    while (true) RunOnce();
}

void Tracking::TrackInput(std::unique_ptr<Input> &&input) {
    std::unique_lock lock(queue_mutex_);
    queue_.push_back(std::move(input));
}

void Tracking::RunOnce() {
    auto input = AcceptInputFromQueue();
    inputs_.push_back(std::move(input));
}

std::unique_ptr<Input> Tracking::AcceptInputFromQueue() {
    while (queue_.empty()) {
        {
            std::unique_lock lock(queue_mutex_);
            if (!queue_.empty()) break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    auto value = std::move(queue_.front());
    queue_.pop_front();
    return value;
}

}  // namespace haiku

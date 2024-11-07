#include "tracking.h"

#include <memory>
#include <thread>

namespace haiku {

Tracking::Tracking(Runtime &runtime) : runtime_(runtime) {}

void Tracking::Run() {
    while (true) RunOnce();
}

void Tracking::TrackInput(std::unique_ptr<Input> &&input) {
    input_queue_.Push(std::move(input));
}

void Tracking::RunOnce() {
    auto input = input_queue_.BlockedPop();
    inputs_.push_back(std::move(input));
}

void Tracking::InputQueue::Push(std::unique_ptr<Input> &&input) {
    std::unique_lock lock(mutex_);
    queue_.push_back(std::move(input));
}

std::unique_ptr<Input> Tracking::InputQueue::BlockedPop() {
    while (true) {
        {
            std::unique_lock lock(mutex_);
            if (!queue_.empty()) break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::unique_lock lock(mutex_);
    auto value = std::move(queue_.front());
    queue_.pop_front();
    return value;
}

}  // namespace haiku

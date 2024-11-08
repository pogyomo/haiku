#include "tracking.h"

#include <thread>

namespace haiku {

Tracking::Tracking(Runtime &runtime) : runtime_(runtime) {}

void Tracking::Run() {
    flags_.SetRunnable();
    flags_.SetRunning();
    while (flags_.IsRunnable()) RunOnce();
    flags_.UnsetRunning();
    flags_.UnsetRunnable();
}

void Tracking::TrackInput(std::unique_ptr<Input> &&input) {
    input_queue_.Push(std::move(input));
}

void Tracking::Terminate() { flags_.UnsetRunnable(); }

bool Tracking::IsRunning() { return flags_.IsRunning(); }

void Tracking::RunOnce() {
    auto input = input_queue_.BlockedPop();
    inputs_.push_back(std::move(input));
}

Tracking::Flags::Flags() : runnable_(false), running_(false) {}

bool Tracking::Flags::IsRunnable() {
    std::unique_lock lock(mutex_);
    return runnable_;
}

bool Tracking::Flags::IsRunning() {
    std::unique_lock lock(mutex_);
    return running_;
}

void Tracking::Flags::SetRunnable() {
    std::unique_lock lock(mutex_);
    runnable_ = true;
}

void Tracking::Flags::SetRunning() {
    std::unique_lock lock(mutex_);
    running_ = true;
}

void Tracking::Flags::UnsetRunnable() {
    std::unique_lock lock(mutex_);
    runnable_ = false;
}

void Tracking::Flags::UnsetRunning() {
    std::unique_lock lock(mutex_);
    running_ = false;
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

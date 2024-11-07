#ifndef HAIKU_TRACKING_H_
#define HAIKU_TRACKING_H_

#include <list>
#include <mutex>

#include "input.h"

namespace haiku {

class Runtime;

class Tracking {
public:
    Tracking(Runtime &runtime);
    void Run();
    void TrackInput(std::unique_ptr<Input> &&input);

private:
    /// A queue for Input which can be used more than one threads.
    class InputQueue {
    public:
        InputQueue() {}
        void Push(std::unique_ptr<Input> &&input);
        std::unique_ptr<Input> BlockedPop();

    private:
        std::mutex mutex_;
        std::list<std::unique_ptr<Input>> queue_;
    };

    void RunOnce();

    Runtime &runtime_;
    InputQueue input_queue_;
    std::vector<std::unique_ptr<Input>> inputs_;
};

}  // namespace haiku

#endif  // HAIKU_TRACKING_H_

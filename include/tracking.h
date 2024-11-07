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
    void RunOnce();
    std::unique_ptr<Input> AcceptInputFromQueue();

    Runtime &runtime_;

    std::mutex queue_mutex_;
    std::list<std::unique_ptr<Input>> queue_;

    std::vector<std::unique_ptr<Input>> inputs_;
};

}  // namespace haiku

#endif  // HAIKU_TRACKING_H_

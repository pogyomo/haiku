#include "runtime.h"

namespace haiku::runtime {

std::future<void> Runtime::ProcessInput(const Input& input) {
    return std::promise<void>().get_future();
}

std::future<void> Runtime::ProcessInput(Input&& input) {
    return std::promise<void>().get_future();
}

}  // namespace haiku::runtime

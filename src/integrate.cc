#include "integrate.h"

namespace haiku {

IntegratedIMU::IntegratedIMU(const std::vector<ImuInput> &imu_inputs,
                             const IntegratedIMU &prev)
    : pos_(prev.pos_), rot_(prev.rot_) {
    if (imu_inputs.empty()) {
        ts_ = prev.ts_;
        return;
    } else {
        ts_ = imu_inputs.back().ts();
    }

    // TODO: Integrate imu data
}

IntegratedIMU::IntegratedIMU(double ts)
    : pos_(Eigen::Vector3d::Zero()), rot_(Eigen::Matrix3d::Identity()), ts_(ts) {}

IntegratedIMU::IntegratedIMU(const Eigen::Vector3d &pos, const Eigen::Matrix3d &rot,
                             double ts)
    : pos_(pos), rot_(rot), ts_(ts) {}

IntegratedIMU::IntegratedIMU(Eigen::Vector3d &&pos, Eigen::Matrix3d &&rot, double ts)
    : pos_(std::move(pos)), rot_(std::move(rot)), ts_(ts) {}

}  // namespace haiku

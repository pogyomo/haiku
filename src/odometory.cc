#include "odometory.h"

#include <cassert>

namespace haiku {

OdometoryData::OdometoryData(std::unique_ptr<OdometoryData> &&prev,
                             std::chrono::steady_clock::time_point timestamp)
    : prev_(std::move(prev)),
      timestamp_(timestamp),
      position_calculated_(false),
      rotation_calculated_(false),
      position_(Eigen::Vector3d::Zero()),
      rotation_(Eigen::Matrix3d::Identity()) {}

Eigen::Vector3d OdometoryData::Position() {
    assert(position_calculated_);
    return position_;
}

Eigen::Matrix3d OdometoryData::Rotation() {
    assert(rotation_calculated_);
    return rotation_;
}

};  // namespace haiku

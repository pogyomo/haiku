#ifndef HAIKU_ODOMETORY_H_
#define HAIKU_ODOMETORY_H_

#include <Eigen/Eigen>
#include <chrono>
#include <memory>

namespace haiku {

/// Base class for various type of odometory data.
class OdometoryData {
public:
    /// Construct a new odometory data.
    /// Position and rotation is uninitialized.
    OdometoryData(std::unique_ptr<OdometoryData> &&prev,
                  std::chrono::steady_clock::time_point timestamp);

    /// Returns robot position vector in world coordination.
    Eigen::Vector3d Position();

    /// Returns robot rotation matrix in world coordination.
    Eigen::Matrix3d Rotation();

protected:
    /// Previous odometory data, or nullptr if this is first data.
    std::unique_ptr<OdometoryData> prev_;

    /// When this data obtained.
    std::chrono::steady_clock::time_point timestamp_;

    /// True if position_ is initialized.
    bool position_calculated_;

    /// True if rotation_ is initialized.
    bool rotation_calculated_;

    /// Calculated position vector.
    Eigen::Vector3d position_;

    /// Calculated rotation matrix.
    Eigen::Matrix3d rotation_;
};

/// Odometory data obtained by inertial measurement unit.
class IMUData : OdometoryData {};

};  // namespace haiku

#endif  // HAIKU_ODOMETORY_H_

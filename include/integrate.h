#ifndef HAIKU_INTEGRATE_H_
#define HAIKU_INTEGRATE_H_

#include <vector>

#include "input.h"

namespace haiku {

class IntegratedIMU {
public:
    IntegratedIMU(const std::vector<ImuInput> &imu_inputs, const IntegratedIMU &prev);
    inline const Eigen::Vector3d &pos() const { return pos_; }
    inline const Eigen::Matrix3d &rot() const { return rot_; }
    inline double ts() const { return ts_; }

private:
    explicit IntegratedIMU(double ts);
    IntegratedIMU(const Eigen::Vector3d &pos, const Eigen::Matrix3d &rot, double ts);
    IntegratedIMU(Eigen::Vector3d &&pos, Eigen::Matrix3d &&rot, double ts);

    Eigen::Vector3d pos_;
    Eigen::Matrix3d rot_;
    double ts_;
};

}  // namespace haiku

#endif  // HAIKU_INTEGRATE_H_

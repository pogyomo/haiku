#ifndef HAIKU_INPUT_H_
#define HAIKU_INPUT_H_

#include <Eigen/Core>
#include <opencv2/core/mat.hpp>
#include <variant>

namespace haiku {

class ImuInput {
public:
    ImuInput(double acc_x, double acc_y, double acc_z, double gyro_x, double gyro_y,
             double gyro_z, double ts)
        : acc_(acc_x, acc_y, acc_z), gyro_(gyro_x, gyro_y, gyro_z), ts_(ts) {}
    inline const Eigen::Vector3d &acc() const { return acc_; }
    inline const Eigen::Vector3d &gyro() const { return gyro_; }
    inline double ts() const { return ts_; }

private:
    Eigen::Vector3d acc_, gyro_;
    double ts_;
};

class CameraInput {
public:
    enum Kind {
        Stereo,
        Monocular,
        RGBD,
    };

    class StereoData {
    public:
        StereoData(const cv::Mat &image_l, const cv::Mat &image_r)
            : image_l_(image_l), image_r_(image_r) {}
        StereoData(cv::Mat &&image_l, cv::Mat &&image_r)
            : image_l_(std::move(image_l)), image_r_(std::move(image_r)) {}
        inline const cv::Mat &image_l() const { return image_l_; }
        inline const cv::Mat &image_r() const { return image_r_; }

    private:
        cv::Mat image_l_, image_r_;
    };

    class MonocularData {
    public:
        MonocularData(const cv::Mat &image) : image_(image) {}
        MonocularData(cv::Mat &&image) : image_(std::move(image)) {}
        inline const cv::Mat &image() const { return image_; }

    private:
        cv::Mat image_;
    };

    class RGBDData {
    public:
        RGBDData(const cv::Mat &image, const cv::Mat &depth)
            : image_(image), depth_(depth) {}
        RGBDData(cv::Mat &&image, cv::Mat &&depth)
            : image_(std::move(image)), depth_(std::move(depth)) {}
        inline const cv::Mat &image() const { return image_; }
        inline const cv::Mat &depth() const { return depth_; }

    private:
        cv::Mat image_, depth_;
    };

    CameraInput() = delete;
    CameraInput(const StereoData &data, double ts) : data_(data), ts_(ts) {}
    CameraInput(StereoData &&data, double ts) : data_(std::move(data)), ts_(ts) {}
    CameraInput(const MonocularData &data, double ts) : data_(data), ts_(ts) {}
    CameraInput(MonocularData &&data, double ts) : data_(std::move(data)), ts_(ts) {}
    CameraInput(const RGBDData &data, double ts) : data_(data), ts_(ts) {}
    CameraInput(RGBDData &&data, double ts) : data_(std::move(data)), ts_(ts) {}

    inline Kind InputKind() const {
        return data_.index() == 0 ? Stereo : (data_.index() == 1 ? Monocular : RGBD);
    }
    inline const StereoData &stereo_data() const { return std::get<0>(data_); }
    inline const MonocularData &monocular_data() const { return std::get<1>(data_); }
    inline const RGBDData &rgbd_data() const { return std::get<2>(data_); }
    inline double ts() const { return ts_; }

private:
    std::variant<StereoData, MonocularData, RGBDData> data_;
    double ts_;
};

/// Conbimation of camera input and imu inputs.
/// These imu inputs is the inputs obtained after previous input.
class Input {
public:
    Input(const CameraInput &camera_input, const std::vector<ImuInput> &imu_inputs)
        : camera_input_(camera_input), imu_inputs_(imu_inputs) {}
    Input(CameraInput &&camera_input, std::vector<ImuInput> &&imu_inputs)
        : camera_input_(std::move(camera_input)), imu_inputs_(std::move(imu_inputs)) {}
    inline const CameraInput &camera_input() const { return camera_input_; }
    inline const std::vector<ImuInput> &imu_inputs() const { return imu_inputs_; }

private:
    CameraInput camera_input_;
    std::vector<ImuInput> imu_inputs_;
};

}  // namespace haiku

#endif  // HAIKU_INPUT_H_

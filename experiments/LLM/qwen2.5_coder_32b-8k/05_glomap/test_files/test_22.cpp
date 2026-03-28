#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <unordered_map>

#include <Eigen/Geometry>



namespace glomap {

    struct image_t {};

    struct camera_t {};

    struct rig_t {};

    struct frame_t {};



    enum class SensorType {

        CAMERA,

        // other sensor types can be added here

    };



    struct sensor_t {

        SensorType type;

        camera_t id;



        sensor_t(SensorType t, camera_t i) : type(t), id(i) {}

    };



    struct Rigid3d {

        Eigen::Quaterniond rotation;

        Eigen::Vector3d translation;



        Rigid3d(Eigen::Quaterniond r, Eigen::Vector3d t) : rotation(r), translation(t) {}

    };



    class Image {

    public:

        bool IsRegistered() const { return is_registered; }

        camera_t camera_id;

        bool is_registered = true;

    };



    class Rig {

    public:

        sensor_t RefSensorId() const { return ref_sensor_id; }



        std::optional<Rigid3d> MaybeSensorFromRig(const sensor_t& sensor) const {

            auto it = sensors.find(sensor);

            if (it != sensors.end()) {

                return it->second;

            }

            return std::nullopt;

        }



        void SetSensorFromRig(const sensor_t& sensor, const Rigid3d& rigid) {

            sensors[sensor] = rigid;

        }



        std::unordered_map<sensor_t, Rigid3d> NonRefSensors() const {

            std::unordered_map<sensor_t, Rigid3d> non_ref_sensors;

            for (const auto& [sensor, rigid] : sensors) {

                if (sensor != ref_sensor_id) {

                    non_ref_sensors[sensor] = rigid;

                }

            }

            return non_ref_sensors;

        }



    private:

        sensor_t ref_sensor_id;

        std::unordered_map<sensor_t, Rigid3d> sensors;

    };



    class Frame {

    public:

        Rig* RigPtr() const { return rig_ptr; }

        void SetRigFromWorld(const Rigid3d& rigid) {

            rig_from_world = rigid;

        }



        struct ImageId {

            image_t id;

        };



        std::vector<ImageId> ImageIds() const { return image_ids; }



    private:

        Rig* rig_ptr;

        std::vector<ImageId> image_ids;

        Rigid3d rig_from_world;

    };



    bool ConvertRotationsFromImageToRig(

            const std::unordered_map<image_t, Rigid3d>& cam_from_worlds,

            const std::unordered_map<image_t, Image>& images,

            std::unordered_map<rig_t, Rig>& rigs,

            std::unordered_map<frame_t, Frame>& frames);

}



namespace {



TEST(ConvertRotationsFromImageToRigTest_22, NormalOperation_22) {

    glomap::image_t img1, img2;

    glomap::camera_t cam1, cam2;

    glomap::rig_t rig1;

    glomap::frame_t frame1;



    glomap::sensor_t ref_sensor(glomap::SensorType::CAMERA, cam1);

    glomap::Rigid3d rig_from_world(Eigen::Quaterniond(), Eigen::Vector3d());

    glomap::Image image1, image2;

    image1.camera_id = cam1;

    image2.camera_id = cam2;



    glomap::Frame frame;

    frame.image_ids = {glomap::Frame::ImageId{img1}, glomap::Frame::ImageId{img2}};

    frame.rig_ptr = new glomap::Rig();

    frame.rig_ptr->ref_sensor_id = ref_sensor;



    std::unordered_map<glomap::image_t, glomap::Rigid3d> cam_from_worlds;

    cam_from_worlds[img1] = glomap::Rigid3d(Eigen::Quaterniond(), Eigen::Vector3d());

    cam_from_worlds[img2] = glomap::Rigid3d(Eigen::Quaterniond(), Eigen::Vector3d());



    std::unordered_map<glomap::image_t, glomap::Image> images;

    images[img1] = image1;

    images[img2] = image2;



    std::unordered_map<glomap::rig_t, glomap::Rig> rigs;

    rigs[rig1] = *frame.rig_ptr;



    std::unordered_map<glomap::frame_t, glomap::Frame> frames;

    frames[frame1] = frame;



    bool result = glomap::ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);



    delete frame.rig_ptr;

}



TEST(ConvertRotationsFromImageToRigTest_22, BoundaryConditions_NoImages_22) {

    std::unordered_map<glomap::image_t, glomap::Rigid3d> cam_from_worlds;

    std::unordered_map<glomap::image_t, glomap::Image> images;

    std::unordered_map<glomap::rig_t, glomap::Rig> rigs;

    std::unordered_map<glomap::frame_t, glomap::Frame> frames;



    bool result = glomap::ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);

}



TEST(ConvertRotationsFromImageToRigTest_22, BoundaryConditions_NoFrames_22) {

    std::unordered_map<glomap::image_t, glomap::Rigid3d> cam_from_worlds;

    std::unordered_map<glomap::image_t, glomap::Image> images;

    std::unordered_map<glomap::rig_t, glomap::Rig> rigs;

    std::unordered_map<glomap::frame_t, glomap::Frame> frames;



    bool result = glomap::ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);

}



TEST(ConvertRotationsFromImageToRigTest_22, ExceptionalCase_ImageNotRegistered_22) {

    glomap::image_t img1;

    glomap::camera_t cam1;

    glomap::rig_t rig1;

    glomap::frame_t frame1;



    glomap::sensor_t ref_sensor(glomap::SensorType::CAMERA, cam1);

    glomap::Rigid3d rig_from_world(Eigen::Quaterniond(), Eigen::Vector3d());

    glomap::Image image1;

    image1.camera_id = cam1;

    image1.is_registered = false;



    glomap::Frame frame;

    frame.image_ids = {glomap::Frame::ImageId{img1}};

    frame.rig_ptr = new glomap::Rig();

    frame.rig_ptr->ref_sensor_id = ref_sensor;



    std::unordered_map<glomap::image_t, glomap::Rigid3d> cam_from_worlds;

    cam_from_worlds[img1] = glomap::Rigid3d(Eigen::Quaterniond(), Eigen::Vector3d());



    std::unordered_map<glomap::image_t, glomap::Image> images;

    images[img1] = image1;



    std::unordered_map<glomap::rig_t, glomap::Rig> rigs;

    rigs[rig1] = *frame.rig_ptr;



    std::unordered_map<glomap::frame_t, glomap::Frame> frames;

    frames[frame1] = frame;



    bool result = glomap::ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);



    delete frame.rig_ptr;

}



TEST(ConvertRotationsFromImageToRigTest_22, ExceptionalCase_ImageNotFound_22) {

    glomap::image_t img1, img2;

    glomap::camera_t cam1, cam2;

    glomap::rig_t rig1;

    glomap::frame_t frame1;



    glomap::sensor_t ref_sensor(glomap::SensorType::CAMERA, cam1);

    glomap::Rigid3d rig_from_world(Eigen::Quaterniond(), Eigen::Vector3d());

    glomap::Image image1, image2;

    image1.camera_id = cam1;

    image2.camera_id = cam2;



    glomap::Frame frame;

    frame.image_ids = {glomap::Frame::ImageId{img1}, glomap::Frame::ImageId{img2}};

    frame.rig_ptr = new glomap::Rig();

    frame.rig_ptr->ref_sensor_id = ref_sensor;



    std::unordered_map<glomap::image_t, glomap::Rigid3d> cam_from_worlds;

    cam_from_worlds[img1] = glomap::Rigid3d(Eigen::Quaterniond(), Eigen::Vector3d());



    std::unordered_map<glomap::image_t, glomap::Image> images;

    images[img1] = image1;



    std::unordered_map<glomap::rig_t, glomap::Rig> rigs;

    rigs[rig1] = *frame.rig_ptr;



    std::unordered_map<glomap::frame_t, glomap::Frame> frames;

    frames[frame1] = frame;



    bool result = glomap::ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);



    delete frame.rig_ptr;

}



TEST(ConvertRotationsFromImageToRigTest_22, Verification_ExternalInteractions_22) {

    glomap::image_t img1, img2;

    glomap::camera_t cam1, cam2;

    glomap::rig_t rig1;

    glomap::frame_t frame1;



    glomap::sensor_t ref_sensor(glomap::SensorType::CAMERA, cam1);

    glomap::Rigid3d rig_from_world(Eigen::Quaterniond(), Eigen::Vector3d());

    glomap::Image image1, image2;

    image1.camera_id = cam1;

    image2.camera_id = cam2;



    glomap::Frame frame;

    frame.image_ids = {glomap::Frame::ImageId{img1}, glomap::Frame::ImageId{img2}};

    frame.rig_ptr = new glomap::Rig();

    frame.rig_ptr->ref_sensor_id = ref_sensor;



    std::unordered_map<glomap::image_t, glomap::Rigid3d> cam_from_worlds;

    cam_from_worlds[img1] = glomap::Rigid3d(Eigen::Quaterniond(), Eigen::Vector3d());

    cam_from_worlds[img2] = glomap::Rigid3d(Eigen::Quaterniond(), Eigen::Vector3d());



    std::unordered_map<glomap::image_t, glomap::Image> images;

    images[img1] = image1;

    images[img2] = image2;



    std::unordered_map<glomap::rig_t, glomap::Rig> rigs;

    rigs[rig1] = *frame.rig_ptr;



    std::unordered_map<glomap::frame_t, glomap::Frame> frames;

    frames[frame1] = frame;



    bool result = glomap::ConvertRotationsFromImageToRig(cam_from_worlds, images, rigs, frames);

    EXPECT_TRUE(result);



    // Verify the results

    auto rig = rigs[rig1];

    for (const auto& [sensor, rigid] : rig.NonRefSensors()) {

        EXPECT_FALSE(rigid.rotation.isApprox(Eigen::Quaterniond()));

    }



    delete frame.rig_ptr;

}



}  // namespace

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::Exactly;

//
// ==== Mock Classes (allowed: external collaborators only) ====
//

class MockViewGraph : public ViewGraph {
public:
    MOCK_METHOD(void, KeepLargestConnectedComponents,
                (std::unordered_map<frame_t, Frame>&,
                 std::unordered_map<image_t, Image>&),
                (override));

    // Expose image_pairs for insertion (no mocking: it is public in real class)
};

class MockRotationEstimator : public RotationEstimator {
public:
    MockRotationEstimator(const RotationEstimatorOptions& opt)
        : RotationEstimator(opt) {}

    MOCK_METHOD(bool, EstimateRotations,
                (ViewGraph&,
                 std::unordered_map<rig_t, Rig>&,
                 std::unordered_map<frame_t, Frame>&,
                 std::unordered_map<image_t, Image>&),
                (override));
};

//
// Helper factory to inject mock RotationEstimator
//
std::function<std::unique_ptr<RotationEstimator>(const RotationEstimatorOptions&)>
g_rotation_estimator_factory;

namespace glomap {
bool SolveRotationAveraging(ViewGraph& view_graph,
                            std::unordered_map<rig_t, Rig>& rigs,
                            std::unordered_map<frame_t, Frame>& frames,
                            std::unordered_map<image_t, Image>& images,
                            const RotationAveragerOptions& options);
}

//
// ==== Test Fixture ====
//
class RotationAveragerTest_52 : public ::testing::Test {
protected:
    MockViewGraph view_graph;
    std::unordered_map<rig_t, Rig> rigs;
    std::unordered_map<frame_t, Frame> frames;
    std::unordered_map<image_t, Image> images;

    RotationAveragerOptions opts;

    void SetUp() override {
        opts.use_gravity = false;
        opts.use_stratified = false;
        opts.skip_initialization = false;

        // Install global factory hook
        g_rotation_estimator_factory =
            [&](const RotationEstimatorOptions& opt) {
                return std::make_unique<MockRotationEstimator>(opt);
            };
    }
};


//
// TEST 1 — Normal flow, EstimateRotations returns true
//
TEST_F(RotationAveragerTest_52, NormalFlowReturnsTrue_52) {
    auto mock_estimator = new MockRotationEstimator(opts);

    EXPECT_CALL(view_graph, KeepLargestConnectedComponents(_, _))
        .Times(Exactly(2));  // initial + final

    EXPECT_CALL(*mock_estimator, EstimateRotations(_, _, _, _))
        .WillOnce(Return(true));

    // Replace factory to return our mock instance
    g_rotation_estimator_factory =
        [&](const RotationEstimatorOptions& opt) {
            return std::unique_ptr<RotationEstimator>(mock_estimator);
        };

    bool status = glomap::SolveRotationAveraging(
        view_graph, rigs, frames, images, opts);

    EXPECT_TRUE(status);
}


//
// TEST 2 — Normal flow, EstimateRotations returns false
//
TEST_F(RotationAveragerTest_52, NormalFlowEstimatorFails_52) {
    auto mock_estimator = new MockRotationEstimator(opts);

    EXPECT_CALL(view_graph, KeepLargestConnectedComponents(_, _))
        .Times(Exactly(2));

    EXPECT_CALL(*mock_estimator, EstimateRotations(_, _, _, _))
        .WillOnce(Return(false));

    g_rotation_estimator_factory =
        [&](const RotationEstimatorOptions& opt) {
            return std::unique_ptr<RotationEstimator>(mock_estimator);
        };

    bool status = glomap::SolveRotationAveraging(
        view_graph, rigs, frames, images, opts);

    EXPECT_FALSE(status);
}


//
// TEST 3 — solve_1dof_system path activated (gravity + stratified)
// But the status forces disable (grav_pairs == 0 triggers)
TEST_F(RotationAveragerTest_52, OneDoFPathDisabledByStatus_52) {
    opts.use_gravity = true;
    opts.use_stratified = true;

    auto mock_estimator = new MockRotationEstimator(opts);

    EXPECT_CALL(view_graph, KeepLargestConnectedComponents(_, _))
        .Times(Exactly(2));

    EXPECT_CALL(*mock_estimator, EstimateRotations(_, _, _, _))
        .WillOnce(Return(true));

    g_rotation_estimator_factory =
        [&](const RotationEstimatorOptions& opt) {
            return std::unique_ptr<RotationEstimator>(mock_estimator);
        };

    bool status = glomap::SolveRotationAveraging(
        view_graph, rigs, frames, images, opts);

    EXPECT_TRUE(status);   // Estimator returned true
}


//
// TEST 4 — unknown_cams_from_rig not empty -> trivial RA path triggered
// We cannot check internal structures, but we verify:
// 1) KeepLargestConnectedComponents is called >= 2 times
// 2) Two separate EstimateRotations calls (trivial + final RA)
//
TEST_F(RotationAveragerTest_52, TrivialRAPipelineTriggeredWhenUnknownCamsExist_52) {
    // Create rig with CAMERA sensor that has no rig transformation
    Rig r;
    r.SetRigId(1);
    sensor_t cam_sensor(SensorType::CAMERA, 42);
    r.AddRefSensor(cam_sensor);   // ref sensor
    rigs[1] = r;

    Frame f;
    f.SetFrameId(1);
    f.SetRigId(1);
    frames[1] = f;

    Image img(1, 42, "image.jpg");
    img.frame_id = 1;
    images[1] = img;

    opts.skip_initialization = false;

    auto mock_estimator_1 = new MockRotationEstimator(opts);
    auto mock_estimator_2 = new MockRotationEstimator(opts);

    ::testing::InSequence seq;

    EXPECT_CALL(view_graph, KeepLargestConnectedComponents(_, _))
        .Times(::testing::AtLeast(2));

    EXPECT_CALL(*mock_estimator_1, EstimateRotations(_, _, _, _))
        .WillOnce(Return(true));

    EXPECT_CALL(*mock_estimator_2, EstimateRotations(_, _, _, _))
        .WillOnce(Return(true));

    int counter = 0;
    g_rotation_estimator_factory =
        [&](const RotationEstimatorOptions& opt) {
            if (counter++ == 0)
                return std::unique_ptr<RotationEstimator>(mock_estimator_1);
            return std::unique_ptr<RotationEstimator>(mock_estimator_2);
        };

    bool status = glomap::SolveRotationAveraging(
        view_graph, rigs, frames, images, opts);

    EXPECT_TRUE(status);
}


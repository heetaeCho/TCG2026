#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

//
// ==== Declare global mockable functions ====
//
namespace colmap {
    MOCK_GLOBAL_FUNC2(ExistsFile, bool(const std::string&, bool));
    MOCK_GLOBAL_FUNC0(Timer_Start, void());
    MOCK_GLOBAL_FUNC0(Timer_Pause, void());
    MOCK_GLOBAL_FUNC0(Timer_ElapsedSeconds, double());
}

namespace glomap {
    MOCK_GLOBAL_FUNC3(ReadRelPose, void(const std::string&, 
                                        std::unordered_map<image_t, Image>&,
                                        ViewGraph&));
    MOCK_GLOBAL_FUNC2(ReadGravity, void(const std::string&, 
                                        std::unordered_map<image_t, Image>&));
    MOCK_GLOBAL_FUNC3(ReadRelWeight, void(const std::string&, 
                                          std::unordered_map<image_t, Image>&,
                                          ViewGraph&));
    MOCK_GLOBAL_FUNC5(SolveRotationAveraging, bool(const ViewGraph&,
                                                   const std::unordered_map<rig_t, Rig>&,
                                                   const std::unordered_map<frame_t, Frame>&,
                                                   const std::unordered_map<image_t, Image>&,
                                                   const RotationAveragerOptions&));
    MOCK_GLOBAL_FUNC2(WriteGlobalRotation, void(const std::string&,
                                                const std::unordered_map<image_t, Image>&));
}

//
// Mock ViewGraph
//
class MockViewGraph : public glomap::ViewGraph {
public:
    MOCK_METHOD2(KeepLargestConnectedComponents,
                 int(std::unordered_map<frame_t, Frame>&,
                     std::unordered_map<image_t, Image>&));
};

//
// Test Fixture
//
class RunRotationAveragerTest_57 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

//
// ================================================================
//  TEST CASES
// ================================================================
//

// ------------------------------------------------------------
// 1. Missing required relpose_path => fails immediately
// ------------------------------------------------------------
TEST_F(RunRotationAveragerTest_57, MissingRelPosePathReturnsFailure_57) {
    const char* argv[] = { "prog", 
                           "--relpose_path=NOFILE",
                           "--output_path=out.txt" };
    int argc = 3;

    EXPECT_CALL(colmap::ExistsFile, ExistsFile("NOFILE", _))
        .WillOnce(Return(false));

    int ret = glomap::RunRotationAverager(argc, const_cast<char**>(argv));

    EXPECT_EQ(ret, EXIT_FAILURE);
}

// ------------------------------------------------------------
// 2. gravity_path provided but file does NOT exist
// ------------------------------------------------------------
TEST_F(RunRotationAveragerTest_57, GravityPathProvidedButMissing_57) {
    const char* argv[] = { "prog",
                           "--relpose_path=rel.txt",
                           "--output_path=out.txt",
                           "--gravity_path=missing_g.txt" };
    int argc = 4;

    EXPECT_CALL(colmap::ExistsFile, ExistsFile("rel.txt", _))
        .WillOnce(Return(true));
    EXPECT_CALL(colmap::ExistsFile, ExistsFile("missing_g.txt", _))
        .WillOnce(Return(false));

    int ret = glomap::RunRotationAverager(argc, const_cast<char**>(argv));

    EXPECT_EQ(ret, EXIT_FAILURE);
}

// ------------------------------------------------------------
// 3. use_weight = true but weight_path = ""
// ------------------------------------------------------------
TEST_F(RunRotationAveragerTest_57, UseWeightWithoutWeightPath_57) {
    const char* argv[] = { "prog",
                           "--relpose_path=rel.txt",
                           "--output_path=out.txt",
                           "--use_weight=true" };
    int argc = 4;

    EXPECT_CALL(colmap::ExistsFile, ExistsFile("rel.txt", _))
        .WillOnce(Return(true));

    // weight_path defaults to "" → error
    int ret = glomap::RunRotationAverager(argc, const_cast<char**>(argv));
    EXPECT_EQ(ret, EXIT_FAILURE);
}

// ------------------------------------------------------------
// 4. Successful full pipeline (no gravity, no weight)
// ------------------------------------------------------------
TEST_F(RunRotationAveragerTest_57, SuccessfulRunMinimalInputs_57) {
    const char* argv[] = { "prog",
                           "--relpose_path=rel.txt",
                           "--output_path=out.txt" };
    int argc = 3;

    // 1. relpose exists
    EXPECT_CALL(colmap::ExistsFile, ExistsFile("rel.txt", _))
        .WillOnce(Return(true));

    // 2. ReadRelPose must be called
    EXPECT_CALL(glomap::ReadRelPose, ReadRelPose(_, _, _))
        .Times(1);

    // 3. ViewGraph::KeepLargestConnectedComponents → return a positive number
    EXPECT_CALL(glomap::SolveRotationAveraging,
                SolveRotationAveraging(_, _, _, _, _))
        .WillOnce(Return(true));

    EXPECT_CALL(glomap::WriteGlobalRotation, WriteGlobalRotation(_, _))
        .Times(1);

    int ret = glomap::RunRotationAverager(argc, const_cast<char**>(argv));
    EXPECT_EQ(ret, EXIT_SUCCESS);
}

// ------------------------------------------------------------
// 5. SolveRotationAveraging fails => whole function fails
// ------------------------------------------------------------
TEST_F(RunRotationAveragerTest_57, SolveRotationAveragingFails_57) {
    const char* argv[] = { "prog",
                           "--relpose_path=rel.txt",
                           "--output_path=out.txt" };
    int argc = 3;

    EXPECT_CALL(colmap::ExistsFile, ExistsFile("rel.txt", _))
        .WillOnce(Return(true));

    EXPECT_CALL(glomap::ReadRelPose, ReadRelPose(_, _, _))
        .Times(1);

    EXPECT_CALL(glomap::SolveRotationAveraging,
                SolveRotationAveraging(_, _, _, _, _))
        .WillOnce(Return(false));  // FAILS

    int ret = glomap::RunRotationAverager(argc, const_cast<char**>(argv));
    EXPECT_EQ(ret, EXIT_FAILURE);
}

// ------------------------------------------------------------
// 6. refine_gravity = true but gravity_path is empty → refine is ignored
// ------------------------------------------------------------
TEST_F(RunRotationAveragerTest_57, RefineGravityIgnoredWhenNoGravityPath_57) {
    const char* argv[] = { "prog",
                           "--relpose_path=rel.txt",
                           "--output_path=out.txt",
                           "--refine_gravity=true" };
    int argc = 4;

    EXPECT_CALL(colmap::ExistsFile, ExistsFile("rel.txt", _))
        .WillOnce(Return(true));

    EXPECT_CALL(glomap::ReadRelPose, ReadRelPose(_, _, _))
        .Times(1);

    // No gravity file, so refine_gravity must NOT call ReadGravity
    EXPECT_CALL(glomap::ReadGravity, ReadGravity(_, _))
        .Times(0);

    EXPECT_CALL(glomap::SolveRotationAveraging,
                SolveRotationAveraging(_, _, _, _, _))
        .WillOnce(Return(true));

    EXPECT_CALL(glomap::WriteGlobalRotation, WriteGlobalRotation(_, _))
        .Times(1);

    int ret = glomap::RunRotationAverager(argc, const_cast<char**>(argv));
    EXPECT_EQ(ret, EXIT_SUCCESS);
}


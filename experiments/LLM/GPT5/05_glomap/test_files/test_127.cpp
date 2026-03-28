#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <unordered_map>
#include <set>
#include "glomap/io/pose_io.h"

using ::testing::Return;

namespace {

class MockImage {
public:
    MOCK_METHOD(bool, IsRegistered, (), (const));
    MOCK_METHOD(Rigid3d, CamFromWorld, (), (const));

    std::string file_name;
};

// Helper to convert MockImage → Real-looking Image wrapper
struct TestImageWrapper : public glomap::Image {
    MockImage* mock;

    TestImageWrapper(MockImage* m, const std::string& name)
        : mock(m) {
        file_name = name;
    }

    bool IsRegistered() const override { return mock->IsRegistered(); }
    Rigid3d CamFromWorld() const override { return mock->CamFromWorld(); }
};

class WriteGlobalRotationTest_127 : public ::testing::Test {
protected:
    std::string temp_file = "test_output_127.txt";

    void TearDown() override {
        std::remove(temp_file.c_str());
    }
};

}  // namespace

// -------------------------------------------------------------
// TEST 1: Empty map → output file should be created but empty
// -------------------------------------------------------------
TEST_F(WriteGlobalRotationTest_127, WriteEmptyMapCreatesFile_127) {
    std::unordered_map<glomap::image_t, glomap::Image> images;

    glomap::WriteGlobalRotation(temp_file, images);

    std::ifstream file(temp_file);
    ASSERT_TRUE(file.is_open());

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    EXPECT_TRUE(content.empty());
}

// -------------------------------------------------------------
// TEST 2: All images unregistered → output file should stay empty
// -------------------------------------------------------------
TEST_F(WriteGlobalRotationTest_127, UnregisteredImagesAreSkipped_127) {
    MockImage m1;

    EXPECT_CALL(m1, IsRegistered()).WillOnce(Return(false));

    TestImageWrapper w1(&m1, "img1.jpg");

    std::unordered_map<glomap::image_t, glomap::Image> images;
    images.emplace(1, w1);

    glomap::WriteGlobalRotation(temp_file, images);

    std::ifstream file(temp_file);
    ASSERT_TRUE(file.is_open());

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    EXPECT_TRUE(content.empty());
}

// -------------------------------------------------------------
// TEST 3: Single registered image writes one line
// -------------------------------------------------------------
TEST_F(WriteGlobalRotationTest_127, SingleRegisteredImageIsWritten_127) {
    MockImage m;
    m.file_name = "imageA.png";

    EXPECT_CALL(m, IsRegistered()).WillRepeatedly(Return(true));

    Eigen::Quaterniond q(0.1, 0.2, 0.3, 0.4);  // w, x, y, z
    Rigid3d pose(Eigen::Vector3d(0, 0, 0), q);

    EXPECT_CALL(m, CamFromWorld()).WillRepeatedly(Return(pose));

    TestImageWrapper wrapper(&m, "imageA.png");

    std::unordered_map<glomap::image_t, glomap::Image> images;
    images.emplace(5, wrapper);

    glomap::WriteGlobalRotation(temp_file, images);

    std::ifstream file(temp_file);
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);

    // Expected quaternion output order: q3 q0 q1 q2
    EXPECT_THAT(line, ::testing::HasSubstr("imageA.png"));
    EXPECT_THAT(line, ::testing::HasSubstr("0.4"));  // qz
    EXPECT_THAT(line, ::testing::HasSubstr("0.1"));  // qw
    EXPECT_THAT(line, ::testing::HasSubstr("0.2"));  // qx
    EXPECT_THAT(line, ::testing::HasSubstr("0.3"));  // qy
}

// -------------------------------------------------------------
// TEST 4: Multiple registered images -> ensure ascending order
// -------------------------------------------------------------
TEST_F(WriteGlobalRotationTest_127, MultipleImagesOrderedById_127) {
    MockImage m1, m2;
    m1.file_name = "A.png";
    m2.file_name = "B.png";

    EXPECT_CALL(m1, IsRegistered()).WillRepeatedly(Return(true));
    EXPECT_CALL(m2, IsRegistered()).WillRepeatedly(Return(true));

    Eigen::Quaterniond q(1, 0, 0, 0);
    Rigid3d pose(Eigen::Vector3d::Zero(), q);

    EXPECT_CALL(m1, CamFromWorld()).WillRepeatedly(Return(pose));
    EXPECT_CALL(m2, CamFromWorld()).WillRepeatedly(Return(pose));

    TestImageWrapper w1(&m1, "A.png");
    TestImageWrapper w2(&m2, "B.png");

    std::unordered_map<glomap::image_t, glomap::Image> images;
    images.emplace(10, w1);
    images.emplace(3, w2);   // lower ID → should appear first

    glomap::WriteGlobalRotation(temp_file, images);

    std::ifstream f(temp_file);
    ASSERT_TRUE(f.is_open());

    std::string line1, line2;
    std::getline(f, line1);
    std::getline(f, line2);

    EXPECT_THAT(line1, ::testing::HasSubstr("B.png"));
    EXPECT_THAT(line2, ::testing::HasSubstr("A.png"));
}

// -------------------------------------------------------------
// TEST 5: Registered + Unregistered mixed
// -------------------------------------------------------------
TEST_F(WriteGlobalRotationTest_127, MixedRegisteredUnregistered_127) {
    MockImage mR, mU;
    mR.file_name = "reg.png";
    mU.file_name = "unreg.png";

    EXPECT_CALL(mR, IsRegistered()).WillRepeatedly(Return(true));
    EXPECT_CALL(mU, IsRegistered()).WillRepeatedly(Return(false));

    Eigen::Quaterniond q(1, 0, 0, 0);
    Rigid3d pose(Eigen::Vector3d::Zero(), q);

    EXPECT_CALL(mR, CamFromWorld()).WillRepeatedly(Return(pose));

    TestImageWrapper wR(&mR, "reg.png");
    TestImageWrapper wU(&mU, "unreg.png");

    std::unordered_map<glomap::image_t, glomap::Image> images;
    images.emplace(1, wR);
    images.emplace(2, wU);

    glomap::WriteGlobalRotation(temp_file, images);

    std::ifstream f(temp_file);
    ASSERT_TRUE(f.is_open());

    std::string content((std::istreambuf_iterator<char>(f)),
                         std::istreambuf_iterator<char>());

    EXPECT_THAT(content, ::testing::HasSubstr("reg.png"));
    EXPECT_THAT(content, ::testing::Not(::testing::HasSubstr("unreg.png")));
}

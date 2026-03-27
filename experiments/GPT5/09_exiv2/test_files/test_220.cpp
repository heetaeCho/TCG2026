#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/rafimage.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

namespace Exiv2 {

class RafImageTest_220 : public ::testing::Test {
protected:
    std::unique_ptr<BasicIo> io_;
    RafImage rafImage_;

    RafImageTest_220() 
        : io_(std::make_unique<BasicIo>()), 
          rafImage_(std::move(io_), true) {}

    void SetUp() override {
        // Setup any necessary mock objects or state here
    }

    void TearDown() override {
        // Clean up if needed
    }
};

// Test case for normal operation of printStructure()
TEST_F(RafImageTest_220, PrintStructure_220) {
    std::ostringstream out;
    EXPECT_NO_THROW(rafImage_.printStructure(out, kpsBasic, 1));

    // Verifying that the output contains expected information.
    std::string output = out.str();
    EXPECT_TRUE(output.find("STRUCTURE OF RAF FILE") != std::string::npos);
    EXPECT_TRUE(output.find("Address") != std::string::npos);
    EXPECT_TRUE(output.find("Length") != std::string::npos);
}

// Test case for when `io_->open()` fails
TEST_F(RafImageTest_220, PrintStructureFailsOnOpen_220) {
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(1));  // Simulate open failure
    std::ostringstream out;
    
    EXPECT_THROW(rafImage_.printStructure(out, kpsBasic, 1), Error);
}

// Test case for when file is not of RAF type
TEST_F(RafImageTest_220, PrintStructureFailsIfNotRAF_220) {
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*io_, error()).WillOnce(testing::Return(true));  // Simulate non-RAF type error

    std::ostringstream out;
    EXPECT_THROW(rafImage_.printStructure(out, kpsBasic, 1), Error);
}

// Test case for verifying printStructure with kpsRecursive option
TEST_F(RafImageTest_220, PrintStructureWithRecursiveOption_220) {
    std::ostringstream out;
    EXPECT_NO_THROW(rafImage_.printStructure(out, kpsRecursive, 2));

    // Verifying recursive structure output
    std::string output = out.str();
    EXPECT_TRUE(output.find("STRUCTURE OF RAF FILE") != std::string::npos);
}

// Test case for normal operation of pixelWidth and pixelHeight
TEST_F(RafImageTest_220, PixelDimensions_220) {
    EXPECT_EQ(rafImage_.pixelWidth(), 0);  // Assuming default values
    EXPECT_EQ(rafImage_.pixelHeight(), 0);
}

// Test case for setting and getting comment
TEST_F(RafImageTest_220, SetAndGetComment_220) {
    std::string comment = "Test comment";
    rafImage_.setComment(comment);
    EXPECT_EQ(rafImage_.comment(), comment);
}

// Test case for exceptional condition: Error in reading metadata
TEST_F(RafImageTest_220, ReadMetadataFails_220) {
    EXPECT_CALL(*io_, error()).WillOnce(testing::Return(true));
    EXPECT_THROW(rafImage_.readMetadata(), Error);
}

// Test case for writeMetadata with failure scenario
TEST_F(RafImageTest_220, WriteMetadataFails_220) {
    EXPECT_CALL(*io_, error()).WillOnce(testing::Return(true));
    EXPECT_THROW(rafImage_.writeMetadata(), Error);
}

// Test case for verifying exception on failed metadata write
TEST_F(RafImageTest_220, WriteMetadataFailsOnWrite_220) {
    EXPECT_CALL(*io_, write(testing::_, testing::_)).WillOnce(testing::Return(0));
    EXPECT_THROW(rafImage_.writeMetadata(), Error);
}

}  // namespace Exiv2
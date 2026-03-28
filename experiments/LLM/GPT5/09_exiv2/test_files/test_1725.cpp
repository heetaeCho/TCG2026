#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {

// Mocking the `Value` class as it is used in the `printStripLabel` method.
class MockValue {
public:
    MOCK_METHOD(std::string, toString, (), (const));  // Mock toString() method
};

// The class to be tested: SigmaMakerNote.
class SigmaMakerNoteTest : public ::testing::Test {
protected:
    SigmaMakerNote sigmaMakerNote;
};

TEST_F(SigmaMakerNoteTest, PrintStripLabel_NormalOperation_1725) {
    // Setup
    std::ostringstream os;
    MockValue value;
    ExifData* exifData = nullptr;

    // Prepare mock behavior for `toString`
    EXPECT_CALL(value, toString()).WillOnce(testing::Return("Label: test value"));

    // Test the behavior of printStripLabel
    sigmaMakerNote.printStripLabel(os, value, exifData);

    // Verify the output
    EXPECT_EQ(os.str(), "test value");
}

TEST_F(SigmaMakerNoteTest, PrintStripLabel_NoColonInValue_1726) {
    // Setup
    std::ostringstream os;
    MockValue value;
    ExifData* exifData = nullptr;

    // Prepare mock behavior for `toString`
    EXPECT_CALL(value, toString()).WillOnce(testing::Return("test value"));

    // Test the behavior of printStripLabel
    sigmaMakerNote.printStripLabel(os, value, exifData);

    // Verify the output (no colon to strip)
    EXPECT_EQ(os.str(), "test value");
}

TEST_F(SigmaMakerNoteTest, PrintStripLabel_EmptyValue_1727) {
    // Setup
    std::ostringstream os;
    MockValue value;
    ExifData* exifData = nullptr;

    // Prepare mock behavior for `toString`
    EXPECT_CALL(value, toString()).WillOnce(testing::Return(":"));

    // Test the behavior of printStripLabel
    sigmaMakerNote.printStripLabel(os, value, exifData);

    // Verify that it outputs an empty string as there's nothing after the colon.
    EXPECT_EQ(os.str(), "");
}

TEST_F(SigmaMakerNoteTest, PrintStripLabel_OnlyColon_1728) {
    // Setup
    std::ostringstream os;
    MockValue value;
    ExifData* exifData = nullptr;

    // Prepare mock behavior for `toString`
    EXPECT_CALL(value, toString()).WillOnce(testing::Return(": "));

    // Test the behavior of printStripLabel
    sigmaMakerNote.printStripLabel(os, value, exifData);

    // Verify that it correctly handles only the colon and space.
    EXPECT_EQ(os.str(), "");
}

}  // namespace Internal
}  // namespace Exiv2
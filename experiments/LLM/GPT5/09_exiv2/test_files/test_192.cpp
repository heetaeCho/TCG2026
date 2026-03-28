#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "pentaxmn_int.cpp" // Make sure the path is correct for your environment

namespace Exiv2 {
namespace Internal {

class MockValue : public Value {
public:
    MOCK_METHOD(int64_t, toInt64, (int index), (const, override));
};

class PentaxMakerNoteTest : public ::testing::Test {
protected:
    PentaxMakerNote pentaxMakerNote;
    MockValue mockValue;
};

TEST_F(PentaxMakerNoteTest, printTime_NormalOperation_192) {
    // Setup mock behavior
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(10));
    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(testing::Return(20));
    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(testing::Return(30));

    std::ostringstream os;
    pentaxMakerNote.printTime(os, mockValue, nullptr);

    // Validate the output
    EXPECT_EQ(os.str(), "10:20:30");
}

TEST_F(PentaxMakerNoteTest, printTime_EmptyValue_193) {
    // Setup mock behavior for empty values
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(0));
    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(testing::Return(0));
    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(testing::Return(0));

    std::ostringstream os;
    pentaxMakerNote.printTime(os, mockValue, nullptr);

    // Validate the output for boundary case
    EXPECT_EQ(os.str(), "00:00:00");
}

TEST_F(PentaxMakerNoteTest, printTime_NegativeValue_194) {
    // Setup mock behavior for negative values
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(-10));
    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(testing::Return(-20));
    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(testing::Return(-30));

    std::ostringstream os;
    pentaxMakerNote.printTime(os, mockValue, nullptr);

    // Validate the output for negative values
    EXPECT_EQ(os.str(), "-10:-20:-30");
}

TEST_F(PentaxMakerNoteTest, printTime_ZeroValues_195) {
    // Setup mock behavior for zero values
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(0));
    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(testing::Return(0));
    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(testing::Return(0));

    std::ostringstream os;
    pentaxMakerNote.printTime(os, mockValue, nullptr);

    // Validate the output for zero values
    EXPECT_EQ(os.str(), "00:00:00");
}

} // namespace Internal
} // namespace Exiv2
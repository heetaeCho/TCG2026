#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Mock the Value class (assumed interface for testing purposes)
class MockValue {
public:
    MOCK_METHOD(int64_t, toInt64, (), (const));
};

// Test fixture for Casio2MakerNote
class Casio2MakerNoteTest : public ::testing::Test {
protected:
    Exiv2::Internal::Casio2MakerNote makerNote;
};

// Normal operation: value is less than 0x20000000
TEST_F(Casio2MakerNoteTest, print0x2022_NormalCase_1823) {
    // Set up a value less than 0x20000000
    MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(1000000)); // 1000000 / 1000.0 = 1000.0

    std::ostringstream os;
    makerNote.print0x2022(os, value, nullptr);

    EXPECT_EQ(os.str(), "1000.00 m");
}

// Normal operation: value is exactly 0x20000000
TEST_F(Casio2MakerNoteTest, print0x2022_BoundaryCase_1824) {
    // Set up a value equal to 0x20000000
    MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(0x20000000));

    std::ostringstream os;
    makerNote.print0x2022(os, value, nullptr);

    EXPECT_EQ(os.str(), "Inf");
}

// Normal operation: value is greater than 0x20000000
TEST_F(Casio2MakerNoteTest, print0x2022_InfCase_1825) {
    // Set up a value greater than 0x20000000
    MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(0x30000000));

    std::ostringstream os;
    makerNote.print0x2022(os, value, nullptr);

    EXPECT_EQ(os.str(), "Inf");
}

// Error case: invalid value (negative number)
TEST_F(Casio2MakerNoteTest, print0x2022_NegativeValue_1826) {
    // Set up a negative value
    MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(-1000000));

    std::ostringstream os;
    makerNote.print0x2022(os, value, nullptr);

    // Check the result, which should still be formatted as a number (we are assuming the negative case would output a formatted string)
    EXPECT_EQ(os.str(), "-1000.00 m");
}

// Error case: large negative value
TEST_F(Casio2MakerNoteTest, print0x2022_LargeNegativeValue_1827) {
    // Set up a very large negative value
    MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(-10000000000));

    std::ostringstream os;
    makerNote.print0x2022(os, value, nullptr);

    // Check the result, which should still be formatted as a number
    EXPECT_EQ(os.str(), "-10000000.00 m");
}
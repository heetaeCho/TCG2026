#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// Mocks and necessary includes
class Value {
public:
    virtual int64_t toInt64(size_t index) const = 0;
};

class ExifData {};

namespace Exiv2 {
namespace Internal {

class PentaxMakerNote {
public:
    std::ostream& printDate(std::ostream& os, const Value& value, const ExifData*) {
        return os << stringFormat("{}:{:02}:{:02}", 
            ((static_cast<uint16_t>(value.toInt64(0)) << 8) + value.toInt64(1)), 
            value.toInt64(2), 
            value.toInt64(3));
    }
};

}  // namespace Internal
}  // namespace Exiv2

// Google Mock for the Value class to mock the toInt64 method
class MockValue : public Value {
public:
    MOCK_METHOD(int64_t, toInt64, (size_t index), (const, override));
};

// Test Fixture
class PentaxMakerNoteTest_191 : public ::testing::Test {
protected:
    Exiv2::Internal::PentaxMakerNote pentaxMakerNote;
};

// Test Case 1: Normal operation
TEST_F(PentaxMakerNoteTest_191, printDate_NormalOperation_191) {
    MockValue value;
    ExifData exifData;

    // Setting up mock returns
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(12));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(34));
    EXPECT_CALL(value, toInt64(2)).WillOnce(testing::Return(56));
    EXPECT_CALL(value, toInt64(3)).WillOnce(testing::Return(78));

    std::ostringstream os;
    pentaxMakerNote.printDate(os, value, &exifData);

    // Verifying the output
    EXPECT_EQ(os.str(), "3006:56:78");
}

// Test Case 2: Boundary condition - smallest possible value
TEST_F(PentaxMakerNoteTest_191, printDate_SmallestValue_191) {
    MockValue value;
    ExifData exifData;

    // Setting up mock returns for smallest value
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(0));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(0));
    EXPECT_CALL(value, toInt64(2)).WillOnce(testing::Return(0));
    EXPECT_CALL(value, toInt64(3)).WillOnce(testing::Return(0));

    std::ostringstream os;
    pentaxMakerNote.printDate(os, value, &exifData);

    // Verifying the output
    EXPECT_EQ(os.str(), "0:00:00");
}

// Test Case 3: Boundary condition - largest possible value (testing large numbers)
TEST_F(PentaxMakerNoteTest_191, printDate_LargestValue_191) {
    MockValue value;
    ExifData exifData;

    // Setting up mock returns for largest value (assuming large values for the test case)
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(0xFFFF));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(0xFFFF));
    EXPECT_CALL(value, toInt64(2)).WillOnce(testing::Return(0xFFFF));
    EXPECT_CALL(value, toInt64(3)).WillOnce(testing::Return(0xFFFF));

    std::ostringstream os;
    pentaxMakerNote.printDate(os, value, &exifData);

    // Verifying the output (specific format of the output is based on values provided)
    std::stringstream expected;
    expected << "65535:65535:65535";
    EXPECT_EQ(os.str(), expected.str());
}

// Test Case 4: Exceptional case - invalid input
TEST_F(PentaxMakerNoteTest_191, printDate_InvalidInput_191) {
    MockValue value;
    ExifData exifData;

    // Setting up mock returns for invalid or unexpected values
    EXPECT_CALL(value, toInt64(0)).WillOnce(testing::Return(-1));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(-1));
    EXPECT_CALL(value, toInt64(2)).WillOnce(testing::Return(-1));
    EXPECT_CALL(value, toInt64(3)).WillOnce(testing::Return(-1));

    std::ostringstream os;
    pentaxMakerNote.printDate(os, value, &exifData);

    // Verifying the output (since -1 is not a valid value for this case, check the result)
    EXPECT_EQ(os.str(), "-1:-1:-1");
}
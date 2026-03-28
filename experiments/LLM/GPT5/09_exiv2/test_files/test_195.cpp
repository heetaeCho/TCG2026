#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// Include the necessary headers
namespace Exiv2 {
    namespace Internal {
        class PentaxMakerNote {
        public:
            std::ostream& printFocalLength(std::ostream& os, const Value& value, const ExifData*) {
                return os << stringFormat("{:.1f} mm", static_cast<float>(value.toInt64()) / 100);
            }
        };
    }
}

// Mocking Value and ExifData classes for testing
class Value {
public:
    MOCK_METHOD(int64_t, toInt64, (), (const));
};

class ExifData {};

class PentaxMakerNoteTest_195 : public testing::Test {
protected:
    Exiv2::Internal::PentaxMakerNote pentaxMakerNote;
};

// Normal operation test
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_Normal_Operation_195) {
    std::ostringstream oss;
    Value value;
    ExifData exifData;
    
    // Mock to return a specific integer value
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(500));

    // Test the printFocalLength function
    pentaxMakerNote.printFocalLength(oss, value, &exifData);

    // Check if the output is formatted correctly
    EXPECT_EQ(oss.str(), "5.0 mm");
}

// Boundary condition test (value = 0)
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_ZeroValue_195) {
    std::ostringstream oss;
    Value value;
    ExifData exifData;
    
    // Mock to return 0
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(0));

    // Test the printFocalLength function
    pentaxMakerNote.printFocalLength(oss, value, &exifData);

    // Check if the output is formatted correctly
    EXPECT_EQ(oss.str(), "0.0 mm");
}

// Boundary condition test (value = negative)
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_NegativeValue_195) {
    std::ostringstream oss;
    Value value;
    ExifData exifData;
    
    // Mock to return a negative value
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(-500));

    // Test the printFocalLength function
    pentaxMakerNote.printFocalLength(oss, value, &exifData);

    // Check if the output is formatted correctly
    EXPECT_EQ(oss.str(), "-5.0 mm");
}

// Exceptional case: Test if the function handles large values
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_LargeValue_195) {
    std::ostringstream oss;
    Value value;
    ExifData exifData;
    
    // Mock to return a very large value
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(1000000000));

    // Test the printFocalLength function
    pentaxMakerNote.printFocalLength(oss, value, &exifData);

    // Check if the output is formatted correctly
    EXPECT_EQ(oss.str(), "10000000.0 mm");
}
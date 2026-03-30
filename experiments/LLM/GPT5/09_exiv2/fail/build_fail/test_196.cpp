#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

namespace Exiv2 {
    namespace Internal {
        class PentaxMakerNote {
        public:
            std::ostream& printCompensation(std::ostream& os, const Value& value, const ExifData*) {
                return os << stringFormat("{:.2g} EV", (static_cast<float>(value.toInt64()) - 50) / 10);
            }
        };
    }
}

class Value {
public:
    int64_t toInt64() const {
        return value_;
    }

    void setValue(int64_t val) {
        value_ = val;
    }

private:
    int64_t value_;
};

// Mock class for ExifData (optional if any external dependencies are involved)
class ExifData {};

// Helper function for formatting
std::string stringFormat(const char* format, float value) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), format, value);
    return std::string(buffer);
}

// Unit test class
class PentaxMakerNoteTest : public ::testing::Test {
protected:
    Exiv2::Internal::PentaxMakerNote pentaxMakerNote;
    Value value;
    ExifData exifData;
};

// Test for normal operation (testing expected output)
TEST_F(PentaxMakerNoteTest, printCompensation_NormalValue_196) {
    value.setValue(70);  // 70 -> (70 - 50) / 10 = 2.0 EV
    std::ostringstream oss;
    pentaxMakerNote.printCompensation(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "2 EV");
}

// Test for boundary conditions (testing edge case of value 50, should be 0.0 EV)
TEST_F(PentaxMakerNoteTest, printCompensation_BoundaryLowValue_196) {
    value.setValue(50);  // 50 -> (50 - 50) / 10 = 0.0 EV
    std::ostringstream oss;
    pentaxMakerNote.printCompensation(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "0 EV");
}

// Test for boundary condition (testing negative value for compensation, should output negative EV)
TEST_F(PentaxMakerNoteTest, printCompensation_NegativeValue_196) {
    value.setValue(40);  // 40 -> (40 - 50) / 10 = -1.0 EV
    std::ostringstream oss;
    pentaxMakerNote.printCompensation(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "-1 EV");
}

// Test for exceptional or error cases (here, assuming no exception is expected but behavior is observable)
TEST_F(PentaxMakerNoteTest, printCompensation_InvalidValue_196) {
    value.setValue(1000);  // Testing with an unusually large value
    std::ostringstream oss;
    pentaxMakerNote.printCompensation(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "95 EV");  // (1000 - 50) / 10 = 95
}

// Test for verification of external interactions (mocking ExifData behavior, if applicable)
TEST_F(PentaxMakerNoteTest, MockExifDataInteraction_196) {
    // Here you would normally mock external dependencies like ExifData if relevant
    // In this case, ExifData is passed but not used in the function, so no specific mock tests required.
    value.setValue(80);  // 80 -> (80 - 50) / 10 = 3.0 EV
    std::ostringstream oss;
    pentaxMakerNote.printCompensation(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "3 EV");
}
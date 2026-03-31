#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// We need to provide minimal stubs/mocks for the Exiv2 types used in the interface

namespace Exiv2 {

class ExifData {};

class Value {
public:
    virtual ~Value() = default;
    virtual int64_t toInt64(size_t n = 0) const = 0;
};

// A simple concrete Value implementation for testing
class TestValue : public Value {
public:
    explicit TestValue(int64_t val) : val_(val) {}
    int64_t toInt64(size_t /*n*/ = 0) const override { return val_; }
private:
    int64_t val_;
};

namespace Internal {

// Forward-declare the helper (from fmt/format.h or similar)
// We need stringFormat to work. Since it's used internally, we provide it.
std::string stringFormat(const char* fmt, float val) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%.2f", val);
    return std::string(buf);
}

class MinoltaMakerNote {
public:
    std::ostream& printMinoltaExposureCompensation5D(std::ostream& os, const Value& value, const ExifData*) {
        return os << stringFormat("{:.2f}", static_cast<float>(value.toInt64() - 300) / 100);
    }
};

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_1011 : public ::testing::Test {
protected:
    MinoltaMakerNote maker_;
    std::ostringstream oss_;
};

// Test: value=300 => (300-300)/100 = 0.00
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationZero_1011) {
    TestValue val(300);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "0.00");
}

// Test: value=400 => (400-300)/100 = 1.00
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationPositiveOne_1011) {
    TestValue val(400);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "1.00");
}

// Test: value=200 => (200-300)/100 = -1.00
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationNegativeOne_1011) {
    TestValue val(200);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "-1.00");
}

// Test: value=350 => (350-300)/100 = 0.50
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationHalfStop_1011) {
    TestValue val(350);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "0.50");
}

// Test: value=333 => (333-300)/100 = 0.33
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationThirdStop_1011) {
    TestValue val(333);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "0.33");
}

// Test: value=267 => (267-300)/100 = -0.33
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationNegativeThirdStop_1011) {
    TestValue val(267);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "-0.33");
}

// Test: value=0 => (0-300)/100 = -3.00
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationZeroValue_1011) {
    TestValue val(0);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "-3.00");
}

// Test: value=600 => (600-300)/100 = 3.00
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationLargePositive_1011) {
    TestValue val(600);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "3.00");
}

// Test: value=301 => (301-300)/100 = 0.01
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationSmallPositive_1011) {
    TestValue val(301);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "0.01");
}

// Test: value=299 => (299-300)/100 = -0.01
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationSmallNegative_1011) {
    TestValue val(299);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "-0.01");
}

// Test: Negative int64 value, e.g. value=-100 => (-100-300)/100 = -4.00
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationNegativeInput_1011) {
    TestValue val(-100);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "-4.00");
}

// Test: Large value, value=1300 => (1300-300)/100 = 10.00
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationLargeValue_1011) {
    TestValue val(1300);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "10.00");
}

// Test: Return value is reference to same ostream
TEST_F(MinoltaMakerNoteTest_1011, ReturnsSameOstream_1011) {
    TestValue val(300);
    std::ostream& result = maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(&result, &oss_);
}

// Test: Passing non-null ExifData pointer (should not affect output)
TEST_F(MinoltaMakerNoteTest_1011, NonNullExifDataIgnored_1011) {
    ExifData exifData;
    TestValue val(300);
    maker_.printMinoltaExposureCompensation5D(oss_, val, &exifData);
    EXPECT_EQ(oss_.str(), "0.00");
}

// Test: value=250 => (250-300)/100 = -0.50
TEST_F(MinoltaMakerNoteTest_1011, ExposureCompensationNegativeHalfStop_1011) {
    TestValue val(250);
    maker_.printMinoltaExposureCompensation5D(oss_, val, nullptr);
    EXPECT_EQ(oss_.str(), "-0.50");
}

#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the MinoltaMakerNote class from the internal namespace
namespace Exiv2 {
namespace Internal {
class MinoltaMakerNote {
public:
    std::ostream& printMinoltaFocalLengthStd(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_1004 : public ::testing::Test {
protected:
    MinoltaMakerNote maker_;
    std::ostringstream oss_;
};

// Test normal value: value=15 => (15/3)-2 = 3
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_NormalValue_1004) {
    ULongValue value;
    value.read("15");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("3", oss_.str());
}

// Test value=0 => (0/3)-2 = -2
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ZeroValue_1004) {
    ULongValue value;
    value.read("0");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("-2", oss_.str());
}

// Test value=3 => (3/3)-2 = -1
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ValueThree_1004) {
    ULongValue value;
    value.read("3");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("-1", oss_.str());
}

// Test value=6 => (6/3)-2 = 0
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ValueSix_1004) {
    ULongValue value;
    value.read("6");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("0", oss_.str());
}

// Test value=9 => (9/3)-2 = 1
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ValueNine_1004) {
    ULongValue value;
    value.read("9");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("1", oss_.str());
}

// Test large value: value=300 => (300/3)-2 = 98
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_LargeValue_1004) {
    ULongValue value;
    value.read("300");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("98", oss_.str());
}

// Test value=1 => (1/3)-2 = -2 (integer division: 1/3 = 0)
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ValueOne_1004) {
    ULongValue value;
    value.read("1");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("-2", oss_.str());
}

// Test value=2 => (2/3)-2 = -2 (integer division: 2/3 = 0)
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ValueTwo_1004) {
    ULongValue value;
    value.read("2");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("-2", oss_.str());
}

// Test that the function returns a reference to the same ostream
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ReturnsOstream_1004) {
    ULongValue value;
    value.read("15");
    std::ostream& result = maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ(&oss_, &result);
}

// Test with nullptr ExifData (should still work fine)
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_NullExifData_1004) {
    ULongValue value;
    value.read("30");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("8", oss_.str());
}

// Test value=4 => (4/3)-2 = -1 (integer division: 4/3 = 1)
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ValueFour_1004) {
    ULongValue value;
    value.read("4");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("-1", oss_.str());
}

// Test value=5 => (5/3)-2 = -1 (integer division: 5/3 = 1)
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_ValueFive_1004) {
    ULongValue value;
    value.read("5");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("-1", oss_.str());
}

// Test a very large value: value=3000 => (3000/3)-2 = 998
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_VeryLargeValue_1004) {
    ULongValue value;
    value.read("3000");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("998", oss_.str());
}

// Test chaining: write to stream that already has content
TEST_F(MinoltaMakerNoteTest_1004, PrintFocalLengthStd_StreamChaining_1004) {
    oss_ << "Focal: ";
    ULongValue value;
    value.read("15");
    maker_.printMinoltaFocalLengthStd(oss_, value, nullptr);
    EXPECT_EQ("Focal: 3", oss_.str());
}

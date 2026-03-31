#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa404(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class Print0xa404Test_1414 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: When denominator is 0, should output "Digital zoom not used"
TEST_F(Print0xa404Test_1414, DenominatorZero_ReturnsDigitalZoomNotUsed_1414) {
    URationalValue value;
    value.value_.push_back({0, 0});
    print0xa404(os, value, nullptr);
    EXPECT_NE(os.str().find("Digital zoom not used"), std::string::npos);
}

// Test: When denominator is 0 and numerator is non-zero, should still output "Digital zoom not used"
TEST_F(Print0xa404Test_1414, NonZeroNumeratorZeroDenominator_ReturnsDigitalZoomNotUsed_1414) {
    URationalValue value;
    value.value_.push_back({100, 0});
    print0xa404(os, value, nullptr);
    EXPECT_NE(os.str().find("Digital zoom not used"), std::string::npos);
}

// Test: Normal zoom ratio 2/1 = 2.0
TEST_F(Print0xa404Test_1414, NormalZoomRatio_2x_1414) {
    URationalValue value;
    value.value_.push_back({2, 1});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "2.0");
}

// Test: Normal zoom ratio 1/1 = 1.0
TEST_F(Print0xa404Test_1414, NormalZoomRatio_1x_1414) {
    URationalValue value;
    value.value_.push_back({1, 1});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "1.0");
}

// Test: Fractional zoom ratio 3/2 = 1.5
TEST_F(Print0xa404Test_1414, FractionalZoomRatio_1_5x_1414) {
    URationalValue value;
    value.value_.push_back({3, 2});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "1.5");
}

// Test: Large zoom ratio 10/1 = 10.0
TEST_F(Print0xa404Test_1414, LargeZoomRatio_10x_1414) {
    URationalValue value;
    value.value_.push_back({10, 1});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "10.0");
}

// Test: Zoom ratio with larger denominator 100/100 = 1.0
TEST_F(Print0xa404Test_1414, ZoomRatio_100_100_1414) {
    URationalValue value;
    value.value_.push_back({100, 100});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "1.0");
}

// Test: Zoom ratio 7/3 ≈ 2.3
TEST_F(Print0xa404Test_1414, ZoomRatio_7_3_1414) {
    URationalValue value;
    value.value_.push_back({7, 3});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "2.3");
}

// Test: Zoom ratio 1/3 ≈ 0.3
TEST_F(Print0xa404Test_1414, ZoomRatio_1_3_1414) {
    URationalValue value;
    value.value_.push_back({1, 3});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "0.3");
}

// Test: Zoom ratio 0/1 = 0.0
TEST_F(Print0xa404Test_1414, ZoomRatio_0_1_1414) {
    URationalValue value;
    value.value_.push_back({0, 1});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "0.0");
}

// Test: ExifData pointer being nullptr should not cause issues
TEST_F(Print0xa404Test_1414, NullExifDataPointer_1414) {
    URationalValue value;
    value.value_.push_back({4, 1});
    EXPECT_NO_THROW(print0xa404(os, value, nullptr));
    EXPECT_EQ(os.str(), "4.0");
}

// Test: Return value is the same ostream reference
TEST_F(Print0xa404Test_1414, ReturnsOstreamReference_1414) {
    URationalValue value;
    value.value_.push_back({2, 1});
    std::ostream& result = print0xa404(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test: Return value is the same ostream reference when denominator is zero
TEST_F(Print0xa404Test_1414, ReturnsOstreamReferenceWhenDenomZero_1414) {
    URationalValue value;
    value.value_.push_back({0, 0});
    std::ostream& result = print0xa404(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test: Zoom ratio 5/2 = 2.5
TEST_F(Print0xa404Test_1414, ZoomRatio_5_2_1414) {
    URationalValue value;
    value.value_.push_back({5, 2});
    print0xa404(os, value, nullptr);
    EXPECT_EQ(os.str(), "2.5");
}

// Test: Very large values
TEST_F(Print0xa404Test_1414, VeryLargeValues_1414) {
    URationalValue value;
    value.value_.push_back({1000000, 1});
    print0xa404(os, value, nullptr);
    // Should contain a formatted number
    EXPECT_FALSE(os.str().empty());
    EXPECT_EQ(os.str().find("Digital zoom not used"), std::string::npos);
}

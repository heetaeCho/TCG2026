#include <gtest/gtest.h>
#include <utility>

// Minimal declarations to match the interface
namespace Exiv2 {

using Rational = std::pair<int, int>;

class LangAltValue {
public:
    mutable bool ok_ = true;

    Rational toRational(size_t /*n*/) const {
        ok_ = false;
        return {0, 0};
    }
};

}  // namespace Exiv2

// Test fixture
class LangAltValueTest_861 : public ::testing::Test {
protected:
    Exiv2::LangAltValue value_;
};

// Test that toRational returns {0, 0}
TEST_F(LangAltValueTest_861, ToRationalReturnsZeroPair_861) {
    auto result = value_.toRational(0);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

// Test that toRational sets ok_ to false
TEST_F(LangAltValueTest_861, ToRationalSetsOkToFalse_861) {
    // ok_ should initially be true (default)
    value_.ok_ = true;
    value_.toRational(0);
    EXPECT_FALSE(value_.ok_);
}

// Test with various index values - boundary: n = 0
TEST_F(LangAltValueTest_861, ToRationalWithIndexZero_861) {
    auto result = value_.toRational(0);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
    EXPECT_FALSE(value_.ok_);
}

// Test with a large index value
TEST_F(LangAltValueTest_861, ToRationalWithLargeIndex_861) {
    auto result = value_.toRational(999999);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
    EXPECT_FALSE(value_.ok_);
}

// Test with max size_t index
TEST_F(LangAltValueTest_861, ToRationalWithMaxIndex_861) {
    auto result = value_.toRational(std::numeric_limits<size_t>::max());
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
    EXPECT_FALSE(value_.ok_);
}

// Test that calling toRational multiple times consistently returns the same result
TEST_F(LangAltValueTest_861, ToRationalMultipleCallsConsistent_861) {
    for (size_t i = 0; i < 10; ++i) {
        value_.ok_ = true;  // Reset before each call
        auto result = value_.toRational(i);
        EXPECT_EQ(result.first, 0);
        EXPECT_EQ(result.second, 0);
        EXPECT_FALSE(value_.ok_);
    }
}

// Test that ok_ is false after toRational even if it was already false
TEST_F(LangAltValueTest_861, ToRationalWhenOkAlreadyFalse_861) {
    value_.ok_ = false;
    auto result = value_.toRational(0);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
    EXPECT_FALSE(value_.ok_);
}

// Test that the returned Rational is a proper std::pair
TEST_F(LangAltValueTest_861, ToRationalReturnType_861) {
    Exiv2::Rational result = value_.toRational(1);
    EXPECT_EQ(result, std::make_pair(0, 0));
}

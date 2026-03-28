#include <gtest/gtest.h>
#include <cstdint>

// Minimal recreation of the interface based on the provided partial code
namespace Exiv2 {

class LangAltValue {
public:
    mutable bool ok_ = true;

    uint32_t toUint32(size_t /*n*/) const {
        ok_ = false;
        return 0;
    }
};

}  // namespace Exiv2

// Test fixture
class LangAltValueTest_859 : public ::testing::Test {
protected:
    Exiv2::LangAltValue value_;
};

// Test that toUint32 returns 0
TEST_F(LangAltValueTest_859, ToUint32ReturnsZero_859) {
    uint32_t result = value_.toUint32(0);
    EXPECT_EQ(result, 0u);
}

// Test that toUint32 sets ok_ to false
TEST_F(LangAltValueTest_859, ToUint32SetsOkToFalse_859) {
    // Ensure ok_ starts as true
    value_.ok_ = true;
    value_.toUint32(0);
    EXPECT_FALSE(value_.ok_);
}

// Test that toUint32 returns 0 for various index values (boundary conditions)
TEST_F(LangAltValueTest_859, ToUint32ReturnsZeroForDifferentIndices_859) {
    EXPECT_EQ(value_.toUint32(0), 0u);
    EXPECT_EQ(value_.toUint32(1), 0u);
    EXPECT_EQ(value_.toUint32(100), 0u);
    EXPECT_EQ(value_.toUint32(SIZE_MAX), 0u);
}

// Test that toUint32 always sets ok_ to false regardless of input
TEST_F(LangAltValueTest_859, ToUint32AlwaysSetsOkFalseRegardlessOfIndex_859) {
    value_.ok_ = true;
    value_.toUint32(0);
    EXPECT_FALSE(value_.ok_);

    value_.ok_ = true;
    value_.toUint32(SIZE_MAX);
    EXPECT_FALSE(value_.ok_);
}

// Test that calling toUint32 multiple times consistently returns 0 and keeps ok_ false
TEST_F(LangAltValueTest_859, ToUint32ConsistentOnMultipleCalls_859) {
    value_.ok_ = true;

    for (size_t i = 0; i < 10; ++i) {
        uint32_t result = value_.toUint32(i);
        EXPECT_EQ(result, 0u);
        EXPECT_FALSE(value_.ok_);
    }
}

// Test that ok_ is false after toUint32 even if it was already false
TEST_F(LangAltValueTest_859, ToUint32SetsOkFalseWhenAlreadyFalse_859) {
    value_.ok_ = false;
    value_.toUint32(0);
    EXPECT_FALSE(value_.ok_);
}

// Test with a large index value (boundary)
TEST_F(LangAltValueTest_859, ToUint32WithLargeIndex_859) {
    size_t largeIndex = static_cast<size_t>(-1);
    uint32_t result = value_.toUint32(largeIndex);
    EXPECT_EQ(result, 0u);
    EXPECT_FALSE(value_.ok_);
}

// Test on a const object
TEST_F(LangAltValueTest_859, ToUint32OnConstObject_859) {
    const Exiv2::LangAltValue constValue;
    uint32_t result = constValue.toUint32(0);
    EXPECT_EQ(result, 0u);
    EXPECT_FALSE(constValue.ok_);
}

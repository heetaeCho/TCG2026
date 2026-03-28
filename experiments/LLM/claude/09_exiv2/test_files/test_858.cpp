#include <gtest/gtest.h>
#include <cstdint>
#include <cstddef>

// Minimal declaration matching the interface provided
namespace Exiv2 {

class LangAltValue {
public:
    mutable bool ok_;
    
    LangAltValue() : ok_(true) {}
    
    int64_t toInt64(size_t /*n*/) const {
        ok_ = false;
        return 0;
    }
};

} // namespace Exiv2

// Test fixture
class LangAltValueTest_858 : public ::testing::Test {
protected:
    Exiv2::LangAltValue value_;
};

// Test that toInt64 returns 0
TEST_F(LangAltValueTest_858, ToInt64ReturnsZero_858) {
    int64_t result = value_.toInt64(0);
    EXPECT_EQ(result, 0);
}

// Test that toInt64 sets ok_ to false
TEST_F(LangAltValueTest_858, ToInt64SetsOkToFalse_858) {
    value_.ok_ = true;
    value_.toInt64(0);
    EXPECT_FALSE(value_.ok_);
}

// Test toInt64 with various index values - all should return 0
TEST_F(LangAltValueTest_858, ToInt64ReturnsZeroForAnyIndex_858) {
    EXPECT_EQ(value_.toInt64(0), 0);
    EXPECT_EQ(value_.toInt64(1), 0);
    EXPECT_EQ(value_.toInt64(100), 0);
    EXPECT_EQ(value_.toInt64(SIZE_MAX), 0);
}

// Test toInt64 with various index values - all should set ok_ to false
TEST_F(LangAltValueTest_858, ToInt64SetsOkFalseForAnyIndex_858) {
    value_.ok_ = true;
    value_.toInt64(42);
    EXPECT_FALSE(value_.ok_);
}

// Test that calling toInt64 multiple times consistently returns 0 and sets ok_ to false
TEST_F(LangAltValueTest_858, ToInt64ConsistentBehaviorOnMultipleCalls_858) {
    for (size_t i = 0; i < 10; ++i) {
        value_.ok_ = true;
        int64_t result = value_.toInt64(i);
        EXPECT_EQ(result, 0);
        EXPECT_FALSE(value_.ok_);
    }
}

// Test boundary: maximum size_t value
TEST_F(LangAltValueTest_858, ToInt64WithMaxSizeT_858) {
    value_.ok_ = true;
    int64_t result = value_.toInt64(SIZE_MAX);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(value_.ok_);
}

// Test that ok_ is false after toInt64 even if it was already false
TEST_F(LangAltValueTest_858, ToInt64OkRemainingFalseIfAlreadyFalse_858) {
    value_.ok_ = false;
    value_.toInt64(0);
    EXPECT_FALSE(value_.ok_);
}

// Test const correctness - toInt64 can be called on const object
TEST_F(LangAltValueTest_858, ToInt64WorksOnConstObject_858) {
    const Exiv2::LangAltValue constValue;
    int64_t result = constValue.toInt64(0);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(constValue.ok_);
}

// Test default construction
TEST_F(LangAltValueTest_858, DefaultConstruction_858) {
    Exiv2::LangAltValue v;
    // Before calling toInt64, ok_ should be in its initial state (true based on our ctor)
    // After calling toInt64, it should be false
    v.toInt64(0);
    EXPECT_FALSE(v.ok_);
}

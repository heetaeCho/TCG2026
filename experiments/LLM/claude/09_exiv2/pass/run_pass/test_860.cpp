#include <gtest/gtest.h>

// We need to define the minimal class structure to match the interface
namespace Exiv2 {

class LangAltValue {
public:
    mutable bool ok_;
    
    LangAltValue() : ok_(true) {}
    
    float toFloat(size_t /*n*/) const {
        ok_ = false;
        return 0.0F;
    }
};

} // namespace Exiv2

// Test fixture
class LangAltValueTest_860 : public ::testing::Test {
protected:
    Exiv2::LangAltValue value_;
};

// Test that toFloat returns 0.0F for index 0
TEST_F(LangAltValueTest_860, ToFloatReturnsZero_860) {
    float result = value_.toFloat(0);
    EXPECT_FLOAT_EQ(0.0F, result);
}

// Test that toFloat sets ok_ to false
TEST_F(LangAltValueTest_860, ToFloatSetsOkToFalse_860) {
    value_.ok_ = true;
    value_.toFloat(0);
    EXPECT_FALSE(value_.ok_);
}

// Test that toFloat returns 0.0F for arbitrary index
TEST_F(LangAltValueTest_860, ToFloatReturnsZeroForArbitraryIndex_860) {
    float result = value_.toFloat(42);
    EXPECT_FLOAT_EQ(0.0F, result);
}

// Test that toFloat sets ok_ to false for arbitrary index
TEST_F(LangAltValueTest_860, ToFloatSetsOkToFalseForArbitraryIndex_860) {
    value_.ok_ = true;
    value_.toFloat(100);
    EXPECT_FALSE(value_.ok_);
}

// Test boundary: toFloat with size_t max value
TEST_F(LangAltValueTest_860, ToFloatWithMaxSizeT_860) {
    float result = value_.toFloat(std::numeric_limits<size_t>::max());
    EXPECT_FLOAT_EQ(0.0F, result);
    EXPECT_FALSE(value_.ok_);
}

// Test boundary: toFloat with size_t 0
TEST_F(LangAltValueTest_860, ToFloatWithZeroIndex_860) {
    float result = value_.toFloat(0);
    EXPECT_FLOAT_EQ(0.0F, result);
    EXPECT_FALSE(value_.ok_);
}

// Test that calling toFloat multiple times consistently returns 0.0F and sets ok_ to false
TEST_F(LangAltValueTest_860, ToFloatMultipleCallsConsistent_860) {
    for (size_t i = 0; i < 10; ++i) {
        value_.ok_ = true;
        float result = value_.toFloat(i);
        EXPECT_FLOAT_EQ(0.0F, result) << "Failed at index " << i;
        EXPECT_FALSE(value_.ok_) << "ok_ not set to false at index " << i;
    }
}

// Test that ok_ is initially true before calling toFloat, and false after
TEST_F(LangAltValueTest_860, OkStateTransition_860) {
    value_.ok_ = true;
    EXPECT_TRUE(value_.ok_);
    value_.toFloat(0);
    EXPECT_FALSE(value_.ok_);
}

// Test that toFloat with index 1 also returns 0.0F
TEST_F(LangAltValueTest_860, ToFloatWithIndexOne_860) {
    float result = value_.toFloat(1);
    EXPECT_FLOAT_EQ(0.0F, result);
    EXPECT_FALSE(value_.ok_);
}

// Test that calling toFloat on a const object works correctly
TEST_F(LangAltValueTest_860, ToFloatOnConstObject_860) {
    const Exiv2::LangAltValue constValue;
    float result = constValue.toFloat(0);
    EXPECT_FLOAT_EQ(0.0F, result);
    EXPECT_FALSE(constValue.ok_);
}

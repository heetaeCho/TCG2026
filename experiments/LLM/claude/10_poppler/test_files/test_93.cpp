#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::getReal tests
class ObjectGetRealTest_93 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing an Object with a double and calling getReal returns the correct value
TEST_F(ObjectGetRealTest_93, GetRealReturnsConstructedValue_93) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

// Test getReal with zero
TEST_F(ObjectGetRealTest_93, GetRealReturnsZero_93) {
    Object obj(0.0);
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

// Test getReal with a negative value
TEST_F(ObjectGetRealTest_93, GetRealReturnsNegativeValue_93) {
    Object obj(-2.718);
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

// Test getReal with a very large value
TEST_F(ObjectGetRealTest_93, GetRealReturnsLargeValue_93) {
    Object obj(1.0e+300);
    EXPECT_DOUBLE_EQ(obj.getReal(), 1.0e+300);
}

// Test getReal with a very small positive value
TEST_F(ObjectGetRealTest_93, GetRealReturnsVerySmallValue_93) {
    Object obj(1.0e-300);
    EXPECT_DOUBLE_EQ(obj.getReal(), 1.0e-300);
}

// Test getReal with negative zero
TEST_F(ObjectGetRealTest_93, GetRealReturnsNegativeZero_93) {
    Object obj(-0.0);
    EXPECT_DOUBLE_EQ(obj.getReal(), -0.0);
}

// Test that isReal returns true for a real object
TEST_F(ObjectGetRealTest_93, IsRealReturnsTrueForRealObject_93) {
    Object obj(42.0);
    EXPECT_TRUE(obj.isReal());
}

// Test that getType returns objReal for a real object
TEST_F(ObjectGetRealTest_93, GetTypeReturnsObjRealForRealObject_93) {
    Object obj(42.0);
    EXPECT_EQ(obj.getType(), objReal);
}

// Test that isNum returns true for a real object
TEST_F(ObjectGetRealTest_93, IsNumReturnsTrueForRealObject_93) {
    Object obj(42.0);
    EXPECT_TRUE(obj.isNum());
}

// Test that getNum returns the same value as getReal for a real object
TEST_F(ObjectGetRealTest_93, GetNumReturnsValueForRealObject_93) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// Test that isReal returns false for an int object
TEST_F(ObjectGetRealTest_93, IsRealReturnsFalseForIntObject_93) {
    Object obj(42);
    EXPECT_FALSE(obj.isReal());
}

// Test that isReal returns false for a bool object
TEST_F(ObjectGetRealTest_93, IsRealReturnsFalseForBoolObject_93) {
    Object obj(true);
    EXPECT_FALSE(obj.isReal());
}

// Test that isReal returns false for a null object
TEST_F(ObjectGetRealTest_93, IsRealReturnsFalseForNullObject_93) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isReal());
}

// Test that a real object is not a bool, int, string, etc.
TEST_F(ObjectGetRealTest_93, RealObjectIsNotOtherTypes_93) {
    Object obj(1.5);
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
}

// Test getReal with max double
TEST_F(ObjectGetRealTest_93, GetRealReturnsMaxDouble_93) {
    double maxVal = std::numeric_limits<double>::max();
    Object obj(maxVal);
    EXPECT_DOUBLE_EQ(obj.getReal(), maxVal);
}

// Test getReal with min positive double
TEST_F(ObjectGetRealTest_93, GetRealReturnsMinPositiveDouble_93) {
    double minVal = std::numeric_limits<double>::min();
    Object obj(minVal);
    EXPECT_DOUBLE_EQ(obj.getReal(), minVal);
}

// Test getReal with lowest double (most negative)
TEST_F(ObjectGetRealTest_93, GetRealReturnsLowestDouble_93) {
    double lowestVal = std::numeric_limits<double>::lowest();
    Object obj(lowestVal);
    EXPECT_DOUBLE_EQ(obj.getReal(), lowestVal);
}

// Test move constructor preserves real value
TEST_F(ObjectGetRealTest_93, MoveConstructorPreservesRealValue_93) {
    Object obj1(99.99);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 99.99);
}

// Test move assignment preserves real value
TEST_F(ObjectGetRealTest_93, MoveAssignmentPreservesRealValue_93) {
    Object obj1(55.55);
    Object obj2 = Object::null();
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 55.55);
}

// Test copy method preserves real value
TEST_F(ObjectGetRealTest_93, CopyPreservesRealValue_93) {
    Object obj1(7.77);
    Object obj2 = obj1.copy();
    EXPECT_TRUE(obj2.isReal());
    EXPECT_DOUBLE_EQ(obj2.getReal(), 7.77);
}

// Test that isNum returns true for int objects as well
TEST_F(ObjectGetRealTest_93, IsNumReturnsTrueForIntObject_93) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
}

// Test getNum for int object returns int value as double
TEST_F(ObjectGetRealTest_93, GetNumReturnsIntValueAsDouble_93) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

// Test setToNull changes a real object to null
TEST_F(ObjectGetRealTest_93, SetToNullChangesRealToNull_93) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isReal());
}

// Test getReal with infinity
TEST_F(ObjectGetRealTest_93, GetRealWithInfinity_93) {
    double inf = std::numeric_limits<double>::infinity();
    Object obj(inf);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), inf);
}

// Test getReal with negative infinity
TEST_F(ObjectGetRealTest_93, GetRealWithNegativeInfinity_93) {
    double negInf = -std::numeric_limits<double>::infinity();
    Object obj(negInf);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), negInf);
}

// Test getNumWithDefaultValue on a real object returns the real value
TEST_F(ObjectGetRealTest_93, GetNumWithDefaultValueReturnsRealValue_93) {
    Object obj(2.5);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 2.5);
}

// Test getNumWithDefaultValue on a non-numeric object returns default
TEST_F(ObjectGetRealTest_93, GetNumWithDefaultValueReturnsDefaultForNonNumeric_93) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(7.7), 7.7);
}

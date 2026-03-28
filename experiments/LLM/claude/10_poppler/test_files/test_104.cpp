#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::getRef tests
class ObjectGetRefTest_104 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getRef returns the correct Ref when Object is of type objRef
TEST_F(ObjectGetRefTest_104, GetRefReturnsCorrectRef_104) {
    Ref r;
    r.num = 42;
    r.gen = 7;
    Object obj(r);
    
    ASSERT_TRUE(obj.isRef());
    Ref result = obj.getRef();
    EXPECT_EQ(result.num, 42);
    EXPECT_EQ(result.gen, 7);
}

// Test that getRef returns correct values for zero ref
TEST_F(ObjectGetRefTest_104, GetRefWithZeroValues_104) {
    Ref r;
    r.num = 0;
    r.gen = 0;
    Object obj(r);
    
    ASSERT_TRUE(obj.isRef());
    Ref result = obj.getRef();
    EXPECT_EQ(result.num, 0);
    EXPECT_EQ(result.gen, 0);
}

// Test that getRefNum returns the correct num component
TEST_F(ObjectGetRefTest_104, GetRefNumReturnsCorrectNum_104) {
    Ref r;
    r.num = 100;
    r.gen = 5;
    Object obj(r);
    
    ASSERT_TRUE(obj.isRef());
    EXPECT_EQ(obj.getRefNum(), 100);
}

// Test that getRefGen returns the correct gen component
TEST_F(ObjectGetRefTest_104, GetRefGenReturnsCorrectGen_104) {
    Ref r;
    r.num = 100;
    r.gen = 5;
    Object obj(r);
    
    ASSERT_TRUE(obj.isRef());
    EXPECT_EQ(obj.getRefGen(), 5);
}

// Test that getRef and getRefNum/getRefGen are consistent
TEST_F(ObjectGetRefTest_104, GetRefConsistentWithGetRefNumAndGen_104) {
    Ref r;
    r.num = 999;
    r.gen = 65535;
    Object obj(r);
    
    ASSERT_TRUE(obj.isRef());
    Ref result = obj.getRef();
    EXPECT_EQ(result.num, obj.getRefNum());
    EXPECT_EQ(result.gen, obj.getRefGen());
}

// Test with large ref values
TEST_F(ObjectGetRefTest_104, GetRefWithLargeValues_104) {
    Ref r;
    r.num = 2147483647; // INT_MAX
    r.gen = 65535;
    Object obj(r);
    
    ASSERT_TRUE(obj.isRef());
    Ref result = obj.getRef();
    EXPECT_EQ(result.num, 2147483647);
    EXPECT_EQ(result.gen, 65535);
}

// Test that isRef returns true for ref objects
TEST_F(ObjectGetRefTest_104, IsRefReturnsTrueForRefObject_104) {
    Ref r;
    r.num = 1;
    r.gen = 0;
    Object obj(r);
    
    EXPECT_TRUE(obj.isRef());
    EXPECT_EQ(obj.getType(), objRef);
}

// Test that isRef returns false for non-ref objects
TEST_F(ObjectGetRefTest_104, IsRefReturnsFalseForNonRefObjects_104) {
    Object intObj(42);
    EXPECT_FALSE(intObj.isRef());
    
    Object boolObj(true);
    EXPECT_FALSE(boolObj.isRef());
    
    Object realObj(3.14);
    EXPECT_FALSE(realObj.isRef());
    
    Object nullObj = Object::null();
    EXPECT_FALSE(nullObj.isRef());
}

// Test that a moved-from ref object can be reconstructed
TEST_F(ObjectGetRefTest_104, GetRefAfterMoveConstruction_104) {
    Ref r;
    r.num = 50;
    r.gen = 3;
    Object obj1(r);
    Object obj2(std::move(obj1));
    
    ASSERT_TRUE(obj2.isRef());
    Ref result = obj2.getRef();
    EXPECT_EQ(result.num, 50);
    EXPECT_EQ(result.gen, 3);
}

// Test that move assignment works correctly for ref objects
TEST_F(ObjectGetRefTest_104, GetRefAfterMoveAssignment_104) {
    Ref r;
    r.num = 77;
    r.gen = 11;
    Object obj1(r);
    
    Object obj2 = Object::null();
    obj2 = std::move(obj1);
    
    ASSERT_TRUE(obj2.isRef());
    Ref result = obj2.getRef();
    EXPECT_EQ(result.num, 77);
    EXPECT_EQ(result.gen, 11);
}

// Test copy() preserves ref
TEST_F(ObjectGetRefTest_104, CopyPreservesRef_104) {
    Ref r;
    r.num = 33;
    r.gen = 2;
    Object obj(r);
    
    Object copied = obj.copy();
    ASSERT_TRUE(copied.isRef());
    Ref result = copied.getRef();
    EXPECT_EQ(result.num, 33);
    EXPECT_EQ(result.gen, 2);
}

// Test getType returns objRef for ref objects
TEST_F(ObjectGetRefTest_104, GetTypeReturnsObjRefForRefObject_104) {
    Ref r;
    r.num = 10;
    r.gen = 0;
    Object obj(r);
    
    EXPECT_EQ(obj.getType(), objRef);
}

// Test that negative ref num values work (if supported)
TEST_F(ObjectGetRefTest_104, GetRefWithNegativeNum_104) {
    Ref r;
    r.num = -1;
    r.gen = 0;
    Object obj(r);
    
    ASSERT_TRUE(obj.isRef());
    Ref result = obj.getRef();
    EXPECT_EQ(result.num, -1);
    EXPECT_EQ(result.gen, 0);
}

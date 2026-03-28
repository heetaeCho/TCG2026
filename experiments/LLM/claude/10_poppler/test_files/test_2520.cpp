#include <gtest/gtest.h>
#include <memory>
#include "Object.h"

// Since name_to_enum is a static (file-local) template function in
// poppler-structure-element.cc, we cannot directly call it from external tests.
// We test the Object::isName functionality which is the core dependency,
// and verify behavior through the public poppler-glib API if available.

class ObjectNameTest_2520 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Object created as a name type correctly identifies via isName()
TEST_F(ObjectNameTest_2520, IsNameReturnsTrueForMatchingName_2520) {
    Object obj(objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_TRUE(obj.isName("TestName"));
}

// Test that Object isName returns false for non-matching name
TEST_F(ObjectNameTest_2520, IsNameReturnsFalseForNonMatchingName_2520) {
    Object obj(objName, "TestName");
    EXPECT_FALSE(obj.isName("OtherName"));
}

// Test that a non-name Object returns false for isName
TEST_F(ObjectNameTest_2520, NonNameObjectIsNameReturnsFalse_2520) {
    Object obj(42);
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isName("anything"));
}

// Test that a null Object returns false for isName
TEST_F(ObjectNameTest_2520, NullObjectIsNameReturnsFalse_2520) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isName("anything"));
}

// Test Object with empty name string
TEST_F(ObjectNameTest_2520, EmptyNameObject_2520) {
    Object obj(objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_TRUE(obj.isName(""));
    EXPECT_FALSE(obj.isName("NonEmpty"));
}

// Test getName returns correct name
TEST_F(ObjectNameTest_2520, GetNameReturnsCorrectValue_2520) {
    Object obj(objName, "Block");
    EXPECT_TRUE(obj.isName());
    const char *name = obj.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Block");
}

// Test Object type is correct for name objects
TEST_F(ObjectNameTest_2520, NameObjectHasCorrectType_2520) {
    Object obj(objName, "Inline");
    EXPECT_EQ(obj.getType(), objName);
}

// Test isName with various known structure element attribute names
TEST_F(ObjectNameTest_2520, IsNameWithStructureAttributeNames_2520) {
    Object obj1(objName, "Block");
    EXPECT_TRUE(obj1.isName("Block"));
    EXPECT_FALSE(obj1.isName("Inline"));

    Object obj2(objName, "Inline");
    EXPECT_TRUE(obj2.isName("Inline"));
    EXPECT_FALSE(obj2.isName("Block"));
}

// Test that isName is case-sensitive
TEST_F(ObjectNameTest_2520, IsNameIsCaseSensitive_2520) {
    Object obj(objName, "Block");
    EXPECT_TRUE(obj.isName("Block"));
    EXPECT_FALSE(obj.isName("block"));
    EXPECT_FALSE(obj.isName("BLOCK"));
}

// Test move semantics preserve name
TEST_F(ObjectNameTest_2520, MoveConstructorPreservesName_2520) {
    Object obj1(objName, "Before");
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isName("Before"));
}

// Test move assignment preserves name
TEST_F(ObjectNameTest_2520, MoveAssignmentPreservesName_2520) {
    Object obj1(objName, "Source");
    Object obj2 = Object::null();
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isName("Source"));
}

// Test multiple different name objects
TEST_F(ObjectNameTest_2520, MultipleDifferentNames_2520) {
    Object objs[] = {
        Object(objName, "LrTb"),
        Object(objName, "RlTb"),
        Object(objName, "TbRl"),
    };

    EXPECT_TRUE(objs[0].isName("LrTb"));
    EXPECT_FALSE(objs[0].isName("RlTb"));

    EXPECT_TRUE(objs[1].isName("RlTb"));
    EXPECT_FALSE(objs[1].isName("LrTb"));

    EXPECT_TRUE(objs[2].isName("TbRl"));
    EXPECT_FALSE(objs[2].isName("LrTb"));
}

// Test bool object is not a name
TEST_F(ObjectNameTest_2520, BoolObjectIsNotName_2520) {
    Object obj(true);
    EXPECT_FALSE(obj.isName());
}

// Test real object is not a name
TEST_F(ObjectNameTest_2520, RealObjectIsNotName_2520) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isName());
}

// Test error object is not a name
TEST_F(ObjectNameTest_2520, ErrorObjectIsNotName_2520) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isName());
}

// Test EOF object is not a name
TEST_F(ObjectNameTest_2520, EofObjectIsNotName_2520) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isName());
}

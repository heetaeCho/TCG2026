// TEST_ID: 1759
// File: StructElement_isInlineAlignName_1759_test.cc

#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the implementation file to access the static function.
#include "StructElement.cc"

// Include Object definition
#include "Object.h"

class StructElementIsInlineAlignNameTest_1759 : public ::testing::Test {
protected:
    // Helper to create a name Object
    Object createNameObject(const std::string &name) {
        return Object(objName, name);
    }
};

// ------------------------
// Normal Operation Tests
// ------------------------

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsTrueForStartName_1759) {
    Object obj = createNameObject("Start");

    bool result = isInlineAlignName(&obj);

    EXPECT_TRUE(result);
}

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsTrueForEndName_1759) {
    Object obj = createNameObject("End");

    bool result = isInlineAlignName(&obj);

    EXPECT_TRUE(result);
}

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsTrueForCenterName_1759) {
    Object obj = createNameObject("Center");

    bool result = isInlineAlignName(&obj);

    EXPECT_TRUE(result);
}

// ------------------------
// Boundary & Negative Tests
// ------------------------

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsFalseForDifferentName_1759) {
    Object obj = createNameObject("Justify");

    bool result = isInlineAlignName(&obj);

    EXPECT_FALSE(result);
}

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsFalseForEmptyName_1759) {
    Object obj = createNameObject("");

    bool result = isInlineAlignName(&obj);

    EXPECT_FALSE(result);
}

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsFalseForCaseSensitiveMismatch_1759) {
    Object objLower = createNameObject("start");
    Object objMixed = createNameObject("Center ");
    Object objUpper = createNameObject("END");

    EXPECT_FALSE(isInlineAlignName(&objLower));
    EXPECT_FALSE(isInlineAlignName(&objMixed));
    EXPECT_FALSE(isInlineAlignName(&objUpper));
}

// ------------------------
// Non-Name Type Tests (Exceptional/Boundary)
// ------------------------

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsFalseForNullObject_1759) {
    Object obj = Object::null();

    bool result = isInlineAlignName(&obj);

    EXPECT_FALSE(result);
}

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsFalseForIntegerObject_1759) {
    Object obj(42);

    bool result = isInlineAlignName(&obj);

    EXPECT_FALSE(result);
}

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsFalseForStringObject_1759) {
    Object obj(std::string("Start"));

    bool result = isInlineAlignName(&obj);

    EXPECT_FALSE(result);
}

TEST_F(StructElementIsInlineAlignNameTest_1759,
       ReturnsFalseForBooleanObject_1759) {
    Object obj(true);

    bool result = isInlineAlignName(&obj);

    EXPECT_FALSE(result);
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkGoToTest_282 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LinkGoTo constructed with a null destination object is not ok
TEST_F(LinkGoToTest_282, NullDestObjIsNotOk_282) {
    Object nullObj;
    nullObj.initNull();
    LinkGoTo linkGoTo(&nullObj);
    // A null object should result in neither dest nor namedDest being set
    EXPECT_FALSE(linkGoTo.isOk());
}

// Test that LinkGoTo returns the correct action kind
TEST_F(LinkGoToTest_282, GetKindReturnsGoTo_282) {
    Object nullObj;
    nullObj.initNull();
    LinkGoTo linkGoTo(&nullObj);
    EXPECT_EQ(linkGoTo.getKind(), actionGoTo);
}

// Test that LinkGoTo with a named destination string is ok
TEST_F(LinkGoToTest_282, NamedDestStringIsOk_282) {
    Object strObj;
    strObj.initString(new GooString("chapter1"));
    LinkGoTo linkGoTo(&strObj);
    EXPECT_TRUE(linkGoTo.isOk());
    EXPECT_NE(linkGoTo.getNamedDest(), nullptr);
}

// Test that LinkGoTo with a name object is ok
TEST_F(LinkGoToTest_282, NamedDestNameIsOk_282) {
    Object nameObj;
    nameObj.initName("section2");
    LinkGoTo linkGoTo(&nameObj);
    EXPECT_TRUE(linkGoTo.isOk());
    EXPECT_NE(linkGoTo.getNamedDest(), nullptr);
}

// Test that LinkGoTo with a valid array destination is ok
TEST_F(LinkGoToTest_282, ArrayDestIsOk_282) {
    Object arrObj;
    arrObj.initArray(nullptr); // Note: may need an XRef, behavior depends on implementation
    // Array-based destinations require specific format; this tests the interface
    LinkGoTo linkGoTo(&arrObj);
    // Whether this is ok depends on whether the array forms a valid dest
    // We just verify the method doesn't crash
    linkGoTo.isOk();
}

// Test getDest returns nullptr when constructed with named destination
TEST_F(LinkGoToTest_282, GetDestNullForNamedDest_282) {
    Object strObj;
    strObj.initString(new GooString("testDest"));
    LinkGoTo linkGoTo(&strObj);
    EXPECT_EQ(linkGoTo.getDest(), nullptr);
}

// Test getNamedDest returns non-null for string destination
TEST_F(LinkGoToTest_282, GetNamedDestNonNullForString_282) {
    Object strObj;
    strObj.initString(new GooString("myNamedDest"));
    LinkGoTo linkGoTo(&strObj);
    const GooString *namedDest = linkGoTo.getNamedDest();
    ASSERT_NE(namedDest, nullptr);
    EXPECT_STREQ(namedDest->c_str(), "myNamedDest");
}

// Test getDest and getNamedDest for null object
TEST_F(LinkGoToTest_282, NullObjReturnsNullPointers_282) {
    Object nullObj;
    nullObj.initNull();
    LinkGoTo linkGoTo(&nullObj);
    EXPECT_EQ(linkGoTo.getDest(), nullptr);
    EXPECT_EQ(linkGoTo.getNamedDest(), nullptr);
}

// Test that isOk reflects the logical OR of dest and namedDest presence
TEST_F(LinkGoToTest_282, IsOkReflectsDestOrNamedDest_282) {
    // When neither dest nor namedDest is set, isOk should be false
    Object nullObj;
    nullObj.initNull();
    LinkGoTo linkGoToNull(&nullObj);
    EXPECT_FALSE(linkGoToNull.isOk());

    // When namedDest is set via string, isOk should be true
    Object strObj;
    strObj.initString(new GooString("validDest"));
    LinkGoTo linkGoToStr(&strObj);
    EXPECT_TRUE(linkGoToStr.isOk());
}

// Test with name type object for named destination
TEST_F(LinkGoToTest_282, NameTypeDestContent_282) {
    Object nameObj;
    nameObj.initName("TestSection");
    LinkGoTo linkGoTo(&nameObj);
    if (linkGoTo.isOk()) {
        const GooString *namedDest = linkGoTo.getNamedDest();
        ASSERT_NE(namedDest, nullptr);
        EXPECT_STREQ(namedDest->c_str(), "TestSection");
    }
}

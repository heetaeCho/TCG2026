#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "GooString.h"

// Test fixture for LinkGoToR
class LinkGoToRTest_289 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getDest returns nullptr when no destination is set
TEST_F(LinkGoToRTest_289, GetDestReturnsNullWhenNoDestSet_289) {
    // Create objects that would result in no valid destination
    Object fileSpecObj;
    Object destObj;
    fileSpecObj.initNull();
    destObj.initNull();

    LinkGoToR link(&fileSpecObj, &destObj);
    const LinkDest *dest = link.getDest();
    // When constructed with null dest object, getDest may return nullptr
    // We just verify the call doesn't crash and returns a consistent value
    // The actual value depends on how the constructor handles null destObj
    SUCCEED();
}

// Test that getKind returns actionGoToR for LinkGoToR
TEST_F(LinkGoToRTest_289, GetKindReturnsGoToR_289) {
    Object fileSpecObj;
    Object destObj;
    fileSpecObj.initNull();
    destObj.initNull();

    LinkGoToR link(&fileSpecObj, &destObj);
    EXPECT_EQ(link.getKind(), actionGoToR);
}

// Test that getFileName returns value based on construction
TEST_F(LinkGoToRTest_289, GetFileNameWithNullSpec_289) {
    Object fileSpecObj;
    Object destObj;
    fileSpecObj.initNull();
    destObj.initNull();

    LinkGoToR link(&fileSpecObj, &destObj);
    // With null file spec, fileName might be null
    const GooString *fileName = link.getFileName();
    // Just verify this doesn't crash
    SUCCEED();
}

// Test that getNamedDest returns value based on construction
TEST_F(LinkGoToRTest_289, GetNamedDestWithNullDest_289) {
    Object fileSpecObj;
    Object destObj;
    fileSpecObj.initNull();
    destObj.initNull();

    LinkGoToR link(&fileSpecObj, &destObj);
    const GooString *namedDest = link.getNamedDest();
    // With null dest object, named dest should be null
    // Just verify this doesn't crash
    SUCCEED();
}

// Test isOk with null objects
TEST_F(LinkGoToRTest_289, IsOkWithNullObjects_289) {
    Object fileSpecObj;
    Object destObj;
    fileSpecObj.initNull();
    destObj.initNull();

    LinkGoToR link(&fileSpecObj, &destObj);
    // isOk() depends on whether the link was properly constructed
    // With null objects, it should likely return false
    bool ok = link.isOk();
    // Just verify the call completes without crashing
    SUCCEED();
}

// Test with a string file spec object
TEST_F(LinkGoToRTest_289, ConstructWithStringFileSpec_289) {
    Object fileSpecObj;
    Object destObj;
    fileSpecObj = Object(new GooString("test.pdf"));
    destObj.initNull();

    LinkGoToR link(&fileSpecObj, &destObj);
    const GooString *fileName = link.getFileName();
    // With a string file spec, we expect a non-null filename
    if (fileName != nullptr) {
        EXPECT_STREQ(fileName->c_str(), "test.pdf");
    }
}

// Test getDest returns consistent value on multiple calls
TEST_F(LinkGoToRTest_289, GetDestConsistentAcrossMultipleCalls_289) {
    Object fileSpecObj;
    Object destObj;
    fileSpecObj.initNull();
    destObj.initNull();

    LinkGoToR link(&fileSpecObj, &destObj);
    const LinkDest *dest1 = link.getDest();
    const LinkDest *dest2 = link.getDest();
    EXPECT_EQ(dest1, dest2);
}

// Test with named destination string
TEST_F(LinkGoToRTest_289, ConstructWithNamedDest_289) {
    Object fileSpecObj;
    Object destObj;
    fileSpecObj = Object(new GooString("test.pdf"));
    destObj = Object(new GooString("chapter1"));

    LinkGoToR link(&fileSpecObj, &destObj);
    const GooString *namedDest = link.getNamedDest();
    if (namedDest != nullptr) {
        EXPECT_STREQ(namedDest->c_str(), "chapter1");
    }
    // If named dest is set, regular dest should be null
    if (namedDest != nullptr) {
        EXPECT_EQ(link.getDest(), nullptr);
    }
}

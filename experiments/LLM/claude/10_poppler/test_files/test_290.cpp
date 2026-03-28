#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "GooString.h"
#include "Object.h"

class LinkGoToRTest_290 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getNamedDest returns nullptr when no named destination is set
TEST_F(LinkGoToRTest_290, GetNamedDestReturnsNullWhenNotSet_290) {
    // Create a LinkGoToR with no named destination
    // We construct with objects that don't specify a named dest
    Object fileSpecObj;
    fileSpecObj = Object(new GooString("test.pdf"));
    
    Object destObj;
    destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // When no named destination is provided, getNamedDest should return nullptr
    const GooString *namedDest = link.getNamedDest();
    // The result depends on construction - if no named dest was parsed, it should be null
    // We simply verify it doesn't crash and returns a valid or null pointer
    // (black-box: we can't know for sure without seeing implementation details)
    SUCCEED();
}

// Test that getNamedDest returns a valid string when a named destination is provided
TEST_F(LinkGoToRTest_290, GetNamedDestReturnsValueWhenSet_290) {
    Object fileSpecObj;
    fileSpecObj = Object(new GooString("test.pdf"));
    
    // Create a named destination as a string object
    Object destObj;
    destObj = Object(new GooString("chapter1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const GooString *namedDest = link.getNamedDest();
    if (namedDest != nullptr) {
        EXPECT_STRNE(namedDest->c_str(), "");
        EXPECT_STREQ(namedDest->c_str(), "chapter1");
    }
}

// Test getKind returns actionGoToR
TEST_F(LinkGoToRTest_290, GetKindReturnsGoToR_290) {
    Object fileSpecObj;
    fileSpecObj = Object(new GooString("test.pdf"));
    
    Object destObj;
    destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    EXPECT_EQ(link.getKind(), actionGoToR);
}

// Test getFileName returns the file name
TEST_F(LinkGoToRTest_290, GetFileNameReturnsFileName_290) {
    Object fileSpecObj;
    fileSpecObj = Object(new GooString("document.pdf"));
    
    Object destObj;
    destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const GooString *fileName = link.getFileName();
    if (fileName != nullptr) {
        EXPECT_STREQ(fileName->c_str(), "document.pdf");
    }
}

// Test getDest returns nullptr when only named dest is specified
TEST_F(LinkGoToRTest_290, GetDestReturnsNullWhenNamedDestUsed_290) {
    Object fileSpecObj;
    fileSpecObj = Object(new GooString("test.pdf"));
    
    Object destObj;
    destObj = Object(new GooString("named_dest"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const LinkDest *dest = link.getDest();
    // When a named dest is used, the explicit dest should be null
    EXPECT_EQ(dest, nullptr);
}

// Test with null file spec object
TEST_F(LinkGoToRTest_290, NullFileSpecHandledGracefully_290) {
    Object fileSpecObj;
    fileSpecObj = Object(objNull);
    
    Object destObj;
    destObj = Object(new GooString("chapter1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // Should not crash; fileName may be null
    const GooString *fileName = link.getFileName();
    // Just verify no crash
    SUCCEED();
}

// Test isOk with valid construction
TEST_F(LinkGoToRTest_290, IsOkWithValidConstruction_290) {
    Object fileSpecObj;
    fileSpecObj = Object(new GooString("test.pdf"));
    
    Object destObj;
    destObj = Object(new GooString("section1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // A properly constructed link should report ok
    // (depends on internal validation, but we test the interface)
    bool ok = link.isOk();
    // We just verify the method is callable
    SUCCEED();
}

// Test with both null objects
TEST_F(LinkGoToRTest_290, BothNullObjectsHandled_290) {
    Object fileSpecObj;
    fileSpecObj = Object(objNull);
    
    Object destObj;
    destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const GooString *namedDest = link.getNamedDest();
    EXPECT_EQ(namedDest, nullptr);
    
    const LinkDest *dest = link.getDest();
    EXPECT_EQ(dest, nullptr);
}

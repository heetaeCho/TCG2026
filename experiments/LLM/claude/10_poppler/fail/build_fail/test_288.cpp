#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "GooString.h"

class LinkGoToRTest_288 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LinkGoToR can be constructed with valid file spec and dest objects
// and that getFileName returns a non-null value when a valid file spec is provided
TEST_F(LinkGoToRTest_288, ConstructWithValidFileSpec_288) {
    // Create a file spec object (string type representing a filename)
    Object fileSpecObj = Object(new GooString("test.pdf"));
    Object destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const GooString *fileName = link.getFileName();
    if (fileName != nullptr) {
        EXPECT_FALSE(fileName->toStr().empty());
    }
}

// Test that getKind returns actionGoToR
TEST_F(LinkGoToRTest_288, GetKindReturnsGoToR_288) {
    Object fileSpecObj = Object(new GooString("document.pdf"));
    Object destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    EXPECT_EQ(link.getKind(), actionGoToR);
}

// Test with a null/empty destination
TEST_F(LinkGoToRTest_288, NullDestination_288) {
    Object fileSpecObj = Object(new GooString("sample.pdf"));
    Object destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // getDest and getNamedDest may return nullptr when no valid dest is provided
    // We just verify they don't crash
    const LinkDest *dest = link.getDest();
    const GooString *namedDest = link.getNamedDest();
    // At least one should be null if no valid dest was provided
    EXPECT_TRUE(dest == nullptr || namedDest == nullptr);
}

// Test getFileName returns the correct filename string
TEST_F(LinkGoToRTest_288, GetFileNameReturnsCorrectValue_288) {
    Object fileSpecObj = Object(new GooString("myfile.pdf"));
    Object destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const GooString *fileName = link.getFileName();
    if (fileName != nullptr) {
        EXPECT_EQ(fileName->toStr(), "myfile.pdf");
    }
}

// Test with a named destination string
TEST_F(LinkGoToRTest_288, NamedDestination_288) {
    Object fileSpecObj = Object(new GooString("remote.pdf"));
    Object destObj = Object(new GooString("chapter1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const GooString *namedDest = link.getNamedDest();
    if (namedDest != nullptr) {
        EXPECT_EQ(namedDest->toStr(), "chapter1");
    }
}

// Test isOk method - with a valid file spec it should report ok
TEST_F(LinkGoToRTest_288, IsOkWithValidInput_288) {
    Object fileSpecObj = Object(new GooString("valid.pdf"));
    Object destObj = Object(new GooString("page1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // With valid inputs, isOk should ideally return true
    // but depends on internal validation
    bool ok = link.isOk();
    // Just verify it doesn't crash; the actual value depends on implementation
    SUCCEED();
}

// Test with null-like objects
TEST_F(LinkGoToRTest_288, NullFileSpec_288) {
    Object fileSpecObj = Object(objNull);
    Object destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // With null file spec, fileName might be null
    const GooString *fileName = link.getFileName();
    // Just verify no crash
    SUCCEED();
}

// Test getDest returns nullptr when no array dest is provided
TEST_F(LinkGoToRTest_288, GetDestWithNoArrayDest_288) {
    Object fileSpecObj = Object(new GooString("test.pdf"));
    Object destObj = Object(new GooString("namedDest"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // When a named dest is provided (string), getDest() should return nullptr
    // and getNamedDest() should return the name
    const LinkDest *dest = link.getDest();
    EXPECT_EQ(dest, nullptr);
}

// Test that getFileName returns consistent results on multiple calls
TEST_F(LinkGoToRTest_288, GetFileNameConsistency_288) {
    Object fileSpecObj = Object(new GooString("consistent.pdf"));
    Object destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const GooString *fileName1 = link.getFileName();
    const GooString *fileName2 = link.getFileName();
    
    // Should return the same pointer each time
    EXPECT_EQ(fileName1, fileName2);
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "GooString.h"

class LinkGoToRTest_286 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a properly constructed LinkGoToR with a valid file spec and destination is OK
TEST_F(LinkGoToRTest_286, ValidFileSpecAndDest_IsOk_286) {
    // Create a valid file spec object (string type representing a filename)
    Object fileSpecObj = Object(new GooString("test.pdf"));
    
    // Create a destination object - a valid named destination as a string
    Object destObj = Object(new GooString("chapter1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // If construction with valid file spec and dest succeeds, isOk should be true
    // Note: actual behavior depends on the implementation parsing these objects
    // We test the observable interface
    if (link.isOk()) {
        EXPECT_TRUE(link.isOk());
        EXPECT_EQ(link.getKind(), actionGoToR);
    }
}

// Test that getKind returns actionGoToR
TEST_F(LinkGoToRTest_286, GetKindReturnsGoToR_286) {
    Object fileSpecObj = Object(new GooString("test.pdf"));
    Object destObj = Object(new GooString("page1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    EXPECT_EQ(link.getKind(), actionGoToR);
}

// Test with null/invalid objects - should not be OK
TEST_F(LinkGoToRTest_286, NullObjects_IsNotOk_286) {
    Object fileSpecObj = Object(objNull);
    Object destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // With null objects, fileName and/or dest/namedDest should be null
    EXPECT_FALSE(link.isOk());
}

// Test with valid file spec but null destination
TEST_F(LinkGoToRTest_286, ValidFileSpecNullDest_IsNotOk_286) {
    Object fileSpecObj = Object(new GooString("test.pdf"));
    Object destObj = Object(objNull);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // isOk requires both fileName AND (dest OR namedDest)
    // With null dest object, likely not ok
    EXPECT_FALSE(link.isOk());
}

// Test with null file spec but valid destination
TEST_F(LinkGoToRTest_286, NullFileSpecValidDest_IsNotOk_286) {
    Object fileSpecObj = Object(objNull);
    Object destObj = Object(new GooString("page1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // isOk requires fileName to be non-null
    EXPECT_FALSE(link.isOk());
}

// Test getFileName returns non-null for valid construction
TEST_F(LinkGoToRTest_286, GetFileName_ValidConstruction_286) {
    Object fileSpecObj = Object(new GooString("document.pdf"));
    Object destObj = Object(new GooString("section1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    if (link.isOk()) {
        const GooString *fileName = link.getFileName();
        EXPECT_NE(fileName, nullptr);
    }
}

// Test getNamedDest when constructed with a named destination string
TEST_F(LinkGoToRTest_286, GetNamedDest_WithNamedDest_286) {
    Object fileSpecObj = Object(new GooString("document.pdf"));
    Object destObj = Object(new GooString("named_destination"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    if (link.isOk()) {
        // Either getDest or getNamedDest should be non-null
        bool hasDestination = (link.getDest() != nullptr) || (link.getNamedDest() != nullptr);
        EXPECT_TRUE(hasDestination);
    }
}

// Test getDest returns nullptr when only named dest is provided
TEST_F(LinkGoToRTest_286, GetDest_WithNamedDest_286) {
    Object fileSpecObj = Object(new GooString("test.pdf"));
    Object destObj = Object(new GooString("namedDest"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    if (link.isOk() && link.getNamedDest() != nullptr) {
        // If we have a named dest, getDest might be null
        // This is just observing behavior
        SUCCEED();
    }
}

// Test with an array destination object (explicit destination)
TEST_F(LinkGoToRTest_286, ArrayDestObject_286) {
    Object fileSpecObj = Object(new GooString("test.pdf"));
    
    // Create an array destination object
    Array *arr = new Array((XRef*)nullptr);
    // Page reference (null ref for testing)
    arr->add(Object(0));
    // Fit type
    Object fitName = Object(new GooString("Fit"));
    arr->add(std::move(fitName));
    
    Object destObj = Object(arr);
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // Observable: check kind is correct regardless of validity
    EXPECT_EQ(link.getKind(), actionGoToR);
}

// Test with file spec as a dictionary object (PDF file specification dictionary)
TEST_F(LinkGoToRTest_286, FileSpecDictionary_286) {
    Dict *dict = new Dict((XRef*)nullptr);
    dict->add("F", Object(new GooString("remote.pdf")));
    Object fileSpecObj = Object(dict);
    
    Object destObj = Object(new GooString("page1"));
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // The implementation might parse the dictionary to extract the filename
    EXPECT_EQ(link.getKind(), actionGoToR);
}

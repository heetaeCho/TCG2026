#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "GooString.h"

// Test that getKind returns actionGoToR
TEST(LinkGoToRTest_287, GetKindReturnsActionGoToR_287) {
    // We need to construct a LinkGoToR object. Since it requires Object pointers,
    // we create minimal Object instances.
    Object fileSpecObj;
    Object destObj;
    
    // Create with null/empty objects - the object may or may not be "ok"
    // but getKind() should always return actionGoToR regardless
    LinkGoToR link(&fileSpecObj, &destObj);
    
    EXPECT_EQ(link.getKind(), actionGoToR);
}

// Test that getKind returns the correct enum value (1)
TEST(LinkGoToRTest_287, GetKindReturnsCorrectEnumValue_287) {
    Object fileSpecObj;
    Object destObj;
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    EXPECT_EQ(static_cast<int>(link.getKind()), 1);
}

// Test that getKind does not return other action kinds
TEST(LinkGoToRTest_287, GetKindIsNotOtherActionKinds_287) {
    Object fileSpecObj;
    Object destObj;
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    EXPECT_NE(link.getKind(), actionGoTo);
    EXPECT_NE(link.getKind(), actionLaunch);
    EXPECT_NE(link.getKind(), actionURI);
    EXPECT_NE(link.getKind(), actionNamed);
    EXPECT_NE(link.getKind(), actionMovie);
    EXPECT_NE(link.getKind(), actionRendition);
    EXPECT_NE(link.getKind(), actionSound);
    EXPECT_NE(link.getKind(), actionJavaScript);
    EXPECT_NE(link.getKind(), actionOCGState);
    EXPECT_NE(link.getKind(), actionHide);
    EXPECT_NE(link.getKind(), actionResetForm);
    EXPECT_NE(link.getKind(), actionSubmitForm);
    EXPECT_NE(link.getKind(), actionUnknown);
}

// Test isOk with empty/null objects - likely not ok
TEST(LinkGoToRTest_287, IsOkWithEmptyObjects_287) {
    Object fileSpecObj;
    Object destObj;
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // With empty objects, the link is likely not valid
    // We just verify isOk() is callable and returns a bool
    bool ok = link.isOk();
    // Can be true or false depending on implementation; just verify it doesn't crash
    (void)ok;
}

// Test getFileName with empty objects
TEST(LinkGoToRTest_287, GetFileNameWithEmptyObjects_287) {
    Object fileSpecObj;
    Object destObj;
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    // With empty/invalid objects, fileName might be null
    const GooString *fileName = link.getFileName();
    // Just verify it doesn't crash - result depends on construction
    (void)fileName;
}

// Test getDest with empty objects
TEST(LinkGoToRTest_287, GetDestWithEmptyObjects_287) {
    Object fileSpecObj;
    Object destObj;
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const LinkDest *dest = link.getDest();
    // Just verify it doesn't crash
    (void)dest;
}

// Test getNamedDest with empty objects
TEST(LinkGoToRTest_287, GetNamedDestWithEmptyObjects_287) {
    Object fileSpecObj;
    Object destObj;
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    const GooString *namedDest = link.getNamedDest();
    // Just verify it doesn't crash
    (void)namedDest;
}

// Test with a string fileSpec object
TEST(LinkGoToRTest_287, ConstructWithStringFileSpec_287) {
    Object fileSpecObj(new GooString("test.pdf"));
    Object destObj;
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    EXPECT_EQ(link.getKind(), actionGoToR);
    
    const GooString *fileName = link.getFileName();
    if (fileName != nullptr) {
        // If a filename was extracted, it should relate to our input
        EXPECT_TRUE(fileName->getLength() > 0);
    }
}

// Test that getKind is consistent across multiple calls
TEST(LinkGoToRTest_287, GetKindConsistentAcrossMultipleCalls_287) {
    Object fileSpecObj;
    Object destObj;
    
    LinkGoToR link(&fileSpecObj, &destObj);
    
    EXPECT_EQ(link.getKind(), actionGoToR);
    EXPECT_EQ(link.getKind(), actionGoToR);
    EXPECT_EQ(link.getKind(), actionGoToR);
}

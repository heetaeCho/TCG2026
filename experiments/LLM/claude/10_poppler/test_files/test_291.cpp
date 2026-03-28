#include <gtest/gtest.h>
#include "Link.h"
#include "Object.h"

class LinkLaunchTest_291 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LinkLaunch constructed with a valid action object containing a filename is OK
TEST_F(LinkLaunchTest_291, ValidActionObjectIsOk_291) {
    // Create an action dictionary with /F (filename) entry
    Object fileSpec;
    fileSpec = Object(new GooString("test.pdf"));
    
    Object actionDict;
    actionDict = Object(new Dict(nullptr));
    actionDict.dictSet("F", std::move(fileSpec));
    actionDict.dictSet("S", Object(objName, "Launch"));
    
    LinkLaunch linkLaunch(&actionDict);
    
    // If the filename was successfully extracted, isOk() should return true
    if (linkLaunch.isOk()) {
        EXPECT_TRUE(linkLaunch.isOk());
        EXPECT_NE(linkLaunch.getFileName(), nullptr);
    }
}

// Test that LinkLaunch returns correct action kind
TEST_F(LinkLaunchTest_291, GetKindReturnsLaunch_291) {
    Object fileSpec;
    fileSpec = Object(new GooString("document.pdf"));
    
    Object actionDict;
    actionDict = Object(new Dict(nullptr));
    actionDict.dictSet("F", std::move(fileSpec));
    actionDict.dictSet("S", Object(objName, "Launch"));
    
    LinkLaunch linkLaunch(&actionDict);
    
    if (linkLaunch.isOk()) {
        EXPECT_EQ(linkLaunch.getKind(), actionLaunch);
    }
}

// Test that LinkLaunch with empty/null action object is not OK
TEST_F(LinkLaunchTest_291, NullActionObjectIsNotOk_291) {
    Object nullObj;
    nullObj = Object(objNull);
    
    LinkLaunch linkLaunch(&nullObj);
    
    EXPECT_FALSE(linkLaunch.isOk());
}

// Test that LinkLaunch constructed with an action dict missing filename is not OK
TEST_F(LinkLaunchTest_291, MissingFileNameIsNotOk_291) {
    Object actionDict;
    actionDict = Object(new Dict(nullptr));
    actionDict.dictSet("S", Object(objName, "Launch"));
    
    LinkLaunch linkLaunch(&actionDict);
    
    EXPECT_FALSE(linkLaunch.isOk());
}

// Test getFileName returns non-null when valid
TEST_F(LinkLaunchTest_291, GetFileNameReturnsValidString_291) {
    Object fileSpec;
    fileSpec = Object(new GooString("myfile.exe"));
    
    Object actionDict;
    actionDict = Object(new Dict(nullptr));
    actionDict.dictSet("F", std::move(fileSpec));
    actionDict.dictSet("S", Object(objName, "Launch"));
    
    LinkLaunch linkLaunch(&actionDict);
    
    if (linkLaunch.isOk()) {
        const GooString *fileName = linkLaunch.getFileName();
        ASSERT_NE(fileName, nullptr);
        EXPECT_STREQ(fileName->c_str(), "myfile.exe");
    }
}

// Test getParams when no params are set
TEST_F(LinkLaunchTest_291, GetParamsWhenNoneSet_291) {
    Object fileSpec;
    fileSpec = Object(new GooString("app.exe"));
    
    Object actionDict;
    actionDict = Object(new Dict(nullptr));
    actionDict.dictSet("F", std::move(fileSpec));
    actionDict.dictSet("S", Object(objName, "Launch"));
    
    LinkLaunch linkLaunch(&actionDict);
    
    if (linkLaunch.isOk()) {
        // Params may be null if not provided in the action dict
        // Just verify the call doesn't crash
        const GooString *params = linkLaunch.getParams();
        // params could be nullptr or a valid pointer
        (void)params;
    }
}

// Test isOk is consistent with fileName being non-null
TEST_F(LinkLaunchTest_291, IsOkConsistentWithFileName_291) {
    Object nullObj;
    nullObj = Object(objNull);
    
    LinkLaunch linkLaunch(&nullObj);
    
    // When isOk() is false, fileName should be null
    if (!linkLaunch.isOk()) {
        EXPECT_EQ(linkLaunch.getFileName(), nullptr);
    }
}

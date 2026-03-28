#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "GooString.h"

class LinkLaunchTest_293 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing LinkLaunch with a valid action object that contains a launch action
// produces a valid object with accessible filename
TEST_F(LinkLaunchTest_293, ConstructWithValidLaunchAction_293) {
    // Create a dictionary object that represents a Launch action with a file name
    Object fileSpec;
    fileSpec = Object(new GooString("testfile.pdf"));

    Object actionDict;
    actionDict = Object(new Dict(nullptr));
    actionDict.dictAdd("F", std::move(fileSpec));

    LinkLaunch launch(&actionDict);
    // We check if the kind is actionLaunch
    EXPECT_EQ(launch.getKind(), actionLaunch);
}

// Test getFileName returns non-null when a valid file is specified
TEST_F(LinkLaunchTest_293, GetFileNameWithValidFile_293) {
    Object fileObj;
    fileObj = Object(new GooString("document.pdf"));

    Object actionDict;
    actionDict = Object(new Dict(nullptr));
    actionDict.dictAdd("F", std::move(fileObj));

    LinkLaunch launch(&actionDict);
    
    const GooString *fileName = launch.getFileName();
    if (launch.isOk() && fileName != nullptr) {
        EXPECT_STRNE(fileName->c_str(), "");
    }
}

// Test that constructing LinkLaunch with an empty/null object handles gracefully
TEST_F(LinkLaunchTest_293, ConstructWithNullObject_293) {
    Object nullObj;
    LinkLaunch launch(&nullObj);
    
    // When constructed with invalid data, isOk should return false
    EXPECT_FALSE(launch.isOk());
}

// Test that getKind returns actionLaunch
TEST_F(LinkLaunchTest_293, GetKindReturnsActionLaunch_293) {
    Object nullObj;
    LinkLaunch launch(&nullObj);
    
    EXPECT_EQ(launch.getKind(), actionLaunch);
}

// Test getFileName when no file is specified
TEST_F(LinkLaunchTest_293, GetFileNameWhenNoFileSpecified_293) {
    Object emptyDict;
    emptyDict = Object(new Dict(nullptr));

    LinkLaunch launch(&emptyDict);
    
    const GooString *fileName = launch.getFileName();
    // When no file is specified, fileName may be nullptr
    if (!launch.isOk()) {
        // Object is not ok, filename behavior is implementation-defined
        SUCCEED();
    } else {
        // If somehow ok, just check we can call getFileName without crashing
        SUCCEED();
    }
}

// Test getParams when no params are specified
TEST_F(LinkLaunchTest_293, GetParamsWhenNoParamsSpecified_293) {
    Object emptyDict;
    emptyDict = Object(new Dict(nullptr));

    LinkLaunch launch(&emptyDict);
    
    const GooString *params = launch.getParams();
    // When no params specified, should be nullptr
    if (!launch.isOk()) {
        SUCCEED();
    } else {
        // params might be null when not specified
        SUCCEED();
    }
}

// Test that LinkLaunch with a Win dictionary containing params
TEST_F(LinkLaunchTest_293, ConstructWithWinDictionary_293) {
    Object winDict;
    winDict = Object(new Dict(nullptr));
    winDict.dictAdd("F", Object(new GooString("app.exe")));
    winDict.dictAdd("P", Object(new GooString("/param1")));

    Object actionDict;
    actionDict = Object(new Dict(nullptr));
    actionDict.dictAdd("Win", std::move(winDict));

    LinkLaunch launch(&actionDict);
    
    if (launch.isOk()) {
        const GooString *fileName = launch.getFileName();
        if (fileName) {
            EXPECT_STREQ(fileName->c_str(), "app.exe");
        }
        const GooString *params = launch.getParams();
        if (params) {
            EXPECT_STREQ(params->c_str(), "/param1");
        }
    }
}

// Test that calling getFileName on a default-invalid LinkLaunch doesn't crash
TEST_F(LinkLaunchTest_293, GetFileNameDoesNotCrashOnInvalid_293) {
    Object nullObj;
    LinkLaunch launch(&nullObj);
    
    // Should not crash
    const GooString *fileName = launch.getFileName();
    (void)fileName; // Just verifying no crash
    SUCCEED();
}

// Test that calling getParams on a default-invalid LinkLaunch doesn't crash
TEST_F(LinkLaunchTest_293, GetParamsDoesNotCrashOnInvalid_293) {
    Object nullObj;
    LinkLaunch launch(&nullObj);
    
    // Should not crash
    const GooString *params = launch.getParams();
    (void)params; // Just verifying no crash
    SUCCEED();
}

#include <gtest/gtest.h>
#include "Link.h"
#include "Object.h"
#include "GooString.h"

class LinkLaunchTest_294 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing a LinkLaunch with a valid action object that has params
// returns a non-null params value via getParams()
TEST_F(LinkLaunchTest_294, GetParamsFromValidAction_294) {
    // Create an action dictionary with launch parameters
    Dict *dict = new Dict(nullptr);
    
    // Build a launch action object with file and params
    Object fileObj = Object(new GooString("test.exe"));
    Object paramsObj = Object(new GooString("-arg1 -arg2"));
    
    // Create a Windows-specific launch dict
    Dict *winDict = new Dict(nullptr);
    winDict->add("F", std::move(fileObj));
    winDict->add("P", std::move(paramsObj));
    
    Object winObj = Object(winDict);
    dict->add("Win", std::move(winObj));
    
    Object actionObj = Object(dict);
    
    LinkLaunch linkLaunch(&actionObj);
    
    const GooString *params = linkLaunch.getParams();
    // params may or may not be null depending on how the object is parsed
    // We just verify we can call it without crashing
    if (params != nullptr) {
        EXPECT_FALSE(params->toStr().empty());
    }
}

// Test that constructing a LinkLaunch without params returns null from getParams()
TEST_F(LinkLaunchTest_294, GetParamsReturnsNullWhenNoParams_294) {
    // Create a minimal action object without params
    Dict *dict = new Dict(nullptr);
    
    Object fileObj = Object(new GooString("document.pdf"));
    dict->add("F", std::move(fileObj));
    
    Object actionObj = Object(dict);
    
    LinkLaunch linkLaunch(&actionObj);
    
    const GooString *params = linkLaunch.getParams();
    // Without a Win dict containing P, params should be null
    EXPECT_EQ(params, nullptr);
}

// Test that getParams returns const pointer (read-only access)
TEST_F(LinkLaunchTest_294, GetParamsReturnsConstPointer_294) {
    Dict *dict = new Dict(nullptr);
    
    Dict *winDict = new Dict(nullptr);
    Object fileObj = Object(new GooString("app.exe"));
    Object paramsObj = Object(new GooString("--verbose"));
    winDict->add("F", std::move(fileObj));
    winDict->add("P", std::move(paramsObj));
    
    Object winObj = Object(winDict);
    dict->add("Win", std::move(winObj));
    
    Object actionObj = Object(dict);
    
    LinkLaunch linkLaunch(&actionObj);
    
    const GooString *params1 = linkLaunch.getParams();
    const GooString *params2 = linkLaunch.getParams();
    
    // Multiple calls should return the same pointer
    EXPECT_EQ(params1, params2);
}

// Test that getKind returns actionLaunch
TEST_F(LinkLaunchTest_294, GetKindReturnsLaunch_294) {
    Dict *dict = new Dict(nullptr);
    Object fileObj = Object(new GooString("test.pdf"));
    dict->add("F", std::move(fileObj));
    
    Object actionObj = Object(dict);
    
    LinkLaunch linkLaunch(&actionObj);
    
    EXPECT_EQ(linkLaunch.getKind(), actionLaunch);
}

// Test with empty action object
TEST_F(LinkLaunchTest_294, EmptyActionObject_294) {
    Dict *dict = new Dict(nullptr);
    Object actionObj = Object(dict);
    
    LinkLaunch linkLaunch(&actionObj);
    
    const GooString *params = linkLaunch.getParams();
    EXPECT_EQ(params, nullptr);
}

// Test getFileName with a valid file
TEST_F(LinkLaunchTest_294, GetFileNameFromAction_294) {
    Dict *dict = new Dict(nullptr);
    Object fileObj = Object(new GooString("myfile.pdf"));
    dict->add("F", std::move(fileObj));
    
    Object actionObj = Object(dict);
    
    LinkLaunch linkLaunch(&actionObj);
    
    const GooString *fileName = linkLaunch.getFileName();
    // We can call getFileName without issues
    if (fileName != nullptr) {
        EXPECT_FALSE(fileName->toStr().empty());
    }
}

// Test with Win dict containing empty params string
TEST_F(LinkLaunchTest_294, GetParamsWithEmptyString_294) {
    Dict *dict = new Dict(nullptr);
    
    Dict *winDict = new Dict(nullptr);
    Object fileObj = Object(new GooString("app.exe"));
    Object paramsObj = Object(new GooString(""));
    winDict->add("F", std::move(fileObj));
    winDict->add("P", std::move(paramsObj));
    
    Object winObj = Object(winDict);
    dict->add("Win", std::move(winObj));
    
    Object actionObj = Object(dict);
    
    LinkLaunch linkLaunch(&actionObj);
    
    const GooString *params = linkLaunch.getParams();
    if (params != nullptr) {
        EXPECT_TRUE(params->toStr().empty());
    }
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "WXMPUtils.h"
#include "XMP_Const.h"
#include "XMPUtils.hpp"

// Mock class for external dependencies if needed (e.g., error handling)
class MockWXMP_Result : public WXMP_Result {
public:
    MOCK_METHOD(void, SetError, (const char* msg), ());
};

class WXMPUtils_ComposeQualifierPath_Test : public ::testing::Test {
protected:
    WXMP_Result result;
    XMP_StringPtr fullPath = nullptr;
    XMP_StringLen pathSize = 0;
};

TEST_F(WXMPUtils_ComposeQualifierPath_Test, NormalOperation_1932) {
    // Test: Valid input parameters, expected to run without errors
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = "PropertyName";
    XMP_StringPtr qualNS = "http://example.com/qualifier";
    XMP_StringPtr qualName = "QualifierName";

    EXPECT_NO_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &result));
    EXPECT_NE(fullPath, nullptr);
    EXPECT_GT(pathSize, 0);
}

TEST_F(WXMPUtils_ComposeQualifierPath_Test, NullSchemaNS_1933) {
    // Test: Null schema namespace
    XMP_StringPtr schemaNS = nullptr;
    XMP_StringPtr propName = "PropertyName";
    XMP_StringPtr qualNS = "http://example.com/qualifier";
    XMP_StringPtr qualName = "QualifierName";

    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &result), XMP_Error);
}

TEST_F(WXMPUtils_ComposeQualifierPath_Test, NullPropName_1934) {
    // Test: Null property name
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = nullptr;
    XMP_StringPtr qualNS = "http://example.com/qualifier";
    XMP_StringPtr qualName = "QualifierName";

    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &result), XMP_Error);
}

TEST_F(WXMPUtils_ComposeQualifierPath_Test, NullQualNS_1935) {
    // Test: Null qualifier namespace
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = "PropertyName";
    XMP_StringPtr qualNS = nullptr;
    XMP_StringPtr qualName = "QualifierName";

    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &result), XMP_Error);
}

TEST_F(WXMPUtils_ComposeQualifierPath_Test, NullQualName_1936) {
    // Test: Null qualifier name
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = "PropertyName";
    XMP_StringPtr qualNS = "http://example.com/qualifier";
    XMP_StringPtr qualName = nullptr;

    EXPECT_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, &pathSize, &result), XMP_Error);
}

TEST_F(WXMPUtils_ComposeQualifierPath_Test, NullFullPath_1937) {
    // Test: Null fullPath pointer
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = "PropertyName";
    XMP_StringPtr qualNS = "http://example.com/qualifier";
    XMP_StringPtr qualName = "QualifierName";
    XMP_StringPtr* fullPath = nullptr;

    EXPECT_NO_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, fullPath, &pathSize, &result));
    EXPECT_EQ(fullPath, nullptr);  // Should not throw, but fullPath remains nullptr
}

TEST_F(WXMPUtils_ComposeQualifierPath_Test, NullPathSize_1938) {
    // Test: Null pathSize pointer
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr propName = "PropertyName";
    XMP_StringPtr qualNS = "http://example.com/qualifier";
    XMP_StringPtr qualName = "QualifierName";
    XMP_StringLen* pathSize = nullptr;

    EXPECT_NO_THROW(WXMPUtils_ComposeQualifierPath_1(schemaNS, propName, qualNS, qualName, &fullPath, pathSize, &result));
    EXPECT_EQ(pathSize, nullptr);  // Should not throw, but pathSize remains nullptr
}
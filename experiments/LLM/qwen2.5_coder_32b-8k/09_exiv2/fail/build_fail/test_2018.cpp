#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



// Mock XMPMeta class to simulate behavior and verify interactions

class MockXMPMeta : public XMPMeta {

public:

    MOCK_METHOD5(DeleteQualifier, void(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_StringPtr qualNS, XMP_StringPtr qualName));

};



// Fixture for WXMPMeta_DeleteQualifier_1 tests

class WXMPMeta_DeleteQualifier_Test : public ::testing::Test {

protected:

    MockXMPMeta mockXMPMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockXMPMeta);

    WXMP_Result wResult;



    void SetUp() override {

        wResult.errMessage = nullptr;

    }

};



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, NormalOperation_2018) {

    EXPECT_CALL(mockXMPMeta, DeleteQualifier("http://example.com/schema", "propName", "http://example.com/qualifier", "qualName"));

    WXMPMeta_DeleteQualifier_1(xmpRef, "http://example.com/schema", "propName", "http://example.com/qualifier", "qualName", &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, SchemaNS_EmptyString_2018) {

    WXMPMeta_DeleteQualifier_1(xmpRef, "", "propName", "http://example.com/qualifier", "qualName", &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, SchemaNS_NullPointer_2018) {

    WXMPMeta_DeleteQualifier_1(xmpRef, nullptr, "propName", "http://example.com/qualifier", "qualName", &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, PropName_EmptyString_2018) {

    WXMPMeta_DeleteQualifier_1(xmpRef, "http://example.com/schema", "", "http://example.com/qualifier", "qualName", &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, PropName_NullPointer_2018) {

    WXMPMeta_DeleteQualifier_1(xmpRef, "http://example.com/schema", nullptr, "http://example.com/qualifier", "qualName", &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, QualNS_EmptyString_2018) {

    WXMPMeta_DeleteQualifier_1(xmpRef, "http://example.com/schema", "propName", "", "qualName", &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, QualNS_NullPointer_2018) {

    WXMPMeta_DeleteQualifier_1(xmpRef, "http://example.com/schema", "propName", nullptr, "qualName", &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, QualName_EmptyString_2018) {

    WXMPMeta_DeleteQualifier_1(xmpRef, "http://example.com/schema", "propName", "http://example.com/qualifier", "", &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_DeleteQualifier_Test_2018, QualName_NullPointer_2018) {

    WXMPMeta_DeleteQualifier_1(xmpRef, "http://example.com/schema", "propName", "http://example.com/qualifier", nullptr, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);

}

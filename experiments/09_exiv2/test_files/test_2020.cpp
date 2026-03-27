#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/include/XMPMeta.hpp"



// Mock XMPMeta class to allow for testing WXMPMeta_DoesArrayItemExist_1

class MockXMPMeta : public XMPMeta {

public:

    MOCK_CONST_METHOD3(DoesArrayItemExist, bool(XMP_StringPtr schemaNS, XMP_StringPtr arrayName, XMP_Index itemIndex));

};



// Fixture class for tests

class WXMPMetaTest_2020 : public ::testing::Test {

protected:

    MockXMPMeta mockXmpMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockXmpMeta);

    WXMP_Result result;



    void SetUp() override {

        memset(&result, 0, sizeof(WXMP_Result));

    }

};



// Test normal operation

TEST_F(WXMPMetaTest_2020, DoesArrayItemExist_ReturnsTrueWhenItemExists_2020) {

    EXPECT_CALL(mockXmpMeta, DoesArrayItemExist("http://example.com", "arrayName", 1)).WillOnce(::testing::Return(true));

    WXMPMeta_DoesArrayItemExist_1(xmpRef, "http://example.com", "arrayName", 1, &result);

    ASSERT_EQ(result.int32Result, true);

}



TEST_F(WXMPMetaTest_2020, DoesArrayItemExist_ReturnsFalseWhenItemDoesNotExist_2020) {

    EXPECT_CALL(mockXmpMeta, DoesArrayItemExist("http://example.com", "arrayName", 1)).WillOnce(::testing::Return(false));

    WXMPMeta_DoesArrayItemExist_1(xmpRef, "http://example.com", "arrayName", 1, &result);

    ASSERT_EQ(result.int32Result, false);

}



// Test boundary conditions

TEST_F(WXMPMetaTest_2020, DoesArrayItemExist_ItemIndexZeroIsValid_2020) {

    EXPECT_CALL(mockXmpMeta, DoesArrayItemExist("http://example.com", "arrayName", 0)).WillOnce(::testing::Return(false));

    WXMPMeta_DoesArrayItemExist_1(xmpRef, "http://example.com", "arrayName", 0, &result);

    ASSERT_EQ(result.int32Result, false);

}



// Test exceptional or error cases

TEST_F(WXMPMetaTest_2020, DoesArrayItemExist_EmptySchemaNamespaceThrowsError_2020) {

    EXPECT_THROW(WXMPMeta_DoesArrayItemExist_1(xmpRef, "", "arrayName", 1, &result), XMP_Error);

}



TEST_F(WXMPMetaTest_2020, DoesArrayItemExist_NullSchemaNamespaceThrowsError_2020) {

    EXPECT_THROW(WXMPMeta_DoesArrayItemExist_1(xmpRef, nullptr, "arrayName", 1, &result), XMP_Error);

}



TEST_F(WXMPMetaTest_2020, DoesArrayItemExist_EmptyArrayNameThrowsError_2020) {

    EXPECT_THROW(WXMPMeta_DoesArrayItemExist_1(xmpRef, "http://example.com", "", 1, &result), XMP_Error);

}



TEST_F(WXMPMetaTest_2020, DoesArrayItemExist_NullArrayNameThrowsError_2020) {

    EXPECT_THROW(WXMPMeta_DoesArrayItemExist_1(xmpRef, "http://example.com", nullptr, 1, &result), XMP_Error);

}

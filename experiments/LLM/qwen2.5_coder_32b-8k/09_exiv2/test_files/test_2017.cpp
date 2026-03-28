#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "client-glue/WXMP_Common.hpp"



// Mock class for XMPMeta to ensure we can create instances without relying on actual implementation details.

class MockXMPMeta : public XMPMeta {

public:

    MOCK_METHOD5(DeleteStructField, void(XMP_StringPtr, XMP_StringPtr, XMP_StringPtr, XMP_StringPtr));

};



TEST_F(WXMPMetaTest_2017, DeleteStructField_SuccessfulDeletion_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField("http://example.com/schema", "structName", "http://example.com/field", "fieldName")).Times(1);

    WXMPMeta_DeleteStructField_1(xmpRef, "http://example.com/schema", "structName", "http://example.com/field", "fieldName", &result);



    EXPECT_EQ(result.errMessage, nullptr);

}



TEST_F(WXMPMetaTest_2017, DeleteStructField_EmptySchemaNamespaceURI_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField).Times(0);

    WXMPMeta_DeleteStructField_1(xmpRef, "", "structName", "http://example.com/field", "fieldName", &result);



    EXPECT_EQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2017, DeleteStructField_EmptyStructName_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField).Times(0);

    WXMPMeta_DeleteStructField_1(xmpRef, "http://example.com/schema", "", "http://example.com/field", "fieldName", &result);



    EXPECT_EQ(result.errMessage, "Empty struct name");

}



TEST_F(WXMPMetaTest_2017, DeleteStructField_EmptyFieldNamespaceURI_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField).Times(0);

    WXMPMeta_DeleteStructField_1(xmpRef, "http://example.com/schema", "structName", "", "fieldName", &result);



    EXPECT_EQ(result.errMessage, "Empty field namespace URI");

}



TEST_F(WXMPMetaTest_2017, DeleteStructField_EmptyFieldName_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField).Times(0);

    WXMPMeta_DeleteStructField_1(xmpRef, "http://example.com/schema", "structName", "http://example.com/field", "", &result);



    EXPECT_EQ(result.errMessage, "Empty field name");

}



TEST_F(WXMPMetaTest_2017, DeleteStructField_NullSchemaNamespaceURI_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField).Times(0);

    WXMPMeta_DeleteStructField_1(xmpRef, nullptr, "structName", "http://example.com/field", "fieldName", &result);



    EXPECT_EQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2017, DeleteStructField_NullStructName_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField).Times(0);

    WXMPMeta_DeleteStructField_1(xmpRef, "http://example.com/schema", nullptr, "http://example.com/field", "fieldName", &result);



    EXPECT_EQ(result.errMessage, "Empty struct name");

}



TEST_F(WXMPMetaTest_2017, DeleteStructField_NullFieldNamespaceURI_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField).Times(0);

    WXMPMeta_DeleteStructField_1(xmpRef, "http://example.com/schema", "structName", nullptr, "fieldName", &result);



    EXPECT_EQ(result.errMessage, "Empty field namespace URI");

}



TEST_F(WXMPMetaTest_2017, DeleteStructField_NullFieldName_2017) {

    MockXMPMeta mockMeta;

    WXMP_Result result = {};

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);



    EXPECT_CALL(mockMeta, DeleteStructField).Times(0);

    WXMPMeta_DeleteStructField_1(xmpRef, "http://example.com/schema", "structName", "http://example.com/field", nullptr, &result);



    EXPECT_EQ(result.errMessage, "Empty field name");

}

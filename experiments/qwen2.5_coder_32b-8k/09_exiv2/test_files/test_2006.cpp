#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "WXMP_Common.hpp"

#include "XMPMeta.hpp"



// Mock class for XMPMeta

class MockXMPMeta : public XMPMeta {

public:

    MOCK_CONST_METHOD5(GetProperty, bool(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_StringPtr * propValue, XMP_StringLen * valueSize, XMP_OptionBits * options));

};



// Test fixture for WXMPMeta_GetProperty_1

class WXMPMetaTest_2006 : public ::testing::Test {

protected:

    MockXMPMeta mockXMPMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockXMPMeta);

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "exampleProperty";

    XMP_StringPtr propValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;

};



// Test normal operation

TEST_F(WXMPMetaTest_2006, GetProperty_Success_2006) {

    EXPECT_CALL(mockXMPMeta, GetProperty(schemaNS, propName, &propValue, &valueSize, &options)).WillOnce(::testing::Return(true));



    WXMPMeta_GetProperty_1(xmpRef, schemaNS, propName, &propValue, &valueSize, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



// Test boundary condition: empty schema namespace URI

TEST_F(WXMPMetaTest_2006, GetProperty_EmptySchemaNamespace_2006) {

    XMP_StringPtr invalidSchemaNS = "";



    EXPECT_THROW(WXMPMeta_GetProperty_1(xmpRef, invalidSchemaNS, propName, &propValue, &valueSize, &options, &wResult), XMP_Error);

}



// Test boundary condition: null schema namespace URI

TEST_F(WXMPMetaTest_2006, GetProperty_NullSchemaNamespace_2006) {

    XMP_StringPtr invalidSchemaNS = nullptr;



    EXPECT_THROW(WXMPMeta_GetProperty_1(xmpRef, invalidSchemaNS, propName, &propValue, &valueSize, &options, &wResult), XMP_Error);

}



// Test boundary condition: empty property name

TEST_F(WXMPMetaTest_2006, GetProperty_EmptyPropertyName_2006) {

    XMP_StringPtr invalidPropName = "";



    EXPECT_THROW(WXMPMeta_GetProperty_1(xmpRef, schemaNS, invalidPropName, &propValue, &valueSize, &options, &wResult), XMP_Error);

}



// Test boundary condition: null property name

TEST_F(WXMPMetaTest_2006, GetProperty_NullPropertyName_2006) {

    XMP_StringPtr invalidPropName = nullptr;



    EXPECT_THROW(WXMPMeta_GetProperty_1(xmpRef, schemaNS, invalidPropName, &propValue, &valueSize, &options, &wResult), XMP_Error);

}



// Test boundary condition: null propValue

TEST_F(WXMPMetaTest_2006, GetProperty_NullPropValue_2006) {

    EXPECT_CALL(mockXMPMeta, GetProperty(schemaNS, propName, nullptr, &valueSize, &options)).WillOnce(::testing::Return(true));



    WXMPMeta_GetProperty_1(xmpRef, schemaNS, propName, nullptr, &valueSize, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



// Test boundary condition: null valueSize

TEST_F(WXMPMetaTest_2006, GetProperty_NullValueSize_2006) {

    EXPECT_CALL(mockXMPMeta, GetProperty(schemaNS, propName, &propValue, nullptr, &options)).WillOnce(::testing::Return(true));



    WXMPMeta_GetProperty_1(xmpRef, schemaNS, propName, &propValue, nullptr, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



// Test boundary condition: null options

TEST_F(WXMPMetaTest_2006, GetProperty_NullOptions_2006) {

    EXPECT_CALL(mockXMPMeta, GetProperty(schemaNS, propName, &propValue, &valueSize, nullptr)).WillOnce(::testing::Return(true));



    WXMPMeta_GetProperty_1(xmpRef, schemaNS, propName, &propValue, &valueSize, nullptr, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}

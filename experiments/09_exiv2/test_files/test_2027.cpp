#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



// Mock XMPMeta class to control its behavior during tests

class MockXMPMeta : public XMPMeta {

public:

    MOCK_CONST_METHOD4(GetProperty_Int64, bool(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_Int64* propValue, XMP_OptionBits* options));

};



// Test fixture class

class WXMPMeta_GetProperty_Int64_Test : public ::testing::Test {

protected:

    MockXMPMeta mockXMPMeta;

    XMPMetaRef xmpRef = &mockXMPMeta;

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "ExampleProperty";

    XMP_Int64 propValue = 0;

    XMP_OptionBits options = 0;

    WXMP_Result wResult;

};



// Normal operation

TEST_F(WXMPMeta_GetProperty_Int64_Test_2027, GetProperty_Successful_2027) {

    EXPECT_CALL(mockXMPMeta, GetProperty_Int64(schemaNS, propName, &propValue, &options)).WillOnce(::testing::Return(true));

    WXMPMeta_GetProperty_Int64_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 1); // true

}



// Boundary conditions: Empty schema namespace URI

TEST_F(WXMPMeta_GetProperty_Int64_Test_2027, GetProperty_EmptySchemaNamespaceURI_2027) {

    EXPECT_THROW(WXMPMeta_GetProperty_Int64_1(xmpRef, "", propName, &propValue, &options, &wResult), XMP_Error);

}



// Boundary conditions: Null schema namespace URI

TEST_F(WXMPMeta_GetProperty_Int64_Test_2027, GetProperty_NullSchemaNamespaceURI_2027) {

    EXPECT_THROW(WXMPMeta_GetProperty_Int64_1(xmpRef, nullptr, propName, &propValue, &options, &wResult), XMP_Error);

}



// Boundary conditions: Empty property name

TEST_F(WXMPMeta_GetProperty_Int64_Test_2027, GetProperty_EmptyPropertyName_2027) {

    EXPECT_THROW(WXMPMeta_GetProperty_Int64_1(xmpRef, schemaNS, "", &propValue, &options, &wResult), XMP_Error);

}



// Boundary conditions: Null property name

TEST_F(WXMPMeta_GetProperty_Int64_Test_2027, GetProperty_NullPropertyName_2027) {

    EXPECT_THROW(WXMPMeta_GetProperty_Int64_1(xmpRef, schemaNS, nullptr, &propValue, &options, &wResult), XMP_Error);

}



// Exceptional or error cases: Property not found

TEST_F(WXMPMeta_GetProperty_Int64_Test_2027, GetProperty_NotFound_2027) {

    EXPECT_CALL(mockXMPMeta, GetProperty_Int64(schemaNS, propName, &propValue, &options)).WillOnce(::testing::Return(false));

    WXMPMeta_GetProperty_Int64_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 0); // false

}



// Verification of external interactions: Correct parameters passed to GetProperty_Int64

TEST_F(WXMPMeta_GetProperty_Int64_Test_2027, GetProperty_CorrectParametersPassed_2027) {

    EXPECT_CALL(mockXMPMeta, GetProperty_Int64(schemaNS, propName, &propValue, &options)).WillOnce(::testing::Return(true));

    WXMPMeta_GetProperty_Int64_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

}

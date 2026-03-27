#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



// Mock class for XMPMeta to simulate behavior

class MockXMPMeta : public XMPMeta {

public:

    MOCK_CONST_METHOD4(GetProperty_Int, bool(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_Int32 * propValue, XMP_OptionBits * options));

};



// Fixture class for setting up and tearing down tests

class WXMPMeta_GetProperty_Int_1Test : public ::testing::Test {

protected:

    MockXMPMeta mockXMPMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockXMPMeta);

    WXMP_Result wResult;



    void SetUp() override {

        // Initialize wResult to default state

        wResult.int32Result = 0;

    }

};



// Test normal operation with valid inputs

TEST_F(WXMPMeta_GetProperty_Int_1Test, ValidInputs_2026) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "propertyName";

    XMP_Int32 propValue;

    XMP_OptionBits options;



    EXPECT_CALL(mockXMPMeta, GetProperty_Int(schemaNS, propName, ::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(42), ::testing::Return(true)));



    WXMPMeta_GetProperty_Int_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, 1); // true

    EXPECT_EQ(propValue, 42);

}



// Test boundary condition with empty schema namespace URI

TEST_F(WXMPMeta_GetProperty_Int_1Test, EmptySchemaNamespaceURI_2026) {

    const char* schemaNS = "";

    const char* propName = "propertyName";

    XMP_Int32 propValue;

    XMP_OptionBits options;



    EXPECT_THROW(WXMPMeta_GetProperty_Int_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult), XMP_Error);

}



// Test boundary condition with null schema namespace URI

TEST_F(WXMPMeta_GetProperty_Int_1Test, NullSchemaNamespaceURI_2026) {

    const char* schemaNS = nullptr;

    const char* propName = "propertyName";

    XMP_Int32 propValue;

    XMP_OptionBits options;



    EXPECT_THROW(WXMPMeta_GetProperty_Int_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult), XMP_Error);

}



// Test boundary condition with empty property name

TEST_F(WXMPMeta_GetProperty_Int_1Test, EmptyPropertyName_2026) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "";

    XMP_Int32 propValue;

    XMP_OptionBits options;



    EXPECT_THROW(WXMPMeta_GetProperty_Int_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult), XMP_Error);

}



// Test boundary condition with null property name

TEST_F(WXMPMeta_GetProperty_Int_1Test, NullPropertyName_2026) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = nullptr;

    XMP_Int32 propValue;

    XMP_OptionBits options;



    EXPECT_THROW(WXMPMeta_GetProperty_Int_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult), XMP_Error);

}



// Test property not found case

TEST_F(WXMPMeta_GetProperty_Int_1Test, PropertyNotFound_2026) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "propertyName";

    XMP_Int32 propValue;

    XMP_OptionBits options;



    EXPECT_CALL(mockXMPMeta, GetProperty_Int(schemaNS, propName, ::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::Return(false));



    WXMPMeta_GetProperty_Int_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, 0); // false

}



// Test default values for propValue and options when not provided

TEST_F(WXMPMeta_GetProperty_Int_1Test, DefaultValues_2026) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "propertyName";



    EXPECT_CALL(mockXMPMeta, GetProperty_Int(schemaNS, propName, ::testing::NotNull(), &voidOptionBits))

        .WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(42), ::testing::Return(true)));



    WXMPMeta_GetProperty_Int_1(xmpRef, schemaNS, propName, nullptr, nullptr, &wResult);



    EXPECT_EQ(wResult.int32Result, 1); // true

}

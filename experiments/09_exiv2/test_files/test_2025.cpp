#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking XMPMeta class to capture interactions

class MockXMPMeta : public XMPMeta {

public:

    MOCK_CONST_METHOD4(GetProperty_Bool, bool(XMP_StringPtr schemaNS, XMP_StringPtr propName, _Bool * propValue, XMP_OptionBits * options));

};



// Test fixture for WXMPMeta_GetProperty_Bool_1 function

class WXMPMetaTest : public ::testing::Test {

protected:

    MockXMPMeta mockMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "exampleProperty";

    XMP_Bool propValue;

    XMP_OptionBits options;

    WXMP_Result wResult;



    void SetUp() override {

        propValue = false;

        options = 0;

        wResult.errMessage = nullptr;

        wResult.int32Result = 0;

    }

};



// Test normal operation where property is found

TEST_F(WXMPMetaTest, GetProperty_Bool_Found_2025) {

    EXPECT_CALL(mockMeta, GetProperty_Bool(schemaNS, propName, ::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<2>(true),

            ::testing::Return(true)));



    WXMPMeta_GetProperty_Bool_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);



    EXPECT_TRUE(propValue);

    EXPECT_EQ(wResult.int32Result, 1); // true

}



// Test normal operation where property is not found

TEST_F(WXMPMetaTest, GetProperty_Bool_NotFound_2025) {

    EXPECT_CALL(mockMeta, GetProperty_Bool(schemaNS, propName, ::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::Return(false));



    WXMPMeta_GetProperty_Bool_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);



    EXPECT_FALSE(propValue);

    EXPECT_EQ(wResult.int32Result, 0); // false

}



// Test boundary condition with null schemaNS

TEST_F(WXMPMetaTest, GetProperty_Bool_NullSchemaNS_2025) {

    EXPECT_THROW(WXMPMeta_GetProperty_Bool_1(xmpRef, nullptr, propName, &propValue, &options, &wResult), XMP_Error);

}



// Test boundary condition with empty schemaNS

TEST_F(WXMPMetaTest, GetProperty_Bool_EmptySchemaNS_2025) {

    EXPECT_THROW(WXMPMeta_GetProperty_Bool_1(xmpRef, "", propName, &propValue, &options, &wResult), XMP_Error);

}



// Test boundary condition with null propName

TEST_F(WXMPMetaTest, GetProperty_Bool_NullPropName_2025) {

    EXPECT_THROW(WXMPMeta_GetProperty_Bool_1(xmpRef, schemaNS, nullptr, &propValue, &options, &wResult), XMP_Error);

}



// Test boundary condition with empty propName

TEST_F(WXMPMetaTest, GetProperty_Bool_EmptyPropName_2025) {

    EXPECT_THROW(WXMPMeta_GetProperty_Bool_1(xmpRef, schemaNS, "", &propValue, &options, &wResult), XMP_Error);

}



// Test boundary condition with null propValue

TEST_F(WXMPMetaTest, GetProperty_Bool_NullPropValue_2025) {

    EXPECT_CALL(mockMeta, GetProperty_Bool(schemaNS, propName, ::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::Return(false));



    WXMPMeta_GetProperty_Bool_1(xmpRef, schemaNS, propName, nullptr, &options, &wResult);



    // Since propValue is null, we can't assert its value, but the call should not throw

}



// Test boundary condition with null wResult

TEST_F(WXMPMetaTest, GetProperty_Bool_NullWResult_2025) {

    EXPECT_CALL(mockMeta, GetProperty_Bool(schemaNS, propName, ::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::Return(false));



    WXMPMeta_GetProperty_Bool_1(xmpRef, schemaNS, propName, &propValue, &options, nullptr);



    // Since wResult is null, we can't assert its value, but the call should not throw

}

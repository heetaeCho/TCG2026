#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "XMPMeta.hpp"



// Mock class for XMPMeta to verify interactions

class MockXMPMeta : public XMPMeta {

public:

    MOCK_CONST_METHOD2(GetObjectName, void(XMP_StringPtr*, XMP_StringLen*));

};



// Test fixture for WXMPMeta_GetObjectName_1 tests

class WXMPMeta_GetObjectName_2041_Test : public ::testing::Test {

protected:

    MockXMPMeta mockMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockMeta);

    WXMP_Result wResult;



    void SetUp() override {

        // Initialize any necessary data or state before each test

    }



    void TearDown() override {

        // Clean up any resources after each test

    }

};



// Test normal operation with non-empty object name

TEST_F(WXMPMeta_GetObjectName_2041_Test, GetObjectName_NormalOperation_2041) {

    const char* expectedName = "Test Object";

    XMP_StringPtr namePtr;

    XMP_StringLen nameLen;



    EXPECT_CALL(mockMeta, GetObjectName(::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(expectedName),

            ::testing::SetArgReferee<1>(strlen(expectedName))

        ));



    WXMPMeta_GetObjectName_1(xmpRef, &namePtr, &nameLen, &wResult);



    EXPECT_STREQ(namePtr, expectedName);

    EXPECT_EQ(nameLen, strlen(expectedName));

}



// Test normal operation with empty object name

TEST_F(WXMPMeta_GetObjectName_2041_Test, GetObjectName_EmptyName_2041) {

    const char* expectedName = "";

    XMP_StringPtr namePtr;

    XMP_StringLen nameLen;



    EXPECT_CALL(mockMeta, GetObjectName(::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(expectedName),

            ::testing::SetArgReferee<1>(strlen(expectedName))

        ));



    WXMPMeta_GetObjectName_1(xmpRef, &namePtr, &nameLen, &wResult);



    EXPECT_STREQ(namePtr, expectedName);

    EXPECT_EQ(nameLen, strlen(expectedName));

}



// Test boundary condition with nullptr namePtr

TEST_F(WXMPMeta_GetObjectName_2041_Test, GetObjectName_NullNamePtr_2041) {

    XMP_StringLen nameLen;



    EXPECT_CALL(mockMeta, GetObjectName(::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(voidStringPtr),

            ::testing::SetArgReferee<1>(0)

        ));



    WXMPMeta_GetObjectName_1(xmpRef, nullptr, &nameLen, &wResult);



    EXPECT_STREQ(voidStringPtr, "");

    EXPECT_EQ(nameLen, 0);

}



// Test boundary condition with nullptr nameLen

TEST_F(WXMPMeta_GetObjectName_2041_Test, GetObjectName_NullNameLen_2041) {

    XMP_StringPtr namePtr;



    EXPECT_CALL(mockMeta, GetObjectName(::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(voidStringPtr),

            ::testing::SetArgReferee<1>(0)

        ));



    WXMPMeta_GetObjectName_1(xmpRef, &namePtr, nullptr, &wResult);



    EXPECT_STREQ(namePtr, voidStringPtr);

}



// Test boundary condition with both nullptr namePtr and nameLen

TEST_F(WXMPMeta_GetObjectName_2041_Test, GetObjectName_NullNamePtrAndNameLen_2041) {

    EXPECT_CALL(mockMeta, GetObjectName(::testing::NotNull(), ::testing::NotNull()))

        .WillOnce(::testing::DoAll(

            ::testing::SetArgReferee<0>(voidStringPtr),

            ::testing::SetArgReferee<1>(0)

        ));



    WXMPMeta_GetObjectName_1(xmpRef, nullptr, nullptr, &wResult);



    // No direct checks for voidStringPtr and voidStringLen as they are internal

}

#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



// Assuming XMPMetaRef and WtoXMPMeta_Ptr are defined somewhere in the codebase.

typedef void* XMPMetaRef;

XMPMeta* WtoXMPMeta_Ptr(XMPMetaRef xmpRef);



class WXMPMetaTest : public ::testing::Test {

protected:

    WXMPMetaRef xmpRef;

    WXMP_Result wResult;



    virtual void SetUp() {

        // Initialize the XMPMeta object and set up any necessary state.

        xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

        memset(&wResult, 0, sizeof(WXMP_Result));

    }



    virtual void TearDown() {

        // Clean up after each test.

        delete WtoXMPMeta_Ptr(xmpRef);

        xmpRef = nullptr;

    }

};



TEST_F(WXMPMetaTest_2042, SetObjectName_ValidName_2042) {

    const char* name = "ValidObjectName";

    WXMPMeta_SetObjectName_1(xmpRef, name, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // Assuming no error message on success.

}



TEST_F(WXMPMetaTest_2042, SetObjectName_EmptyName_2042) {

    const char* name = "";

    WXMPMeta_SetObjectName_1(xmpRef, name, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // Assuming no error message on success.

}



TEST_F(WXMPMetaTest_2042, SetObjectName_NullName_2042) {

    const char* name = nullptr;

    WXMPMeta_SetObjectName_1(xmpRef, name, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // Assuming no error message on success.

}



TEST_F(WXMPMetaTest_2042, SetObjectName_LongName_2042) {

    std::string longName(1000, 'A'); // A very long name

    WXMPMeta_SetObjectName_1(xmpRef, longName.c_str(), &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // Assuming no error message on success.

}



// Exceptional or error cases (if observable through the interface)

// For this particular function, there are no exceptional cases that would be observable from the interface.



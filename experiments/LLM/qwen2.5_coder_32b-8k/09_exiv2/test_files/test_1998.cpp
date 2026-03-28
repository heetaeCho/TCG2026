#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



// Assuming WXMPMeta_RegisterNamespace_1 is declared in some header file that we include here

extern "C" void WXMPMeta_RegisterNamespace_1(XMP_StringPtr namespaceURI, XMP_StringPtr prefix, WXMP_Result* wResult);



class WXMPMeta_RegisterNamespace_Test : public ::testing::Test {

protected:

    WXMP_Result result;

};



TEST_F(WXMPMeta_RegisterNamespace_Test_1998, NormalOperation_1998) {

    const char* namespaceURI = "http://example.com/namespace";

    const char* prefix = "ex";



    WXMPMeta_RegisterNamespace_1(namespaceURI, prefix, &result);



    EXPECT_EQ(result.errMessage, nullptr);

}



TEST_F(WXMPMeta_RegisterNamespace_Test_1998, EmptyNamespaceURIThrowsError_1998) {

    const char* namespaceURI = "";

    const char* prefix = "ex";



    WXMPMeta_RegisterNamespace_1(namespaceURI, prefix, &result);



    EXPECT_STREQ(result.errMessage, "Empty namespace URI");

}



TEST_F(WXMPMeta_RegisterNamespace_Test_1998, NullNamespaceURIThrowsError_1998) {

    const char* namespaceURI = nullptr;

    const char* prefix = "ex";



    WXMPMeta_RegisterNamespace_1(namespaceURI, prefix, &result);



    EXPECT_STREQ(result.errMessage, "Empty namespace URI");

}



TEST_F(WXMPMeta_RegisterNamespace_Test_1998, EmptyPrefixThrowsError_1998) {

    const char* namespaceURI = "http://example.com/namespace";

    const char* prefix = "";



    WXMPMeta_RegisterNamespace_1(namespaceURI, prefix, &result);



    EXPECT_STREQ(result.errMessage, "Empty prefix");

}



TEST_F(WXMPMeta_RegisterNamespace_Test_1998, NullPrefixThrowsError_1998) {

    const char* namespaceURI = "http://example.com/namespace";

    const char* prefix = nullptr;



    WXMPMeta_RegisterNamespace_1(namespaceURI, prefix, &result);



    EXPECT_STREQ(result.errMessage, "Empty prefix");

}

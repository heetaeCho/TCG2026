#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"



extern void WXMPMeta_DeleteNamespace_1(XMP_StringPtr namespaceURI, WXMP_Result* wResult);



class WXMPMetaDeleteNamespaceTest : public ::testing::Test {

protected:

    WXMP_Result result;



    virtual void SetUp() {

        memset(&result, 0, sizeof(WXMP_Result));

    }

};



TEST_F(WXMPMetaDeleteNamespaceTest_NormalOperation_2001, ValidNamespaceURI) {

    XMP_StringPtr namespaceURI = "http://example.com/namespace";

    WXMPMeta_DeleteNamespace_1(namespaceURI, &result);

    EXPECT_STREQ(result.errMessage, nullptr); // Assuming no error message on success

}



TEST_F(WXMPMetaDeleteNamespaceTest_BoundaryConditions_2001, EmptyNamespaceURIPtr) {

    XMP_StringPtr namespaceURI = nullptr;

    WXMPMeta_DeleteNamespace_1(namespaceURI, &result);

    EXPECT_STREQ(result.errMessage, "Empty namespace URI");

}



TEST_F(WXMPMetaDeleteNamespaceTest_BoundaryConditions_2001, EmptyNamespaceURIString) {

    XMP_StringPtr namespaceURI = "";

    WXMPMeta_DeleteNamespace_1(namespaceURI, &result);

    EXPECT_STREQ(result.errMessage, "Empty namespace URI");

}



TEST_F(WXMPMetaDeleteNamespaceTest_ExceptionalCases_2001, NullResultPtr) {

    XMP_StringPtr namespaceURI = "http://example.com/namespace";

    WXMPMeta_DeleteNamespace_1(namespaceURI, nullptr); // Assuming no crash and proper handling

}

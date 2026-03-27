#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"



extern "C" {

    void WXMPMeta_DeleteAlias_1(XMP_StringPtr aliasNS, XMP_StringPtr aliasProp, WXMP_Result * wResult);

}



TEST(WXMPMeta_DeleteAliasTest_2004, NormalOperation_2004) {

    WXMP_Result result;

    XMP_StringPtr aliasNS = "http://example.com/namespace";

    XMP_StringPtr aliasProp = "exampleProperty";



    WXMPMeta_DeleteAlias_1(aliasNS, aliasProp, &result);



    EXPECT_EQ(result.errMessage, nullptr);

}



TEST(WXMPMeta_DeleteAliasTest_2004, EmptyNamespaceURI_2004) {

    WXMP_Result result;

    XMP_StringPtr aliasNS = "";

    XMP_StringPtr aliasProp = "exampleProperty";



    WXMPMeta_DeleteAlias_1(aliasNS, aliasProp, &result);



    EXPECT_STREQ(result.errMessage, "Empty alias namespace URI");

}



TEST(WXMPMeta_DeleteAliasTest_2004, NullNamespaceURI_2004) {

    WXMP_Result result;

    XMP_StringPtr aliasNS = nullptr;

    XMP_StringPtr aliasProp = "exampleProperty";



    WXMPMeta_DeleteAlias_1(aliasNS, aliasProp, &result);



    EXPECT_STREQ(result.errMessage, "Empty alias namespace URI");

}



TEST(WXMPMeta_DeleteAliasTest_2004, EmptyPropertyName_2004) {

    WXMP_Result result;

    XMP_StringPtr aliasNS = "http://example.com/namespace";

    XMP_StringPtr aliasProp = "";



    WXMPMeta_DeleteAlias_1(aliasNS, aliasProp, &result);



    EXPECT_STREQ(result.errMessage, "Empty alias property name");

}



TEST(WXMPMeta_DeleteAliasTest_2004, NullPropertyName_2004) {

    WXMP_Result result;

    XMP_StringPtr aliasNS = "http://example.com/namespace";

    XMP_StringPtr aliasProp = nullptr;



    WXMPMeta_DeleteAlias_1(aliasNS, aliasProp, &result);



    EXPECT_STREQ(result.errMessage, "Empty alias property name");

}

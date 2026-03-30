#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"



extern "C" {

    void WXMPMeta_RegisterAlias_1(XMP_StringPtr aliasNS, XMP_StringPtr aliasProp, XMP_StringPtr actualNS, XMP_StringPtr actualProp, XMP_OptionBits arrayForm, WXMP_Result * wResult);

}



class WXMPMetaRegisterAliasTest : public ::testing::Test {

protected:

    WXMP_Result result;



    void SetUp() override {

        memset(&result, 0, sizeof(WXMP_Result));

    }

};



TEST_F(WXMPMetaRegisterAliasTest_NormalOperation_2002, RegisterValidAlias_2002) {

    XMP_StringPtr aliasNS = "http://example.com/alias";

    XMP_StringPtr aliasProp = "aliasProperty";

    XMP_StringPtr actualNS = "http://example.com/actual";

    XMP_StringPtr actualProp = "actualProperty";

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, nullptr);

}



TEST_F(WXMPMetaRegisterAliasTest_BoundaryConditions_2002, RegisterEmptyAliasNamespaceURI_2002) {

    XMP_StringPtr aliasNS = "";

    XMP_StringPtr aliasProp = "aliasProperty";

    XMP_StringPtr actualNS = "http://example.com/actual";

    XMP_StringPtr actualProp = "actualProperty";

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, "Empty alias namespace URI");

}



TEST_F(WXMPMetaRegisterAliasTest_BoundaryConditions_2002, RegisterNullAliasNamespaceURI_2002) {

    XMP_StringPtr aliasNS = nullptr;

    XMP_StringPtr aliasProp = "aliasProperty";

    XMP_StringPtr actualNS = "http://example.com/actual";

    XMP_StringPtr actualProp = "actualProperty";

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, "Empty alias namespace URI");

}



TEST_F(WXMPMetaRegisterAliasTest_BoundaryConditions_2002, RegisterEmptyAliasPropertyName_2002) {

    XMP_StringPtr aliasNS = "http://example.com/alias";

    XMP_StringPtr aliasProp = "";

    XMP_StringPtr actualNS = "http://example.com/actual";

    XMP_StringPtr actualProp = "actualProperty";

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, "Empty alias property name");

}



TEST_F(WXMPMetaRegisterAliasTest_BoundaryConditions_2002, RegisterNullAliasPropertyName_2002) {

    XMP_StringPtr aliasNS = "http://example.com/alias";

    XMP_StringPtr aliasProp = nullptr;

    XMP_StringPtr actualNS = "http://example.com/actual";

    XMP_StringPtr actualProp = "actualProperty";

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, "Empty alias property name");

}



TEST_F(WXMPMetaRegisterAliasTest_BoundaryConditions_2002, RegisterEmptyActualNamespaceURI_2002) {

    XMP_StringPtr aliasNS = "http://example.com/alias";

    XMP_StringPtr aliasProp = "aliasProperty";

    XMP_StringPtr actualNS = "";

    XMP_StringPtr actualProp = "actualProperty";

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, "Empty actual namespace URI");

}



TEST_F(WXMPMetaRegisterAliasTest_BoundaryConditions_2002, RegisterNullActualNamespaceURI_2002) {

    XMP_StringPtr aliasNS = "http://example.com/alias";

    XMP_StringPtr aliasProp = "aliasProperty";

    XMP_StringPtr actualNS = nullptr;

    XMP_StringPtr actualProp = "actualProperty";

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, "Empty actual namespace URI");

}



TEST_F(WXMPMetaRegisterAliasTest_BoundaryConditions_2002, RegisterEmptyActualPropertyName_2002) {

    XMP_StringPtr aliasNS = "http://example.com/alias";

    XMP_StringPtr aliasProp = "aliasProperty";

    XMP_StringPtr actualNS = "http://example.com/actual";

    XMP_StringPtr actualProp = "";

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, "Empty actual property name");

}



TEST_F(WXMPMetaRegisterAliasTest_BoundaryConditions_2002, RegisterNullActualPropertyName_2002) {

    XMP_StringPtr aliasNS = "http://example.com/alias";

    XMP_StringPtr aliasProp = "aliasProperty";

    XMP_StringPtr actualNS = "http://example.com/actual";

    XMP_StringPtr actualProp = nullptr;

    XMP_OptionBits arrayForm = 0;



    WXMPMeta_RegisterAlias_1(aliasNS, aliasProp, actualNS, actualProp, arrayForm, &result);



    EXPECT_STREQ(result.errMessage, "Empty actual property name");

}

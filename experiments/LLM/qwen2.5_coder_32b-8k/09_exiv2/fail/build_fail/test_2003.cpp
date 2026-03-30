#include <gtest/gtest.h>

#include "WXMPMeta.cpp"



namespace {

    TEST(WXMPMeta_ResolveAlias_Test_2003, NormalOperation_2003) {

        XMP_StringPtr aliasNS = "http://example.com/alias";

        XMP_StringPtr aliasProp = "testAlias";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, &nsSize, &actualProp, &propSize, &arrayForm, &wResult);



        EXPECT_EQ(wResult.int32Result, true); // Assuming ResolveAlias returns true for this input

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, EmptyAliasNamespaceURI_2003) {

        XMP_StringPtr aliasNS = "";

        XMP_StringPtr aliasProp = "testAlias";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        EXPECT_THROW(WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, &nsSize, &actualProp, &propSize, &arrayForm, &wResult), XMP_Error);

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, NullAliasNamespaceURI_2003) {

        XMP_StringPtr aliasNS = nullptr;

        XMP_StringPtr aliasProp = "testAlias";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        EXPECT_THROW(WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, &nsSize, &actualProp, &propSize, &arrayForm, &wResult), XMP_Error);

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, EmptyAliasPropertyName_2003) {

        XMP_StringPtr aliasNS = "http://example.com/alias";

        XMP_StringPtr aliasProp = "";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        EXPECT_THROW(WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, &nsSize, &actualProp, &propSize, &arrayForm, &wResult), XMP_Error);

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, NullAliasPropertyName_2003) {

        XMP_StringPtr aliasNS = "http://example.com/alias";

        XMP_StringPtr aliasProp = nullptr;

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        EXPECT_THROW(WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, &nsSize, &actualProp, &propSize, &arrayForm, &wResult), XMP_Error);

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, NullActualNSPointer_2003) {

        XMP_StringPtr aliasNS = "http://example.com/alias";

        XMP_StringPtr aliasProp = "testAlias";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, nullptr, &nsSize, &actualProp, &propSize, &arrayForm, &wResult);



        EXPECT_EQ(wResult.int32Result, true); // Assuming ResolveAlias returns true for this input

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, NullNSSizePointer_2003) {

        XMP_StringPtr aliasNS = "http://example.com/alias";

        XMP_StringPtr aliasProp = "testAlias";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, nullptr, &actualProp, &propSize, &arrayForm, &wResult);



        EXPECT_EQ(wResult.int32Result, true); // Assuming ResolveAlias returns true for this input

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, NullActualPropPointer_2003) {

        XMP_StringPtr aliasNS = "http://example.com/alias";

        XMP_StringPtr aliasProp = "testAlias";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, &nsSize, nullptr, &propSize, &arrayForm, &wResult);



        EXPECT_EQ(wResult.int32Result, true); // Assuming ResolveAlias returns true for this input

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, NullPropSizePointer_2003) {

        XMP_StringPtr aliasNS = "http://example.com/alias";

        XMP_StringPtr aliasProp = "testAlias";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, &nsSize, &actualProp, nullptr, &arrayForm, &wResult);



        EXPECT_EQ(wResult.int32Result, true); // Assuming ResolveAlias returns true for this input

    }



    TEST(WXMPMeta_ResolveAlias_Test_2003, NullArrayFormPointer_2003) {

        XMP_StringPtr aliasNS = "http://example.com/alias";

        XMP_StringPtr aliasProp = "testAlias";

        XMP_StringPtr actualNS = nullptr;

        XMP_StringLen nsSize = 0;

        XMP_StringPtr actualProp = nullptr;

        XMP_StringLen propSize = 0;

        XMP_OptionBits arrayForm = 0;

        WXMP_Result wResult;



        WXMPMeta_ResolveAlias_1(aliasNS, aliasProp, &actualNS, &nsSize, &actualProp, &propSize, nullptr, &wResult);



        EXPECT_EQ(wResult.int32Result, true); // Assuming ResolveAlias returns true for this input

    }

}

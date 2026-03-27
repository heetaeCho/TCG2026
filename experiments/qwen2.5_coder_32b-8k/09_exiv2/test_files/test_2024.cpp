#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

#include "./TestProjects/exiv2/xmpsdk/src/client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"



class WXMPMeta_SetLocalizedText_Test : public ::testing::Test {

protected:

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    void SetUp() override {

        // Assuming there's a way to create an XMPMeta object and get its reference

        xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

    }



    void TearDown() override {

        delete reinterpret_cast<XMPMeta*>(xmpRef);

    }

};



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, NormalOperation_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, "http://example.com/schema", "AltText", "en", "US", "Hello World", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, EmptySchemaNamespaceURI_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, "", "AltText", "en", "US", "Hello World", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, NullSchemaNamespaceURI_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, nullptr, "AltText", "en", "US", "Hello World", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, EmptyArrayName_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, "http://example.com/schema", "", "en", "US", "Hello World", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, NullArrayName_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, "http://example.com/schema", nullptr, "en", "US", "Hello World", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty array name");

}



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, EmptySpecificLang_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, "http://example.com/schema", "AltText", "en", "", "Hello World", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty specific language");

}



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, NullSpecificLang_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, "http://example.com/schema", "AltText", "en", nullptr, "Hello World", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, "Empty specific language");

}



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, NullItemValue_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, "http://example.com/schema", "AltText", "en", "US", nullptr, 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // Empty string should be accepted

}



TEST_F(WXMPMeta_SetLocalizedText_Test_2024, NormalOperationWithEmptyGenericLang_2024) {

    WXMPMeta_SetLocalizedText_1(xmpRef, "http://example.com/schema", "AltText", "", "US", "Hello World", 0, &wResult);

    EXPECT_STREQ(wResult.errMessage, nullptr); // Empty generic language should be accepted

}

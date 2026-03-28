#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



class WXMPMeta_DeletePropertyTest : public ::testing::Test {

protected:

    XMPMeta* meta;

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    void SetUp() override {

        meta = new XMPMeta();

        xmpRef = XMPMetaPtr(meta);

    }



    void TearDown() override {

        delete meta;

    }

};



TEST_F(WXMPMeta_DeletePropertyTest_2015, DeleteProperty_NormalOperation_2015) {

    // Arrange

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "exampleProp";

    meta->SetProperty(schemaNS, propName, "value", 0);



    // Act

    WXMPMeta_DeleteProperty_1(xmpRef, schemaNS, propName, &wResult);



    // Assert

    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_FALSE(meta->DoesPropertyExist(schemaNS, propName));

}



TEST_F(WXMPMeta_DeletePropertyTest_2015, DeleteProperty_EmptySchemaNamespaceURI_2015) {

    // Arrange

    const char* schemaNS = "";

    const char* propName = "exampleProp";



    // Act & Assert

    EXPECT_THROW(WXMPMeta_DeleteProperty_1(xmpRef, schemaNS, propName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DeletePropertyTest_2015, DeleteProperty_NullSchemaNamespaceURI_2015) {

    // Arrange

    const char* schemaNS = nullptr;

    const char* propName = "exampleProp";



    // Act & Assert

    EXPECT_THROW(WXMPMeta_DeleteProperty_1(xmpRef, schemaNS, propName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DeletePropertyTest_2015, DeleteProperty_EmptyPropertyName_2015) {

    // Arrange

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "";



    // Act & Assert

    EXPECT_THROW(WXMPMeta_DeleteProperty_1(xmpRef, schemaNS, propName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DeletePropertyTest_2015, DeleteProperty_NullPropertyName_2015) {

    // Arrange

    const char* schemaNS = "http://example.com/schema";

    const char* propName = nullptr;



    // Act & Assert

    EXPECT_THROW(WXMPMeta_DeleteProperty_1(xmpRef, schemaNS, propName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DeletePropertyTest_2015, DeleteProperty_PropertyDoesNotExist_2015) {

    // Arrange

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "nonexistentProp";



    // Act

    WXMPMeta_DeleteProperty_1(xmpRef, schemaNS, propName, &wResult);



    // Assert

    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_FALSE(meta->DoesPropertyExist(schemaNS, propName));

}

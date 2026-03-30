#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



class WXMPMetaTest_2016 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpRef = new XMPMeta();

        wResult = new WXMP_Result();

    }



    void TearDown() override {

        delete static_cast<XMPMeta*>(xmpRef);

        delete wResult;

    }



    XMPMetaRef xmpRef;

    WXMP_Result* wResult;

};



TEST_F(WXMPMetaTest_2016, DeleteArrayItem_NormalOperation_2016) {

    // Assuming some setup to ensure array exists and is populated

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "exampleArray";

    XMP_Index itemIndex = 1;



    WXMPMeta_DeleteArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, wResult);



    EXPECT_EQ(wResult->errMessage, nullptr);

}



TEST_F(WXMPMetaTest_2016, DeleteArrayItem_EmptySchemaNamespaceURI_2016) {

    const char* emptySchemaNS = "";

    const char* arrayName = "exampleArray";

    XMP_Index itemIndex = 1;



    WXMPMeta_DeleteArrayItem_1(xmpRef, emptySchemaNS, arrayName, itemIndex, wResult);



    EXPECT_STREQ(wResult->errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_2016, DeleteArrayItem_EmptyArrayName_2016) {

    const char* schemaNS = "http://example.com/schema";

    const char* emptyArrayName = "";

    XMP_Index itemIndex = 1;



    WXMPMeta_DeleteArrayItem_1(xmpRef, schemaNS, emptyArrayName, itemIndex, wResult);



    EXPECT_STREQ(wResult->errMessage, "Empty array name");

}



TEST_F(WXMPMetaTest_2016, DeleteArrayItem_ItemIndexBoundaryCondition_2016) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "exampleArray";



    // Assuming the array has at least one item

    XMP_Index validItemIndex = 1;

    WXMPMeta_DeleteArrayItem_1(xmpRef, schemaNS, arrayName, validItemIndex, wResult);

    EXPECT_EQ(wResult->errMessage, nullptr);



    // Testing invalid boundary (assuming no items exist after the previous deletion)

    XMP_Index invalidItemIndex = 100;

    WXMPMeta_DeleteArrayItem_1(xmpRef, schemaNS, arrayName, invalidItemIndex, wResult);

    EXPECT_STREQ(wResult->errMessage, "Bad index");

}

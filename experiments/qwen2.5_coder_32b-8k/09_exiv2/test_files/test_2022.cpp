#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp"



class WXMPMeta_DoesQualifierExist_Test_2022 : public ::testing::Test {

protected:

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    void SetUp() override {

        // Assuming there's a way to create an XMPMetaRef, if not, this is a placeholder

        xmpRef = new XMPMeta();

        memset(&wResult, 0, sizeof(WXMP_Result));

    }



    void TearDown() override {

        delete static_cast<XMPMeta*>(xmpRef);

    }

};



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, NormalOperation_QualifierExists_2022) {

    const char* schemaNS = "http://purl.org/dc/elements/1.1/";

    const char* propName = "title";

    const char* qualNS = "http://www.w3.org/XML/1998/namespace";

    const char* qualName = "lang";



    // Assuming the qualifier exists in the meta data for this test

    WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult);



    EXPECT_EQ(wResult.int32Result, 1);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, NormalOperation_QualifierDoesNotExist_2022) {

    const char* schemaNS = "http://purl.org/dc/elements/1.1/";

    const char* propName = "title";

    const char* qualNS = "http://www.w3.org/XML/1998/namespace";

    const char* qualName = "nonexistent";



    WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult);



    EXPECT_EQ(wResult.int32Result, 0);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, BoundaryCondition_EmptySchemaNamespace_2022) {

    const char* schemaNS = "";

    const char* propName = "title";

    const char* qualNS = "http://www.w3.org/XML/1998/namespace";

    const char* qualName = "lang";



    EXPECT_THROW(WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, BoundaryCondition_NullSchemaNamespace_2022) {

    const char* schemaNS = nullptr;

    const char* propName = "title";

    const char* qualNS = "http://www.w3.org/XML/1998/namespace";

    const char* qualName = "lang";



    EXPECT_THROW(WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, BoundaryCondition_EmptyPropertyName_2022) {

    const char* schemaNS = "http://purl.org/dc/elements/1.1/";

    const char* propName = "";

    const char* qualNS = "http://www.w3.org/XML/1998/namespace";

    const char* qualName = "lang";



    EXPECT_THROW(WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, BoundaryCondition_NullPropertyName_2022) {

    const char* schemaNS = "http://purl.org/dc/elements/1.1/";

    const char* propName = nullptr;

    const char* qualNS = "http://www.w3.org/XML/1998/namespace";

    const char* qualName = "lang";



    EXPECT_THROW(WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, BoundaryCondition_EmptyQualNamespace_2022) {

    const char* schemaNS = "http://purl.org/dc/elements/1.1/";

    const char* propName = "title";

    const char* qualNS = "";

    const char* qualName = "lang";



    EXPECT_THROW(WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, BoundaryCondition_NullQualNamespace_2022) {

    const char* schemaNS = "http://purl.org/dc/elements/1.1/";

    const char* propName = "title";

    const char* qualNS = nullptr;

    const char* qualName = "lang";



    EXPECT_THROW(WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, BoundaryCondition_EmptyQualName_2022) {

    const char* schemaNS = "http://purl.org/dc/elements/1.1/";

    const char* propName = "title";

    const char* qualNS = "http://www.w3.org/XML/1998/namespace";

    const char* qualName = "";



    EXPECT_THROW(WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_DoesQualifierExist_Test_2022, BoundaryCondition_NullQualName_2022) {

    const char* schemaNS = "http://purl.org/dc/elements/1.1/";

    const char* propName = "title";

    const char* qualNS = "http://www.w3.org/XML/1998/namespace";

    const char* qualName = nullptr;



    EXPECT_THROW(WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, &wResult), XMP_Error);

}

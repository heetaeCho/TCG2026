#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp"

}



using namespace testing;



class WXMPMetaTest : public Test {

protected:

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    void SetUp() override {

        xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

        memset(&wResult, 0, sizeof(WXMP_Result));

    }



    void TearDown() override {

        delete reinterpret_cast<XMPMeta*>(xmpRef);

    }

};



TEST_F(WXMPMetaTest_SetProperty_2010, NormalOperation_2010) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "propName";

    const char* propValue = "propValue";



    WXMPMeta_SetProperty_1(xmpRef, schemaNS, propName, propValue, 0, &wResult);



    ASSERT_STREQ(wResult.errMessage, nullptr);

}



TEST_F(WXMPMetaTest_SetProperty_2010, EmptySchemaNamespaceURI_2010) {

    const char* schemaNS = "";

    const char* propName = "propName";

    const char* propValue = "propValue";



    WXMPMeta_SetProperty_1(xmpRef, schemaNS, propName, propValue, 0, &wResult);



    ASSERT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_SetProperty_2010, NullSchemaNamespaceURI_2010) {

    const char* schemaNS = nullptr;

    const char* propName = "propName";

    const char* propValue = "propValue";



    WXMPMeta_SetProperty_1(xmpRef, schemaNS, propName, propValue, 0, &wResult);



    ASSERT_STREQ(wResult.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPMetaTest_SetProperty_2010, EmptyPropertyName_2010) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "";

    const char* propValue = "propValue";



    WXMPMeta_SetProperty_1(xmpRef, schemaNS, propName, propValue, 0, &wResult);



    ASSERT_STREQ(wResult.errMessage, "Empty property name");

}



TEST_F(WXMPMetaTest_SetProperty_2010, NullPropertyName_2010) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = nullptr;

    const char* propValue = "propValue";



    WXMPMeta_SetProperty_1(xmpRef, schemaNS, propName, propValue, 0, &wResult);



    ASSERT_STREQ(wResult.errMessage, "Empty property name");

}



TEST_F(WXMPMetaTest_SetProperty_2010, NullPropertyValue_2010) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "propName";

    const char* propValue = nullptr;



    WXMPMeta_SetProperty_1(xmpRef, schemaNS, propName, propValue, 0, &wResult);



    ASSERT_STREQ(wResult.errMessage, nullptr);

}

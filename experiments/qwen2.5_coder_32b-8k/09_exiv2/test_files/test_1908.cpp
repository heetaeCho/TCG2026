#include <gtest/gtest.h>

#include "client-glue/WXMP_Common.hpp"

#include "TestProjects/exiv2/xmpsdk/src/XMPIterator.hpp"



class WXMPIteratorTest_1908 : public ::testing::Test {

protected:

    WXMP_Result wResult;



    void SetUp() override {

        wResult.errMessage = nullptr;

        wResult.ptrResult = nullptr;

        wResult.floatResult = 0.0;

        wResult.int64Result = 0;

        wResult.int32Result = 0;

    }



    void TearDown() override {

        if (wResult.ptrResult) {

            XMPIterator* iter = static_cast<XMPIterator*>(wResult.ptrResult);

            iter->clientRefs--;

            if (iter->clientRefs == 0) {

                delete iter;

            }

        }

    }

};



TEST_F(WXMPIteratorTest_1908, NormalOperation_1908) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_OptionBits options = 0;



    WXMPIterator_TableCTor_1(schemaNS, propName, options, &wResult);



    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_NE(wResult.ptrResult, nullptr);

}



TEST_F(WXMPIteratorTest_1908, NullSchemaAndPropName_1908) {

    XMP_StringPtr schemaNS = nullptr;

    XMP_StringPtr propName = nullptr;

    XMP_OptionBits options = 0;



    WXMPIterator_TableCTor_1(schemaNS, propName, options, &wResult);



    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_NE(wResult.ptrResult, nullptr);

}



TEST_F(WXMPIteratorTest_1908, EmptySchemaAndPropName_1908) {

    XMP_StringPtr schemaNS = "";

    XMP_StringPtr propName = "";

    XMP_OptionBits options = 0;



    WXMPIterator_TableCTor_1(schemaNS, propName, options, &wResult);



    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_NE(wResult.ptrResult, nullptr);

}



TEST_F(WXMPIteratorTest_1908, LargeSchemaAndPropName_1908) {

    std::string largeSchema(1024, 'a');

    std::string largePropName(1024, 'b');



    XMP_StringPtr schemaNS = largeSchema.c_str();

    XMP_StringPtr propName = largePropName.c_str();

    XMP_OptionBits options = 0;



    WXMPIterator_TableCTor_1(schemaNS, propName, options, &wResult);



    EXPECT_EQ(wResult.errMessage, nullptr);

    EXPECT_NE(wResult.ptrResult, nullptr);

}



TEST_F(WXMPIteratorTest_1908, InvalidOptions_1908) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_OptionBits options = 0xFFFFFFFF; // Assuming this is an invalid option set



    WXMPIterator_TableCTor_1(schemaNS, propName, options, &wResult);



    EXPECT_EQ(wResult.errMessage, nullptr); // Assuming the function does not fail with bad options

    EXPECT_NE(wResult.ptrResult, nullptr);

}

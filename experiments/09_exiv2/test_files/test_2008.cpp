#include <gtest/gtest.h>

#include "WXMPMeta.cpp"

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"



// Assuming XMPMetaRef can be created and destroyed properly in these tests.

// Mocking external collaborators or dependencies is not required here.



class WXMPMetaTest_2008 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary state before each test

        xmpRef = new XMPMeta();

    }



    void TearDown() override {

        // Clean up after each test

        delete xmpRef;

    }



    XMPMetaRef xmpRef;

};



TEST_F(WXMPMetaTest_2008, NormalOperation_2008) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = "ExampleStruct";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "ExampleField";

    XMP_StringPtr fieldValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    // Assuming SetStructField is available to set a value for testing

    xmpRef->SetStructField(schemaNS, structName, fieldNS, fieldName, "TestValue", 0);



    WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 1); // true for found

    EXPECT_STREQ(fieldValue, "TestValue");

}



TEST_F(WXMPMetaTest_2008, EmptySchemaNamespaceURI_2008) {

    XMP_StringPtr schemaNS = nullptr;

    XMP_StringPtr structName = "ExampleStruct";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "ExampleField";

    XMP_StringPtr fieldValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult), std::exception);

}



TEST_F(WXMPMetaTest_2008, EmptyStructName_2008) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = nullptr;

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "ExampleField";

    XMP_StringPtr fieldValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult), std::exception);

}



TEST_F(WXMPMetaTest_2008, EmptyFieldNamespaceURI_2008) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = "ExampleStruct";

    XMP_StringPtr fieldNS = nullptr;

    XMP_StringPtr fieldName = "ExampleField";

    XMP_StringPtr fieldValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult), std::exception);

}



TEST_F(WXMPMetaTest_2008, EmptyFieldName_2008) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = "ExampleStruct";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = nullptr;

    XMP_StringPtr fieldValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult), std::exception);

}



TEST_F(WXMPMetaTest_2008, FieldNotFound_2008) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = "ExampleStruct";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "NonExistentField";

    XMP_StringPtr fieldValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 0); // false for not found

}



TEST_F(WXMPMetaTest_2008, NullFieldPointer_2008) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = "ExampleStruct";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "ExampleField";

    XMP_StringPtr fieldValue = nullptr;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    // Assuming SetStructField is available to set a value for testing

    xmpRef->SetStructField(schemaNS, structName, fieldNS, fieldName, "TestValue", 0);



    WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 1); // true for found

    EXPECT_STREQ(fieldValue, "TestValue");

}



TEST_F(WXMPMetaTest_2008, NullValueSizePointer_2008) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = "ExampleStruct";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "ExampleField";

    XMP_StringPtr fieldValue;

    XMP_StringLen valueSize = nullptr;

    XMP_OptionBits options;

    WXMP_Result wResult;



    // Assuming SetStructField is available to set a value for testing

    xmpRef->SetStructField(schemaNS, structName, fieldNS, fieldName, "TestValue", 0);



    WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 1); // true for found

    EXPECT_STREQ(fieldValue, "TestValue");

}



TEST_F(WXMPMetaTest_2008, NullOptionsPointer_2008) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr structName = "ExampleStruct";

    XMP_StringPtr fieldNS = "http://example.com/field";

    XMP_StringPtr fieldName = "ExampleField";

    XMP_StringPtr fieldValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options = nullptr;

    WXMP_Result wResult;



    // Assuming SetStructField is available to set a value for testing

    xmpRef->SetStructField(schemaNS, structName, fieldNS, fieldName, "TestValue", 0);



    WXMPMeta_GetStructField_1(xmpRef, schemaNS, structName, fieldNS, fieldName, &fieldValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 1); // true for found

    EXPECT_STREQ(fieldValue, "TestValue");

}

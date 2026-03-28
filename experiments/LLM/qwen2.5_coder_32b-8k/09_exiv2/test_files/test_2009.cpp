#include <gtest/gtest.h>

#include "WXMPMeta.cpp"

#include "XMP_Const.h"



// Mock class to simulate XMPMetaRef and its behavior

class MockXMPMeta {

public:

    MOCK_CONST_METHOD7(GetQualifier, bool(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_StringPtr qualNS, XMP_StringPtr qualName, XMP_StringPtr * qualValue, XMP_StringLen * valueSize, XMP_OptionBits * options));

};



// Helper function to create an XMPMetaRef from a MockXMPMeta object

XMPMetaRef WtoXMPMeta_Ref(MockXMPMeta* mock) {

    return reinterpret_cast<XMPMetaRef>(mock);

}



class WXMPMeta_GetQualifier_Test : public ::testing::Test {

protected:

    MockXMPMeta mockXmpMeta;

    XMPMetaRef xmpRef;



    WXMPMeta_GetQualifier_Test() : xmpRef(WtoXMPMeta_Ref(&mockXmpMeta)) {}



    void SetUp() override {

        // Reset any previous expectations or results

        testing::Mock::VerifyAndClearExpectations(&mockXmpMeta);

    }

};



TEST_F(WXMPMeta_GetQualifier_Test, ValidInput_ReturnsTrue_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_CALL(mockXmpMeta, GetQualifier(schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options))

        .WillOnce(::testing::Return(true));



    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, 1);

}



TEST_F(WXMPMeta_GetQualifier_Test, ValidInput_ReturnsFalse_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_CALL(mockXmpMeta, GetQualifier(schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options))

        .WillOnce(::testing::Return(false));



    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, 0);

}



TEST_F(WXMPMeta_GetQualifier_Test, NullSchemaNS_ThrowsException_2009) {

    XMP_StringPtr schemaNS = nullptr;

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_GetQualifier_Test, EmptySchemaNS_ThrowsException_2009) {

    XMP_StringPtr schemaNS = "";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_GetQualifier_Test, NullPropName_ThrowsException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = nullptr;

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_GetQualifier_Test, EmptyPropName_ThrowsException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_GetQualifier_Test, NullQualNS_ThrowsException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = nullptr;

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_GetQualifier_Test, EmptyQualNS_ThrowsException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_GetQualifier_Test, NullQualName_ThrowsException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = nullptr;

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_GetQualifier_Test, EmptyQualName_ThrowsException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMeta_GetQualifier_Test, NullQualValue_DoesNotThrowException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr * qualValue = nullptr;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_CALL(mockXmpMeta, GetQualifier(schemaNS, propName, qualNS, qualName, &voidStringPtr, &valueSize, &options))

        .WillOnce(::testing::Return(false));



    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, qualValue, &valueSize, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, 0);

}



TEST_F(WXMPMeta_GetQualifier_Test, NullValueSize_DoesNotThrowException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen * valueSize = nullptr;

    XMP_OptionBits options;

    WXMP_Result wResult;



    EXPECT_CALL(mockXmpMeta, GetQualifier(schemaNS, propName, qualNS, qualName, &qualValue, &voidStringLen, &options))

        .WillOnce(::testing::Return(false));



    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, valueSize, &options, &wResult);



    EXPECT_EQ(wResult.int32Result, 0);

}



TEST_F(WXMPMeta_GetQualifier_Test, NullOptions_DoesNotThrowException_2009) {

    XMP_StringPtr schemaNS = "http://example.com/schema";

    XMP_StringPtr propName = "propertyName";

    XMP_StringPtr qualNS = "http://example.com/qualifier";

    XMP_StringPtr qualName = "qualifierName";

    XMP_StringPtr qualValue;

    XMP_StringLen valueSize;

    XMP_OptionBits * options = nullptr;

    WXMP_Result wResult;



    EXPECT_CALL(mockXmpMeta, GetQualifier(schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, &voidOptionBits))

        .WillOnce(::testing::Return(false));



    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, propName, qualNS, qualName, &qualValue, &valueSize, options, &wResult);



    EXPECT_EQ(wResult.int32Result, 0);

}

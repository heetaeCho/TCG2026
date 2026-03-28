#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "WXMP_Common.hpp"



// Mock XMPMeta class to simulate external collaborator behavior

class MockXMPMeta {

public:

    MOCK_METHOD5(SeparateArrayItems, void(XMP_StringPtr schemaNS, XMP_StringPtr arrayName, XMP_OptionBits options, XMP_StringPtr catedStr));

};



extern "C" {

    XMPMeta* WtoXMPMeta_Ptr(XMPMetaRef wxmpObj) {

        return reinterpret_cast<XMPMeta*>(wxmpObj);

    }

}



class WXMPUtilsTest_1955 : public ::testing::Test {

protected:

    MockXMPMeta mockXMPMeta;

    XMPMetaRef xmpObj = reinterpret_cast<XMPMetaRef>(&mockXMPMeta);

    WXMP_Result wResult;



    void SetUp() override {

        wResult.errMessage = nullptr;

        wResult.ptrResult = nullptr;

        wResult.floatResult = 0.0;

        wResult.int64Result = 0;

        wResult.int32Result = 0;

    }

};



TEST_F(WXMPUtilsTest_1955, NullWXMPObject_ThrowsBadParamError_1955) {

    EXPECT_THROW(WXMPUtils_SeparateArrayItems_1(nullptr, "schemaNS", "arrayName", 0, "", &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1955, EmptySchemaNamespaceURI_ThrowsBadSchemaError_1955) {

    EXPECT_THROW(WXMPUtils_SeparateArrayItems_1(xmpObj, nullptr, "arrayName", 0, "", &wResult), XMP_Error);

    EXPECT_THROW(WXMPUtils_SeparateArrayItems_1(xmpObj, "", "arrayName", 0, "", &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1955, EmptyArrayName_ThrowsBadXPathError_1955) {

    EXPECT_THROW(WXMPUtils_SeparateArrayItems_1(xmpObj, "schemaNS", nullptr, 0, "", &wResult), XMP_Error);

    EXPECT_THROW(WXMPUtils_SeparateArrayItems_1(xmpObj, "schemaNS", "", 0, "", &wResult), XMP_Error);

}



TEST_F(WXMPUtilsTest_1955, NullCatedStr_DoesNotThrowError_1955) {

    EXPECT_NO_THROW(WXMPUtils_SeparateArrayItems_1(xmpObj, "schemaNS", "arrayName", 0, nullptr, &wResult));

}



TEST_F(WXMPUtilsTest_1955, ValidParameters_CallsSeparateArrayItemsOnMockObject_1955) {

    EXPECT_CALL(mockXMPMeta, SeparateArrayItems("schemaNS", "arrayName", 0, "")).Times(1);

    WXMPUtils_SeparateArrayItems_1(xmpObj, "schemaNS", "arrayName", 0, "", &wResult);

}



TEST_F(WXMPUtilsTest_1955, NonEmptyCatedStr_CallsSeparateArrayItemsOnMockObject_1955) {

    EXPECT_CALL(mockXMPMeta, SeparateArrayItems("schemaNS", "arrayName", 0, "catedString")).Times(1);

    WXMPUtils_SeparateArrayItems_1(xmpObj, "schemaNS", "arrayName", 0, "catedString", &wResult);

}

#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



// Mock class for XMPMeta to verify interactions

class MockXMPMeta : public XMPMeta {

public:

    MOCK_METHOD5(SetProperty_Int, void(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_Int32 propValue, XMP_OptionBits options));

};



TEST_F(MockXMPMetaTest_2031, SetValidProperty_2031) {

    MockXMPMeta mockXmpMeta;

    WXMP_Result wResult;



    EXPECT_CALL(mockXmpMeta, SetProperty_Int("http://example.com/schema", "propertyName", 42, 0)).Times(1);



    WXMPMeta_SetProperty_Int_1(&mockXmpMeta, "http://example.com/schema", "propertyName", 42, 0, &wResult);

}



TEST_F(MockXMPMetaTest_2031, SetEmptySchemaNamespace_2031) {

    MockXMPMeta mockXmpMeta;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_SetProperty_Int_1(&mockXmpMeta, "", "propertyName", 42, 0, &wResult), XMP_Error);

}



TEST_F(MockXMPMetaTest_2031, SetNullSchemaNamespace_2031) {

    MockXMPMeta mockXmpMeta;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_SetProperty_Int_1(&mockXmpMeta, nullptr, "propertyName", 42, 0, &wResult), XMP_Error);

}



TEST_F(MockXMPMetaTest_2031, SetEmptyPropertyName_2031) {

    MockXMPMeta mockXmpMeta;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_SetProperty_Int_1(&mockXmpMeta, "http://example.com/schema", "", 42, 0, &wResult), XMP_Error);

}



TEST_F(MockXMPMetaTest_2031, SetNullPropertyName_2031) {

    MockXMPMeta mockXmpMeta;

    WXMP_Result wResult;



    EXPECT_THROW(WXMPMeta_SetProperty_Int_1(&mockXmpMeta, "http://example.com/schema", nullptr, 42, 0, &wResult), XMP_Error);

}

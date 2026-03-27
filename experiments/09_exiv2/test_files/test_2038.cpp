#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



// Mock XMPMeta class for testing purposes

class MockXMPMeta : public XMPMeta {

public:

    MOCK_METHOD(void, Clone, (XMPMeta * clone, XMP_OptionBits options), (const override));

};



TEST_F(WXMPMeta_CloneTest_2038, NormalOperation_2038) {

    MockXMPMeta mockOriginal;

    WXMP_Result result;



    EXPECT_CALL(mockOriginal, Clone(testing::NotNull(), testing::_))

        .WillOnce(testing::Return());



    XMPMetaRef xmpRef = &mockOriginal;

    XMP_OptionBits options = 0;



    WXMPMeta_Clone_1(xmpRef, options, &result);



    EXPECT_NE(result.ptrResult, nullptr);

}



TEST_F(WXMPMeta_CloneTest_2038, NullPointer_2038) {

    WXMP_Result result;

    XMP_OptionBits options = 0;



    // Test with null pointer for xmpRef

    WXMPMeta_Clone_1(nullptr, options, &result);



    EXPECT_EQ(result.ptrResult, nullptr);

}



TEST_F(WXMPMeta_CloneTest_2038, NullResultPointer_2038) {

    MockXMPMeta mockOriginal;



    XMPMetaRef xmpRef = &mockOriginal;

    XMP_OptionBits options = 0;



    // Test with null pointer for result

    WXMPMeta_Clone_1(xmpRef, options, nullptr);

}



TEST_F(WXMPMeta_CloneTest_2038, BoundaryOptions_2038) {

    MockXMPMeta mockOriginal;

    WXMP_Result result;



    EXPECT_CALL(mockOriginal, Clone(testing::NotNull(), testing::_))

        .WillOnce(testing::Return());



    XMPMetaRef xmpRef = &mockOriginal;

    XMP_OptionBits options = 0xFFFFFFFF; // Test with maximum option bits



    WXMPMeta_Clone_1(xmpRef, options, &result);



    EXPECT_NE(result.ptrResult, nullptr);

}

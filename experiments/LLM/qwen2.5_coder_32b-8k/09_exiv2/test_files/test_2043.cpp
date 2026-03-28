#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "WXMP_Common.hpp"

#include "XMPMeta.hpp"



// Mock class for XMPMetaRef

class MockXMPMeta {

public:

    MOCK_CONST_METHOD0(GetObjectOptions, XMP_OptionBits());

};



extern "C" {

    const XMPMeta& WtoXMPMeta_Ref(XMPMetaRef xmpRef) {

        return *static_cast<const MockXMPMeta*>(xmpRef);

    }

}



class WXMPMeta_GetObjectOptionsTest_2043 : public ::testing::Test {

protected:

    MockXMPMeta mockXMPMeta;

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockXMPMeta);

    WXMP_Result wResult;

};



TEST_F(WXMPMeta_GetObjectOptionsTest_2043, NormalOperation_ReturnsValidOptions_2043) {

    EXPECT_CALL(mockXMPMeta, GetObjectOptions()).WillOnce(::testing::Return(0x1F));

    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult);

    EXPECT_EQ(wResult.int32Result, 0x1F);

}



TEST_F(WXMPMeta_GetObjectOptionsTest_2043, ZeroOptions_ReturnsZero_2043) {

    EXPECT_CALL(mockXMPMeta, GetObjectOptions()).WillOnce(::testing::Return(0));

    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult);

    EXPECT_EQ(wResult.int32Result, 0);

}



TEST_F(WXMPMeta_GetObjectOptionsTest_2043, MaxOptionValue_ReturnsMaxValue_2043) {

    XMP_OptionBits maxOptions = std::numeric_limits<XMP_OptionBits>::max();

    EXPECT_CALL(mockXMPMeta, GetObjectOptions()).WillOnce(::testing::Return(maxOptions));

    WXMPMeta_GetObjectOptions_1(xmpRef, &wResult);

    EXPECT_EQ(wResult.int32Result, static_cast<int>(maxOptions));

}

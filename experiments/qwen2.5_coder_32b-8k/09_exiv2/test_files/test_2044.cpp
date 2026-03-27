#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



// Mocking external collaborators if needed (none in this case)

class MockXMPMeta : public XMPMeta {

public:

    MOCK_METHOD(void, SetObjectOptions, (XMP_OptionBits options), (override));

};



TEST_F(WXMPMetaTest_2044, SetObjectOptions_SetsOptionsCorrectly_2044) {

    // Arrange

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

    WXMP_Result wResult;

    XMP_OptionBits options = kXMPErr_NoMemory; // Example option



    // Act

    WXMPMeta_SetObjectOptions_1(xmpRef, options, &wResult);



    // Assert

    // Since we cannot access the internal state directly, we rely on observable behavior.

    // In this case, we assume that if no exception is thrown and wResult remains unchanged,

    // the operation was successful.



    EXPECT_EQ(wResult.errMessage, 0);

    delete reinterpret_cast<XMPMeta*>(xmpRef);

}



TEST_F(WXMPMetaTest_2044, SetObjectOptions_HandlesNullXMPMetaRef_2044) {

    // Arrange

    XMPMetaRef xmpRef = nullptr;

    WXMP_Result wResult;

    XMP_OptionBits options = kXMPErr_NoMemory; // Example option



    // Act & Assert

    EXPECT_DEATH(WXMPMeta_SetObjectOptions_1(xmpRef, options, &wResult), ".*");

}



TEST_F(WXMPMetaTest_2044, SetObjectOptions_HandlesNullWXMPResult_2044) {

    // Arrange

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

    WXMP_Result* wResult = nullptr;

    XMP_OptionBits options = kXMPErr_NoMemory; // Example option



    // Act & Assert

    EXPECT_DEATH(WXMPMeta_SetObjectOptions_1(xmpRef, options, wResult), ".*");

    delete reinterpret_cast<XMPMeta*>(xmpRef);

}



TEST_F(WXMPMetaTest_2044, SetObjectOptions_BoundaryCondition_MaxOptionBits_2044) {

    // Arrange

    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

    WXMP_Result wResult;

    XMP_OptionBits options = static_cast<XMP_OptionBits>(-1); // All bits set



    // Act

    WXMPMeta_SetObjectOptions_1(xmpRef, options, &wResult);



    // Assert

    EXPECT_EQ(wResult.errMessage, 0);

    delete reinterpret_cast<XMPMeta*>(xmpRef);

}

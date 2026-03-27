#include <gtest/gtest.h>

#include "XMPMeta.hpp"



// Assuming XMPMetaRef is a typedef for XMPMeta*

typedef XMPMeta* XMPMetaRef;



// Test fixture for WXMPMeta_DecrementRefCount_1

class WXMPMeta_DecrementRefCountTest_1992 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize the XMPMeta object

        xmpMeta = new XMPMeta();

        xmpRef = static_cast<XMPMetaRef>(xmpMeta);

        xmpMeta->clientRefs = 1; // Start with one reference count

    }



    virtual void TearDown() {

        // Clean up if needed, but the function should delete the object when ref count reaches 0

    }



    XMPMeta* xmpMeta;

    XMPMetaRef xmpRef;

};



// Test normal operation where ref count is decremented by 1 and object is not deleted

TEST_F(WXMPMeta_DecrementRefCountTest_1992, DecrementRefCount_Normal_1992) {

    WXMPMeta_DecrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta->clientRefs, 0);

}



// Test boundary condition where ref count is already 1 and will be deleted

TEST_F(WXMPMeta_DecrementRefCountTest_1992, DecrementRefCount_DeleteObject_1992) {

    WXMPMeta_DecrementRefCount_1(xmpRef);

    EXPECT_DEATH(WXMPMeta_DecrementRefCount_1(xmpRef), ".*"); // Expect crash if trying to access deleted object

}



// Test boundary condition where ref count is set to a higher value and then decremented multiple times

TEST_F(WXMPMeta_DecrementRefCountTest_1992, DecrementRefCount_MultipleTimes_1992) {

    xmpMeta->clientRefs = 3; // Set initial ref count to 3

    WXMPMeta_DecrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta->clientRefs, 2);



    WXMPMeta_DecrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta->clientRefs, 1);



    WXMPMeta_DecrementRefCount_1(xmpRef);

    EXPECT_DEATH(WXMPMeta_DecrementRefCount_1(xmpRef), ".*"); // Expect crash if trying to access deleted object

}



// Test exceptional case where ref count is 0 and function should not be called (assertion failure)

TEST_F(WXMPMeta_DecrementRefCountTest_1992, DecrementRefCount_ZeroRefCount_1992) {

    xmpMeta->clientRefs = 0; // Set initial ref count to 0

    EXPECT_DEATH(WXMPMeta_DecrementRefCount_1(xmpRef), ".*"); // Expect assertion failure due to zero ref count

}

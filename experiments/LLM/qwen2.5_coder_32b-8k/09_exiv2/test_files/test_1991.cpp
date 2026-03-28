#include <gtest/gtest.h>

#include "XMPMeta.hpp"



// Mock class for XMLParserAdapter if needed

class MockXMLParserAdapter : public XMLParserAdapter {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



TEST(WXMPMeta_IncrementRefCountTest_1991, NormalOperation_1991) {

    XMPMeta xmpMeta;

    XMPMetaRef xmpRef = static_cast<XMPMetaRef>(&xmpMeta);

    

    ASSERT_EQ(xmpMeta.clientRefs, 0);

    WXMPMeta_IncrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta.clientRefs, 1);

}



TEST(WXMPMeta_IncrementRefCountTest_1991, MultipleIncrements_1991) {

    XMPMeta xmpMeta;

    XMPMetaRef xmpRef = static_cast<XMPMetaRef>(&xmpMeta);

    

    ASSERT_EQ(xmpMeta.clientRefs, 0);

    WXMPMeta_IncrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta.clientRefs, 1);

    WXMPMeta_IncrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta.clientRefs, 2);

}



TEST(WXMPMeta_IncrementRefCountTest_1991, BoundaryConditionInitialValue_1991) {

    XMPMeta xmpMeta;

    XMPMetaRef xmpRef = static_cast<XMPMetaRef>(&xmpMeta);

    

    ASSERT_EQ(xmpMeta.clientRefs, 0);

    WXMPMeta_IncrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta.clientRefs, 1);

}



TEST(WXMPMeta_IncrementRefCountTest_1991, ExceptionalCaseNegativeReference_1991) {

    XMPMeta xmpMeta;

    XMPMetaRef xmpRef = static_cast<XMPMetaRef>(&xmpMeta);



    // Assuming the function does not throw or handle negative values explicitly

    ASSERT_EQ(xmpMeta.clientRefs, 0);

    WXMPMeta_IncrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta.clientRefs, 1);

    xmpMeta.clientRefs = -1; // Simulating an invalid state

    WXMPMeta_IncrementRefCount_1(xmpRef);

    EXPECT_EQ(xmpMeta.clientRefs, 0); // Should not go below 0

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming RDFTermKind and related constants are defined somewhere in the codebase

enum XMP_Uns8 {

    kRDFTerm_Description,

    // Add other possible values of RDFTermKind as needed for testing

};



extern bool IsOldTerm(RDFTermKind term);

extern bool IsCoreSyntaxTerm(RDFTermKind term);



// Mocking IsOldTerm and IsCoreSyntaxTerm if they are not defined in the test file

class MockRDFUtils {

public:

    MOCK_CONST_METHOD1(IsOldTermMock, bool(XMP_Uns8));

    MOCK_CONST_METHOD1(IsCoreSyntaxTermMock, bool(XMP_Uns8));

};



// Global mock objects for IsOldTerm and IsCoreSyntaxTerm

MockRDFUtils g_mockRDFUtils;



bool IsOldTerm(RDFTermKind term) {

    return g_mockRDFUtils.IsOldTermMock(term);

}



bool IsCoreSyntaxTerm(RDFTermKind term) {

    return g_mockRDFUtils.IsCoreSyntaxTermMock(term);

}



TEST(IsPropertyElementNameTest_2119, NormalOperation_Description_2119) {

    EXPECT_CALL(g_mockRDFUtils, IsOldTermMock(kRDFTerm_Description)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_Description));

}



TEST(IsPropertyElementNameTest_2119, NormalOperation_OldTerm_2119) {

    const XMP_Uns8 oldTerm = static_cast<XMP_Uns8>(42); // Assuming 42 is an old term for testing

    EXPECT_CALL(g_mockRDFUtils, IsOldTermMock(oldTerm)).WillOnce(::testing::Return(true));

    EXPECT_FALSE(IsPropertyElementName(oldTerm));

}



TEST(IsPropertyElementNameTest_2119, NormalOperation_CoreSyntaxTerm_2119) {

    const XMP_Uns8 coreSyntaxTerm = static_cast<XMP_Uns8>(43); // Assuming 43 is a core syntax term for testing

    EXPECT_CALL(g_mockRDFUtils, IsOldTermMock(coreSyntaxTerm)).WillOnce(::testing::Return(false));

    EXPECT_CALL(g_mockRDFUtils, IsCoreSyntaxTermMock(coreSyntaxTerm)).WillOnce(::testing::Return(true));

    EXPECT_FALSE(IsPropertyElementName(coreSyntaxTerm));

}



TEST(IsPropertyElementNameTest_2119, NormalOperation_OtherTerm_2119) {

    const XMP_Uns8 otherTerm = static_cast<XMP_Uns8>(44); // Assuming 44 is neither old term nor core syntax term for testing

    EXPECT_CALL(g_mockRDFUtils, IsOldTermMock(otherTerm)).WillOnce(::testing::Return(false));

    EXPECT_CALL(g_mockRDFUtils, IsCoreSyntaxTermMock(otherTerm)).WillOnce(::testing::Return(false));

    EXPECT_TRUE(IsPropertyElementName(otherTerm));

}



TEST(IsPropertyElementNameTest_2119, BoundaryCondition_MinValue_2119) {

    const XMP_Uns8 minValue = static_cast<XMP_Uns8>(0);

    EXPECT_CALL(g_mockRDFUtils, IsOldTermMock(minValue)).WillOnce(::testing::Return(false));

    EXPECT_CALL(g_mockRDFUtils, IsCoreSyntaxTermMock(minValue)).WillOnce(::testing::Return(false));

    EXPECT_TRUE(IsPropertyElementName(minValue));

}



TEST(IsPropertyElementNameTest_2119, BoundaryCondition_MaxValue_2119) {

    const XMP_Uns8 maxValue = static_cast<XMP_Uns8>(255);

    EXPECT_CALL(g_mockRDFUtils, IsOldTermMock(maxValue)).WillOnce(::testing::Return(false));

    EXPECT_CALL(g_mockRDFUtils, IsCoreSyntaxTermMock(maxValue)).WillOnce(::testing::Return(false));

    EXPECT_TRUE(IsPropertyElementName(maxValue));

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



// Mocking external collaborators if needed

class MockIfdId {

public:

    MOCK_CONST_METHOD0(asUint16, uint16_t());

};



TEST_F(ArrayDefTest_247, OperatorEqual_ReturnsTrueWhenIndicesMatch_247) {

    ArrayDef arrayDef;

    arrayDef.idx_ = 5;

    EXPECT_TRUE(arrayDef == 5);

}



TEST_F(ArrayDefTest_247, OperatorEqual_ReturnsFalseWhenIndicesDontMatch_247) {

    ArrayDef arrayDef;

    arrayDef.idx_ = 5;

    EXPECT_FALSE(arrayDef == 10);

}



TEST_F(ArrayDefTest_247, Size_ReturnsCountWhenTagAndGroupAreValid_247) {

    ArrayDef arrayDef;

    arrayDef.count_ = 3;

    MockIfdId mockGroup;

    EXPECT_CALL(mockGroup, asUint16()).WillRepeatedly(testing::Return(0));

    EXPECT_EQ(arrayDef.size(0x0100, mockGroup), 3);

}



TEST_F(ArrayDefTest_247, Size_ReturnsZeroWhenCountIsZero_247) {

    ArrayDef arrayDef;

    arrayDef.count_ = 0;

    MockIfdId mockGroup;

    EXPECT_CALL(mockGroup, asUint16()).WillRepeatedly(testing::Return(0));

    EXPECT_EQ(arrayDef.size(0x0100, mockGroup), 0);

}



TEST_F(ArrayDefTest_247, Size_HandlesBoundaryConditionsWithValidInputs_247) {

    ArrayDef arrayDef;

    arrayDef.count_ = UINT32_MAX;

    MockIfdId mockGroup;

    EXPECT_CALL(mockGroup, asUint16()).WillRepeatedly(testing::Return(0));

    EXPECT_EQ(arrayDef.size(0xFFFF, mockGroup), UINT32_MAX);

}



TEST_F(ArrayDefTest_247, Size_VerifiesExternalInteractionsWithMockGroup_247) {

    ArrayDef arrayDef;

    arrayDef.count_ = 1;

    MockIfdId mockGroup;

    EXPECT_CALL(mockGroup, asUint16()).Times(1);

    arrayDef.size(0x0100, mockGroup);

}

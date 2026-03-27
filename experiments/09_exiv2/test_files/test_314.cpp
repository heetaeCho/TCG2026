#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(uint16_t, tag, (), (const, override));

    MOCK_METHOD(byte*, start, (), (const, override));

};



TEST_F(TiffBinaryArrayTest_314, InitializeWithoutCfgSelFct_ReturnsTrue_314) {

    TiffBinaryArray tba(0x123, IfdId::rootIFD);

    MockTiffComponent mockRoot;

    EXPECT_CALL(mockRoot, tag()).WillOnce(testing::Return(0x123));

    EXPECT_TRUE(tba.initialize(&mockRoot));

}



TEST_F(TiffBinaryArrayTest_314, InitializeWithCfgSelFctValidIndex_ReturnsTrue_314) {

    TiffBinaryArray tba(0x123, IfdId::rootIFD, nullptr, 0, [](uint16_t tag, byte* pData, size_t size, TiffComponent* pRoot) { return 0; });

    MockTiffComponent mockRoot;

    EXPECT_CALL(mockRoot, tag()).WillOnce(testing::Return(0x123));

    EXPECT_TRUE(tba.initialize(&mockRoot));

}



TEST_F(TiffBinaryArrayTest_314, InitializeWithCfgSelFctInvalidIndex_ReturnsFalse_314) {

    TiffBinaryArray tba(0x123, IfdId::rootIFD, nullptr, 0, [](uint16_t tag, byte* pData, size_t size, TiffComponent* pRoot) { return -1; });

    MockTiffComponent mockRoot;

    EXPECT_CALL(mockRoot, tag()).WillOnce(testing::Return(0x123));

    EXPECT_FALSE(tba.initialize(&mockRoot));

}



TEST_F(TiffBinaryArrayTest_314, InitializeWithNullCfgSelFct_ReturnsTrue_314) {

    TiffBinaryArray tba(0x123, IfdId::rootIFD, nullptr, 0, nullptr);

    MockTiffComponent mockRoot;

    EXPECT_CALL(mockRoot, tag()).WillOnce(testing::Return(0x123));

    EXPECT_TRUE(tba.initialize(&mockRoot));

}



TEST_F(TiffBinaryArrayTest_314, InitializeWithMismatchedTag_ReturnsFalse_314) {

    TiffBinaryArray tba(0x123, IfdId::rootIFD, nullptr, 0, [](uint16_t tag, byte* pData, size_t size, TiffComponent* pRoot) { return -1; });

    MockTiffComponent mockRoot;

    EXPECT_CALL(mockRoot, tag()).WillOnce(testing::Return(0x456));

    EXPECT_FALSE(tba.initialize(&mockRoot));

}



TEST_F(TiffBinaryArrayTest_314, InitializeWithValidTag_ReturnsTrue_314) {

    TiffBinaryArray tba(0x123, IfdId::rootIFD, nullptr, 0, [](uint16_t tag, byte* pData, size_t size, TiffComponent* pRoot) { return 0; });

    MockTiffComponent mockRoot;

    EXPECT_CALL(mockRoot, tag()).WillOnce(testing::Return(0x123));

    EXPECT_TRUE(tba.initialize(&mockRoot));

}

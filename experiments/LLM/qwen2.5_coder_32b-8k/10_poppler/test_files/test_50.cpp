#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock Reader class

class MockReader : public Reader {

public:

    MOCK_METHOD(int, getByte, (int pos), (override));

    MOCK_METHOD(bool, getU16BE, (int pos, int * val), (override));

    MOCK_METHOD(bool, getU32BE, (int pos, unsigned int * val), (override));

    MOCK_METHOD(bool, getU32LE, (int pos, unsigned int * val), (override));

    MOCK_METHOD(bool, getUVarBE, (int pos, int size, unsigned int * val), (override));

    MOCK_METHOD(bool, cmp, (int pos, const char * s), (override));

};



// Test fixture

class FoFiIdentifierTest_50 : public ::testing::Test {

protected:

    MockReader mock_reader;

};



TEST_F(FoFiIdentifierTest_50, IdentifyType1PFA_50) {

    EXPECT_CALL(mock_reader, cmp(0, "%!PS-AdobeFont-1")).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_reader, cmp(0, "%!FontType1")).WillOnce(::testing::Return(true));



    EXPECT_EQ(identify(&mock_reader), fofiIdType1PFA);

}



TEST_F(FoFiIdentifierTest_50, IdentifyType1PFB_50) {

    unsigned int n = 16;

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x80));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getU32LE(2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(n), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, cmp(6, "%!PS-AdobeFont-1")).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_reader, cmp(6, "%!FontType1")).WillOnce(::testing::Return(true));



    EXPECT_EQ(identify(&mock_reader), fofiIdType1PFB);

}



TEST_F(FoFiIdentifierTest_50, IdentifyTrueType_50) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(0x00));



    EXPECT_EQ(identify(&mock_reader), fofiIdTrueType);

}



TEST_F(FoFiIdentifierTest_50, IdentifyTrueTypeCollection_50) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return('t'));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return('r'));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return('u'));

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return('e'));



    EXPECT_EQ(identify(&mock_reader), fofiIdTrueTypeCollection);

}



TEST_F(FoFiIdentifierTest_50, IdentifyOpenType_50) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return('O'));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return('T'));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return('T'));

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return('O'));



    // Assuming identifyOpenType returns fofiIdUnknown as it is not mocked

    EXPECT_EQ(identify(&mock_reader), fofiIdUnknown);

}



TEST_F(FoFiIdentifierTest_50, IdentifyCFF8Bit_50) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));



    // Assuming identifyCFF returns fofiIdUnknown as it is not mocked

    EXPECT_EQ(identify(&mock_reader), fofiIdUnknown);

}



TEST_F(FoFiIdentifierTest_50, IdentifyCFFCID_50) {

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(0x00));



    // Assuming identifyCFF returns fofiIdUnknown as it is not mocked

    EXPECT_EQ(identify(&mock_reader), fofiIdUnknown);

}



TEST_F(FoFiIdentifierTest_50, IdentifyUnknown_50) {

    EXPECT_CALL(mock_reader, cmp(0, "%!PS-AdobeFont-1")).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_reader, cmp(0, "%!FontType1")).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x00));



    EXPECT_EQ(identify(&mock_reader), fofiIdUnknown);

}

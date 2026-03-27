#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "FoFiIdentifier.h"



using namespace testing;



class MockReader : public Reader {

public:

    MOCK_METHOD(int, getByte, (int pos), (override));

    MOCK_METHOD(bool, getU16BE, (int pos, int * val), (override));

    MOCK_METHOD(bool, getU32BE, (int pos, unsigned int * val), (override));

    MOCK_METHOD(bool, getU32LE, (int pos, unsigned int * val), (override));

    MOCK_METHOD(bool, getUVarBE, (int pos, int size, unsigned int * val), (override));

    MOCK_METHOD(bool, cmp, (int pos, const char * s), (override));

};



class FoFiIdentifierTest_51 : public ::testing::Test {

protected:

    MockReader mock_reader;

};



TEST_F(FoFiIdentifierTest_51, NormalOperation_CFF8Bit_51) {

    EXPECT_CALL(mock_reader, getU16BE(4, _))

        .WillOnce(DoAll(SetArgReferee<1>(2), Return(true)));



    EXPECT_CALL(mock_reader, cmp(12, "CFF "))

        .WillOnce(Return(true));



    EXPECT_CALL(mock_reader, getU32BE(20, _))

        .WillOnce(DoAll(SetArgReferee<1>(50), Return(true)));



    EXPECT_CALL(mock_reader, getByte(50))  // Mocking identifyCFF which is not to be simulated but we need to simulate its effect

        .WillOnce(Return(8)); // Assuming this would lead to fofiIdCFF8Bit



    ASSERT_EQ(identifyOpenType(&mock_reader), fofiIdOpenTypeCFF8Bit);

}



TEST_F(FoFiIdentifierTest_51, NormalOperation_CFFCID_51) {

    EXPECT_CALL(mock_reader, getU16BE(4, _))

        .WillOnce(DoAll(SetArgReferee<1>(2), Return(true)));



    EXPECT_CALL(mock_reader, cmp(12, "CFF "))

        .WillOnce(Return(true));



    EXPECT_CALL(mock_reader, getU32BE(20, _))

        .WillOnce(DoAll(SetArgReferee<1>(50), Return(true)));



    EXPECT_CALL(mock_reader, getByte(50))  // Mocking identifyCFF which is not to be simulated but we need to simulate its effect

        .WillOnce(Return(9)); // Assuming this would lead to fofiIdCFFCID



    ASSERT_EQ(identifyOpenType(&mock_reader), fofiIdOpenTypeCFFCID);

}



TEST_F(FoFiIdentifierTest_51, NoTables_51) {

    EXPECT_CALL(mock_reader, getU16BE(4, _))

        .WillOnce(DoAll(SetArgReferee<1>(0), Return(true)));



    ASSERT_EQ(identifyOpenType(&mock_reader), fofiIdUnknown);

}



TEST_F(FoFiIdentifierTest_51, InvalidTableCount_51) {

    EXPECT_CALL(mock_reader, getU16BE(4, _))

        .WillOnce(Return(false));



    ASSERT_EQ(identifyOpenType(&mock_reader), fofiIdUnknown);

}



TEST_F(FoFiIdentifierTest_51, NonCFFTables_51) {

    EXPECT_CALL(mock_reader, getU16BE(4, _))

        .WillOnce(DoAll(SetArgReferee<1>(2), Return(true)));



    EXPECT_CALL(mock_reader, cmp(12, "CFF "))

        .Times(2)

        .WillRepeatedly(Return(false));



    ASSERT_EQ(identifyOpenType(&mock_reader), fofiIdUnknown);

}



TEST_F(FoFiIdentifierTest_51, OffsetTooLarge_51) {

    EXPECT_CALL(mock_reader, getU16BE(4, _))

        .WillOnce(DoAll(SetArgReferee<1>(2), Return(true)));



    EXPECT_CALL(mock_reader, cmp(12, "CFF "))

        .WillOnce(Return(true));



    EXPECT_CALL(mock_reader, getU32BE(20, _))

        .WillOnce(DoAll(SetArgReferee<1>(static_cast<unsigned int>(INT_MAX) + 1), Return(true)));



    ASSERT_EQ(identifyOpenType(&mock_reader), fofiIdUnknown);

}



TEST_F(FoFiIdentifierTest_51, GetU32BEFailure_51) {

    EXPECT_CALL(mock_reader, getU16BE(4, _))

        .WillOnce(DoAll(SetArgReferee<1>(2), Return(true)));



    EXPECT_CALL(mock_reader, cmp(12, "CFF "))

        .WillOnce(Return(true));



    EXPECT_CALL(mock_reader, getU32BE(20, _))

        .WillOnce(Return(false));



    ASSERT_EQ(identifyOpenType(&mock_reader), fofiIdUnknown);

}

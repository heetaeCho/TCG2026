#include <gtest/gtest.h>

#include <gmock/gmock.h>



class MockReader : public Reader {

public:

    MOCK_METHOD(int, getByte, (int pos), (override));

    MOCK_METHOD(bool, getU16BE, (int pos, int *val), (override));

    MOCK_METHOD(bool, getUVarBE, (int pos, int size, unsigned int *val), (override));

};



class IdentifyCFFTest_52 : public ::testing::Test {

protected:

    MockReader mock_reader;

};



TEST_F(IdentifyCFFTest_52, ValidCFFHeader_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset1 = 5;

    EXPECT_CALL(mock_reader, getUVarBE(10, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_CALL(mock_reader, getU16BE(17, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(19)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset0 = 3;

    EXPECT_CALL(mock_reader, getUVarBE(20, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset0), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getUVarBE(24, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_CALL(mock_reader, getByte(28)).WillOnce(::testing::Return(0x1d));

    EXPECT_CALL(mock_reader, getByte(30)).WillOnce(::testing::Return(12));

    EXPECT_CALL(mock_reader, getByte(31)).WillOnce(::testing::Return(30));



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdCFFCID);

}



TEST_F(IdentifyCFFTest_52, InvalidHeader_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x02));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, NegativeHdrSize_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(-1)); // hdrSize



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, InvalidOffSize0_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(0)); // offSize0



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, InvalidOffSize1FirstRead_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(5)); // offSize1



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, InvalidOffset1_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset1 = (unsigned int)INT_MAX + 1;

    EXPECT_CALL(mock_reader, getUVarBE(10, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, InvalidOffSize1SecondRead_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset1 = 5;

    EXPECT_CALL(mock_reader, getUVarBE(10, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_CALL(mock_reader, getU16BE(17, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(19)).WillOnce(::testing::Return(5)); // offSize1



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, InvalidOffset0_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset1 = 5;

    EXPECT_CALL(mock_reader, getUVarBE(10, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_CALL(mock_reader, getU16BE(17, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(19)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset0 = (unsigned int)INT_MAX + 1;

    EXPECT_CALL(mock_reader, getUVarBE(20, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset0), ::testing::Return(true)));



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, InvalidOffsetRelation_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset1 = 5;

    EXPECT_CALL(mock_reader, getUVarBE(10, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_CALL(mock_reader, getU16BE(17, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(19)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset0 = 6;

    EXPECT_CALL(mock_reader, getUVarBE(20, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset0), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getUVarBE(24, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, InvalidAdditionOverflow_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset1 = 5;

    EXPECT_CALL(mock_reader, getUVarBE(10, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_CALL(mock_reader, getU16BE(17, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(19)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset0 = 3;

    EXPECT_CALL(mock_reader, getUVarBE(20, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset0), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getUVarBE(24, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_EQ(identifyCFF(&mock_reader, INT_MAX - 30), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, ValidCFF8Bit_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset1 = 5;

    EXPECT_CALL(mock_reader, getUVarBE(10, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_CALL(mock_reader, getU16BE(17, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(19)).WillOnce(::testing::Return(2)); // offSize1



    unsigned int offset0 = 3;

    EXPECT_CALL(mock_reader, getUVarBE(20, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset0), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getUVarBE(24, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(offset1), ::testing::Return(true)));



    EXPECT_CALL(mock_reader, getByte(28)).WillOnce(::testing::Return(0x1c));



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdCFF8Bit);

}



TEST_F(IdentifyCFFTest_52, InvalidReads_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(false)));



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}



TEST_F(IdentifyCFFTest_52, InvalidUVarBE_52) {

    EXPECT_CALL(mock_reader, getByte(0)).WillOnce(::testing::Return(0x01));

    EXPECT_CALL(mock_reader, getByte(1)).WillOnce(::testing::Return(0x00));

    EXPECT_CALL(mock_reader, getByte(2)).WillOnce(::testing::Return(4)); // hdrSize

    EXPECT_CALL(mock_reader, getByte(3)).WillOnce(::testing::Return(2)); // offSize0



    EXPECT_CALL(mock_reader, getU16BE(7, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(1), ::testing::Return(true)));

    EXPECT_CALL(mock_reader, getByte(9)).WillOnce(::testing::Return(2)); // offSize1



    EXPECT_CALL(mock_reader, getUVarBE(10, 2, ::testing::_)).WillOnce(::testing::DoAll(::testing::SetArgReferee<2>(5), ::testing::Return(false)));



    EXPECT_EQ(identifyCFF(&mock_reader, 0), fofiIdUnknown);

}

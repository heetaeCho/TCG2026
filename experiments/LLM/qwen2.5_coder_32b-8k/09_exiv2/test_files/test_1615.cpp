#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sonymn_int.hpp"

#include "exif.hpp"



using namespace Exiv2::Internal;

using namespace ::testing;



class SonyMakerNoteTest_1615 : public Test {

protected:

    SonyMakerNote sonyMakerNote;

    NiceMock<MockValue> mockValue;

    NiceMock<MockExifData> mockMetadata;

};



TEST_F(SonyMakerNoteTest_1615, ValueCountNotOne_ReturnsFormattedString_1615) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(2));



    std::ostringstream os;

    sonyMakerNote.printSony2FpFocusPosition2(os, mockValue, &mockMetadata);



    EXPECT_EQ(os.str(), "(value)");

}



TEST_F(SonyMakerNoteTest_1615, MetadataIsNull_ReturnsFormattedString_1615) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));



    std::ostringstream os;

    sonyMakerNote.printSony2FpFocusPosition2(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "(value)");

}



TEST_F(SonyMakerNoteTest_1615, ModelStartsWithDSC_ReturnsN_A_1615) {

    std::string model = "DSC-RX100";

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(DoAll(SetArgReferee<0>(model), Return(true)));



    std::ostringstream os;

    sonyMakerNote.printSony2FpFocusPosition2(os, mockValue, &mockMetadata);



    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1615, ModelStartsWithStellar_ReturnsN_A_1615) {

    std::string model = "Stellar-01";

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(DoAll(SetArgReferee<0>(model), Return(true)));



    std::ostringstream os;

    sonyMakerNote.printSony2FpFocusPosition2(os, mockValue, &mockMetadata);



    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1615, ModelDoesNotStartWithKnownPrefix_ReturnsIntValue_1615) {

    std::string model = "UnknownModel";

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(DoAll(SetArgReferee<0>(model), Return(true)));

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(150));



    std::ostringstream os;

    sonyMakerNote.printSony2FpFocusPosition2(os, mockValue, &mockMetadata);



    EXPECT_EQ(os.str(), "150");

}



TEST_F(SonyMakerNoteTest_1615, ValueIs255_ReturnsInfinity_1615) {

    std::string model = "UnknownModel";

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(DoAll(SetArgReferee<0>(model), Return(true)));

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(255));



    std::ostringstream os;

    sonyMakerNote.printSony2FpFocusPosition2(os, mockValue, &mockMetadata);



    EXPECT_EQ(os.str(), "Infinity");

}



class MockExifData {

public:

    MOCK_METHOD(bool, getModel, (std::string&), (const));

};



class MockValue {

public:

    MOCK_METHOD(size_t, count, (), (const));

    MOCK_METHOD(int64_t, toInt64, (), (const));

};

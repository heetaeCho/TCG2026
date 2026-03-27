#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace ::testing;

using namespace Exiv2::Internal;



class SonyMakerNoteTest : public Test {

protected:

    Value value;

    std::ostringstream os;

    NiceMock<Exiv2::ExifData> metadata;



    SonyMakerNoteTest() : value(0) {}

};



TEST_F(SonyMakerNoteTest, printSonyMisc2bFocusPosition2_NormalOperation_1618) {

    EXPECT_CALL(metadata, count()).WillOnce(Return(1));

    EXPECT_CALL(metadata, getModel(_)).WillOnce(DoAll(SetArgReferee<0>("ILCE-7"), Return(true)));



    SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, &metadata);



    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(SonyMakerNoteTest, printSonyMisc2bFocusPosition2_MetadataNull_1618) {

    SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, nullptr);



    EXPECT_EQ(os.str(), "(" + value.toString() + ")");

}



TEST_F(SonyMakerNoteTest, printSonyMisc2bFocusPosition2_ValueCountNotOne_1618) {

    ON_CALL(value, count()).WillByDefault(Return(2));



    SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, &metadata);



    EXPECT_EQ(os.str(), "(" + value.toString() + ")");

}



TEST_F(SonyMakerNoteTest, printSonyMisc2bFocusPosition2_ModelNotFound_1618) {

    EXPECT_CALL(metadata, count()).WillOnce(Return(1));

    EXPECT_CALL(metadata, getModel(_)).WillOnce(DoAll(SetArgReferee<0>("UnknownModel"), Return(true)));



    SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, &metadata);



    EXPECT_EQ(os.str(), value.toString());

}



TEST_F(SonyMakerNoteTest, printSonyMisc2bFocusPosition2_ModelNotMatching_1618) {

    EXPECT_CALL(metadata, count()).WillOnce(Return(1));

    EXPECT_CALL(metadata, getModel(_)).WillOnce(DoAll(SetArgReferee<0>("NEX-5R"), Return(true)));



    SonyMakerNote::printSonyMisc2bFocusPosition2(os, value, &metadata);



    EXPECT_EQ(os.str(), value.toString());

}

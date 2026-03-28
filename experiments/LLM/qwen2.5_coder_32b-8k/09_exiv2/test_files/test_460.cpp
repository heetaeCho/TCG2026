#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <Exiv2/nikonmn_int.hpp>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_460 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    Value valueMock;

    const ExifData* exifDataMock = nullptr; // Assuming no interaction with this in the provided function

};



TEST_F(Nikon3MakerNoteTest_460, Print0x0002_SingleValue_460) {

    std::ostringstream os;

    EXPECT_CALL(valueMock, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(valueMock, toString()).WillOnce(::testing::Return("mockValue"));



    nikonMakerNote.print0x0002(os, valueMock, exifDataMock);



    EXPECT_EQ(os.str(), "(mockValue)");

}



TEST_F(Nikon3MakerNoteTest_460, Print0x0002_MultipleValues_460) {

    std::ostringstream os;

    EXPECT_CALL(valueMock, count()).WillOnce(::testing::Return(2));

    EXPECT_CALL(valueMock, toInt64(1)).WillOnce(::testing::Return(123));



    nikonMakerNote.print0x0002(os, valueMock, exifDataMock);



    EXPECT_EQ(os.str(), "123");

}



TEST_F(Nikon3MakerNoteTest_460, Print0x0002_ZeroValues_460) {

    std::ostringstream os;

    EXPECT_CALL(valueMock, count()).WillOnce(::testing::Return(0));



    nikonMakerNote.print0x0002(os, valueMock, exifDataMock);



    EXPECT_EQ(os.str(), "()");

}



TEST_F(Nikon3MakerNoteTest_460, Print0x0002_LargeCount_460) {

    std::ostringstream os;

    EXPECT_CALL(valueMock, count()).WillOnce(::testing::Return(10));

    EXPECT_CALL(valueMock, toInt64(1)).WillOnce(::testing::Return(456));



    nikonMakerNote.print0x0002(os, valueMock, exifDataMock);



    EXPECT_EQ(os.str(), "456");

}



TEST_F(Nikon3MakerNoteTest_460, Print0x0002_NegativeValue_460) {

    std::ostringstream os;

    EXPECT_CALL(valueMock, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(valueMock, toString()).WillOnce(::testing::Return("-mockValue"));



    nikonMakerNote.print0x0002(os, valueMock, exifDataMock);



    EXPECT_EQ(os.str(), "(-mockValue)");

}

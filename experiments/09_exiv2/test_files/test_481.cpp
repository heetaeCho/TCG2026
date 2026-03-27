#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/exiv2.hpp>



using namespace Exiv2::Internal;

using namespace testing;



class Nikon3MakerNoteTest_481 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    ExifData exifData;

};



TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_NormalOperation_481) {

    Value* value = new UShortValue(Exiv2::unsignedByte);

    value->makeArray(1);

    value->set(0, static_cast<Exiv2::uint16_t>(512));

    

    std::ostringstream os;

    nikon3MakerNote.printExitPupilPosition(os, *value, &exifData);



    EXPECT_EQ("4.0 mm", os.str());



    delete value;

}



TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_BoundaryValueCountZero_481) {

    Value* value = new UShortValue(Exiv2::unsignedByte);

    value->makeArray(0);



    std::ostringstream os;

    nikon3MakerNote.printExitPupilPosition(os, *value, &exifData);



    EXPECT_EQ("()()", os.str());



    delete value;

}



TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_BoundaryValueTypeMismatch_481) {

    Value* value = new UShortValue(Exiv2::signedLong);

    value->makeArray(1);

    value->set(0, static_cast<Exiv2::int64_t>(512));



    std::ostringstream os;

    nikon3MakerNote.printExitPupilPosition(os, *value, &exifData);



    EXPECT_EQ("()()", os.str());



    delete value;

}



TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_ErrorValueZero_481) {

    Value* value = new UShortValue(Exiv2::unsignedByte);

    value->makeArray(1);

    value->set(0, static_cast<Exiv2::uint16_t>(0));



    std::ostringstream os;

    nikon3MakerNote.printExitPupilPosition(os, *value, &exifData);



    EXPECT_EQ("()(0)", os.str());



    delete value;

}

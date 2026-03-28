#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/exif.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class OlympusMakerNoteTest_898 : public ::testing::Test {

protected:

    OlympusMakerNote olympusMakerNote;

    ExifData exifData;

};



TEST_F(OlympusMakerNoteTest_898, Print0x0204_NormalOperation_898) {

    Value* value = Value::create(TiffLong);

    value->read("1/3", 5);

    std::ostringstream os;

    olympusMakerNote.print0x0204(os, *value, &exifData);

    EXPECT_EQ(os.str(), "0.3x");

}



TEST_F(OlympusMakerNoteTest_898, Print0x0204_ValueCountZero_898) {

    Value* value = Value::create(TiffLong);

    std::ostringstream os;

    olympusMakerNote.print0x0204(os, *value, &exifData);

    EXPECT_EQ(os.str(), "(0)");

}



TEST_F(OlympusMakerNoteTest_898, Print0x0204_SecondRationalZero_898) {

    Value* value = Value::create(TiffLong);

    value->read("1/0", 3);

    std::ostringstream os;

    olympusMakerNote.print0x0204(os, *value, &exifData);

    EXPECT_EQ(os.str(), "(1/0)");

}



TEST_F(OlympusMakerNoteTest_898, Print0x0204_ValueZeroFloat_898) {

    Value* value = Value::create(TiffLong);

    value->read("0/1", 3);

    std::ostringstream os;

    olympusMakerNote.print0x0204(os, *value, &exifData);

    EXPECT_EQ(os.str(), "None");

}



TEST_F(OlympusMakerNoteTest_898, Print0x0204_ValueOneFloat_898) {

    Value* value = Value::create(TiffLong);

    value->read("1/1", 3);

    std::ostringstream os;

    olympusMakerNote.print0x0204(os, *value, &exifData);

    EXPECT_EQ(os.str(), "None");

}



TEST_F(OlympusMakerNoteTest_898, Print0x0204_NegativeFloatValue_898) {

    Value* value = Value::create(TiffLong);

    value->read("-3/1", 4);

    std::ostringstream os;

    olympusMakerNote.print0x0204(os, *value, &exifData);

    EXPECT_EQ(os.str(), "-3.0x");

}

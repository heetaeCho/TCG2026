#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/olympusmn_int.cpp"



using namespace Exiv2::Internal;



class OlympusMakerNoteTest_900 : public ::testing::Test {

protected:

    OlympusMakerNote maker_note_;

};



TEST_F(OlympusMakerNoteTest_900, Print0x0201_ReturnsValueStringForInvalidInput_900) {

    Value value;

    value.setValue(std::vector<long>{1, 2});

    ExifData exif_data;



    std::ostringstream os;

    maker_note_.print0x0201(os, value, &exif_data);



    EXPECT_EQ(os.str(), "[1 2]");

}



TEST_F(OlympusMakerNoteTest_900, Print0x0201_ReturnsSpecificLensTypeForValidInput_900) {

    Value value;

    value.setValue(std::vector<long>{0, 1, 0, 1, 2, 3});

    ExifData exif_data;



    std::ostringstream os;

    maker_note_.print0x0201(os, value, &exif_data);



    EXPECT_EQ(os.str(), "Olympus Zuiko Digital ED 50mm F2.0 Macro");

}



TEST_F(OlympusMakerNoteTest_900, Print0x0201_ReturnsValueStringForUnknownLensType_900) {

    Value value;

    value.setValue(std::vector<long>{99, 99, 99, 99, 99, 99});

    ExifData exif_data;



    std::ostringstream os;

    maker_note_.print0x0201(os, value, &exif_data);



    EXPECT_EQ(os.str(), "[99 99 99 99 99 99]");

}



TEST_F(OlympusMakerNoteTest_900, Print0x0201_ReturnsValueStringForIncorrectTypeId_900) {

    Value value;

    value.setValue(std::vector<long>{0, 1, 0, 1, 2, 3});

    value.setType(Exiv2::shortType);

    ExifData exif_data;



    std::ostringstream os;

    maker_note_.print0x0201(os, value, &exif_data);



    EXPECT_EQ(os.str(), "[0 1 0 1 2 3]");

}



TEST_F(OlympusMakerNoteTest_900, Print0x0201_ReturnsValueStringForIncorrectCount_900) {

    Value value;

    value.setValue(std::vector<long>{0, 1, 0});

    ExifData exif_data;



    std::ostringstream os;

    maker_note_.print0x0201(os, value, &exif_data);



    EXPECT_EQ(os.str(), "[0 1 0]");

}

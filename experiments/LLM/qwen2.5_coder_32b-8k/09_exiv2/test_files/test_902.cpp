#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/olympusmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class OlympusMakerNoteTest_902 : public ::testing::Test {

protected:

    OlympusMakerNote olympusMakerNote;

};



TEST_F(OlympusMakerNoteTest_902, PrintEq0x0301_ValidInput_ReturnsCorrectLabel_902) {

    struct ExifData dummyExifData;

    Value value;

    value.setValue(std::vector<uint8_t>({0, 0, 4, 0, 0, 0}));

    

    std::ostringstream os;

    olympusMakerNote.printEq0x0301(os, value, &dummyExifData);



    EXPECT_EQ(os.str(), "Olympus Zuiko Digital EC-14 1.4x Teleconverter");

}



TEST_F(OlympusMakerNoteTest_902, PrintEq0x0301_UnknownValue_ReturnsRawValue_902) {

    struct ExifData dummyExifData;

    Value value;

    value.setValue(std::vector<uint8_t>({1, 0, 1, 0, 0, 0}));

    

    std::ostringstream os;

    olympusMakerNote.printEq0x0301(os, value, &dummyExifData);



    EXPECT_EQ(os.str(), "1 0 1 0 0 0");

}



TEST_F(OlympusMakerNoteTest_902, PrintEq0x0301_WrongSize_ReturnsRawValue_902) {

    struct ExifData dummyExifData;

    Value value;

    value.setValue(std::vector<uint8_t>({0, 4, 0}));

    

    std::ostringstream os;

    olympusMakerNote.printEq0x0301(os, value, &dummyExifData);



    EXPECT_EQ(os.str(), "0 4 0");

}



TEST_F(OlympusMakerNoteTest_902, PrintEq0x0301_WrongType_ReturnsRawValue_902) {

    struct ExifData dummyExifData;

    Value value;

    value.typeId() = shortText; // Assuming shortText is a different type ID

    value.setValue(std::vector<uint8_t>({0, 4, 0, 0, 0, 0}));

    

    std::ostringstream os;

    olympusMakerNote.printEq0x0301(os, value, &dummyExifData);



    EXPECT_EQ(os.str(), "0 4 0 0 0 0");

}



TEST_F(OlympusMakerNoteTest_902, PrintEq0x0301_ZeroSize_ReturnsRawValue_902) {

    struct ExifData dummyExifData;

    Value value;

    value.setValue(std::vector<uint8_t>({}));

    

    std::ostringstream os;

    olympusMakerNote.printEq0x0301(os, value, &dummyExifData);



    EXPECT_EQ(os.str(), "");

}

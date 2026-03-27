#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include "exiv2/src/olympusmn_int.cpp"  // Assuming the class definition is included here



using namespace Exiv2::Internal;

using namespace testing;



class OlympusMakerNoteTest_905 : public Test {

protected:

    OlympusMakerNote olympusMakerNote;

    std::ostringstream output;

    ExifData exifData;  // Mock dependency if needed, but not used in this case

};



TEST_F(OlympusMakerNoteTest_905, Print0x1209_ValueCountNotTwo_905) {

    Value value;

    olympusMakerNote.print0x1209(output, value, &exifData);

    EXPECT_EQ(output.str(), "");

}



TEST_F(OlympusMakerNoteTest_905, Print0x1209_ValueTypeNotUnsignedShort_905) {

    Value value;

    value.typeId() = short;  // Assuming there's a way to set type, otherwise mock if needed

    olympusMakerNote.print0x1209(output, value, &exifData);

    EXPECT_EQ(output.str(), "");

}



TEST_F(OlympusMakerNoteTest_905, Print0x1209_ValueOff_905) {

    Value value;

    value.typeId() = unsignedShort;

    value.toInt64(0) = 0;

    value.toInt64(1) = 123;

    olympusMakerNote.print0x1209(output, value, &exifData);

    EXPECT_EQ(output.str(), "Off 123 ");

}



TEST_F(OlympusMakerNoteTest_905, Print0x1209_ValueOn_905) {

    Value value;

    value.typeId() = unsignedShort;

    value.toInt64(0) = 1;

    value.toInt64(1) = 456;

    olympusMakerNote.print0x1209(output, value, &exifData);

    EXPECT_EQ(output.str(), "On 456 ");

}



TEST_F(OlympusMakerNoteTest_905, Print0x1209_ValueDefault_905) {

    Value value;

    value.typeId() = unsignedShort;

    value.toInt64(0) = 2;  // Default case

    value.toInt64(1) = 789;

    olympusMakerNote.print0x1209(output, value, &exifData);

    EXPECT_EQ(output.str(), "2 789 ");

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using namespace testing;



class Nikon3MakerNoteTest_483 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

};



TEST_F(Nikon3MakerNoteTest_483, PrintRepeatingFlashRate_ValueCountNotOne_483) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedByte, 2); // count != 1

    nikon3MakerNote.printRepeatingFlashRate(os, value, nullptr);

    EXPECT_EQ(os.str(), "(0 0 )");

}



TEST_F(Nikon3MakerNoteTest_483, PrintRepeatingFlashRate_ValueTypeNotUnsignedByte_483) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::shortType, 1); // type != unsignedByte

    nikon3MakerNote.printRepeatingFlashRate(os, value, nullptr);

    EXPECT_EQ(os.str(), "(0 )");

}



TEST_F(Nikon3MakerNoteTest_483, PrintRepeatingFlashRate_ValueZero_483) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedByte, 1);

    value[0] = 0; // temp == 0

    nikon3MakerNote.printRepeatingFlashRate(os, value, nullptr);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_483, PrintRepeatingFlashRate_Value255_483) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedByte, 1);

    value[0] = 255; // temp == 255

    nikon3MakerNote.printRepeatingFlashRate(os, value, nullptr);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_483, PrintRepeatingFlashRate_ValueNormal_483) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedByte, 1);

    value[0] = 5; // normal value

    nikon3MakerNote.printRepeatingFlashRate(os, value, nullptr);

    EXPECT_EQ(os.str(), " 5 Hz");

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/exiv2.hpp>



using namespace Exiv2::Internal;

using ::testing::_;



class Nikon3MakerNoteTest_484 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    std::ostringstream os;

};



TEST_F(Nikon3MakerNoteTest_484, PrintRepeatingFlashCount_NormalOperation_484) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1, 5); // Set a typical value



    nikon3MakerNote.printRepeatingFlashCount(os, value, nullptr);



    EXPECT_EQ("5", os.str());

}



TEST_F(Nikon3MakerNoteTest_484, PrintRepeatingFlashCount_ValueCountNotOne_484) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(2, 5, 10); // Set multiple values



    nikon3MakerNote.printRepeatingFlashCount(os, value, nullptr);



    EXPECT_EQ("(5 10)", os.str());

}



TEST_F(Nikon3MakerNoteTest_484, PrintRepeatingFlashCount_ValueTypeNotUnsignedByte_484) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::shortType);

    value.modify(1, 5); // Set a typical value with wrong type



    nikon3MakerNote.printRepeatingFlashCount(os, value, nullptr);



    EXPECT_EQ("(5)", os.str());

}



TEST_F(Nikon3MakerNoteTest_484, PrintRepeatingFlashCount_ValueZero_484) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1, 0); // Set zero



    nikon3MakerNote.printRepeatingFlashCount(os, value, nullptr);



    EXPECT_EQ("n/a", os.str());

}



TEST_F(Nikon3MakerNoteTest_484, PrintRepeatingFlashCount_Value255_484) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1, 255); // Set 255



    nikon3MakerNote.printRepeatingFlashCount(os, value, nullptr);



    EXPECT_EQ("n/a", os.str());

}

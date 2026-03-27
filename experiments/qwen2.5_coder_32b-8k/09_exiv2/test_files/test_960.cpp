#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class CanonMakerNoteTest_960 : public ::testing::Test {

protected:

    CanonMakerNote canMakerNote;

    std::ostringstream os;

};



TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_NormalValue_960) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(4500);

    canMakerNote.printSi0x0013(os, value, nullptr);

    EXPECT_EQ(os.str(), "45.0 m");

}



TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_ZeroValue_960) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0);

    canMakerNote.printSi0x0013(os, value, nullptr);

    EXPECT_EQ(os.str(), "0.0 m");

}



TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_InfiniteValue_960) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0xffff);

    canMakerNote.printSi0x0013(os, value, nullptr);

    EXPECT_EQ(os.str(), "Infinite");

}



TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_WrongType_960) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString);

    value.modify("test");

    canMakerNote.printSi0x0013(os, value, nullptr);

    EXPECT_EQ(os.str(), "test");

}



TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_EmptyValue_960) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    canMakerNote.printSi0x0013(os, value, nullptr);

    EXPECT_EQ(os.str(), "");

}

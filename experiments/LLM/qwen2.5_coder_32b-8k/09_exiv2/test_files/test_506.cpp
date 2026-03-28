#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>

#include <sstream>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    Value value;

    std::ostringstream os;

};



TEST_F(Nikon3MakerNoteTest_506, PutIncreasesCount_ValidInput_506) {

    value = Exiv2::Value::create(Exiv2::unsignedShort);

    for (int i = 0; i < 10; ++i) {

        value.setValue(i, static_cast<uint16_t>(i));

    }

    nikonMakerNote.print0x009e(os, value, nullptr);

    EXPECT_EQ("0; 1; 2; 3; 4; 5; 6; 7; 8; 9", os.str());

}



TEST_F(Nikon3MakerNoteTest_506, PutIncreasesCount_TrimZeros_506) {

    value = Exiv2::Value::create(Exiv2::unsignedShort);

    for (int i = 0; i < 10; ++i) {

        value.setValue(i, static_cast<uint16_t>(i % 3 == 0 ? 0 : i));

    }

    nikonMakerNote.print0x009e(os, value, nullptr);

    EXPECT_EQ("1; 2; 4; 5; 7; 8", os.str());

}



TEST_F(Nikon3MakerNoteTest_506, PutIncreasesCount_AllZeros_506) {

    value = Exiv2::Value::create(Exiv2::unsignedShort);

    for (int i = 0; i < 10; ++i) {

        value.setValue(i, static_cast<uint16_t>(0));

    }

    nikonMakerNote.print0x009e(os, value, nullptr);

    EXPECT_EQ("", os.str());

}



TEST_F(Nikon3MakerNoteTest_506, PutIncreasesCount_InvalidType_506) {

    value = Exiv2::Value::create(Exiv2::asciiString);

    nikonMakerNote.print0x009e(os, value, nullptr);

    EXPECT_EQ("", os.str());

}



TEST_F(Nikon3MakerNoteTest_506, PutIncreasesCount_InvalidCount_506) {

    value = Exiv2::Value::create(Exiv2::unsignedShort);

    for (int i = 0; i < 9; ++i) {

        value.setValue(i, static_cast<uint16_t>(i));

    }

    nikonMakerNote.print0x009e(os, value, nullptr);

    EXPECT_EQ("", os.str());

}



TEST_F(Nikon3MakerNoteTest_506, PutIncreasesCount_OutOfRangeValue_506) {

    value = Exiv2::Value::create(Exiv2::unsignedShort);

    for (int i = 0; i < 10; ++i) {

        value.setValue(i, static_cast<uint16_t>(9999)); // Assuming 9999 is out of range

    }

    nikonMakerNote.print0x009e(os, value, nullptr);

    EXPECT_EQ("Unknown (9999); Unknown (9999); Unknown (9999); Unknown (9999); Unknown (9999); "

              "Unknown (9999); Unknown (9999); Unknown (9999); Unknown (9999); Unknown (9999)", os.str());

}

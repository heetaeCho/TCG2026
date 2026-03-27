#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/exiv2.hpp>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Nikon3MakerNoteTest_482 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    Value value;

};



TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_NormalOperation_482) {

    std::ostringstream os;

    value = Value::create(Exiv2::unsignedByte);

    value.copy(10); // Normal value



    nikonMakerNote.printFlashFocalLength(os, value, nullptr);



    EXPECT_EQ(os.str(), "10 mm");

}



TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_BoundaryValueZero_482) {

    std::ostringstream os;

    value = Value::create(Exiv2::unsignedByte);

    value.copy(0); // Boundary value



    nikonMakerNote.printFlashFocalLength(os, value, nullptr);



    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_BoundaryValueMax_482) {

    std::ostringstream os;

    value = Value::create(Exiv2::unsignedByte);

    value.copy(255); // Boundary value



    nikonMakerNote.printFlashFocalLength(os, value, nullptr);



    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_ValueCountNotOne_482) {

    std::ostringstream os;

    value = Value::create(Exiv2::unsignedByte);

    value.copy(10);

    value.copy(20); // Invalid count



    nikonMakerNote.printFlashFocalLength(os, value, nullptr);



    EXPECT_EQ(os.str(), "(10 20)");

}



TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_ValueTypeNotUnsignedByte_482) {

    std::ostringstream os;

    value = Value::create(Exiv2::short); // Invalid type

    value.copy(10);



    nikonMakerNote.printFlashFocalLength(os, value, nullptr);



    EXPECT_EQ(os.str(), "(10)");

}

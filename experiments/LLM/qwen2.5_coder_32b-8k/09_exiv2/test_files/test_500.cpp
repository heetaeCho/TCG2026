#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.cpp"



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_500 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    std::ostringstream os;

};



TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_NormalOperation_500) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1);

    value.toUint32(0, 10); // Setting the value to 10



    nikon3MakerNote.printCameraExposureCompensation(os, value, nullptr);



    EXPECT_EQ(os.str(), "Flash compensation: +1.6 EV");

}



TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_BoundaryValue_Zero_500) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1);

    value.toUint32(0, 0); // Setting the value to 0



    nikon3MakerNote.printCameraExposureCompensation(os, value, nullptr);



    EXPECT_EQ(os.str(), "Flash compensation: +0.0 EV");

}



TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_BoundaryValue_Maximum_500) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1);

    value.toUint32(0, 255); // Setting the value to 255



    nikon3MakerNote.printCameraExposureCompensation(os, value, nullptr);



    EXPECT_EQ(os.str(), "Flash compensation: +40.8 EV");

}



TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_ValueCountNotOne_500) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(2); // Setting count to 2



    nikon3MakerNote.printCameraExposureCompensation(os, value, nullptr);



    EXPECT_EQ(os.str(), "(value)");

}



TEST_F(Nikon3MakerNoteTest_500, PrintCameraExposureCompensation_ValueTypeNotUnsignedByte_500) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::short); // Using short type instead of unsigned byte



    nikon3MakerNote.printCameraExposureCompensation(os, value, nullptr);



    EXPECT_EQ(os.str(), "(value)");

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include "TestProjects/exiv2/src/olympusmn_int.cpp"



namespace Exiv2 {

namespace Internal {



class OlympusMakerNoteTest_903 : public ::testing::Test {

protected:

    OlympusMakerNote olympusMakerNote;

    std::ostringstream os;

};



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_SingleAF_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 0); // Single AF

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "Single AF0");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_SequentialAF_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 1); // Sequential shooting AF

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "Sequential shooting AF1");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_ContinuousAF_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 2); // Continuous AF

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "Continuous AF2");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_MultiAF_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 3); // Multi AF

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "Multi AF3");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_FaceDetect_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 4); // Face detect

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "Face detect4");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_MF_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 10); // MF

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "MF10");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_SAF_CAF_MF_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 0); // SAF

    value.modify(1, 0x0015); // C-AF (4), MF (16)

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "C-AF, MF1");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_MultiAF_FaceDetect_ImagerAF_AFsensor_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort);

    value.modify(0, 0); // Not used

    value.modify(1, 0x0175); // Multi AF (4), Face detect (32), Imager AF (64), AF sensor (256)

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "Multi AF, Face detect, Imager AF, AF sensor1");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_InvalidType_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString); // Invalid type

    value.modify(0, 0);

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "(string)");

}



TEST_F(OlympusMakerNoteTest_903, PrintCs0x0301_ZeroCount_903) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedShort); // Zero count

    olympusMakerNote.printCs0x0301(os, value, nullptr);

    EXPECT_EQ(os.str(), "(value)");

}



} // namespace Internal

} // namespace Exiv2

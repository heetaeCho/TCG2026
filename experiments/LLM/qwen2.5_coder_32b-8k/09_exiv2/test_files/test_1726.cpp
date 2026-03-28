#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include "exiv2/src/sigmamn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SigmaMakerNoteTest_1726 : public ::testing::Test {

protected:

    SigmaMakerNote sigmaMakerNote_;

    std::ostringstream outputStream_;

};



TEST_F(SigmaMakerNoteTest_1726, Print0x0008_ProgramMode_1726) {

    Value value;

    value.setValue("P");

    sigmaMakerNote_.print0x0008(outputStream_, value, nullptr);

    EXPECT_EQ(outputStream_.str(), "Program");

}



TEST_F(SigmaMakerNoteTest_1726, Print0x0008_AperturePriorityMode_1726) {

    Value value;

    value.setValue("A");

    sigmaMakerNote_.print0x0008(outputStream_, value, nullptr);

    EXPECT_EQ(outputStream_.str(), "Aperture priority");

}



TEST_F(SigmaMakerNoteTest_1726, Print0x0008_ShutterPriorityMode_1726) {

    Value value;

    value.setValue("S");

    sigmaMakerNote_.print0x0008(outputStream_, value, nullptr);

    EXPECT_EQ(outputStream_.str(), "Shutter priority");

}



TEST_F(SigmaMakerNoteTest_1726, Print0x0008_ManualMode_1726) {

    Value value;

    value.setValue("M");

    sigmaMakerNote_.print0x0008(outputStream_, value, nullptr);

    EXPECT_EQ(outputStream_.str(), "Manual");

}



TEST_F(SigmaMakerNoteTest_1726, Print0x0008_DefaultCase_1726) {

    Value value;

    value.setValue("X"); // Invalid mode

    sigmaMakerNote_.print0x0008(outputStream_, value, nullptr);

    EXPECT_EQ(outputStream_.str(), "(X)");

}



TEST_F(SigmaMakerNoteTest_1726, Print0x0008_EmptyString_1726) {

    Value value;

    value.setValue("");

    sigmaMakerNote_.print0x0008(outputStream_, value, nullptr);

    EXPECT_EQ(outputStream_.str(), "( )");

}



TEST_F(SigmaMakerNoteTest_1726, Print0x0008_LongString_1726) {

    Value value;

    value.setValue("PLongValue");

    sigmaMakerNote_.print0x0008(outputStream_, value, nullptr);

    EXPECT_EQ(outputStream_.str(), "Program");

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/canonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class CanonMakerNoteTest_957 : public ::testing::Test {

protected:

    CanonMakerNote cannmaker_note_;

};



TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_ValueZero_957) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metadatumMkvalue(Exiv2::int64_t(0)));

    cannmaker_note_.printSi0x000c(os, value, nullptr);

    EXPECT_EQ("--", os.str());

}



TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_ValueNonZero_957) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metadatumMkvalue(Exiv2::int64_t(138)));

    cannmaker_note_.printSi0x000c(os, value, nullptr);

    EXPECT_EQ("10 °C", os.str());

}



TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_ValueBoundaryCondition_957) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metadatumMkvalue(Exiv2::int64_t(128)));

    cannmaker_note_.printSi0x000c(os, value, nullptr);

    EXPECT_EQ("0 °C", os.str());

}



TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_ValueNegative_957) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metadatumMkvalue(Exiv2::int64_t(100)));

    cannmaker_note_.printSi0x000c(os, value, nullptr);

    EXPECT_EQ("-28 °C", os.str());

}

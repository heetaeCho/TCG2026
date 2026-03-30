#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include <Exiv2/exiv2.hpp>



using namespace Exiv2::Internal;



class PentaxMakerNoteTest_198 : public ::testing::Test {

protected:

    PentaxMakerNote pentaxMakerNote;

};



TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_NormalOperation_198) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metaRational);

    value.rational(0) = Exiv2::URational(512, 256); // 2 EV

    pentaxMakerNote.printFlashCompensation(os, value, nullptr);

    EXPECT_EQ(os.str(), "2 EV");

}



TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_ZeroValue_198) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metaNumeric);

    value.long_(0); // 0 EV

    pentaxMakerNote.printFlashCompensation(os, value, nullptr);

    EXPECT_EQ(os.str(), "0 EV");

}



TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_NegativeValue_198) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metaNumeric);

    value.long_(-256); // -1 EV

    pentaxMakerNote.printFlashCompensation(os, value, nullptr);

    EXPECT_EQ(os.str(), "-1 EV");

}



TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_BoundaryValue_198) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metaNumeric);

    value.long_(1); // 0.00390625 EV

    pentaxMakerNote.printFlashCompensation(os, value, nullptr);

    EXPECT_EQ(os.str(), "4e-03 EV");

}



TEST_F(PentaxMakerNoteTest_198, PrintFlashCompensation_HighValue_198) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metaNumeric);

    value.long_(65536); // 256 EV

    pentaxMakerNote.printFlashCompensation(os, value, nullptr);

    EXPECT_EQ(os.str(), "256 EV");

}

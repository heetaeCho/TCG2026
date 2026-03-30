#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/exiv2.hpp>



using namespace Exiv2::Internal;



class MinoltaMakerNoteTest_1004 : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

};



TEST_F(MinoltaMakerNoteTest_1004, PrintMinoltaFocalLengthStd_NormalOperation_1004) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metInt32);

    value.modify(9); // (9 / 3) - 2 = 1

    minoltaMakerNote.printMinoltaFocalLengthStd(os, value, nullptr);

    EXPECT_EQ(os.str(), "1");

}



TEST_F(MinoltaMakerNoteTest_1004, PrintMinoltaFocalLengthStd_ZeroValue_1004) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metInt32);

    value.modify(0); // (0 / 3) - 2 = -2

    minoltaMakerNote.printMinoltaFocalLengthStd(os, value, nullptr);

    EXPECT_EQ(os.str(), "-2");

}



TEST_F(MinoltaMakerNoteTest_1004, PrintMinoltaFocalLengthStd_NegativeValue_1004) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metInt32);

    value.modify(-6); // (-6 / 3) - 2 = -4

    minoltaMakerNote.printMinoltaFocalLengthStd(os, value, nullptr);

    EXPECT_EQ(os.str(), "-4");

}



TEST_F(MinoltaMakerNoteTest_1004, PrintMinoltaFocalLengthStd_LargeValue_1004) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::metInt32);

    value.modify(1005); // (1005 / 3) - 2 = 331

    minoltaMakerNote.printMinoltaFocalLengthStd(os, value, nullptr);

    EXPECT_EQ(os.str(), "331");

}

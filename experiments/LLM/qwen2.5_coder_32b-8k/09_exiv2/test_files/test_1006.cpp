#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "minoltamn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class MinoltaMakerNoteTest_1006 : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

    std::ostringstream os;

};



TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_NormalOperation_1006) {

    Exiv2::Value value(Exiv2::valueTypeString);

    value.modify(197385);  // Example value representing 00:03:00



    minoltaMakerNote.printMinoltaTimeStd(os, value, nullptr);



    EXPECT_EQ("00:03:00", os.str());

}



TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_BoundaryConditionZero_1006) {

    Exiv2::Value value(Exiv2::valueTypeString);

    value.modify(0);  // Example value representing 00:00:00



    minoltaMakerNote.printMinoltaTimeStd(os, value, nullptr);



    EXPECT_EQ("00:00:00", os.str());

}



TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_BoundaryConditionMaxValue_1006) {

    Exiv2::Value value(Exiv2::valueTypeString);

    value.modify(16777215);  // Example value representing 99:99:99



    minoltaMakerNote.printMinoltaTimeStd(os, value, nullptr);



    EXPECT_EQ("99:99:99", os.str());

}



TEST_F(MinoltaMakerNoteTest_1006, PrintMinoltaTimeStd_ExceptionalCaseNegativeValue_1006) {

    Exiv2::Value value(Exiv2::valueTypeString);

    value.modify(-1);  // Example negative value



    minoltaMakerNote.printMinoltaTimeStd(os, value, nullptr);



    EXPECT_EQ("99:99:255", os.str());  // Since -1 % 65536 is 65535 and further broken down

}

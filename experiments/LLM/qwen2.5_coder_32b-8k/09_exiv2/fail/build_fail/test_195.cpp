#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/src/pentaxmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class PentaxMakerNoteTest_195 : public ::testing::Test {

protected:

    PentaxMakerNote pentaxMakerNote;

};



TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_NormalOperation_195) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeLong(300); // 3.0 mm

    pentaxMakerNote.printFocalLength(os, value, nullptr);

    EXPECT_EQ("3.0 mm", os.str());

}



TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_BoundaryCondition_Zero_195) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeLong(0); // 0.0 mm

    pentaxMakerNote.printFocalLength(os, value, nullptr);

    EXPECT_EQ("0.0 mm", os.str());

}



TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_BoundaryCondition_Max_195) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeLong(std::numeric_limits<int64_t>::max()); // max possible value

    pentaxMakerNote.printFocalLength(os, value, nullptr);

    EXPECT_THAT(os.str(), HasSubstr(" mm")); // exact value is less important than format

}



TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_ExceptionalCase_NegativeValue_195) {

    std::ostringstream os;

    Exiv2::Value value;

    value.makeLong(-300); // -3.0 mm (unusual but should handle)

    pentaxMakerNote.printFocalLength(os, value, nullptr);

    EXPECT_EQ("-3.0 mm", os.str());

}

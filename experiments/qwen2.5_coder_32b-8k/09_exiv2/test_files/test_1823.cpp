#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/casiomn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using namespace testing;



class Casio2MakerNoteTest : public Test {

protected:

    Casio2MakerNote casio2MakerNote;

};



TEST_F(Casio2MakerNoteTest_1823, Print0x2022_NormalOperation_LessThanThreshold_1823) {

    std::stringstream ss;

    Value value;

    value.setValue(19999999); // Less than 0x20000000

    casio2MakerNote.print0x2022(ss, value, nullptr);

    EXPECT_EQ(ss.str(), "19.99 m");

}



TEST_F(Casio2MakerNoteTest_1823, Print0x2022_NormalOperation_EqualToThreshold_1823) {

    std::stringstream ss;

    Value value;

    value.setValue(0x20000000); // Equal to 0x20000000

    casio2MakerNote.print0x2022(ss, value, nullptr);

    EXPECT_EQ(ss.str(), "Inf");

}



TEST_F(Casio2MakerNoteTest_1823, Print0x2022_NormalOperation_GreaterThanThreshold_1823) {

    std::stringstream ss;

    Value value;

    value.setValue(0x20000001); // Greater than 0x20000000

    casio2MakerNote.print0x2022(ss, value, nullptr);

    EXPECT_EQ(ss.str(), "Inf");

}



TEST_F(Casio2MakerNoteTest_1823, Print0x2022_BoundaryCondition_Zero_1823) {

    std::stringstream ss;

    Value value;

    value.setValue(0); // Boundary condition: zero

    casio2MakerNote.print0x2022(ss, value, nullptr);

    EXPECT_EQ(ss.str(), "0.00 m");

}



TEST_F(Casio2MakerNoteTest_1823, Print0x2022_BoundaryCondition_MaxInt64_1823) {

    std::stringstream ss;

    Value value;

    value.setValue(std::numeric_limits<int64_t>::max()); // Boundary condition: max int64

    casio2MakerNote.print0x2022(ss, value, nullptr);

    EXPECT_EQ(ss.str(), "Inf");

}



TEST_F(Casio2MakerNoteTest_1823, Print0x2022_ExceptionalCase_NegativeValue_1823) {

    std::stringstream ss;

    Value value;

    value.setValue(-1); // Exceptional case: negative value

    casio2MakerNote.print0x2022(ss, value, nullptr);

    EXPECT_EQ(ss.str(), "-0.00 m");

}

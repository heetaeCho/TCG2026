#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/src/minoltamn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::StrEq;



class MinoltaMakerNoteTest_1008 : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

    std::ostringstream os;

    Value value;

};



TEST_F(MinoltaMakerNoteTest_1008, PrintMinoltaWhiteBalanceStd_NormalOperation_1008) {

    int64_t testValue = 512; // Example value that should output "2"

    value._content = &testValue;



    minoltaMakerNote.printMinoltaWhiteBalanceStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "2");

}



TEST_F(MinoltaMakerNoteTest_1008, PrintMinoltaWhiteBalanceStd_BoundaryCondition_Zero_1008) {

    int64_t testValue = 0; // Boundary condition: zero

    value._content = &testValue;



    minoltaMakerNote.printMinoltaWhiteBalanceStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "0");

}



TEST_F(MinoltaMakerNoteTest_1008, PrintMinoltaWhiteBalanceStd_BoundaryCondition_MaxInt64_1008) {

    int64_t testValue = INT64_MAX; // Boundary condition: max int64

    value._content = &testValue;



    minoltaMakerNote.printMinoltaWhiteBalanceStd(os, value, nullptr);



    EXPECT_EQ(os.str(), std::to_string(INT64_MAX / 256));

}



TEST_F(MinoltaMakerNoteTest_1008, PrintMinoltaWhiteBalanceStd_BoundaryCondition_MinInt64_1008) {

    int64_t testValue = INT64_MIN; // Boundary condition: min int64

    value._content = &testValue;



    minoltaMakerNote.printMinoltaWhiteBalanceStd(os, value, nullptr);



    EXPECT_EQ(os.str(), std::to_string(INT64_MIN / 256));

}



TEST_F(MinoltaMakerNoteTest_1008, PrintMinoltaWhiteBalanceStd_ExceptionalCase_ValuePtrNull_1008) {

    value._content = nullptr;



    minoltaMakerNote.printMinoltaWhiteBalanceStd(os, value, nullptr);



    EXPECT_EQ(os.str(), "");

}

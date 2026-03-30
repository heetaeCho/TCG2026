#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/pentaxmn_int.cpp"



using namespace Exiv2::Internal;



class PentaxMakerNoteTest_197 : public ::testing::Test {

protected:

    PentaxMakerNote pentaxMakerNote;

    std::ostringstream oss;

};



TEST_F(PentaxMakerNoteTest_197, PrintTemperature_NormalOperation_197) {

    Exiv2::Value value(Exiv2::valueInt64);

    value.setInt64(25);



    std::ostream& result = pentaxMakerNote.printTemperature(oss, value, nullptr);



    EXPECT_EQ(result.str(), "25 C");

}



TEST_F(PentaxMakerNoteTest_197, PrintTemperature_BoundaryCondition_Zero_197) {

    Exiv2::Value value(Exiv2::valueInt64);

    value.setInt64(0);



    std::ostream& result = pentaxMakerNote.printTemperature(oss, value, nullptr);



    EXPECT_EQ(result.str(), "0 C");

}



TEST_F(PentaxMakerNoteTest_197, PrintTemperature_BoundaryCondition_Negative_197) {

    Exiv2::Value value(Exiv2::valueInt64);

    value.setInt64(-30);



    std::ostream& result = pentaxMakerNote.printTemperature(oss, value, nullptr);



    EXPECT_EQ(result.str(), "-30 C");

}



TEST_F(PentaxMakerNoteTest_197, PrintTemperature_BoundaryCondition_MaxValue_197) {

    Exiv2::Value value(Exiv2::valueInt64);

    value.setInt64(std::numeric_limits<int64_t>::max());



    std::ostream& result = pentaxMakerNote.printTemperature(oss, value, nullptr);



    EXPECT_EQ(result.str(), std::to_string(std::numeric_limits<int64_t>::max()) + " C");

}



TEST_F(PentaxMakerNoteTest_197, PrintTemperature_BoundaryCondition_MinValue_197) {

    Exiv2::Value value(Exiv2::valueInt64);

    value.setInt64(std::numeric_limits<int64_t>::min());



    std::ostream& result = pentaxMakerNote.printTemperature(oss, value, nullptr);



    EXPECT_EQ(result.str(), std::to_string(std::numeric_limits<int64_t>::min()) + " C");

}

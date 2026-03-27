#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/pentaxmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class PentaxMakerNoteTest_194 : public ::testing::Test {

protected:

    PentaxMakerNote makerNote;

};



TEST_F(PentaxMakerNoteTest_194, PrintFValue_NormalOperation_194) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::valueTypeSize);

    value.modify(35); // Example value for testing



    makerNote.printFValue(os, value, nullptr);



    EXPECT_EQ("F3.5", os.str());

}



TEST_F(PentaxMakerNoteTest_194, PrintFValue_BoundaryCondition_Zero_194) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::valueTypeSize);

    value.modify(0);



    makerNote.printFValue(os, value, nullptr);



    EXPECT_EQ("F0", os.str());

}



TEST_F(PentaxMakerNoteTest_194, PrintFValue_BoundaryCondition_MaxInt64_194) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::valueTypeSize);

    value.modify(std::numeric_limits<int64_t>::max());



    makerNote.printFValue(os, value, nullptr);



    EXPECT_EQ("F" + std::to_string(static_cast<double>(std::numeric_limits<int64_t>::max()) / 10), os.str());

}



TEST_F(PentaxMakerNoteTest_194, PrintFValue_BoundaryCondition_MinInt64_194) {

    std::ostringstream os;

    Exiv2::Value value(Exiv2::valueTypeSize);

    value.modify(std::numeric_limits<int64_t>::min());



    makerNote.printFValue(os, value, nullptr);



    EXPECT_EQ("F" + std::to_string(static_cast<double>(std::numeric_limits<int64_t>::min()) / 10), os.str());

}



TEST_F(PentaxMakerNoteTest_194, PrintFValue_ExceptionalCase_ValueTypeMismatch_194) {

    // Assuming that the implementation will not throw an exception for different value types

    std::ostringstream os;

    Exiv2::Value value(Exiv2::valueTypeUndefined); // Different type



    makerNote.printFValue(os, value, nullptr);



    EXPECT_EQ("F0", os.str()); // Should handle gracefully and not crash

}

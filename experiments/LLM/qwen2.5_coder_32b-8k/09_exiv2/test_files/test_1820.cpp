#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "casiomn_int.cpp"  // Adjust include path as necessary



using namespace Exiv2::Internal;

using ::testing::_;



class CasioMakerNoteTest_1820 : public ::testing::Test {

protected:

    CasioMakerNote casioMakerNote;

    std::ostringstream os;

};



TEST_F(CasioMakerNoteTest_1820, Print0x0006_NormalOperation_1820) {

    Exiv2::Value value;

    value.setValue(1500);  // Example value



    std::ostream& resultStream = casioMakerNote.print0x0006(os, value, nullptr);



    EXPECT_EQ(resultStream.str(), "1.50 m");

}



TEST_F(CasioMakerNoteTest_1820, Print0x0006_BoundaryZero_1820) {

    Exiv2::Value value;

    value.setValue(0);  // Boundary case



    std::ostream& resultStream = casioMakerNote.print0x0006(os, value, nullptr);



    EXPECT_EQ(resultStream.str(), "0.00 m");

}



TEST_F(CasioMakerNoteTest_1820, Print0x0006_BoundaryNegative_1820) {

    Exiv2::Value value;

    value.setValue(-500);  // Boundary case



    std::ostream& resultStream = casioMakerNote.print0x0006(os, value, nullptr);



    EXPECT_EQ(resultStream.str(), "-0.50 m");

}



TEST_F(CasioMakerNoteTest_1820, Print0x0006_LargeValue_1820) {

    Exiv2::Value value;

    value.setValue(999999);  // Large value



    std::ostream& resultStream = casioMakerNote.print0x0006(os, value, nullptr);



    EXPECT_EQ(resultStream.str(), "999.99 m");

}

```



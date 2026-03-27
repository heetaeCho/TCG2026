#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "TestProjects/exiv2/src/canonmn_int.cpp" // Adjust the path if necessary



using namespace Exiv2::Internal;



class CanonMakerNoteTest_958 : public ::testing::Test {

protected:

    CanonMakerNote makerNote;

};



TEST_F(CanonMakerNoteTest_958, PrintSi0x000d_NormalOperation_958) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(1024); // Example value that is not 65535



    makerNote.printSi0x000d(os, value, nullptr);



    EXPECT_EQ(os.str(), "32");

}



TEST_F(CanonMakerNoteTest_958, PrintSi0x000d_BoundaryCondition_MaxValue_958) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(65535); // Boundary condition



    makerNote.printSi0x000d(os, value, nullptr);



    EXPECT_EQ(os.str(), "--");

}



TEST_F(CanonMakerNoteTest_958, PrintSi0x000d_BoundaryCondition_ZeroValue_958) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(0); // Boundary condition



    makerNote.printSi0x000d(os, value, nullptr);



    EXPECT_EQ(os.str(), "0");

}



TEST_F(CanonMakerNoteTest_958, PrintSi0x000d_ExceptionalCase_NegativeValue_958) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue(-1); // Exceptional case



    makerNote.printSi0x000d(os, value, nullptr);



    EXPECT_EQ(os.str(), "-0.03125");

}

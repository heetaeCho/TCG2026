#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/canonmn_int.cpp"



using namespace Exiv2::Internal;



class CanonMakerNoteTest_951 : public ::testing::Test {

protected:

    CanonMakerNote canonChange;

    Value mockValue;

};



TEST_F(CanonMakerNoteTest_951, PrintCsLens_NormalOperation_951) {

    std::ostringstream os;

    mockValue.typeId_ = unsignedShort;  // Assuming typeId is a public member for testing

    mockValue.size_ = 3;                // Assuming size is a public member for testing

    mockValue.data_.push_back(200);       // Example data, assuming data is a public member for testing

    mockValue.data_.push_back(100);

    mockValue.data_.push_back(50);



    canonChange.printCsLens(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "4.0 - 2.0 mm");

}



TEST_F(CanonMakerNoteTest_951, PrintCsLens_BoundaryCondition_CountLessThanThree_951) {

    std::ostringstream os;

    mockValue.typeId_ = unsignedShort;  // Assuming typeId is a public member for testing

    mockValue.size_ = 2;                // Less than 3



    canonChange.printCsLens(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "(Value())");

}



TEST_F(CanonMakerNoteTest_951, PrintCsLens_BoundaryCondition_TypeIdNotUnsignedShort_951) {

    std::ostringstream os;

    mockValue.typeId_ = long;  // Not unsignedShort

    mockValue.size_ = 3;



    canonChange.printCsLens(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "(Value())");

}



TEST_F(CanonMakerNoteTest_951, PrintCsLens_ExceptionalCase_ZeroFu_951) {

    std::ostringstream os;

    mockValue.typeId_ = unsignedShort;  // Assuming typeId is a public member for testing

    mockValue.size_ = 3;                // Assuming size is a public member for testing

    mockValue.data_.push_back(0);         // Fu will be zero



    canonChange.printCsLens(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "Value()");

}



TEST_F(CanonMakerNoteTest_951, PrintCsLens_EqualLengths_951) {

    std::ostringstream os;

    mockValue.typeId_ = unsignedShort;  // Assuming typeId is a public member for testing

    mockValue.size_ = 3;                // Assuming size is a public member for testing

    mockValue.data_.push_back(100);       // Example data, assuming data is a public member for testing

    mockValue.data_.push_back(50);

    mockValue.data_.push_back(2);



    canonChange.printCsLens(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "25.0 mm");

}

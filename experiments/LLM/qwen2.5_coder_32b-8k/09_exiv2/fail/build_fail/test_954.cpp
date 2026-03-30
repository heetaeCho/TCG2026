#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.cpp" // Assuming the header or relevant declarations are in this file



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class CanonMakerNoteTest_954 : public ::testing::Test {

protected:

    CanonMakerNote canoni;

    std::ostringstream os;

};



TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_NormalOperation_954) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::unsignedShort;

    value.size_ = 1;

    value.pData_ = new uint16_t(1); // log2 of the EV value



    canoni.printSi0x0002(os, value, nullptr);



    EXPECT_EQ(os.str(), "3.125");

}



TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_ZeroEVValue_954) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::unsignedShort;

    value.size_ = 1;

    value.pData_ = new uint16_t(0); // log2 of the EV value



    canoni.printSi0x0002(os, value, nullptr);



    EXPECT_EQ(os.str(), "3.125");

}



TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_BoundaryCondition_MaxValue_954) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::unsignedShort;

    value.size_ = 1;

    value.pData_ = new uint16_t(65535); // log2 of the EV value



    canoni.printSi0x0002(os, value, nullptr);



    EXPECT_EQ(os.str(), "3.789430783205128e+1921");

}



TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_TypeMismatch_954) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::signedLong;

    value.size_ = 1;

    value.pData_ = new int32_t(1);



    canoni.printSi0x0002(os, value, nullptr);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_CountZero_954) {

    Exiv2::Value value;

    value.typeId_ = Exiv2::unsignedShort;

    value.size_ = 0;

    value.pData_ = new uint16_t(1);



    canoni.printSi0x0002(os, value, nullptr);



    EXPECT_EQ(os.str(), "");

}

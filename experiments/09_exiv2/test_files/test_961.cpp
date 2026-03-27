#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "canonmn_int.cpp" // Assuming this is how the header/implementation is included



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class CanonMakerNoteTest_961 : public testing::Test {

protected:

    CanonMakerNote canMakerNote;

    Value mockValue;

    ExifData exifData;



    void SetUp() override {

        // Setup any common state here if needed

    }

};



TEST_F(CanonMakerNoteTest_961, NormalOperation_PositiveValue_961) {

    std::ostringstream os;

    mockValue.typeId_ = unsignedShort; // Simulating the type ID for unsigned short

    mockValue.count_ = 1; // Setting count to 1 for a single value

    mockValue.toInt64_ = []() { return 2048; }; // Example value that should convert correctly



    canMakerNote.printSi0x0015(os, mockValue, &exifData);



    EXPECT_THAT(os.str(), HasSubstr("F3.5"));

}



TEST_F(CanonMakerNoteTest_961, NormalOperation_ZeroCount_961) {

    std::ostringstream os;

    mockValue.typeId_ = unsignedShort; // Simulating the type ID for unsigned short

    mockValue.count_ = 0; // Setting count to 0



    canMakerNote.printSi0x0015(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_961, BoundaryCondition_ZeroValue_961) {

    std::ostringstream os;

    mockValue.typeId_ = unsignedShort; // Simulating the type ID for unsigned short

    mockValue.count_ = 1; // Setting count to 1 for a single value

    mockValue.toInt64_ = []() { return 0; }; // Zero value



    canMakerNote.printSi0x0015(os, mockValue, &exifData);



    EXPECT_THAT(os.str(), HasSubstr("F1"));

}



TEST_F(CanonMakerNoteTest_961, BoundaryCondition_MaxValue_961) {

    std::ostringstream os;

    mockValue.typeId_ = unsignedShort; // Simulating the type ID for unsigned short

    mockValue.count_ = 1; // Setting count to 1 for a single value

    mockValue.toInt64_ = []() { return 65535; }; // Maximum value for unsigned short



    canMakerNote.printSi0x0015(os, mockValue, &exifData);



    EXPECT_THAT(os.str(), HasSubstr("F")); // Specific expected output is dependent on actual function logic

}



TEST_F(CanonMakerNoteTest_961, ErrorCase_WrongTypeId_961) {

    std::ostringstream os;

    mockValue.typeId_ = short; // Incorrect type ID

    mockValue.count_ = 1; // Setting count to 1 for a single value



    canMakerNote.printSi0x0015(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "");

}

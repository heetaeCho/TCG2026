#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include "nikonmn_int.cpp"  // Assuming this file contains the Nikon1MakerNote class



using namespace Exiv2::Internal;



class Nikon1MakerNoteTest : public ::testing::Test {

protected:

    Nikon1MakerNote nikonMakerNote;

    std::ostringstream os;

};



TEST_F(Nikon1MakerNoteTest_453, Print0x0085_UnknownValue_453) {

    Exiv2::Value value;  // Assuming Value is a class that can be default constructed

    value.toRational = []() -> std::pair<int64_t, int64_t> { return {0, 1}; };

    nikonMakerNote.print0x0085(os, value, nullptr);

    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(Nikon1MakerNoteTest_453, Print0x0085_ValidRationalValue_453) {

    Exiv2::Value value;  // Assuming Value is a class that can be default constructed

    value.toRational = []() -> std::pair<int64_t, int64_t> { return {100, 5}; };

    nikonMakerNote.print0x0085(os, value, nullptr);

    EXPECT_EQ(os.str(), "20.00 m");

}



TEST_F(Nikon1MakerNoteTest_453, Print0x0085_ZeroDenominator_453) {

    Exiv2::Value value;  // Assuming Value is a class that can be default constructed

    value.toRational = []() -> std::pair<int64_t, int64_t> { return {100, 0}; };

    nikonMakerNote.print0x0085(os, value, nullptr);

    EXPECT_EQ(os.str(), "(Value object)");  // Assuming the string representation of Value is "Value object"

}



TEST_F(Nikon1MakerNoteTest_453, Print0x0085_NegativeRationalValue_453) {

    Exiv2::Value value;  // Assuming Value is a class that can be default constructed

    value.toRational = []() -> std::pair<int64_t, int64_t> { return {-100, 5}; };

    nikonMakerNote.print0x0085(os, value, nullptr);

    EXPECT_EQ(os.str(), "-20.00 m");

}



TEST_F(Nikon1MakerNoteTest_453, Print0x0085_LargeRationalValue_453) {

    Exiv2::Value value;  // Assuming Value is a class that can be default constructed

    value.toRational = []() -> std::pair<int64_t, int64_t> { return {999999999, 1000}; };

    nikonMakerNote.print0x0085(os, value, nullptr);

    EXPECT_EQ(os.str(), "999999999.00 m");

}

```



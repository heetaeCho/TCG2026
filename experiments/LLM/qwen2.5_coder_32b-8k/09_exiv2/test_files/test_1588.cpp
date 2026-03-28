#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/sonymn_int.cpp"

#include <sstream>

#include <cstdint>



using namespace Exiv2::Internal;

using ::testing::_;



class SonyMakerNoteTest_1588 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote_;

    std::ostringstream oss_;

    ExifData exifData_;  // Assuming ExifData is a necessary dependency, though not mocked in this case

};



TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_ValidValue_1588) {

    Value value;

    value.setValue(42U);  // Set a valid unsigned long value



    sonyMakerNote_.printWhiteBalanceFineTune(oss_, value, &exifData_);



    EXPECT_EQ(oss_.str(), "42");

}



TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_InvalidCount_1588) {

    Value value;

    value.setValue(42U, 2);  // Set an invalid count



    sonyMakerNote_.printWhiteBalanceFineTune(oss_, value, &exifData_);



    EXPECT_EQ(oss_.str(), "(42 42)");

}



TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_InvalidType_1588) {

    Value value;

    value.setType(short);  // Set an invalid type

    value.setValue(42);



    sonyMakerNote_.printWhiteBalanceFineTune(oss_, value, &exifData_);



    EXPECT_EQ(oss_.str(), "(42)");

}



TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_ZeroValue_1588) {

    Value value;

    value.setValue(0U);  // Set zero as the value



    sonyMakerNote_.printWhiteBalanceFineTune(oss_, value, &exifData_);



    EXPECT_EQ(oss_.str(), "0");

}



TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_MaxValue_1588) {

    Value value;

    value.setValue(std::numeric_limits<uint32_t>::max());  // Set max uint32_t as the value



    sonyMakerNote_.printWhiteBalanceFineTune(oss_, value, &exifData_);



    EXPECT_EQ(oss_.str(), std::to_string(static_cast<int32_t>(std::numeric_limits<uint32_t>::max())));

}



TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_NegativeValue_1588) {

    Value value;

    uint32_t largeValue = static_cast<uint32_t>(std::numeric_limits<int32_t>::max()) + 1;  // This will be interpreted as a negative int32_t

    value.setValue(largeValue);



    sonyMakerNote_.printWhiteBalanceFineTune(oss_, value, &exifData_);



    EXPECT_EQ(oss_.str(), std::to_string(static_cast<int32_t>(largeValue)));

}

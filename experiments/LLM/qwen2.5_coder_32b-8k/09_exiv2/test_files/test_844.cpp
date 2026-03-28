#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;



class XmpArrayValueTest_844 : public ::testing::Test {

protected:

    XmpArrayValue xmpArrayValue_{TypeId::tString};

};



TEST_F(XmpArrayValueTest_844, CloneReturnsNonNullPointer_844) {

    auto clone = xmpArrayValue_.clone();

    EXPECT_NE(clone.get(), nullptr);

}



TEST_F(XmpArrayValueTest_844, CountInitiallyZero_844) {

    EXPECT_EQ(xmpArrayValue_.count(), 0u);

}



TEST_F(XmpArrayValueTest_844, ToStringOnEmptyThrows_844) {

    EXPECT_THROW(xmpArrayValue_.toString(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_844, ToInt64OnEmptyThrows_844) {

    EXPECT_THROW(xmpArrayValue_.toInt64(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_844, ToUint32OnEmptyThrows_844) {

    EXPECT_THROW(xmpArrayValue_.toUint32(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_844, ToFloatOnEmptyThrows_844) {

    EXPECT_THROW(xmpArrayValue_.toFloat(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_844, ToRationalOnEmptyThrows_844) {

    EXPECT_THROW(xmpArrayValue_.toRational(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_844, WriteToStreamDoesNotThrow_844) {

    std::ostringstream os;

    EXPECT_NO_THROW(xmpArrayValue_.write(os));

}



TEST_F(XmpArrayValueTest_844, ReadFromBufferDoesNotThrow_844) {

    std::string buffer = "test_buffer";

    EXPECT_NO_THROW(xmpArrayValue_.read(buffer));

}



// Assuming read populates the internal state and count increases

TEST_F(XmpArrayValueTest_844, CountIncreasesAfterRead_844) {

    std::string buffer = "test_buffer";

    xmpArrayValue_.read(buffer);

    EXPECT_GT(xmpArrayValue_.count(), 0u);

}

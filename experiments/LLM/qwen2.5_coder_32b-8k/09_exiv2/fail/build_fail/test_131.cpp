#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class AsciiValueTest_131 : public ::testing::Test {

protected:

    AsciiValueTest_131() {}

};



TEST_F(AsciiValueTest_131, DefaultConstructorInitializesCorrectly_131) {

    AsciiValue value;

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("", os.str());

}



TEST_F(AsciiValueTest_131, ParameterizedConstructorInitializesCorrectly_131) {

    AsciiValue value("test");

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("test", os.str());

}



TEST_F(AsciiValueTest_131, ReadMethodUpdatesValue_131) {

    AsciiValue value;

    int result = value.read("new_value");

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("new_value", os.str());

    EXPECT_EQ(7, result); // Assuming read returns the length of the input string

}



TEST_F(AsciiValueTest_131, WriteMethodOutputsCorrectly_131) {

    AsciiValue value("example");

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("example", os.str());

}



TEST_F(AsciiValueTest_131, CloneMethodCreatesIndependentInstance_131) {

    AsciiValue original("original_value");

    UniquePtr clone = original.clone();

    std::ostringstream originalOs;

    std::ostringstream cloneOs;

    original.write(originalOs);

    clone->write(cloneOs);

    EXPECT_EQ("original_value", originalOs.str());

    EXPECT_EQ("original_value", cloneOs.str());



    // Modify the clone and check that the original is unchanged

    clone->read("modified_value");

    originalOs.str("");

    cloneOs.str("");

    original.write(originalOs);

    clone->write(cloneOs);

    EXPECT_EQ("original_value", originalOs.str());

    EXPECT_EQ("modified_value", cloneOs.str());

}



TEST_F(AsciiValueTest_131, ReadWithEmptyStringDoesNotChangeValue_131) {

    AsciiValue value("initial");

    int result = value.read("");

    std::ostringstream os;

    value.write(os);

    EXPECT_EQ("initial", os.str());

    EXPECT_EQ(0, result); // Assuming read returns the length of the input string

}



TEST_F(AsciiValueTest_131, WriteToEmptyStreamDoesNotThrow_131) {

    AsciiValue value("data");

    std::ostringstream os;

    EXPECT_NO_THROW(value.write(os));

    EXPECT_EQ("data", os.str());

}

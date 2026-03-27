#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/value.hpp>

#include <string>

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class XmpTextValueTest_836 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    XmpTextValue xmpTextValue;

};



TEST_F(XmpTextValueTest_836, DefaultConstructorSetsSizeToZero_836) {

    EXPECT_EQ(xmpTextValue.size(), 0);

}



TEST_F(XmpTextValueTest_836, ConstructorWithEmptyStringSetsSizeToZero_836) {

    XmpTextValue xmpTextValue("");

    EXPECT_EQ(xmpTextValue.size(), 0);

}



TEST_F(XmpTextValueTest_836, ConstructorWithNonEmptyStringSetsCorrectSize_836) {

    std::string testString = "HelloWorld";

    XmpTextValue xmpTextValue(testString);

    EXPECT_EQ(xmpTextValue.size(), testString.size());

}



TEST_F(XmpTextValueTest_836, ReadMethodUpdatesSizeCorrectly_836) {

    std::string testString = "SampleData";

    int result = xmpTextValue.read(testString);

    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

    EXPECT_EQ(xmpTextValue.size(), testString.size());

}



TEST_F(XmpTextValueTest_836, CountMethodReturnsSameAsSize_836) {

    std::string testString = "MultipleWords";

    xmpTextValue.read(testString);

    EXPECT_EQ(xmpTextValue.count(), xmpTextValue.size());

}



TEST_F(XmpTextValueTest_836, ToInt64MethodThrowsOnInvalidData_836) {

    std::string nonNumericString = "NotANumber";

    xmpTextValue.read(nonNumericString);

    EXPECT_THROW(xmpTextValue.toInt64(0), Exiv2::Error); // Assuming Exiv2::Error is thrown on conversion failure

}



TEST_F(XmpTextValueTest_836, ToUint32MethodThrowsOnInvalidData_836) {

    std::string nonNumericString = "NotANumber";

    xmpTextValue.read(nonNumericString);

    EXPECT_THROW(xmpTextValue.toUint32(0), Exiv2::Error); // Assuming Exiv2::Error is thrown on conversion failure

}



TEST_F(XmpTextValueTest_836, ToFloatMethodThrowsOnInvalidData_836) {

    std::string nonNumericString = "NotANumber";

    xmpTextValue.read(nonNumericString);

    EXPECT_THROW(xmpTextValue.toFloat(0), Exiv2::Error); // Assuming Exiv2::Error is thrown on conversion failure

}



TEST_F(XmpTextValueTest_836, ToRationalMethodThrowsOnInvalidData_836) {

    std::string nonNumericString = "NotANumber";

    xmpTextValue.read(nonNumericString);

    EXPECT_THROW(xmpTextValue.toRational(0), Exiv2::Error); // Assuming Exiv2::Error is thrown on conversion failure

}



TEST_F(XmpTextValueTest_836, WriteMethodOutputsCorrectData_836) {

    std::string testString = "OutputTest";

    xmpTextValue.read(testString);

    std::ostringstream oss;

    xmpTextValue.write(oss);

    EXPECT_EQ(oss.str(), testString);

}



TEST_F(XmpTextValueTest_836, CloneMethodCreatesIdenticalInstance_836) {

    std::string testString = "CloneMe";

    xmpTextValue.read(testString);

    auto clone = xmpTextValue.clone();

    EXPECT_EQ(clone->size(), testString.size());

    std::ostringstream originalOss;

    std::ostringstream cloneOss;

    xmpTextValue.write(originalOss);

    clone->write(cloneOss);

    EXPECT_EQ(originalOss.str(), cloneOss.str());

}

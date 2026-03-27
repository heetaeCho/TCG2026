#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;



class XmpTextValueTest_2168 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(XmpTextValueTest_2168, ConstructorWithEmptyString_2168) {

    XmpTextValue xmpValue("");

    EXPECT_EQ(xmpValue.size(), 0u);

}



TEST_F(XmpTextValueTest_2168, ConstructorWithNonEmptyString_2168) {

    std::string testString = "Sample text";

    XmpTextValue xmpValue(testString);

    EXPECT_EQ(xmpValue.size(), testString.size());

}



TEST_F(XmpTextValueTest_2168, ReadWithEmptyString_2168) {

    XmpTextValue xmpValue;

    int result = xmpValue.read("");

    EXPECT_EQ(result, 0);

    EXPECT_EQ(xmpValue.size(), 0u);

}



TEST_F(XmpTextValueTest_2168, ReadWithNonEmptyString_2168) {

    std::string testString = "Sample text";

    XmpTextValue xmpValue;

    int result = xmpValue.read(testString);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(xmpValue.size(), testString.size());

}



TEST_F(XmpTextValueTest_2168, SizeAfterRead_2168) {

    std::string testString = "Another sample";

    XmpTextValue xmpValue;

    xmpValue.read(testString);

    EXPECT_EQ(xmpValue.size(), testString.size());

}



TEST_F(XmpTextValueTest_2168, CountDefault_2168) {

    XmpTextValue xmpValue;

    EXPECT_EQ(xmpValue.count(), 1u);

}



TEST_F(XmpTextValueTest_2168, ToInt64Default_2168) {

    XmpTextValue xmpValue;

    EXPECT_THROW(xmpValue.toInt64(0), Error); // Assuming toInt64 throws an error for non-numeric content

}



TEST_F(XmpTextValueTest_2168, ToUint32Default_2168) {

    XmpTextValue xmpValue;

    EXPECT_THROW(xmpValue.toUint32(0), Error); // Assuming toUint32 throws an error for non-numeric content

}



TEST_F(XmpTextValueTest_2168, ToFloatDefault_2168) {

    XmpTextValue xmpValue;

    EXPECT_THROW(xmpValue.toFloat(0), Error); // Assuming toFloat throws an error for non-numeric content

}



TEST_F(XmpTextValueTest_2168, ToRationalDefault_2168) {

    XmpTextValue xmpValue;

    EXPECT_THROW(xmpValue.toRational(0), Error); // Assuming toRational throws an error for non-rational content

}



TEST_F(XmpTextValueTest_2168, WriteToStream_2168) {

    std::string testString = "Writable text";

    XmpTextValue xmpValue(testString);

    std::ostringstream oss;

    xmpValue.write(oss);

    EXPECT_EQ(oss.str(), testString);

}

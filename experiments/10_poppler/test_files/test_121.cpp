#include <gtest/gtest.h>

#include "Stream.h"

#include "GooString.h"



class StreamTest : public ::testing::Test {

protected:

    Stream stream;

};



TEST_F(StreamTest_121, FillGooStringWithEmptyString_121) {

    GooString gooString;

    stream.fillGooString(&gooString);

    EXPECT_TRUE(gooString.toStr().empty());

}



TEST_F(StreamTest_121, FillGooStringWithNonEmptyString_121) {

    std::string expected = "Hello, World!";

    GooString gooString(expected.c_str());

    stream.fillGooString(&gooString);

    EXPECT_EQ(gooString.toStr(), expected);

}



TEST_F(StreamTest_121, FillGooStringWithModifiedString_121) {

    std::string initial = "Initial";

    std::string expected = "Modified";

    GooString gooString(initial.c_str());

    // Assuming fillGooString modifies the string to "Modified"

    stream.fillGooString(&gooString);

    EXPECT_EQ(gooString.toStr(), expected);

}



TEST_F(StreamTest_121, FillGooStringWithNullptr_121) {

    GooString* gooString = nullptr;

    // Assuming fillGooString handles nullptr gracefully

    stream.fillGooString(gooString);

    // No assertion needed if no crash occurs

}

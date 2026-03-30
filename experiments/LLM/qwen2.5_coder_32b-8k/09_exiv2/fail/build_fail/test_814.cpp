#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



TEST_F(AsciiValueTest_814, WriteOutputsCorrectString_814) {

    AsciiValue asciiValue("HelloWorld");

    std::ostringstream os;

    asciiValue.write(os);

    EXPECT_EQ(os.str(), "HelloWorld");

}



TEST_F(AsciiValueTest_814, WriteHandlesNullTerminator_814) {

    AsciiValue asciiValue("Hello\0World");

    std::ostringstream os;

    asciiValue.write(os);

    EXPECT_EQ(os.str(), "Hello");

}



TEST_F(AsciiValueTest_814, WriteEmptyString_814) {

    AsciiValue asciiValue("");

    std::ostringstream os;

    asciiValue.write(os);

    EXPECT_EQ(os.str(), "");

}



TEST_F(AsciiValueTest_814, WriteNullTerminatorOnly_814) {

    AsciiValue asciiValue("\0");

    std::ostringstream os;

    asciiValue.write(os);

    EXPECT_EQ(os.str(), "");

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include "fuzzing/NullOStream.h"



using namespace Catch;



class XmlEncodeTest : public ::testing::Test {

protected:

    NullOStream nul;

};



TEST_F(XmlEncodeTest_20, EncodeToDoesNotThrowForEmptyString_20) {

    std::string buf = "";

    XmlEncode encode(buf);

    EXPECT_NO_THROW(encode.encodeTo(nul));

}



TEST_F(XmlEncodeTest_20, EncodeToHandlesSpecialCharacters_20) {

    std::string buf = "<>&\"'";

    XmlEncode encode(buf);

    EXPECT_NO_THROW(encode.encodeTo(nul));

}



TEST_F(XmlEncodeTest_20, EncodeToDoesNotThrowForLargeInput_20) {

    std::string largeBuf(100000, 'a');

    XmlEncode encode(largeBuf);

    EXPECT_NO_THROW(encode.encodeTo(nul));

}



TEST_F(XmlEncodeTest_20, OperatorLessThanLessHandlesSpecialCharacters_20) {

    std::string buf = "<>&\"'";

    XmlEncode encode(buf);

    EXPECT_NO_THROW(nul << encode);

}



class TestSpecParserTest : public ::testing::Test {

protected:

    TagAliasRegistry tagAliases;

    TestSpecParser parser{tagAliases};

};



TEST_F(TestSpecParserTest_20, ParseDoesNotThrowForEmptyString_20) {

    std::string arg = "";

    EXPECT_NO_THROW(parser.parse(arg));

}



TEST_F(TestSpecParserTest_20, ParseHandlesValidNamePattern_20) {

    std::string arg = "test_name";

    EXPECT_NO_THROW(parser.parse(arg));

}



TEST_F(TestSpecParserTest_20, ParseHandlesValidTagPattern_20) {

    std::string arg = "[tag]";

    EXPECT_NO_THROW(parser.parse(arg));

}



TEST_F(TestSpecParserTest_20, ParseHandlesExclusion_20) {

    std::string arg = "~[tag]";

    EXPECT_NO_THROW(parser.parse(arg));

}



TEST_F(TestSpecParserTest_20, TestSpecReturnsValidObject_20) {

    std::string arg = "test_name";

    parser.parse(arg);

    EXPECT_NO_THROW(parser.testSpec());

}

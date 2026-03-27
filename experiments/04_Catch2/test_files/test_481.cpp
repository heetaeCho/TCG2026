#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::HasSubstr;



class XmlWriterTest_481 : public ::testing::Test {

protected:

    std::ostringstream stream;

    XmlWriter writer{stream};

};



TEST_F(XmlWriterTest_481, WriteStylesheetRef_ValidUrl_481) {

    StringRef url("http://example.com/style.xsl");

    writer.writeStylesheetRef(url);

    EXPECT_THAT(stream.str(), HasSubstr(R"(<?xml-stylesheet type="text/xsl" href="http://example.com/style.xsl"?>)"));

}



TEST_F(XmlWriterTest_481, WriteStylesheetRef_EmptyUrl_481) {

    StringRef url("");

    writer.writeStylesheetRef(url);

    EXPECT_THAT(stream.str(), HasSubstr(R"(<?xml-stylesheet type="text/xsl" href=""?>)"));

}



TEST_F(XmlWriterTest_481, WriteStylesheetRef_SpecialCharactersInUrl_481) {

    StringRef url("http://example.com/style?param=value#section");

    writer.writeStylesheetRef(url);

    EXPECT_THAT(stream.str(), HasSubstr(R"(<?xml-stylesheet type="text/xsl" href="http://example.com/style?param=value#section"?>)"));

}

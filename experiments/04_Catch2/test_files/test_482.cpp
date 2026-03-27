#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;

using namespace testing;



class XmlWriterTest_482 : public Test {

protected:

    std::ostringstream oss;

    XmlWriter writer;



    XmlWriterTest_482() : writer(oss) {}

};



TEST_F(XmlWriterTest_482, EnsureTagClosed_NoOpenTag_482) {

    writer.ensureTagClosed();

    EXPECT_EQ(oss.str(), "");

}



TEST_F(XmlWriterTest_482, EnsureTagClosed_OpenTag_482) {

    writer.startElement("test", XmlFormatting::None);

    writer.ensureTagClosed();

    EXPECT_EQ(oss.str(), "<test>");

}



TEST_F(XmlWriterTest_482, EnsureTagClosed_MultipleCalls_482) {

    writer.startElement("test", XmlFormatting::None);

    writer.ensureTagClosed();

    writer.ensureTagClosed(); // Subsequent call should have no effect

    EXPECT_EQ(oss.str(), "<test>");

}



TEST_F(XmlWriterTest_482, EnsureTagClosed_NewlineAfterClose_482) {

    writer.startElement("test", XmlFormatting::Newline);

    writer.ensureTagClosed();

    EXPECT_EQ(oss.str(), "<test>\n");

}

#include <gtest/gtest.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include <sstream>



using namespace Catch;



class XmlWriterTest_477 : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter xmlWriter{oss};

};



TEST_F(XmlWriterTest_477, WriteAttributeBooleanTrue_477) {

    xmlWriter.writeAttribute("attribute", true);

    EXPECT_EQ(oss.str(), " attribute=\"true\"");

}



TEST_F(XmlWriterTest_477, WriteAttributeBooleanFalse_477) {

    xmlWriter.writeAttribute("attribute", false);

    EXPECT_EQ(oss.str(), " attribute=\"false\"");

}



TEST_F(XmlWriterTest_477, WriteAttributeStringRef_477) {

    StringRef value("value");

    xmlWriter.writeAttribute("attribute", value);

    EXPECT_EQ(oss.str(), " attribute=\"value\"");

}



TEST_F(XmlWriterTest_477, WriteAttributeCString_477) {

    const char* cStringValue = "cStringValue";

    xmlWriter.writeAttribute("attribute", cStringValue);

    EXPECT_EQ(oss.str(), " attribute=\"cStringValue\"");

}



TEST_F(XmlWriterTest_477, WriteAttributeEmptyString_477) {

    StringRef emptyValue("");

    xmlWriter.writeAttribute("attribute", emptyValue);

    EXPECT_EQ(oss.str(), " attribute=\"\"");

}



TEST_F(XmlWriterTest_477, WriteMultipleAttributes_477) {

    xmlWriter.writeAttribute("first", true)

             .writeAttribute("second", false)

             .writeAttribute("third", StringRef("value"));

    EXPECT_EQ(oss.str(), " first=\"true\" second=\"false\" third=\"value\"");

}

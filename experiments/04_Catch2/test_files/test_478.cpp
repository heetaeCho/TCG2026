#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Catch2/internal/catch_xmlwriter.hpp>

#include <sstream>



using namespace Catch;

using ::testing::HasSubstr;



class XmlWriterTest_478 : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter xmlWriter{oss};

};



TEST_F(XmlWriterTest_478, WriteAttributeWithStringRef_478) {

    StringRef name("name");

    StringRef attribute("value");

    xmlWriter.writeAttribute(name, attribute);

}



TEST_F(XmlWriterTest_478, WriteAttributeWithCString_478) {

    const char* name = "name";

    const char* attribute = "value";

    xmlWriter.writeAttribute(name, attribute);

}



TEST_F(XmlWriterTest_478, WriteAttributeWithEmptyName_478) {

    StringRef emptyName("");

    StringRef attribute("value");

    xmlWriter.writeAttribute(emptyName, attribute);

}



TEST_F(XmlWriterTest_478, WriteAttributeWithEmptyValue_478) {

    StringRef name("name");

    StringRef emptyAttribute("");

    xmlWriter.writeAttribute(name, emptyAttribute);

}



TEST_F(XmlWriterTest_478, WriteMultipleAttributes_478) {

    xmlWriter.writeAttribute(StringRef("name1"), "value1")

             .writeAttribute(StringRef("name2"), StringRef("value2"));

}

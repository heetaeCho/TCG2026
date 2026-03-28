#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_xmlwriter.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;



class MockXmlWriter : public XmlWriter {

public:

    MOCK_METHOD(void, writeAttribute, (StringRef name, StringRef attribute), (override));

};



class ScopedElementTest_17 : public ::testing::Test {

protected:

    MockXmlWriter mockXmlWriter;

    XmlWriter::ScopedElement scopedElement{&mockXmlWriter, XmlFormatting::Default};

};



TEST_F(ScopedElementTest_17, WriteAttributeWithStringRefValue_17) {

    StringRef name("testName");

    StringRef attribute("testValue");



    EXPECT_CALL(mockXmlWriter, writeAttribute(name, attribute));



    scopedElement.writeAttribute(name, attribute);

}



TEST_F(ScopedElementTest_17, WriteAttributeWithConvertibleType_17) {

    StringRef name("testName");

    int attribute = 42;



    EXPECT_CALL(mockXmlWriter, writeAttribute(name, "42"));



    scopedElement.writeAttribute(name, attribute);

}



TEST_F(ScopedElementTest_17, WriteAttributeWithEmptyStringRef_17) {

    StringRef name("");

    StringRef attribute("");



    EXPECT_CALL(mockXmlWriter, writeAttribute(name, attribute));



    scopedElement.writeAttribute(name, attribute);

}



TEST_F(ScopedElementTest_17, WriteAttributeWithNullPointer_17) {

    StringRef name("testName");

    StringRef attribute(nullptr);



    EXPECT_CALL(mockXmlWriter, writeAttribute(name, ""));



    scopedElement.writeAttribute(name, attribute);

}

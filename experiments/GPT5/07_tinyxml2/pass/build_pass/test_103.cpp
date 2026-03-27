#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeDoubleTest_103 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* element;

    void SetUp() override {
        element = doc.NewElement("TestElement");
        doc.InsertFirstChild(element);
    }
};

// Normal operation: set and retrieve a simple double attribute
TEST_F(XMLElementSetAttributeDoubleTest_103, SetAndQueryDoubleAttribute_103) {
    double value = 3.14159;
    element->SetAttribute("pi", value);

    double queried = 0.0;
    XMLError err = element->QueryDoubleAttribute("pi", &queried);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(queried, value);
}

// Boundary condition: set a very large double
TEST_F(XMLElementSetAttributeDoubleTest_103, SetLargeDoubleAttribute_103) {
    double value = 1e308;  // near max for double
    element->SetAttribute("large", value);

    double queried = 0.0;
    EXPECT_EQ(element->QueryDoubleAttribute("large", &queried), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(queried, value);
}

// Boundary condition: set a very small (subnormal) double
TEST_F(XMLElementSetAttributeDoubleTest_103, SetSmallDoubleAttribute_103) {
    double value = 1e-308;
    element->SetAttribute("small", value);

    double queried = 0.0;
    EXPECT_EQ(element->QueryDoubleAttribute("small", &queried), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(queried, value);
}

// Exceptional case: querying a non-existent attribute
TEST_F(XMLElementSetAttributeDoubleTest_103, QueryNonExistentAttribute_103) {
    double queried = 0.0;
    XMLError err = element->QueryDoubleAttribute("nonexistent", &queried);

    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Update existing attribute: overwrite previous value
TEST_F(XMLElementSetAttributeDoubleTest_103, OverwriteAttribute_103) {
    element->SetAttribute("value", 1.23);
    element->SetAttribute("value", 4.56);  // overwrite

    double queried = 0.0;
    EXPECT_EQ(element->QueryDoubleAttribute("value", &queried), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(queried, 4.56);
}

// Negative value
TEST_F(XMLElementSetAttributeDoubleTest_103, SetNegativeDoubleAttribute_103) {
    double value = -42.42;
    element->SetAttribute("negative", value);

    double queried = 0.0;
    EXPECT_EQ(element->QueryDoubleAttribute("negative", &queried), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(queried, value);
}

// Zero value
TEST_F(XMLElementSetAttributeDoubleTest_103, SetZeroDoubleAttribute_103) {
    double value = 0.0;
    element->SetAttribute("zero", value);

    double queried = 1.0;  // initialize to non-zero to ensure it's updated
    EXPECT_EQ(element->QueryDoubleAttribute("zero", &queried), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(queried, 0.0);
}

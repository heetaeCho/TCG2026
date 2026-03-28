// File: tests/xmlwriter_writeAttribute_stringref_test_476.cpp

#include <gtest/gtest.h>
#include <sstream>

#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;

class XmlWriterWriteAttributeTest_476 : public ::testing::Test {
protected:
    std::ostringstream oss;
    XmlWriter writer{oss};
};

// [Normal] Writes attribute when both name and value are non-empty.
// Verifies exact formatting (leading space, name, ="value", closing quote).
TEST_F(XmlWriterWriteAttributeTest_476, WritesAttributeWhenNameAndValueNonEmpty_476) {
    writer.writeAttribute(StringRef("id"), StringRef("node42"));

    EXPECT_EQ(oss.str(), " id=\"node42\"");
}

// [Boundary] No output when the attribute name is empty (value non-empty).
TEST_F(XmlWriterWriteAttributeTest_476, NoOutputWhenNameEmpty_476) {
    writer.writeAttribute(StringRef(""), StringRef("value"));

    EXPECT_TRUE(oss.str().empty());
}

// [Boundary] No output when the attribute value is empty (name non-empty).
TEST_F(XmlWriterWriteAttributeTest_476, NoOutputWhenValueEmpty_476) {
    writer.writeAttribute(StringRef("class"), StringRef(""));

    EXPECT_TRUE(oss.str().empty());
}

// [Boundary] No output when both name and value are empty.
TEST_F(XmlWriterWriteAttributeTest_476, NoOutputWhenNameAndValueEmpty_476) {
    writer.writeAttribute(StringRef(""), StringRef(""));

    EXPECT_TRUE(oss.str().empty());
}

// [Normal] Multiple attributes: each valid call appends a leading space and formatted pair.
TEST_F(XmlWriterWriteAttributeTest_476, AppendsMultipleAttributesSequentially_476) {
    writer.writeAttribute(StringRef("a"), StringRef("x"))
          .writeAttribute(StringRef("b"), StringRef("y"));

    EXPECT_EQ(oss.str(), " a=\"x\" b=\"y\"");
}

// [Boundary] Skipped (empty) attribute does not introduce stray spaces or characters.
TEST_F(XmlWriterWriteAttributeTest_476, SkipsEmptyAttributeWithoutExtraSpaces_476) {
    writer.writeAttribute(StringRef(""), StringRef("ignored"))
          .writeAttribute(StringRef("valid"), StringRef("ok"));

    EXPECT_EQ(oss.str(), " valid=\"ok\"");
}

// [API] Returns reference to self to allow chaining.
TEST_F(XmlWriterWriteAttributeTest_476, ReturnsSelfForChaining_476) {
    auto* ret = &writer.writeAttribute(StringRef("k"), StringRef("v"));
    EXPECT_EQ(ret, &writer); // same object
    EXPECT_EQ(oss.str(), " k=\"v\"");
}

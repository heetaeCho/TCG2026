#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch;

class XmlWriterScopedElementTest_17 : public ::testing::Test {
protected:
    std::ostringstream oss;
    std::unique_ptr<XmlWriter> writer;

    void SetUp() override {
        writer = std::make_unique<XmlWriter>(oss);
    }

    void TearDown() override {
        writer.reset();
    }
};

// Test that creating a scoped element and letting it go out of scope produces valid XML
TEST_F(XmlWriterScopedElementTest_17, ScopedElementCreatesAndClosesTag_17) {
    {
        auto elem = writer->scopedElement("TestElement");
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("TestElement"), std::string::npos);
}

// Test writing a string attribute via ScopedElement
TEST_F(XmlWriterScopedElementTest_17, WriteStringAttribute_17) {
    {
        auto elem = writer->scopedElement("Element");
        elem.writeAttribute("name"_catch_sr, "value"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// Test writing a non-string attribute (int) via template writeAttribute
TEST_F(XmlWriterScopedElementTest_17, WriteIntAttribute_17) {
    {
        auto elem = writer->scopedElement("Element");
        elem.writeAttribute("count", 42);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("count"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test writing a bool attribute via template writeAttribute
TEST_F(XmlWriterScopedElementTest_17, WriteBoolAttribute_17) {
    {
        auto elem = writer->scopedElement("Element");
        elem.writeAttribute("flag", true);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("flag"), std::string::npos);
}

// Test writing a double/float attribute via template writeAttribute
TEST_F(XmlWriterScopedElementTest_17, WriteDoubleAttribute_17) {
    {
        auto elem = writer->scopedElement("Element");
        elem.writeAttribute("ratio", 3.14);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("ratio"), std::string::npos);
}

// Test chaining multiple writeAttribute calls
TEST_F(XmlWriterScopedElementTest_17, ChainingMultipleAttributes_17) {
    {
        auto elem = writer->scopedElement("Element");
        elem.writeAttribute("attr1"_catch_sr, "val1"_catch_sr)
            .writeAttribute("attr2", 100)
            .writeAttribute("attr3"_catch_sr, "val3"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("attr1"), std::string::npos);
    EXPECT_NE(output.find("val1"), std::string::npos);
    EXPECT_NE(output.find("attr2"), std::string::npos);
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("attr3"), std::string::npos);
    EXPECT_NE(output.find("val3"), std::string::npos);
}

// Test writeText on ScopedElement
TEST_F(XmlWriterScopedElementTest_17, WriteText_17) {
    {
        auto elem = writer->scopedElement("Element");
        elem.writeText("Hello World"_catch_sr, XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

// Test move constructor of ScopedElement
TEST_F(XmlWriterScopedElementTest_17, MoveConstructor_17) {
    {
        auto elem1 = writer->scopedElement("Original");
        auto elem2 = std::move(elem1);
        elem2.writeAttribute("moved"_catch_sr, "yes"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("moved"), std::string::npos);
    EXPECT_NE(output.find("yes"), std::string::npos);
}

// Test move assignment of ScopedElement
TEST_F(XmlWriterScopedElementTest_17, MoveAssignment_17) {
    {
        auto elem1 = writer->scopedElement("First");
        {
            auto elem2 = writer->scopedElement("Second");
            elem1 = std::move(elem2);
        }
        elem1.writeAttribute("key"_catch_sr, "val"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
}

// Test writing text and attributes together
TEST_F(XmlWriterScopedElementTest_17, WriteAttributeAndText_17) {
    {
        auto elem = writer->scopedElement("Mixed");
        elem.writeAttribute("id", 1)
            .writeText("content"_catch_sr, XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("id"), std::string::npos);
    EXPECT_NE(output.find("content"), std::string::npos);
}

// Test nested scoped elements
TEST_F(XmlWriterScopedElementTest_17, NestedScopedElements_17) {
    {
        auto outer = writer->scopedElement("Outer");
        outer.writeAttribute("level"_catch_sr, "1"_catch_sr);
        {
            auto inner = writer->scopedElement("Inner");
            inner.writeAttribute("level"_catch_sr, "2"_catch_sr);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("Outer"), std::string::npos);
    EXPECT_NE(output.find("Inner"), std::string::npos);
}

// Test empty attribute name and value
TEST_F(XmlWriterScopedElementTest_17, EmptyAttributeNameAndValue_17) {
    {
        auto elem = writer->scopedElement("Element");
        elem.writeAttribute(""_catch_sr, ""_catch_sr);
    }
    // Just verify it doesn't crash
    std::string output = oss.str();
    EXPECT_NE(output.find("Element"), std::string::npos);
}

// Test empty text
TEST_F(XmlWriterScopedElementTest_17, EmptyText_17) {
    {
        auto elem = writer->scopedElement("Element");
        elem.writeText(""_catch_sr, XmlFormatting::None);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("Element"), std::string::npos);
}

// Test writing unsigned long attribute
TEST_F(XmlWriterScopedElementTest_17, WriteUnsignedLongAttribute_17) {
    {
        auto elem = writer->scopedElement("Element");
        unsigned long val = 999999UL;
        elem.writeAttribute("bignum", val);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("bignum"), std::string::npos);
    EXPECT_NE(output.find("999999"), std::string::npos);
}

// Test that writeAttribute returns a reference for chaining (compile-time + runtime)
TEST_F(XmlWriterScopedElementTest_17, WriteAttributeReturnsSelfReference_17) {
    {
        auto elem = writer->scopedElement("Chain");
        auto& ref1 = elem.writeAttribute("a"_catch_sr, "1"_catch_sr);
        auto& ref2 = ref1.writeAttribute("b", 2);
        EXPECT_EQ(&ref1, &elem);
        EXPECT_EQ(&ref2, &elem);
    }
}

// Test writeText returns self reference for chaining
TEST_F(XmlWriterScopedElementTest_17, WriteTextReturnsSelfReference_17) {
    {
        auto elem = writer->scopedElement("Chain");
        auto& ref = elem.writeText("text"_catch_sr, XmlFormatting::None);
        EXPECT_EQ(&ref, &elem);
    }
}

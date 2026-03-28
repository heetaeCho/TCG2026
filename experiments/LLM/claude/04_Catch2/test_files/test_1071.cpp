#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"
#include <gtest/gtest.h>

using namespace Catch;

class ScopedElementTest_1071 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

TEST_F(ScopedElementTest_1071, MoveConstructorTransfersOwnership_1071) {
    // When a ScopedElement is move-constructed, the source should no longer
    // write the closing tag on destruction
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("outer");
            auto moved = std::move(elem);
            // moved now owns the element; elem should be empty
        }
    }
    std::string output = oss.str();
    // The element "outer" should appear exactly once as opening and closing
    EXPECT_NE(output.find("<outer"), std::string::npos);
    // Should have closing tag
    EXPECT_NE(output.find("</outer>"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, ScopedElementWritesOpenAndCloseTag_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("testElement");
        }
    }
    std::string output = oss.str();
    // Should contain the element
    EXPECT_NE(output.find("testElement"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, WriteAttributeAddsAttribute_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("item");
            elem.writeAttribute("name", "value");
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, WriteTextAddsTextContent_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("paragraph");
            elem.writeText("hello world", XmlFormatting::None);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("hello world"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, ChainingWriteAttributeCalls_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("item");
            elem.writeAttribute("attr1", "val1")
                .writeAttribute("attr2", "val2");
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("attr1"), std::string::npos);
    EXPECT_NE(output.find("val1"), std::string::npos);
    EXPECT_NE(output.find("attr2"), std::string::npos);
    EXPECT_NE(output.find("val2"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, MoveAssignmentTransfersOwnership_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem1 = writer.scopedElement("first");
            auto elem2 = writer.scopedElement("second");
            elem1 = std::move(elem2);
            // elem2 is now empty, elem1 owns "second"
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("second"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, WriteAttributeWithIntegerType_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("item");
            elem.writeAttribute("count", 42);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("count"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, WriteTextWithFormattingIndent_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("p");
            elem.writeText("indented text", XmlFormatting::Indent);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("indented text"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, WriteTextWithFormattingNewline_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("p");
            elem.writeText("newline text", XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("newline text"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, NestedScopedElements_1071) {
    {
        XmlWriter writer(oss);
        {
            auto outer = writer.scopedElement("outer");
            {
                auto inner = writer.scopedElement("inner");
                inner.writeText("nested content", XmlFormatting::None);
            }
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("outer"), std::string::npos);
    EXPECT_NE(output.find("inner"), std::string::npos);
    EXPECT_NE(output.find("nested content"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, WriteAttributeEmptyStrings_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("item");
            elem.writeAttribute("emptyAttr", "");
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("emptyAttr"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, MoveConstructedElementCanWriteAttributes_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("tag");
            auto moved = std::move(elem);
            moved.writeAttribute("key", "val");
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("val"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, WriteAttributeWithBoolType_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("item");
            elem.writeAttribute("flag", true);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("flag"), std::string::npos);
}

TEST_F(ScopedElementTest_1071, ChainingWriteTextAndAttribute_1071) {
    {
        XmlWriter writer(oss);
        {
            auto elem = writer.scopedElement("mixed");
            elem.writeAttribute("id", "1")
                .writeText("some text", XmlFormatting::None);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("id"), std::string::npos);
    EXPECT_NE(output.find("some text"), std::string::npos);
}

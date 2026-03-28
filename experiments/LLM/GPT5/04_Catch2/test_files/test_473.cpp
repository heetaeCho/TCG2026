// File: test_xmlwriter_startElement_473.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the public interface (as provided)
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

namespace {

// We don't rely on any particular enum value semantics – we only need *a* value.
static constexpr XmlFormatting kFmt = static_cast<XmlFormatting>(0);

TEST(XmlWriterStartElement_473, WritesOpeningTagSubstring_473) {
    std::ostringstream oss;
    XmlWriter writer(oss);

    writer.startElement("root", kFmt);

    const std::string out = oss.str();
    // Observable behavior: output should contain "<root"
    // (indentation/newlines may precede it; we don't assert on them).
    ASSERT_NE(out.find("<root"), std::string::npos);
}

TEST(XmlWriterStartElement_473, ReturnsSelfForChaining_473) {
    std::ostringstream oss;
    XmlWriter writer(oss);

    XmlWriter& ret = writer.startElement("node", kFmt);

    // Observable behavior: startElement returns *this, enabling chaining
    EXPECT_EQ(&ret, &writer);
}

TEST(XmlWriterStartElement_473, MultipleStartsAppendInOrder_473) {
    std::ostringstream oss;
    XmlWriter writer(oss);

    writer.startElement("first", kFmt);
    writer.startElement("second", kFmt);

    const std::string out = oss.str();
    const auto pos_first  = out.find("<first");
    const auto pos_second = out.find("<second");

    // Both substrings should exist and be in order
    ASSERT_NE(pos_first,  std::string::npos);
    ASSERT_NE(pos_second, std::string::npos);
    EXPECT_LT(pos_first, pos_second);
}

TEST(XmlWriterStartElement_473, EmptyNameStillWritesOpeningAngle_473) {
    std::ostringstream oss;
    XmlWriter writer(oss);

    writer.startElement("", kFmt);

    const std::string out = oss.str();
    // The most conservative observable expectation: at least a '<' is written.
    // We do not assume anything about further formatting/newlines/indentation.
    ASSERT_NE(out.find('<'), std::string::npos);
}

} // namespace

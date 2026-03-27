// File: tests/xmlwriter_writeAttribute_bool_477_tests.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "catch2/internal/catch_xmlwriter.hpp"

namespace {

using Catch::XmlWriter;

// We don't rely on XmlFormatting's concrete values/semantics.
// Passing a zero-initialized value is sufficient for API invocation.
static constexpr auto FMT_NONE = static_cast<Catch::XmlFormatting>(0);

// Helper: returns true if `needle` appears in `haystack`.
static bool Contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

// --- Tests ---

// Normal operation: true -> "true"
TEST(XmlWriterWriteAttributeBoolTest_477, WritesTrueLiteral_477) {
    std::ostringstream os;
    XmlWriter w(os);

    w.startElement("root", FMT_NONE)
     .writeAttribute("enabled", true)
     .endElement(FMT_NONE);

    const std::string out = os.str();
    EXPECT_TRUE(Contains(out, R"(enabled="true")"))
        << "Expected attribute value to be the literal \"true\".";
}

// Normal operation: false -> "false"
TEST(XmlWriterWriteAttributeBoolTest_477, WritesFalseLiteral_477) {
    std::ostringstream os;
    XmlWriter w(os);

    w.startElement("root", FMT_NONE)
     .writeAttribute("enabled", false)
     .endElement(FMT_NONE);

    const std::string out = os.str();
    EXPECT_TRUE(Contains(out, R"(enabled="false")"))
        << "Expected attribute value to be the literal \"false\".";
}

// Boundary-ish input type for name: ensure StringRef conversions are accepted (std::string -> StringRef)
TEST(XmlWriterWriteAttributeBoolTest_477, AcceptsStringLikeName_477) {
    std::ostringstream os;
    XmlWriter w(os);

    std::string name = "flag";
    w.startElement("root", FMT_NONE)
     .writeAttribute(name.c_str(), true)   // const char* path to StringRef
     .writeAttribute(name, false)          // std::string path to StringRef
     .endElement(FMT_NONE);

    const std::string out = os.str();
    EXPECT_TRUE(Contains(out, R"(flag="true")"));
    EXPECT_TRUE(Contains(out, R"(flag="false")"));
}

// API behavior: method returns *this to support chaining
TEST(XmlWriterWriteAttributeBoolTest_477, ReturnsSelfForChaining_477) {
    std::ostringstream os;
    XmlWriter w(os);

    XmlWriter* ret =
        &w.startElement("root", FMT_NONE)
           .writeAttribute("x", true);

    EXPECT_EQ(ret, &w) << "writeAttribute(bool) should return *this for fluent chaining.";

    w.endElement(FMT_NONE);
}

} // namespace

// File: tests/xmlwriter_ctor_1072.tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <type_traits>

// Catch2 forward declaration header(s)
#include "catch2/internal/catch_xmlwriter.hpp"

namespace {

using Catch::XmlWriter;

std::string::size_type findXmlDecl(const std::string& s) {
    // Look for the common XML declaration marker. We do not assert full content,
    // only the presence of the declaration signature.
    return s.find("<?xml");
}

// ---- Compile-time interface checks (based on public declarations) ----

static_assert(!std::is_copy_constructible<XmlWriter>::value,
              "XmlWriter must not be copy-constructible per interface");
static_assert(!std::is_copy_assignable<XmlWriter>::value,
              "XmlWriter must not be copy-assignable per interface");

} // namespace

// -------------------- Runtime observable-behavior tests --------------------

TEST(XmlWriterCtorTest_1072, WritesDeclarationOnConstruction_1072) {
    std::ostringstream os;
    {
        XmlWriter w(os); // constructor should write XML declaration to 'os'
        (void)w;
    }

    const std::string out = os.str();

    // Stream should not be empty after construction
    EXPECT_FALSE(out.empty());

    // Output should start with an XML-ish opening marker (very weak assumption)
    ASSERT_FALSE(out.empty());
    EXPECT_EQ(out.front(), '<');

    // The XML declaration signature should be present
    EXPECT_NE(findXmlDecl(out), std::string::npos);
}

TEST(XmlWriterCtorTest_1072, DoesNotInvalidateStreamState_1072) {
    std::ostringstream os;
    // Pre-check: stream is good before construction
    ASSERT_TRUE(os.good());

    {
        XmlWriter w(os);
        (void)w;
    }

    // Observable: using the provided ostream should not set error flags
    EXPECT_TRUE(os.good());

    // And it should contain the declaration signature
    EXPECT_NE(findXmlDecl(os.str()), std::string::npos);
}

TEST(XmlWriterCtorTest_1072, AppendsToExistingContent_1072) {
    std::ostringstream os;
    os << "prefix:"; // simulate pre-existing content in the stream

    {
        XmlWriter w(os);
        (void)w;
    }

    const std::string out = os.str();

    // The existing content should remain at the beginning
    ASSERT_GE(out.size(), std::string("prefix:").size());
    EXPECT_EQ(out.rfind("prefix:", 0), 0u);

    // The declaration should also be present somewhere after the prefix
    auto declPos = findXmlDecl(out);
    ASSERT_NE(declPos, std::string::npos);
    EXPECT_GT(declPos, 0u);
}

TEST(XmlWriterCtorTest_1072, MultipleWritersEmitDeclarationEach_1072) {
    std::ostringstream os;

    {
        XmlWriter w1(os);
        (void)w1;
    }
    {
        XmlWriter w2(os);
        (void)w2;
    }

    const std::string out = os.str();

    // We expect two occurrences of the declaration signature in the same stream.
    auto first = findXmlDecl(out);
    ASSERT_NE(first, std::string::npos);

    auto second = out.find("<?xml", first + 1);
    EXPECT_NE(second, std::string::npos);
}

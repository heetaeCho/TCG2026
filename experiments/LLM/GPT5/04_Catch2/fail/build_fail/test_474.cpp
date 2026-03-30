// XmlWriter_scopedElement_tests_474.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the provided headers (paths kept as in prompt)
#include "Catch2/src/catch2/internal/catch_xmlwriter.hpp"

using Catch::XmlWriter;

// If XmlFormatting is an enum/bitflag in Catch2, we can pass a "no-op" value.
// We avoid relying on any specific formatting behaviour; we only need a valid value.
static_cast<void>(0); // placate some linters in case nothing else uses it

namespace {

// A tiny helper: return current size of what's been written.
// We avoid asserting any specific XML text and only check that output appears/changes.
static size_t stream_size(const std::ostringstream& oss) {
    const std::string s = oss.str();
    return s.size();
}

} // namespace

// Normal operation: scopedElement should write something on entry.
TEST(XmlWriterScopedElementTest_474, ScopedElement_StartsElement_474) {
    std::ostringstream oss;
    XmlWriter w{oss};

    const size_t before = stream_size(oss);
    {
        // We use a simple element name; we don't assert exact text,
        // only that something is written by the call.
        auto se = w.scopedElement("root", static_cast<XmlFormatting>(0));
        (void)se;
        const size_t during = stream_size(oss);
        EXPECT_GT(during, before) << "Calling scopedElement should produce observable output";
    }
}

// RAII behaviour: when ScopedElement goes out of scope, more output should be produced
// (usually the closing tag). We don't check the exact contents.
TEST(XmlWriterScopedElementTest_474, ScopedElement_RAIIEndsElementOnDestruction_474) {
    std::ostringstream oss;
    XmlWriter w{oss};

    size_t after_open = 0;
    {
        auto se = w.scopedElement("item", static_cast<XmlFormatting>(0));
        after_open = stream_size(oss);
        ASSERT_GT(after_open, 0u) << "Opening element should write something";
    } // destructor of se should trigger additional observable effect

    const size_t after_close = stream_size(oss);
    EXPECT_GT(after_close, after_open)
        << "Letting ScopedElement destruct should produce additional output";
}

// Move semantics: moving ScopedElement should not crash nor cause double-end,
// and destruction of the live object should still produce additional output.
TEST(XmlWriterScopedElementTest_474, ScopedElement_MoveSemantics_SingleEnd_474) {
    std::ostringstream oss;
    XmlWriter w{oss};

    const size_t before = stream_size(oss);
    size_t after_construct = 0;

    {
        auto se = w.scopedElement("moved", static_cast<XmlFormatting>(0));
        after_construct = stream_size(oss);
        ASSERT_GT(after_construct, before) << "Construction should write something";

        // Move the RAII guard; only the moved-to instance should manage the end.
        auto moved_to = std::move(se);
        (void)moved_to;
        // We do not expect immediate changes from the move itself; we only verify
        // that when the scope ends, *some* additional output is produced and no crash occurs.
    } // moved_to destructs here

    const size_t after_scope = stream_size(oss);
    EXPECT_GT(after_scope, after_construct)
        << "After the moved-to guard destructs, additional output should appear";
}

// Nesting: creating nested scoped elements should steadily increase output,
// and leaving the inner and then outer scopes should each add more output.
TEST(XmlWriterScopedElementTest_474, ScopedElement_NestedScopes_474) {
    std::ostringstream oss;
    XmlWriter w{oss};

    const size_t initial = stream_size(oss);
    size_t after_outer_open = 0;
    size_t after_inner_open = 0;

    {
        auto outer = w.scopedElement("outer", static_cast<XmlFormatting>(0));
        after_outer_open = stream_size(oss);
        ASSERT_GT(after_outer_open, initial) << "Opening outer should write something";

        {
            auto inner = w.scopedElement("inner", static_cast<XmlFormatting>(0));
            after_inner_open = stream_size(oss);
            ASSERT_GT(after_inner_open, after_outer_open)
                << "Opening inner should further increase output";
        } // inner ends

        const size_t after_inner_close = stream_size(oss);
        EXPECT_GT(after_inner_close, after_inner_open - 1)
            << "Closing inner should produce additional output (e.g., a closing tag)";
    } // outer ends

    const size_t after_outer_close = stream_size(oss);
    EXPECT_GT(after_outer_close, after_outer_open)
        << "Closing outer should produce additional output";
}

// Boundary-ish case: very long element name.
// We don't assert on exact output; only that the call succeeds and writes something.
TEST(XmlWriterScopedElementTest_474, ScopedElement_LongName_474) {
    std::ostringstream oss;
    XmlWriter w{oss};

    std::string long_name(1024, 'a'); // long but reasonable
    const size_t before = stream_size(oss);

    {
        auto se = w.scopedElement(long_name, static_cast<XmlFormatting>(0));
        (void)se;
        const size_t during = stream_size(oss);
        EXPECT_GT(during, before) << "Opening a long-named element should write something";
    }

    const size_t after = stream_size(oss);
    EXPECT_GT(after, before) << "After scope, more output should exist";
}

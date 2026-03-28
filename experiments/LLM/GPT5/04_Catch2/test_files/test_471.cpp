// XmlWriter_ScopedElement_WriteAttribute_tests_471.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the provided (partial) public interfaces
// Adjust include paths as needed for your project layout.
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;

class ScopedElementWriteAttributeTest_471 : public ::testing::Test {
protected:
    std::ostringstream os_;
    // Construct a real XmlWriter; we do not test its internals here.
    XmlWriter writer_{os_};

    // Helper: construct a ScopedElement directly using its public ctor
    // The specific XmlFormatting value does not matter for these tests,
    // as we do not assert on formatting/output (black-box constraint).
    XmlWriter::ScopedElement makeScoped() {
        // Choose a default-constructed formatting flag; we do not rely on its value.
        XmlFormatting fmt{};
        return XmlWriter::ScopedElement(&writer_, fmt);
    }
};

// Normal operation: returns self (reference stability).
TEST_F(ScopedElementWriteAttributeTest_471, ReturnsSelfReference_471) {
    auto scoped = makeScoped();
    StringRef key("k");
    StringRef val("v");

    auto& returned = scoped.writeAttribute(key, val);
    EXPECT_EQ(&returned, &scoped) << "writeAttribute should return *this for fluent chaining";
}

// Normal operation: chaining multiple attributes compiles and returns same object.
TEST_F(ScopedElementWriteAttributeTest_471, SupportsChaining_471) {
    auto scoped = makeScoped();

    auto& ref = scoped
        .writeAttribute(StringRef("a"), StringRef("1"))
        .writeAttribute(StringRef("b"), StringRef("2"))
        .writeAttribute(StringRef("c"), StringRef("3"));

    EXPECT_EQ(&ref, &scoped) << "Chained writeAttribute calls should keep returning the same object";
}

// Boundary: empty name and empty value should be accepted as StringRef inputs (no crash/throw).
TEST_F(ScopedElementWriteAttributeTest_471, AcceptsEmptyNameAndValue_471) {
    auto scoped = makeScoped();

    // Empty StringRef from empty C-string
    EXPECT_NO_THROW({
        scoped.writeAttribute(StringRef(""), StringRef(""));
    });
}

// Boundary: very long values (stress StringRef usage without assuming internals).
TEST_F(ScopedElementWriteAttributeTest_471, AcceptsLongAttributeValue_471) {
    auto scoped = makeScoped();

    std::string longValue(10000, 'x'); // large but reasonable buffer
    EXPECT_NO_THROW({
        scoped.writeAttribute(StringRef("long"), StringRef(longValue));
    });
}

// Unicode/UTF-8 input should be accepted (no assumptions about escaping).
TEST_F(ScopedElementWriteAttributeTest_471, AcceptsUtf8Inputs_471) {
    auto scoped = makeScoped();

    // UTF-8 sequences (Korean + emoji). We only verify no-throw.
    const char* key = u8"키";
    const char* val = u8"값🙂";

    EXPECT_NO_THROW({
        scoped.writeAttribute(StringRef(key), StringRef(val));
    });
}

// Input sources: ensure StringRef-constructible sources are fine (std::string, const char*).
TEST_F(ScopedElementWriteAttributeTest_471, AcceptsVariousStringRefSources_471) {
    auto scoped = makeScoped();

    std::string kStr = "name";
    const char* vCStr = "value";

    EXPECT_NO_THROW({
        scoped.writeAttribute(StringRef(kStr), StringRef(vCStr));
    });
}

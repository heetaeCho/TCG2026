// File: test_convert_range_91.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the header under test (path from your snippet)
#include "Catch2/src/catch2/catch_tostring.hpp"

// ---------- Test types in their own namespaces to exercise ADL ----------

namespace foo {
struct Range {
    std::vector<int> data;
};

// Non-template, exact-match ADL target
inline std::string rangeToString(const Range& r) {
    if (r.data.empty()) return "foo:[]";
    std::string out = "foo:[";
    for (size_t i = 0; i < r.data.size(); ++i) {
        out += std::to_string(r.data[i]);
        if (i + 1 < r.data.size()) out += ",";
    }
    out += "]";
    return out;
}
} // namespace foo

namespace bar {
struct RangeLike {
    bool is_empty{};
};

// Another ADL target to verify “pass-through” of whatever the ADL function returns
inline std::string rangeToString(const RangeLike& r) {
    return r.is_empty ? "bar:empty" : "bar:nonempty";
}
} // namespace bar

// A global, more-generic candidate that should be *worse* than foo::rangeToString
// (template is lower priority than a non-template exact match), ensuring ADL
// selects the associated-namespace version rather than this one.
template <typename T>
std::string rangeToString(const T&) {
    return "global:template";
}

// For convenience
namespace CCD = ::Catch::Catch::Detail;

// ------------------------------ Tests -------------------------------------

// Normal operation: ADL finds foo::rangeToString and Detail::convert returns its value.
TEST(ConvertRange_91, DetailConvert_DelegatesToADL_91) {
    foo::Range r{{1, 2, 3}};
    // Calls: Catch::Catch::Detail::convert(r) -> rangeToString(r) (ADL)
    std::string s = CCD::convert(r);
    EXPECT_EQ(s, "foo:[1,2,3]");
}

// Boundary: Empty range should still “pass through” exactly whatever ADL returns.
TEST(ConvertRange_91, DetailConvert_EmptyRange_PassThrough_91) {
    foo::Range r{};  // empty
    std::string s = CCD::convert(r);
    EXPECT_EQ(s, "foo:[]");
}

// Exceptional-ish observable behavior: Using a different type with a different
// ADL function; verify we get *exactly* that function’s output (including for flags).
TEST(ConvertRange_91, DetailConvert_DifferentType_ADLPassThrough_91) {
    bar::RangeLike a{true};
    bar::RangeLike b{false};

    EXPECT_EQ(CCD::convert(a), "bar:empty");
    EXPECT_EQ(CCD::convert(b), "bar:nonempty");
}

// ADL preference check: ensure associated-namespace function is preferred
// over a generic global template (no ambiguity, non-template exact match wins).
TEST(ConvertRange_91, DetailConvert_ADLBeatsGlobalTemplate_91) {
    foo::Range r{{42}};
    // Should call foo::rangeToString, NOT the global template.
    EXPECT_EQ(CCD::convert(r), "foo:[42]");
}

// Rvalue usage (boundary of value category): ensure it works with temporaries.
TEST(ConvertRange_91, DetailConvert_RvalueTemporary_91) {
    std::string s = CCD::convert(foo::Range{{9, 8}});
    EXPECT_EQ(s, "foo:[9,8]");
}

// Repeat the key checks through the public-facing StringMaker<T>::convert,
// which exposes the same observable behavior via the public interface.
TEST(ConvertRange_91, StringMaker_DelegatesToADL_91) {
    foo::Range r{{5, 6}};
    // Calls: Catch::StringMaker<foo::Range>::convert(r) -> (rangeToString via the interface)
    std::string s = ::Catch::StringMaker<foo::Range>::convert(r);
    EXPECT_EQ(s, "foo:[5,6]");
}

TEST(ConvertRange_91, StringMaker_EmptyRange_PassThrough_91) {
    foo::Range r{};
    std::string s = ::Catch::StringMaker<foo::Range>::convert(r);
    EXPECT_EQ(s, "foo:[]");
}

TEST(ConvertRange_91, StringMaker_DifferentType_ADLPassThrough_91) {
    bar::RangeLike rl{true};
    EXPECT_EQ(::Catch::StringMaker<bar::RangeLike>::convert(rl), "bar:empty");
}

TEST(ConvertRange_91, StringMaker_ADLBeatsGlobalTemplate_91) {
    foo::Range r{{7}};
    EXPECT_EQ(::Catch::StringMaker<foo::Range>::convert(r), "foo:[7]");
}

TEST(ConvertRange_91, StringMaker_RvalueTemporary_91) {
    EXPECT_EQ(::Catch::StringMaker<foo::Range>::convert(foo::Range{{1}}), "foo:[1]");
}

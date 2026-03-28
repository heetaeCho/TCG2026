// File: tests/make_test_case_info_994_tests.cpp

#include <gtest/gtest.h>
#include <memory>
#include <string>

// Use the provided (internal) public interfaces only.
// If your include paths differ, adjust as needed:
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_test_registry.hpp>

// The factory function is implemented in Catch2/extras/catch_amalgamated.cpp,
// but it might not have a dedicated public header. We forward declare it here
// based strictly on the provided interface (no private internals).
namespace Catch {
    struct TestCaseInfo; // forward declaration only (we never inspect internals)
    namespace Detail {
        template <typename T>
        using unique_ptr = std::unique_ptr<T>;
    }

    // Factory under test (signature from the prompt)
    Detail::unique_ptr<TestCaseInfo>
    makeTestCaseInfo(StringRef _className,
                     NameAndTags const& nameAndTags,
                     SourceLineInfo const& _lineInfo);
}

using Catch::StringRef;
using Catch::NameAndTags;
using Catch::SourceLineInfo;

class MakeTestCaseInfoTest_994 : public ::testing::Test {
protected:
    // Utility to safely "forget" the pointer without requiring a complete type.
    // We avoid invoking the destructor in this TU (black-box) by releasing it.
    // NOTE: This intentionally leaks a tiny object during the test process to
    // keep us from depending on TestCaseInfo's definition. If your environment
    // requires leak-free tests and you have the public header defining
    // TestCaseInfo, include it instead and remove the release().
    static void ReleaseWithoutDelete(Catch::Detail::unique_ptr<Catch::TestCaseInfo>& ptr) {
        (void)ptr.release();
    }
};

// Normal case: valid inputs produce a non-null unique_ptr.
TEST_F(MakeTestCaseInfoTest_994, ReturnsNonNull_994) {
    StringRef className("SampleSuite");
    NameAndTags nat{ StringRef("SampleCase"), StringRef("[quick][unit]") };
    SourceLineInfo sli("file.cpp", 42);

    auto tc = Catch::makeTestCaseInfo(className, nat, sli);
    EXPECT_NE(tc.get(), nullptr);

    ReleaseWithoutDelete(tc);
}

// Ownership semantics: result is move-only; move leaves source null and transfers pointer.
TEST_F(MakeTestCaseInfoTest_994, UniqueOwnershipMovesCorrectly_994) {
    StringRef className("MoveSuite");
    NameAndTags nat{ StringRef("MoveCase"), StringRef("[move]") };
    SourceLineInfo sli("move.cpp", 10);

    auto p1 = Catch::makeTestCaseInfo(className, nat, sli);
    ASSERT_NE(p1.get(), nullptr);
    auto* raw = p1.get();

    auto p2 = std::move(p1);
    EXPECT_EQ(p1.get(), nullptr);
    EXPECT_EQ(p2.get(), raw);

    ReleaseWithoutDelete(p2);
}

// Boundary: default/empty strings for name/tags are accepted; still returns a non-null pointer.
TEST_F(MakeTestCaseInfoTest_994, AcceptsEmptyNameAndTags_994) {
    StringRef className; // default constructed (empty)
    NameAndTags nat;     // both name and tags default to empty StringRef
    // SourceLineInfo requires explicit values; use minimal edge-like values
    SourceLineInfo sli("", 0);

    auto tc = Catch::makeTestCaseInfo(className, nat, sli);
    EXPECT_NE(tc.get(), nullptr);

    ReleaseWithoutDelete(tc);
}

// Construction flexibility: StringRef from std::string & C-string both work (observable: no throw + non-null).
TEST_F(MakeTestCaseInfoTest_994, WorksWithVariousStringRefSources_994) {
    std::string cls = std::string("StdStringSuite");
    StringRef classNameFromStd(cls);
    StringRef classNameFromCStr("CStringSuite");

    NameAndTags nat1{ StringRef("Case1"), StringRef("[tag1][tag2]") };
    NameAndTags nat2{ StringRef("Case2"), StringRef() };
    SourceLineInfo sli1("a.cpp", 1);
    SourceLineInfo sli2("b.cpp", 999999);

    // std::string backed
    auto tc1 = Catch::makeTestCaseInfo(classNameFromStd, nat1, sli1);
    EXPECT_NE(tc1.get(), nullptr);
    ReleaseWithoutDelete(tc1);

    // c-string backed
    auto tc2 = Catch::makeTestCaseInfo(classNameFromCStr, nat2, sli2);
    EXPECT_NE(tc2.get(), nullptr);
    ReleaseWithoutDelete(tc2);
}

// Exception-safety (observable): the factory should not throw for typical valid inputs.
TEST_F(MakeTestCaseInfoTest_994, DoesNotThrowOnValidInputs_994) {
    StringRef className("NoThrowSuite");
    NameAndTags nat{ StringRef("NoThrowCase"), StringRef("[stable]") };
    SourceLineInfo sli("nothrow.cpp", 123);

    EXPECT_NO_THROW({
        auto tc = Catch::makeTestCaseInfo(className, nat, sli);
        // Ensure we actually used the object before releasing.
        ASSERT_NE(tc.get(), nullptr);
        ReleaseWithoutDelete(tc);
    });
}

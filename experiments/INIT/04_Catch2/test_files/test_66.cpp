// MessageInfo_eq_tests_66.cpp
#include <gtest/gtest.h>

// Include the production header
#include "catch2/internal/catch_message_info.hpp"

namespace {

using Catch::MessageInfo;
using Catch::ResultWas;
using Catch::SourceLineInfo;
using Catch::StringRef;

MessageInfo makeMsg(const char* macro = "MACRO",
                    const char* file = "file.cpp",
                    std::size_t line = 42,
                    ResultWas::OfType type = ResultWas::Ok) {
    return MessageInfo(StringRef(macro), SourceLineInfo(file, line), type);
}

// ---- Tests ----

TEST(MessageInfoTest_66, EqualsSelf_66) {
    auto m = makeMsg();
    EXPECT_TRUE(m == m);
}

TEST(MessageInfoTest_66, CopyHasEqualSequence_66) {
    auto a = makeMsg();
    auto b = a; // copy preserves sequence
    EXPECT_TRUE(a == b);
}

TEST(MessageInfoTest_66, DifferentInstancesNotEqual_66) {
    // Two separately constructed instances have distinct sequences
    auto a = makeMsg("A", "a.cpp", 1, ResultWas::Ok);
    auto b = makeMsg("B", "b.cpp", 2, ResultWas::Error);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a); // sanity/symmetry check for inequality
}

TEST(MessageInfoTest_66, EqualityIsSymmetric_66) {
    auto a = makeMsg();
    auto b = a; // same sequence via copy
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}

TEST(MessageInfoTest_66, EqualityIgnoresOtherPublicFieldsWhenSequenceSame_66) {
    auto a = makeMsg("M1", "x.cpp", 10, ResultWas::Ok);
    auto b = a;                     // same sequence
    b.type = ResultWas::Error;      // change another public field
    // Even with different 'type', equality should depend only on sequence
    EXPECT_TRUE(a == b);
}

} // namespace

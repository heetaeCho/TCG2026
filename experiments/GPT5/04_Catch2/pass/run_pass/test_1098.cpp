// File: tests/exename_tests_1098.cpp

#include <gtest/gtest.h>
#include <string>

// Include the public interface (treat implementation as a black box)
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::ExeName;

class Clara_ExeNameTest_1098 : public ::testing::Test {
protected:
    // Helper that asserts ParserResult indicates success without relying on internals.
    // Clara's ParserResult typically supports operator bool for success checks.
    static void ExpectSuccess(const Catch::Clara::Detail::ParserResult& res) {
        ASSERT_TRUE(static_cast<bool>(res))
            << "Expected ParserResult to indicate success.";
    }
};

// [Normal] Default-constructed name is the advertised default "<executable>"
TEST_F(Clara_ExeNameTest_1098, DefaultNameIsExecutable_1098) {
    ExeName parser; // Default construction via ExeName()
    // Observable behavior: name() should provide current value
    EXPECT_EQ(parser.name(), std::string("<executable>"));
}

// [Normal] set(...) propagates to an external bound reference passed to the ctor
TEST_F(Clara_ExeNameTest_1098, SetUpdatesBoundRefAndName_1098) {
    std::string bound;
    ExeName parser(bound);  // construct with external reference

    // Before calling set, the external string should remain unchanged
    EXPECT_TRUE(bound.empty());

    // After set, both name() and the external ref should reflect the new value
    auto res = parser.set("my_app");
    ExpectSuccess(res);

    EXPECT_EQ(parser.name(), std::string("my_app"));
    EXPECT_EQ(bound, std::string("my_app"));
}

// [Boundary] set to empty string is allowed and observable via name() and external ref
TEST_F(Clara_ExeNameTest_1098, SetEmptyString_1098) {
    std::string bound = "preexisting";
    ExeName parser(bound);

    auto res = parser.set("");
    ExpectSuccess(res);

    EXPECT_EQ(parser.name(), std::string(""));
    EXPECT_EQ(bound, std::string(""));
}

// [Boundary] set supports long / path-like / unicode names (observable via outputs)
TEST_F(Clara_ExeNameTest_1098, SetUnicodeAndPathyStrings_1098) {
    std::string bound;
    ExeName parser(bound);

    const std::string longName(1024, 'A');  // 1k 'A's
    ExpectSuccess(parser.set(longName));
    EXPECT_EQ(parser.name(), longName);
    EXPECT_EQ(bound, longName);

    const std::string pathy = R"(C:\Program Files\Catch2\catch2.exe)";
    ExpectSuccess(parser.set(pathy));
    EXPECT_EQ(parser.name(), pathy);
    EXPECT_EQ(bound, pathy);

    const std::string unicode = u8"실행파일_테스트🚀";
    ExpectSuccess(parser.set(unicode));
    EXPECT_EQ(parser.name(), unicode);
    EXPECT_EQ(bound, unicode);
}

// [Behavior] Multiple set(...) calls: last set wins and is reflected everywhere
TEST_F(Clara_ExeNameTest_1098, MultipleSetsLastWins_1098) {
    std::string bound;
    ExeName parser(bound);

    ExpectSuccess(parser.set("first"));
    EXPECT_EQ(parser.name(), std::string("first"));
    EXPECT_EQ(bound, std::string("first"));

    ExpectSuccess(parser.set("second"));
    EXPECT_EQ(parser.name(), std::string("second"));
    EXPECT_EQ(bound, std::string("second"));

    ExpectSuccess(parser.set("final_name"));
    EXPECT_EQ(parser.name(), std::string("final_name"));
    EXPECT_EQ(bound, std::string("final_name"));
}

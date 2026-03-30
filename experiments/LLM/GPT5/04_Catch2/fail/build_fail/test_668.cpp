// File: tests/parser_or_combine_668_tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Parser;
using Catch::Clara::Arg;
using Catch::Clara::ExeName;

namespace {

class ClaraParserOrCombineTest_668 : public ::testing::Test {
protected:
    static std::string toHelp(const Parser& p) {
        std::ostringstream os;
        p.writeToStream(os);
        return os.str();
    }
};

} // namespace

// [668] Returns self reference
TEST_F(ClaraParserOrCombineTest_668, ReturnsSelfReference_668) {
    Parser lhs;
    Parser rhs;

    Parser* lhsPtr = &lhs;
    Parser& ret = (lhs |= rhs);

    EXPECT_EQ(&ret, lhsPtr);  // Operator should return reference to lhs
}

// [668] Combining with an empty parser does not change output
TEST_F(ClaraParserOrCombineTest_668, CombineWithEmptyDoesNotChangeOutput_668) {
    Parser base;

    // Give base some visible surface behavior through public API
    std::string inputVal;
    base |= ExeName{"prog"};
    base |= Arg(inputVal, "input", "input file");

    const std::string before = toHelp(base);

    Parser empty;
    base |= empty; // combining with empty should not change observable help text

    const std::string after = toHelp(base);
    EXPECT_EQ(before, after);
}

// [668] Appends args from the other parser; order should be preserved (A before B)
TEST_F(ClaraParserOrCombineTest_668, AppendsArgsAndPreservesOrder_668) {
    Parser pA;
    std::string aStorage;
    pA |= ExeName{"prog"};
    pA |= Arg(aStorage, "A", "first arg");

    Parser pB;
    std::string bStorage;
    pB |= Arg(bStorage, "B", "second arg");

    // Combine
    pA |= pB;

    const std::string help = toHelp(pA);

    // Observable check: both tokens appear, and "A" occurs before "B"
    const auto posA = help.find("A");
    const auto posB = help.find("B");

    ASSERT_NE(posA, std::string::npos) << "Expected help to mention Arg 'A'.";
    ASSERT_NE(posB, std::string::npos) << "Expected help to mention Arg 'B'.";
    EXPECT_LT(posA, posB) << "Args should be appended preserving order (A before B).";
}

// [668] Combining does not mutate the right-hand side parser
TEST_F(ClaraParserOrCombineTest_668, DoesNotMutateOther_668) {
    Parser lhs;
    lhs |= ExeName{"prog"};

    Parser rhs;
    std::string rhsStorage;
    rhs |= Arg(rhsStorage, "RHS", "right-side arg");

    const std::string rhsBefore = toHelp(rhs);

    lhs |= rhs; // combine

    const std::string rhsAfter = toHelp(rhs);
    EXPECT_EQ(rhsBefore, rhsAfter) << "Right-hand side parser should remain unchanged.";
}

// [668] Supports chaining: (p1 |= p2) |= p3; overall order A, B, C
TEST_F(ClaraParserOrCombineTest_668, SupportsChainingAndMaintainsOverallOrder_668) {
    Parser p1, p2, p3;

    std::string a, b, c;
    p1 |= ExeName{"prog"};
    p1 |= Arg(a, "A", "first");

    p2 |= Arg(b, "B", "second");
    p3 |= Arg(c, "C", "third");

    (p1 |= p2) |= p3;

    const std::string help = toHelp(p1);

    const auto posA = help.find("A");
    const auto posB = help.find("B");
    const auto posC = help.find("C");

    ASSERT_NE(posA, std::string::npos);
    ASSERT_NE(posB, std::string::npos);
    ASSERT_NE(posC, std::string::npos);

    EXPECT_LT(posA, posB);
    EXPECT_LT(posB, posC);
}

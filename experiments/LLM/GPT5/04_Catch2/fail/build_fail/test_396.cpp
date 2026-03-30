// File: parser_opt_or_equals_tests_396.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the header under test (paths based on the prompt)
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::Parser;
using Catch::Clara::Opt;
using Catch::Clara::ExeName;

class ParserOptOrEqualsTest_396 : public ::testing::Test {};

// [396] Ensures operator|= returns Parser& to the same object (chainable)
TEST_F(ParserOptOrEqualsTest_396, ReturnsSelfReference_396) {
    Parser p;
    bool flag = false;
    Opt o(flag);
    // action
    Parser* ret = &(p |= o);
    // assert
    EXPECT_EQ(ret, &p);
}

// [396] Supports chaining multiple Opt additions to same Parser
TEST_F(ParserOptOrEqualsTest_396, ChainingMultipleOptions_396) {
    Parser p;
    bool f1 = false, f2 = false;
    Opt o1(f1);  o1["-a"];
    Opt o2(f2);  o2["--beta"];
    // action: chain the |= operator
    Parser* ret = &((p |= o1) |= o2);
    EXPECT_EQ(ret, &p); // still the same object (chainable)
}

// [396] Interoperates with other Parser operators (ExeName and Parser merge) without throwing
TEST_F(ParserOptOrEqualsTest_396, InteropWithExeNameAndParserMerge_396) {
    Parser p, q;
    bool f1 = false, f2 = false;

    Opt o1(f1);  o1["-x"];
    Opt o2(f2);  o2["--yep"];

    // Add an option to q, then merge into p
    q |= o1;
    p |= ExeName("prog");     // should be valid to set executable name
    p |= q;                   // merge another parser's configuration
    // Finally add another option directly
    p |= o2;

    // If anything above broke the operator contract, it would fail to compile or throw.
    SUCCEED();
}

// [396] After adding an Opt with a name, writeToStream should include that name (observable effect)
TEST_F(ParserOptOrEqualsTest_396, WriteToStreamIncludesAddedOptName_396) {
    Parser p;
    bool flag = false;
    // Give the option a recognizable name; we don't assume anything else about formatting
    Opt o(flag);
    o["-f"]["--flag"];
    p |= o;

    std::ostringstream oss;
    p.writeToStream(oss);

    const std::string out = oss.str();
    // We only assert presence of the opt names, not exact layout.
    EXPECT_NE(out.find("-f"), std::string::npos);
    EXPECT_NE(out.find("--flag"), std::string::npos);
}

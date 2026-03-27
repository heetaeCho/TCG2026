#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



// Assuming the function BuildShiftDFA is part of a class or namespace re2

namespace re2 {

    uint64_t* BuildShiftDFA(std::string prefix);

    const size_t kShiftDFAFinal = 9;

}



using ::testing::ElementsAre;



class BuildShiftDFATest_417 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    // Helper function to free the allocated memory

    void FreeDFA(uint64_t* dfa) {

        delete[] dfa;

    }

};



TEST_F(BuildShiftDFATest_417, NormalOperation_417) {

    std::string prefix = "abc";

    uint64_t* result = re2::BuildShiftDFA(prefix);

    ASSERT_NE(result, nullptr);



    // Expected DFA values are based on the observable behavior

    EXPECT_EQ(result['a'], 0x3c);

    EXPECT_EQ(result['b'], 0x1e0);

    EXPECT_EQ(result['c'], 0xf000);

    EXPECT_EQ(result['A'], 0x3c); // Case insensitivity

    EXPECT_EQ(result['B'], 0x1e0);

    EXPECT_EQ(result['C'], 0xf000);



    FreeDFA(result);

}



TEST_F(BuildShiftDFATest_417, EmptyPrefix_417) {

    std::string prefix = "";

    uint64_t* result = re2::BuildShiftDFA(prefix);

    ASSERT_NE(result, nullptr);



    // All entries should point to the final state

    for (int b = 0; b < 256; ++b) {

        EXPECT_EQ(result[b], static_cast<uint64_t>(re2::kShiftDFAFinal * 6) << (re2::kShiftDFAFinal * 6));

    }



    FreeDFA(result);

}



TEST_F(BuildShiftDFATest_417, SingleCharPrefix_417) {

    std::string prefix = "a";

    uint64_t* result = re2::BuildShiftDFA(prefix);

    ASSERT_NE(result, nullptr);



    // 'a' should point to the final state

    EXPECT_EQ(result['a'], static_cast<uint64_t>(1 * 6) << (0 * 6));

    EXPECT_EQ(result['A'], static_cast<uint64_t>(1 * 6) << (0 * 6)); // Case insensitivity



    // Other characters should point to the final state

    for (int b = 0; b < 256; ++b) {

        if (b != 'a' && b != 'A') {

            EXPECT_EQ(result[b], static_cast<uint64_t>(re2::kShiftDFAFinal * 6) << (re2::kShiftDFAFinal * 6));

        }

    }



    FreeDFA(result);

}



TEST_F(BuildShiftDFATest_417, RepeatedCharsPrefix_417) {

    std::string prefix = "aa";

    uint64_t* result = re2::BuildShiftDFA(prefix);

    ASSERT_NE(result, nullptr);



    // 'a' should point to the final state

    EXPECT_EQ(result['a'], static_cast<uint64_t>(1 * 6) << (0 * 6));

    EXPECT_EQ(result['A'], static_cast<uint64_t>(1 * 6) << (0 * 6)); // Case insensitivity



    // Other characters should point to the final state

    for (int b = 0; b < 256; ++b) {

        if (b != 'a' && b != 'A') {

            EXPECT_EQ(result[b], static_cast<uint64_t>(re2::kShiftDFAFinal * 6) << (re2::kShiftDFAFinal * 6));

        }

    }



    FreeDFA(result);

}



TEST_F(BuildShiftDFATest_417, CaseInsensitive_417) {

    std::string prefix = "aBc";

    uint64_t* result = re2::BuildShiftDFA(prefix);

    ASSERT_NE(result, nullptr);



    // Both lower and upper case should point to the same state

    EXPECT_EQ(result['a'], result['A']);

    EXPECT_EQ(result['b'], result['B']);

    EXPECT_EQ(result['c'], result['C']);



    FreeDFA(result);

}



TEST_F(BuildShiftDFATest_417, NonAlphabetChars_417) {

    std::string prefix = "123";

    uint64_t* result = re2::BuildShiftDFA(prefix);

    ASSERT_NE(result, nullptr);



    // '1', '2', '3' should point to the final state

    EXPECT_EQ(result['1'], static_cast<uint64_t>(1 * 6) << (0 * 6));

    EXPECT_EQ(result['2'], static_cast<uint64_t>(1 * 6) << (1 * 6));

    EXPECT_EQ(result['3'], static_cast<uint64_t>(1 * 6) << (2 * 6));



    // Other characters should point to the final state

    for (int b = 0; b < 256; ++b) {

        if (b != '1' && b != '2' && b != '3') {

            EXPECT_EQ(result[b], static_cast<uint64_t>(re2::kShiftDFAFinal * 6) << (re2::kShiftDFAFinal * 6));

        }

    }



    FreeDFA(result);

}

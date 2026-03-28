#include "catch2/internal/catch_stringref.hpp"
#include <gtest/gtest.h>
#include <string>
#include <sstream>

using Catch::StringRef;

class StringRefSubstrTest_9 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== substr tests ====================

TEST_F(StringRefSubstrTest_9, SubstrFromBeginning_9) {
    StringRef ref("Hello, World!");
    auto result = ref.substr(0, 5);
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result, StringRef("Hello"));
}

TEST_F(StringRefSubstrTest_9, SubstrFromMiddle_9) {
    StringRef ref("Hello, World!");
    auto result = ref.substr(7, 5);
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result, StringRef("World"));
}

TEST_F(StringRefSubstrTest_9, SubstrEntireString_9) {
    StringRef ref("Hello");
    auto result = ref.substr(0, 5);
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result, StringRef("Hello"));
}

TEST_F(StringRefSubstrTest_9, SubstrLengthExceedsRemaining_9) {
    StringRef ref("Hello");
    auto result = ref.substr(3, 100);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result, StringRef("lo"));
}

TEST_F(StringRefSubstrTest_9, SubstrStartAtLastChar_9) {
    StringRef ref("Hello");
    auto result = ref.substr(4, 1);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'o');
}

TEST_F(StringRefSubstrTest_9, SubstrStartBeyondSize_9) {
    StringRef ref("Hello");
    auto result = ref.substr(5, 1);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(StringRefSubstrTest_9, SubstrStartWayBeyondSize_9) {
    StringRef ref("Hello");
    auto result = ref.substr(100, 1);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(StringRefSubstrTest_9, SubstrZeroLength_9) {
    StringRef ref("Hello");
    auto result = ref.substr(0, 0);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(StringRefSubstrTest_9, SubstrFromEmptyString_9) {
    StringRef ref("");
    auto result = ref.substr(0, 5);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(StringRefSubstrTest_9, SubstrDefaultConstructed_9) {
    StringRef ref;
    auto result = ref.substr(0, 5);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(StringRefSubstrTest_9, SubstrStartEqualToSizeOnDefaultConstructed_9) {
    StringRef ref;
    auto result = ref.substr(0, 0);
    EXPECT_TRUE(result.empty());
}

TEST_F(StringRefSubstrTest_9, SubstrWithLengthOne_9) {
    StringRef ref("ABCDE");
    auto result = ref.substr(2, 1);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'C');
}

TEST_F(StringRefSubstrTest_9, SubstrChainedCalls_9) {
    StringRef ref("Hello, World!");
    auto result = ref.substr(0, 12).substr(7, 5);
    EXPECT_EQ(result, StringRef("World"));
}

TEST_F(StringRefSubstrTest_9, SubstrMaxSizeType_9) {
    StringRef ref("Test");
    auto result = ref.substr(0, static_cast<StringRef::size_type>(-1));
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result, StringRef("Test"));
}

TEST_F(StringRefSubstrTest_9, SubstrStartOneBeforeEnd_9) {
    StringRef ref("AB");
    auto result = ref.substr(1, 100);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'B');
}

TEST_F(StringRefSubstrTest_9, SubstrFromStdString_9) {
    std::string str = "Hello, World!";
    StringRef ref(str);
    auto result = ref.substr(0, 5);
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result, StringRef("Hello"));
}

TEST_F(StringRefSubstrTest_9, SubstrDataPointerCorrectness_9) {
    const char* raw = "Hello, World!";
    StringRef ref(raw, 13);
    auto result = ref.substr(7, 5);
    // The data pointer should point into the original string
    EXPECT_EQ(result.data(), raw + 7);
}

TEST_F(StringRefSubstrTest_9, SubstrPreservesContentIntegrity_9) {
    StringRef ref("abcdefghij");
    auto result = ref.substr(3, 4);
    EXPECT_EQ(std::string(result), "defg");
}

// ==================== General StringRef interface tests ====================

class StringRefTest_9 : public ::testing::Test {};

TEST_F(StringRefTest_9, DefaultConstructorIsEmpty_9) {
    StringRef ref;
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

TEST_F(StringRefTest_9, ConstructFromCString_9) {
    StringRef ref("Hello");
    EXPECT_EQ(ref.size(), 5u);
    EXPECT_FALSE(ref.empty());
}

TEST_F(StringRefTest_9, ConstructFromCStringAndSize_9) {
    StringRef ref("Hello World", 5);
    EXPECT_EQ(ref.size(), 5u);
    EXPECT_EQ(ref, StringRef("Hello"));
}

TEST_F(StringRefTest_9, ConstructFromStdString_9) {
    std::string str = "Hello";
    StringRef ref(str);
    EXPECT_EQ(ref.size(), 5u);
    EXPECT_EQ(ref, StringRef("Hello"));
}

TEST_F(StringRefTest_9, EqualityOperator_9) {
    StringRef a("Hello");
    StringRef b("Hello");
    EXPECT_TRUE(a == b);
}

TEST_F(StringRefTest_9, InequalityOperator_9) {
    StringRef a("Hello");
    StringRef b("World");
    EXPECT_TRUE(a != b);
}

TEST_F(StringRefTest_9, EqualityDifferentLengths_9) {
    StringRef a("Hello");
    StringRef b("Hell");
    EXPECT_FALSE(a == b);
}

TEST_F(StringRefTest_9, IndexOperator_9) {
    StringRef ref("ABC");
    EXPECT_EQ(ref[0], 'A');
    EXPECT_EQ(ref[1], 'B');
    EXPECT_EQ(ref[2], 'C');
}

TEST_F(StringRefTest_9, EmptyOnNonEmpty_9) {
    StringRef ref("Test");
    EXPECT_FALSE(ref.empty());
}

TEST_F(StringRefTest_9, EmptyOnEmpty_9) {
    StringRef ref("");
    EXPECT_TRUE(ref.empty());
}

TEST_F(StringRefTest_9, ExplicitConversionToStdString_9) {
    StringRef ref("Hello");
    std::string str = static_cast<std::string>(ref);
    EXPECT_EQ(str, "Hello");
}

TEST_F(StringRefTest_9, CompareEqual_9) {
    StringRef a("Hello");
    StringRef b("Hello");
    EXPECT_EQ(a.compare(b), 0);
}

TEST_F(StringRefTest_9, CompareLessThan_9) {
    StringRef a("Apple");
    StringRef b("Banana");
    EXPECT_LT(a.compare(b), 0);
}

TEST_F(StringRefTest_9, CompareGreaterThan_9) {
    StringRef a("Banana");
    StringRef b("Apple");
    EXPECT_GT(a.compare(b), 0);
}

TEST_F(StringRefTest_9, LessThanOperator_9) {
    StringRef a("Apple");
    StringRef b("Banana");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(StringRefTest_9, DataPointer_9) {
    const char* raw = "Hello";
    StringRef ref(raw, 5);
    EXPECT_EQ(ref.data(), raw);
}

TEST_F(StringRefTest_9, BeginEndIteration_9) {
    StringRef ref("ABC");
    std::string result;
    for (auto it = ref.begin(); it != ref.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "ABC");
}

TEST_F(StringRefTest_9, OperatorPlusStringRefs_9) {
    StringRef a("Hello");
    StringRef b(" World");
    std::string result = a + b;
    EXPECT_EQ(result, "Hello World");
}

TEST_F(StringRefTest_9, OperatorPlusEqualsToString_9) {
    std::string str = "Hello";
    StringRef ref(" World");
    str += ref;
    EXPECT_EQ(str, "Hello World");
}

TEST_F(StringRefTest_9, OperatorOutputStream_9) {
    StringRef ref("Hello");
    std::ostringstream oss;
    oss << ref;
    EXPECT_EQ(oss.str(), "Hello");
}

TEST_F(StringRefTest_9, SizeOfEmptyStringRef_9) {
    StringRef ref;
    EXPECT_EQ(ref.size(), 0u);
}

TEST_F(StringRefTest_9, EqualityBothEmpty_9) {
    StringRef a;
    StringRef b("");
    EXPECT_TRUE(a == b);
}

TEST_F(StringRefTest_9, SubstrZeroStartZeroLengthOnNonEmpty_9) {
    StringRef ref("Hello");
    auto result = ref.substr(0, 0);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(StringRefTest_9, ComparePrefixShorterString_9) {
    StringRef a("Hell");
    StringRef b("Hello");
    EXPECT_LT(a.compare(b), 0);
}

TEST_F(StringRefTest_9, ComparePrefixLongerString_9) {
    StringRef a("Hello");
    StringRef b("Hell");
    EXPECT_GT(a.compare(b), 0);
}

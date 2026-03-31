#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <vector>

// Include the necessary headers from Catch2
#include "catch_amalgamated.hpp"

using namespace Catch;

// Helper to create TestCaseInfo objects
// We need SourceLineInfo and NameAndTags to construct TestCaseInfo
static std::unique_ptr<TestCaseInfo> makeTestCaseInfo(
    const std::string& className,
    const std::string& name,
    const std::string& tags,
    const SourceLineInfo& lineInfo = SourceLineInfo("test.cpp", 1))
{
    NameAndTags nameAndTags(name, tags);
    return std::make_unique<TestCaseInfo>(StringRef(className), nameAndTags, lineInfo);
}

class TestCaseInfoHasherTest_1011 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the hasher produces a consistent hash for the same input
TEST_F(TestCaseInfoHasherTest_1011, SameInputProducesSameHash_1011) {
    TestCaseInfoHasher hasher(12345u);
    
    auto tc1 = makeTestCaseInfo("MyClass", "test_name", "[tag1]");
    auto tc2 = makeTestCaseInfo("MyClass", "test_name", "[tag1]");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_EQ(hash1, hash2);
}

// Test that different names produce different hashes
TEST_F(TestCaseInfoHasherTest_1011, DifferentNamesProduceDifferentHashes_1011) {
    TestCaseInfoHasher hasher(12345u);
    
    auto tc1 = makeTestCaseInfo("MyClass", "test_name_a", "[tag1]");
    auto tc2 = makeTestCaseInfo("MyClass", "test_name_b", "[tag1]");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_NE(hash1, hash2);
}

// Test that different class names produce different hashes
TEST_F(TestCaseInfoHasherTest_1011, DifferentClassNamesProduceDifferentHashes_1011) {
    TestCaseInfoHasher hasher(12345u);
    
    auto tc1 = makeTestCaseInfo("ClassA", "test_name", "[tag1]");
    auto tc2 = makeTestCaseInfo("ClassB", "test_name", "[tag1]");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_NE(hash1, hash2);
}

// Test that different tags produce different hashes
TEST_F(TestCaseInfoHasherTest_1011, DifferentTagsProduceDifferentHashes_1011) {
    TestCaseInfoHasher hasher(12345u);
    
    auto tc1 = makeTestCaseInfo("MyClass", "test_name", "[tag1]");
    auto tc2 = makeTestCaseInfo("MyClass", "test_name", "[tag2]");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_NE(hash1, hash2);
}

// Test that different seeds produce different hashes for the same input
TEST_F(TestCaseInfoHasherTest_1011, DifferentSeedsProduceDifferentHashes_1011) {
    TestCaseInfoHasher hasher1(12345u);
    TestCaseInfoHasher hasher2(54321u);
    
    auto tc = makeTestCaseInfo("MyClass", "test_name", "[tag1]");
    
    uint32_t hash1 = hasher1(*tc);
    uint32_t hash2 = hasher2(*tc);
    
    EXPECT_NE(hash1, hash2);
}

// Test with seed of 0
TEST_F(TestCaseInfoHasherTest_1011, ZeroSeedProducesConsistentHash_1011) {
    TestCaseInfoHasher hasher(0u);
    
    auto tc1 = makeTestCaseInfo("MyClass", "test_name", "[tag1]");
    auto tc2 = makeTestCaseInfo("MyClass", "test_name", "[tag1]");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_EQ(hash1, hash2);
}

// Test with empty name, class, and no tags
TEST_F(TestCaseInfoHasherTest_1011, EmptyFieldsProduceConsistentHash_1011) {
    TestCaseInfoHasher hasher(42u);
    
    auto tc1 = makeTestCaseInfo("", "", "");
    auto tc2 = makeTestCaseInfo("", "", "");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_EQ(hash1, hash2);
}

// Test that empty fields with seed 0 vs seed 1 differ
TEST_F(TestCaseInfoHasherTest_1011, EmptyFieldsDifferentSeedsDiffer_1011) {
    TestCaseInfoHasher hasher1(0u);
    TestCaseInfoHasher hasher2(1u);
    
    auto tc = makeTestCaseInfo("", "", "");
    
    uint32_t hash1 = hasher1(*tc);
    uint32_t hash2 = hasher2(*tc);
    
    EXPECT_NE(hash1, hash2);
}

// Test with multiple tags
TEST_F(TestCaseInfoHasherTest_1011, MultipleTagsProduceConsistentHash_1011) {
    TestCaseInfoHasher hasher(99u);
    
    auto tc1 = makeTestCaseInfo("Cls", "test", "[tag1][tag2][tag3]");
    auto tc2 = makeTestCaseInfo("Cls", "test", "[tag1][tag2][tag3]");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_EQ(hash1, hash2);
}

// Test that the hash is deterministic across multiple calls
TEST_F(TestCaseInfoHasherTest_1011, DeterministicAcrossMultipleCalls_1011) {
    TestCaseInfoHasher hasher(777u);
    
    auto tc = makeTestCaseInfo("SomeClass", "some_test", "[important]");
    
    uint32_t hash1 = hasher(*tc);
    uint32_t hash2 = hasher(*tc);
    uint32_t hash3 = hasher(*tc);
    
    EXPECT_EQ(hash1, hash2);
    EXPECT_EQ(hash2, hash3);
}

// Test with very long name
TEST_F(TestCaseInfoHasherTest_1011, LongNameProducesValidHash_1011) {
    TestCaseInfoHasher hasher(123u);
    
    std::string longName(1000, 'x');
    auto tc = makeTestCaseInfo("MyClass", longName, "[tag]");
    
    // Just verify it doesn't crash and produces a result
    uint32_t hash = hasher(*tc);
    // Hash should be some non-trivial value (can't assert specific value as black box)
    (void)hash;
}

// Test with very long class name
TEST_F(TestCaseInfoHasherTest_1011, LongClassNameProducesValidHash_1011) {
    TestCaseInfoHasher hasher(123u);
    
    std::string longClassName(1000, 'y');
    auto tc = makeTestCaseInfo(longClassName, "test", "[tag]");
    
    uint32_t hash = hasher(*tc);
    (void)hash;
}

// Test that max seed value works
TEST_F(TestCaseInfoHasherTest_1011, MaxSeedValueWorks_1011) {
    TestCaseInfoHasher hasher(std::numeric_limits<uint64_t>::max());
    
    auto tc = makeTestCaseInfo("Class", "test", "[tag]");
    
    uint32_t hash1 = hasher(*tc);
    uint32_t hash2 = hasher(*tc);
    
    EXPECT_EQ(hash1, hash2);
}

// Test that swapping name and className produces different hashes
TEST_F(TestCaseInfoHasherTest_1011, SwappedNameAndClassProduceDifferentHashes_1011) {
    TestCaseInfoHasher hasher(42u);
    
    auto tc1 = makeTestCaseInfo("alpha", "beta", "");
    auto tc2 = makeTestCaseInfo("beta", "alpha", "");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    // Since name and className are hashed in sequence, swapping should produce different results
    EXPECT_NE(hash1, hash2);
}

// Test with special characters in name
TEST_F(TestCaseInfoHasherTest_1011, SpecialCharactersInName_1011) {
    TestCaseInfoHasher hasher(55u);
    
    auto tc1 = makeTestCaseInfo("Class", "test with spaces & symbols!@#$%", "[tag]");
    auto tc2 = makeTestCaseInfo("Class", "test with spaces & symbols!@#$%", "[tag]");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_EQ(hash1, hash2);
}

// Test single character differences
TEST_F(TestCaseInfoHasherTest_1011, SingleCharDifferenceCausesDifferentHash_1011) {
    TestCaseInfoHasher hasher(42u);
    
    auto tc1 = makeTestCaseInfo("Class", "testA", "");
    auto tc2 = makeTestCaseInfo("Class", "testB", "");
    
    uint32_t hash1 = hasher(*tc1);
    uint32_t hash2 = hasher(*tc2);
    
    EXPECT_NE(hash1, hash2);
}

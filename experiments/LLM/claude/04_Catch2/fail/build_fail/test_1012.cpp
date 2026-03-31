#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <algorithm>

// Include necessary Catch2 headers
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/extras/catch_amalgamated.hpp"

// Forward declare the function under test
namespace Catch {
    std::vector<TestCaseHandle> sortTests(IConfig const& config, std::vector<TestCaseHandle> const& unsortedTestCases);
}

// Mock IConfig
class MockConfig : public Catch::IConfig {
public:
    ~MockConfig() override = default;

    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// Helper to create TestCaseInfo objects for testing
// We need to create TestCaseInfo instances with different names to test sorting
class SortTestsFixture_1012 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test case infos with different names
        // Using Catch2's own mechanisms to create TestCaseInfo
    }

    void TearDown() override {
        for (auto* info : infos_) {
            delete info;
        }
        infos_.clear();
    }

    Catch::TestCaseInfo* makeInfo(const std::string& name, const std::string& className = "",
                                   const Catch::SourceLineInfo& lineInfo = {"file.cpp", 1},
                                   const std::string& description = "") {
        auto tags = std::vector<Catch::Tag>{};
        auto* info = new Catch::TestCaseInfo(name, className, description, tags, lineInfo);
        infos_.push_back(info);
        return info;
    }

    Catch::TestCaseHandle makeHandle(Catch::TestCaseInfo* info) {
        return Catch::TestCaseHandle(info, nullptr);
    }

    std::vector<Catch::TestCaseInfo*> infos_;
    MockConfig config_;
};

// Test: Empty list with Declared order returns empty
TEST_F(SortTestsFixture_1012, DeclaredOrder_EmptyList_ReturnsEmpty_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Declared));

    std::vector<Catch::TestCaseHandle> empty;
    auto result = Catch::sortTests(config_, empty);

    EXPECT_TRUE(result.empty());
}

// Test: Declared order returns tests in same order
TEST_F(SortTestsFixture_1012, DeclaredOrder_ReturnsSameOrder_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Declared));

    auto* info1 = makeInfo("Zebra");
    auto* info2 = makeInfo("Apple");
    auto* info3 = makeInfo("Mango");

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(info1), makeHandle(info2), makeHandle(info3)
    };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(&result[0].getTestCaseInfo(), info1);
    EXPECT_EQ(&result[1].getTestCaseInfo(), info2);
    EXPECT_EQ(&result[2].getTestCaseInfo(), info3);
}

// Test: Lexicographic order sorts alphabetically
TEST_F(SortTestsFixture_1012, LexicographicOrder_SortsAlphabetically_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::LexicographicallySorted));

    auto* infoZ = makeInfo("Zebra", "", {"file.cpp", 1});
    auto* infoA = makeInfo("Apple", "", {"file.cpp", 2});
    auto* infoM = makeInfo("Mango", "", {"file.cpp", 3});

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(infoZ), makeHandle(infoA), makeHandle(infoM)
    };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 3u);
    // Expect alphabetical order: Apple, Mango, Zebra
    EXPECT_EQ(&result[0].getTestCaseInfo(), infoA);
    EXPECT_EQ(&result[1].getTestCaseInfo(), infoM);
    EXPECT_EQ(&result[2].getTestCaseInfo(), infoZ);
}

// Test: Lexicographic order with empty list
TEST_F(SortTestsFixture_1012, LexicographicOrder_EmptyList_ReturnsEmpty_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::LexicographicallySorted));

    std::vector<Catch::TestCaseHandle> empty;
    auto result = Catch::sortTests(config_, empty);

    EXPECT_TRUE(result.empty());
}

// Test: Lexicographic order with single element
TEST_F(SortTestsFixture_1012, LexicographicOrder_SingleElement_ReturnsSame_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::LexicographicallySorted));

    auto* info = makeInfo("OnlyTest");
    std::vector<Catch::TestCaseHandle> tests = { makeHandle(info) };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(&result[0].getTestCaseInfo(), info);
}

// Test: Randomized order returns all elements
TEST_F(SortTestsFixture_1012, RandomizedOrder_ReturnsAllElements_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(42u));

    auto* info1 = makeInfo("TestA", "", {"file.cpp", 1});
    auto* info2 = makeInfo("TestB", "", {"file.cpp", 2});
    auto* info3 = makeInfo("TestC", "", {"file.cpp", 3});

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(info1), makeHandle(info2), makeHandle(info3)
    };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 3u);

    // All original infos should be present
    std::vector<Catch::TestCaseInfo const*> resultInfos;
    for (auto const& h : result) {
        resultInfos.push_back(&h.getTestCaseInfo());
    }

    EXPECT_THAT(resultInfos, ::testing::UnorderedElementsAre(info1, info2, info3));
}

// Test: Randomized order with empty list
TEST_F(SortTestsFixture_1012, RandomizedOrder_EmptyList_ReturnsEmpty_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(42u));

    std::vector<Catch::TestCaseHandle> empty;
    auto result = Catch::sortTests(config_, empty);

    EXPECT_TRUE(result.empty());
}

// Test: Randomized order is deterministic for same seed
TEST_F(SortTestsFixture_1012, RandomizedOrder_SameSeedProducesSameOrder_1012) {
    auto* info1 = makeInfo("Alpha", "", {"file1.cpp", 10});
    auto* info2 = makeInfo("Beta", "", {"file2.cpp", 20});
    auto* info3 = makeInfo("Gamma", "", {"file3.cpp", 30});
    auto* info4 = makeInfo("Delta", "", {"file4.cpp", 40});

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(info1), makeHandle(info2), makeHandle(info3), makeHandle(info4)
    };

    // First call
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(12345u));
    auto result1 = Catch::sortTests(config_, tests);

    // Second call with same seed
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(12345u));
    auto result2 = Catch::sortTests(config_, tests);

    ASSERT_EQ(result1.size(), result2.size());
    for (size_t i = 0; i < result1.size(); ++i) {
        EXPECT_EQ(&result1[i].getTestCaseInfo(), &result2[i].getTestCaseInfo());
    }
}

// Test: Randomized order with different seeds may produce different order
TEST_F(SortTestsFixture_1012, RandomizedOrder_DifferentSeedsMayProduceDifferentOrder_1012) {
    auto* info1 = makeInfo("Test1", "", {"a.cpp", 1});
    auto* info2 = makeInfo("Test2", "", {"b.cpp", 2});
    auto* info3 = makeInfo("Test3", "", {"c.cpp", 3});
    auto* info4 = makeInfo("Test4", "", {"d.cpp", 4});
    auto* info5 = makeInfo("Test5", "", {"e.cpp", 5});

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(info1), makeHandle(info2), makeHandle(info3),
        makeHandle(info4), makeHandle(info5)
    };

    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(1u));
    auto result1 = Catch::sortTests(config_, tests);

    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(999999u));
    auto result2 = Catch::sortTests(config_, tests);

    // We can't guarantee they're different, but we can check both have all elements
    ASSERT_EQ(result1.size(), 5u);
    ASSERT_EQ(result2.size(), 5u);
}

// Test: Declared order does not modify input vector
TEST_F(SortTestsFixture_1012, DeclaredOrder_DoesNotModifyInput_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Declared));

    auto* info1 = makeInfo("B_Test");
    auto* info2 = makeInfo("A_Test");

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(info1), makeHandle(info2)
    };

    auto result = Catch::sortTests(config_, tests);

    // Original should be unchanged
    EXPECT_EQ(&tests[0].getTestCaseInfo(), info1);
    EXPECT_EQ(&tests[1].getTestCaseInfo(), info2);
}

// Test: Lexicographic order does not modify input vector
TEST_F(SortTestsFixture_1012, LexicographicOrder_DoesNotModifyInput_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::LexicographicallySorted));

    auto* info1 = makeInfo("Z_Test", "", {"file.cpp", 1});
    auto* info2 = makeInfo("A_Test", "", {"file.cpp", 2});

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(info1), makeHandle(info2)
    };

    auto result = Catch::sortTests(config_, tests);

    // Original should be unchanged
    EXPECT_EQ(&tests[0].getTestCaseInfo(), info1);
    EXPECT_EQ(&tests[1].getTestCaseInfo(), info2);

    // Result should be sorted
    EXPECT_EQ(&result[0].getTestCaseInfo(), info2);
    EXPECT_EQ(&result[1].getTestCaseInfo(), info1);
}

// Test: Lexicographic order with already sorted input
TEST_F(SortTestsFixture_1012, LexicographicOrder_AlreadySorted_ReturnsSameOrder_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::LexicographicallySorted));

    auto* infoA = makeInfo("Apple", "", {"file.cpp", 1});
    auto* infoB = makeInfo("Banana", "", {"file.cpp", 2});
    auto* infoC = makeInfo("Cherry", "", {"file.cpp", 3});

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(infoA), makeHandle(infoB), makeHandle(infoC)
    };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(&result[0].getTestCaseInfo(), infoA);
    EXPECT_EQ(&result[1].getTestCaseInfo(), infoB);
    EXPECT_EQ(&result[2].getTestCaseInfo(), infoC);
}

// Test: Randomized with single element returns that element
TEST_F(SortTestsFixture_1012, RandomizedOrder_SingleElement_ReturnsSame_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(42u));

    auto* info = makeInfo("Solo");
    std::vector<Catch::TestCaseHandle> tests = { makeHandle(info) };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(&result[0].getTestCaseInfo(), info);
}

// Test: Declared order with single element
TEST_F(SortTestsFixture_1012, DeclaredOrder_SingleElement_ReturnsSame_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Declared));

    auto* info = makeInfo("Solo");
    std::vector<Catch::TestCaseHandle> tests = { makeHandle(info) };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(&result[0].getTestCaseInfo(), info);
}

// Test: Lexicographic sort with reverse order input
TEST_F(SortTestsFixture_1012, LexicographicOrder_ReverseInput_SortsCorrectly_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::LexicographicallySorted));

    auto* infoD = makeInfo("D_test", "", {"file.cpp", 1});
    auto* infoC = makeInfo("C_test", "", {"file.cpp", 2});
    auto* infoB = makeInfo("B_test", "", {"file.cpp", 3});
    auto* infoA = makeInfo("A_test", "", {"file.cpp", 4});

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(infoD), makeHandle(infoC), makeHandle(infoB), makeHandle(infoA)
    };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(&result[0].getTestCaseInfo(), infoA);
    EXPECT_EQ(&result[1].getTestCaseInfo(), infoB);
    EXPECT_EQ(&result[2].getTestCaseInfo(), infoC);
    EXPECT_EQ(&result[3].getTestCaseInfo(), infoD);
}

// Test: Randomized order preserves count with many elements
TEST_F(SortTestsFixture_1012, RandomizedOrder_ManyElements_PreservesCount_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(7u));

    std::vector<Catch::TestCaseHandle> tests;
    for (int i = 0; i < 20; ++i) {
        auto* info = makeInfo("Test_" + std::to_string(i), "", {"file.cpp", static_cast<std::size_t>(i + 1)});
        tests.push_back(makeHandle(info));
    }

    auto result = Catch::sortTests(config_, tests);

    EXPECT_EQ(result.size(), 20u);
}

// Test: Randomized with seed 0
TEST_F(SortTestsFixture_1012, RandomizedOrder_SeedZero_Works_1012) {
    EXPECT_CALL(config_, runOrder()).WillOnce(::testing::Return(Catch::TestRunOrder::Randomized));
    EXPECT_CALL(config_, rngSeed()).WillOnce(::testing::Return(0u));

    auto* info1 = makeInfo("First", "", {"file.cpp", 1});
    auto* info2 = makeInfo("Second", "", {"file.cpp", 2});

    std::vector<Catch::TestCaseHandle> tests = {
        makeHandle(info1), makeHandle(info2)
    };

    auto result = Catch::sortTests(config_, tests);

    ASSERT_EQ(result.size(), 2u);
    // Both elements should be present
    std::vector<Catch::TestCaseInfo const*> resultInfos;
    for (auto const& h : result) {
        resultInfos.push_back(&h.getTestCaseInfo());
    }
    EXPECT_THAT(resultInfos, ::testing::UnorderedElementsAre(info1, info2));
}

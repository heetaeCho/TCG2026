#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"



using namespace Catch;



class TestCaseInfoHasherTest : public ::testing::Test {

protected:

    hash_t seed = 12345;

    TestCaseInfoHasher hasher{seed};

};



TEST_F(TestCaseInfoHasherTest_1011, HashValueConsistency_1011) {

    TestCaseInfo testCase("ClassName", {"testName", "tag1"}, SourceLineInfo{"file.cpp", 10});

    uint32_t hash1 = hasher(testCase);

    uint32_t hash2 = hasher(testCase);

    EXPECT_EQ(hash1, hash2);

}



TEST_F(TestCaseInfoHasherTest_1011, DifferentNamesDifferentHashes_1011) {

    TestCaseInfo testCase1("ClassName", {"testName1", "tag1"}, SourceLineInfo{"file.cpp", 10});

    TestCaseInfo testCase2("ClassName", {"testName2", "tag1"}, SourceLineInfo{"file.cpp", 10});

    EXPECT_NE(hasher(testCase1), hasher(testCase2));

}



TEST_F(TestCaseInfoHasherTest_1011, DifferentClassesDifferentHashes_1011) {

    TestCaseInfo testCase1("ClassName1", {"testName", "tag1"}, SourceLineInfo{"file.cpp", 10});

    TestCaseInfo testCase2("ClassName2", {"testName", "tag1"}, SourceLineInfo{"file.cpp", 10});

    EXPECT_NE(hasher(testCase1), hasher(testCase2));

}



TEST_F(TestCaseInfoHasherTest_1011, DifferentTagsDifferentHashes_1011) {

    TestCaseInfo testCase1("ClassName", {"testName", "tag1"}, SourceLineInfo{"file.cpp", 10});

    TestCaseInfo testCase2("ClassName", {"testName", "tag2"}, SourceLineInfo{"file.cpp", 10});

    EXPECT_NE(hasher(testCase1), hasher(testCase2));

}



TEST_F(TestCaseInfoHasherTest_1011, EmptyTagsValidHash_1011) {

    TestCaseInfo testCase("ClassName", {"testName", ""}, SourceLineInfo{"file.cpp", 10});

    EXPECT_NO_THROW(hasher(testCase));

}



TEST_F(TestCaseInfoHasherTest_1011, MultipleTagsValidHash_1011) {

    TestCaseInfo testCase("ClassName", {"testName", "tag1,tag2"}, SourceLineInfo{"file.cpp", 10});

    EXPECT_NO_THROW(hasher(testCase));

}

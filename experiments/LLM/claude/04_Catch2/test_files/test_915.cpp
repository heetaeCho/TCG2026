#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <string>

// Test that a default-constructed Benchmark with a name is valid (operator bool)
TEST(BenchmarkTest_915, ConstructWithName_OperatorBoolReturnsTrue_915) {
    Catch::Benchmark::Benchmark bm(std::string("test_benchmark"));
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test that a Benchmark constructed with name and function is valid
TEST(BenchmarkTest_915, ConstructWithNameAndFunction_OperatorBoolReturnsTrue_915) {
    Catch::Benchmark::Benchmark bm(std::string("test_benchmark_with_func"), [](Catch::Benchmark::Chronometer) {});
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test operator bool explicitly returns true
TEST(BenchmarkTest_915, ExplicitOperatorBool_915) {
    Catch::Benchmark::Benchmark bm(std::string("bool_test"));
    bool result = static_cast<bool>(bm);
    EXPECT_TRUE(result);
}

// Test that assignment with a lambda works and benchmark remains valid
TEST(BenchmarkTest_915, AssignFunctionOperator_BenchmarkRemainsValid_915) {
    Catch::Benchmark::Benchmark bm(std::string("assign_test"));
    bm = [](Catch::Benchmark::Chronometer) {};
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test construction with empty name
TEST(BenchmarkTest_915, ConstructWithEmptyName_OperatorBoolReturnsTrue_915) {
    Catch::Benchmark::Benchmark bm(std::string(""));
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test that multiple benchmarks can be created independently
TEST(BenchmarkTest_915, MultipleBenchmarksIndependent_915) {
    Catch::Benchmark::Benchmark bm1(std::string("bench1"));
    Catch::Benchmark::Benchmark bm2(std::string("bench2"));
    EXPECT_TRUE(static_cast<bool>(bm1));
    EXPECT_TRUE(static_cast<bool>(bm2));
}

// Test reassignment with different functions
TEST(BenchmarkTest_915, ReassignFunction_BenchmarkStillValid_915) {
    Catch::Benchmark::Benchmark bm(std::string("reassign_test"));
    bm = [](Catch::Benchmark::Chronometer) { /* first */ };
    EXPECT_TRUE(static_cast<bool>(bm));
    bm = [](Catch::Benchmark::Chronometer) { /* second */ };
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test construction with a long benchmark name
TEST(BenchmarkTest_915, ConstructWithLongName_915) {
    std::string longName(10000, 'a');
    Catch::Benchmark::Benchmark bm(std::move(longName));
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test construction with special characters in name
TEST(BenchmarkTest_915, ConstructWithSpecialCharacterName_915) {
    Catch::Benchmark::Benchmark bm(std::string("!@#$%^&*()_+-=[]{}|;':\",./<>?"));
    EXPECT_TRUE(static_cast<bool>(bm));
}

// Test that operator= returns a reference to the benchmark
TEST(BenchmarkTest_915, AssignOperatorReturnsReference_915) {
    Catch::Benchmark::Benchmark bm(std::string("ref_test"));
    Catch::Benchmark::Benchmark& ref = (bm = [](Catch::Benchmark::Chronometer) {});
    EXPECT_EQ(&ref, &bm);
}

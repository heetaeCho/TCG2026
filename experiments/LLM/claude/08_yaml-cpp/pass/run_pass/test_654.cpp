#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <array>
#include <sstream>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/stlemitter.h"
#include "yaml-cpp/emittermanip.h"

class EmitSeqTest_654 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// Test EmitSeq with a vector of integers
TEST_F(EmitSeqTest_654, EmitVectorOfIntegers_654) {
    std::vector<int> seq = {1, 2, 3};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
    // Should contain the values
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Test EmitSeq with an empty vector
TEST_F(EmitSeqTest_654, EmitEmptyVector_654) {
    std::vector<int> seq;
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test EmitSeq with a vector of strings
TEST_F(EmitSeqTest_654, EmitVectorOfStrings_654) {
    std::vector<std::string> seq = {"hello", "world", "yaml"};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
    EXPECT_NE(output.find("world"), std::string::npos);
    EXPECT_NE(output.find("yaml"), std::string::npos);
}

// Test EmitSeq with a single element
TEST_F(EmitSeqTest_654, EmitSingleElementVector_654) {
    std::vector<int> seq = {42};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test EmitSeq with a list container
TEST_F(EmitSeqTest_654, EmitList_654) {
    std::list<int> seq = {10, 20, 30};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("20"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}

// Test EmitSeq with a deque container
TEST_F(EmitSeqTest_654, EmitDeque_654) {
    std::deque<int> seq = {5, 6, 7};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("5"), std::string::npos);
    EXPECT_NE(output.find("6"), std::string::npos);
    EXPECT_NE(output.find("7"), std::string::npos);
}

// Test EmitSeq with a set container
TEST_F(EmitSeqTest_654, EmitSet_654) {
    std::set<int> seq = {100, 200, 300};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("200"), std::string::npos);
    EXPECT_NE(output.find("300"), std::string::npos);
}

// Test EmitSeq returns a reference to the same emitter
TEST_F(EmitSeqTest_654, ReturnsEmitterReference_654) {
    std::vector<int> seq = {1};
    YAML::Emitter& result = YAML::EmitSeq(emitter, seq);
    EXPECT_EQ(&result, &emitter);
}

// Test EmitSeq with vector of doubles
TEST_F(EmitSeqTest_654, EmitVectorOfDoubles_654) {
    std::vector<double> seq = {1.5, 2.5, 3.5};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test EmitSeq with vector of booleans
TEST_F(EmitSeqTest_654, EmitVectorOfBools_654) {
    std::vector<std::string> seq = {"true", "false"};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
    EXPECT_NE(output.find("false"), std::string::npos);
}

// Test EmitSeq with Flow format
TEST_F(EmitSeqTest_654, EmitFlowSeq_654) {
    emitter.SetSeqFormat(YAML::Flow);
    std::vector<int> seq = {1, 2, 3};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Flow sequence uses brackets
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test EmitSeq with Block format
TEST_F(EmitSeqTest_654, EmitBlockSeq_654) {
    emitter.SetSeqFormat(YAML::Block);
    std::vector<int> seq = {1, 2, 3};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Block sequence uses dashes
    EXPECT_NE(output.find("- "), std::string::npos);
}

// Test EmitSeq with output to a stream
TEST_F(EmitSeqTest_654, EmitSeqToStream_654) {
    std::stringstream ss;
    YAML::Emitter streamEmitter(ss);
    std::vector<int> seq = {1, 2, 3};
    YAML::EmitSeq(streamEmitter, seq);
    EXPECT_TRUE(streamEmitter.good());
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Test EmitSeq with a large vector
TEST_F(EmitSeqTest_654, EmitLargeVector_654) {
    std::vector<int> seq;
    for (int i = 0; i < 100; ++i) {
        seq.push_back(i);
    }
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
    EXPECT_NE(output.find("99"), std::string::npos);
}

// Test EmitSeq with array
TEST_F(EmitSeqTest_654, EmitArray_654) {
    std::array<int, 3> seq = {10, 20, 30};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("20"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}

// Test EmitSeq size is non-zero for non-empty sequence
TEST_F(EmitSeqTest_654, EmitSeqSizeNonZero_654) {
    std::vector<int> seq = {1, 2};
    YAML::EmitSeq(emitter, seq);
    EXPECT_GT(emitter.size(), 0u);
}

// Test EmitSeq with negative numbers
TEST_F(EmitSeqTest_654, EmitVectorOfNegativeNumbers_654) {
    std::vector<int> seq = {-1, -2, -3};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-1"), std::string::npos);
    EXPECT_NE(output.find("-2"), std::string::npos);
    EXPECT_NE(output.find("-3"), std::string::npos);
}

// Test EmitSeq with vector of chars
TEST_F(EmitSeqTest_654, EmitVectorOfChars_654) {
    std::vector<char> seq = {'a', 'b', 'c'};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("a"), std::string::npos);
    EXPECT_NE(output.find("b"), std::string::npos);
    EXPECT_NE(output.find("c"), std::string::npos);
}

// Test EmitSeq with strings containing special characters
TEST_F(EmitSeqTest_654, EmitVectorOfSpecialStrings_654) {
    std::vector<std::string> seq = {"hello world", "key: value", "item\nnewline"};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// Test EmitSeq with empty strings
TEST_F(EmitSeqTest_654, EmitVectorOfEmptyStrings_654) {
    std::vector<std::string> seq = {"", "", ""};
    YAML::EmitSeq(emitter, seq);
    EXPECT_TRUE(emitter.good());
}

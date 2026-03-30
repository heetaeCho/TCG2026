#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/stlemitter.h"



using namespace YAML;



class EmitterTest_657 : public ::testing::Test {

protected:

    std::stringstream stream;

    Emitter emitter;

    

    EmitterTest_657() : emitter(stream) {}

};



TEST_F(EmitterTest_657, WriteSetNormalOperation_657) {

    std::set<int> values = {1, 2, 3};

    emitter << values;

    EXPECT_EQ(emitter.c_str(), "[1, 2, 3]\n");

}



TEST_F(EmitterTest_657, WriteEmptySet_657) {

    std::set<int> empty_set;

    emitter << empty_set;

    EXPECT_EQ(emitter.c_str(), "[]\n");

}



TEST_F(EmitterTest_657, WriteSetWithSingleElement_657) {

    std::set<int> single_element_set = {42};

    emitter << single_element_set;

    EXPECT_EQ(emitter.c_str(), "[42]\n");

}



TEST_F(EmitterTest_657, WriteSetWithDuplicateElements_657) {

    // Sets do not allow duplicate elements, so this is a normal operation test

    std::set<int> values = {1, 2, 2, 3};

    emitter << values;

    EXPECT_EQ(emitter.c_str(), "[1, 2, 3]\n");

}



TEST_F(EmitterTest_657, WriteSetWithDifferentTypes_657) {

    std::set<std::string> string_values = {"apple", "banana", "cherry"};

    emitter << string_values;

    EXPECT_EQ(emitter.c_str(), "[\"apple\", \"banana\", \"cherry\"]\n");

}



TEST_F(EmitterTest_657, WriteSetWithMixedTypesError_657) {

    // Since the set is templated, it should only contain elements of the same type.

    // This test case is more about ensuring that the set itself doesn't have mixed types,

    // which would be a compile-time error rather than a runtime one. Hence, this test

    // focuses on ensuring the correct behavior with consistent types.

    std::set<int> values = {1, 2, 3};

    emitter << values;

    EXPECT_EQ(emitter.c_str(), "[1, 2, 3]\n");

}



TEST_F(EmitterTest_657, WriteSetWithGoodState_657) {

    std::set<int> values = {1, 2, 3};

    emitter << values;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_657, WriteSetWithErrorState_657) {

    // To simulate an error state, we can try writing to a closed stream.

    stream.clear(std::ios_base::badbit);

    std::set<int> values = {1, 2, 3};

    emitter << values;

    EXPECT_FALSE(emitter.good());

}



TEST_F(EmitterTest_657, WriteSetAndGetLastError_657) {

    // To simulate an error state, we can try writing to a closed stream.

    stream.clear(std::ios_base::badbit);

    std::set<int> values = {1, 2, 3};

    emitter << values;

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(emitter.GetLastError(), "output error");

}

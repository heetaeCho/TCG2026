#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators.hpp"



using namespace Catch::Generators;



class GeneratorsTest_321 : public ::testing::Test {

protected:

    using T = int;  // Assuming a concrete type for the generator, e.g., int

    std::vector<GeneratorWrapper<T>> generators;

    Generators<T> gen;



    GeneratorsTest_321() : gen(Generators<T>()) {}



    void SetUp() override {

        // Initialize with some generators if needed

        generators.emplace_back(GeneratorWrapper<T>(T{}));

        generators.emplace_back(GeneratorWrapper<T>(T{}));

        for (auto&& generator : generators) {

            gen.add_generator(std::move(generator));

        }

    }

};



TEST_F(GeneratorsTest_321, NextReturnsTrueWhenMoreElementsExist_321) {

    EXPECT_TRUE(gen.next());

}



TEST_F(GeneratorsTest_321, NextReturnsFalseWhenNoMoreElementsExist_321) {

    gen.next();  // Move to the first element

    gen.next();  // Move to the second element (last one)

    EXPECT_FALSE(gen.next());  // No more elements

}



TEST_F(GeneratorsTest_321, NextAdvancesToNextElement_321) {

    EXPECT_TRUE(gen.next());

    EXPECT_TRUE(gen.next());

}



TEST_F(GeneratorsTest_321, GetReturnsCurrentElement_321) {

    gen.next();

    T current = gen.get();

    EXPECT_EQ(current, generators[0].get());

}



TEST_F(GeneratorsTest_321, BoundaryConditionSingleGenerator_321) {

    Generators<T> singleGen(generators[0]);

    EXPECT_TRUE(singleGen.next());

    EXPECT_FALSE(singleGen.next());

}



TEST_F(GeneratorsTest_321, ExceptionalCaseEmptyGenerators_321) {

    Generators<T> emptyGen;

    EXPECT_FALSE(emptyGen.next());

}

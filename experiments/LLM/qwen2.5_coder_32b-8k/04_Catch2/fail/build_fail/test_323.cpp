#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function makeGenerators is part of a class or can be tested in isolation

// For the purpose of this exercise, we will assume it can be tested directly.



using namespace Catch::Generators;



TEST(MakeGeneratorsTest_323, SingleGenerator_323) {

    // Test with a single generator

    auto gen1 = Generators<int>([]() { return 42; });

    auto result = makeGenerators(CATCH_MOVE(gen1));



    EXPECT_EQ(result.get(), 42);

}



TEST(MakeGeneratorsTest_323, MultipleGenerators_323) {

    // Test with multiple generators

    auto gen1 = Generators<int>([]() { return 42; });

    auto gen2 = Generators<int>([]() { return 84; });



    auto result = makeGenerators(CATCH_MOVE(gen1), CATCH_MOVE(gen2));



    EXPECT_EQ(result.get(), 42);

    EXPECT_EQ(result.get(), 84);

}



TEST(MakeGeneratorsTest_323, BoundaryCondition_NoGenerators_323) {

    // Test with no generators

    auto result = makeGenerators();



    // Assuming get() on an empty Generators object throws or returns a default value

    EXPECT_THROW(result.get(), std::runtime_error); // or EXPECT_EQ(result.get(), some_default_value);

}



TEST(MakeGeneratorsTest_323, ExceptionalCase_GeneratorThrows_323) {

    // Test with a generator that throws an exception

    auto gen1 = Generators<int>([]() -> int { throw std::runtime_error("Generator error"); });



    auto result = makeGenerators(CATCH_MOVE(gen1));



    EXPECT_THROW(result.get(), std::runtime_error);

}

```



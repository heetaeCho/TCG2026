#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators.hpp"



// Assuming we have a class to test that uses makeGenerators internally

class GeneratorUser {

public:

    template<typename T, typename U, typename... Gs>

    auto generateValues(Catch::Generators::as<T>, U&& val, Gs &&... moreGenerators) -> Catch::Generators::Generators<T> {

        return Catch::Generators::makeGenerators(Catch::Generators::as<T>(), CATCH_FORWARD(val), CATCH_FORWARD(moreGenerators)...);

    }

};



using namespace ::testing;



class GeneratorUserTest_326 : public Test {

protected:

    GeneratorUser generator_user;

};



TEST_F(GeneratorUserTest_326, GenerateSingleValue_326) {

    auto gen = generator_user.generateValues(Catch::Generators::as<int>(), 42);

    EXPECT_EQ(gen.get(), 42);

}



TEST_F(GeneratorUserTest_326, GenerateMultipleValues_326) {

    auto gen = generator_user.generateValues(Catch::Generators::as<int>(), 1, 2, 3);

    EXPECT_EQ(gen.get(), 1);

    gen.next();

    EXPECT_EQ(gen.get(), 2);

    gen.next();

    EXPECT_EQ(gen.get(), 3);

}



TEST_F(GeneratorUserTest_326, GenerateNoValues_326) {

    // This test is more about ensuring the generator doesn't break when no values are provided.

    // Since makeGenerators requires at least one value, this scenario might not be directly applicable.

    // However, we can ensure that providing a single value and then exhausting it behaves correctly.

    auto gen = generator_user.generateValues(Catch::Generators::as<int>(), 1);

    EXPECT_EQ(gen.get(), 1);

    gen.next();

    EXPECT_FALSE(gen.currentContext().isNextAvailable());

}



TEST_F(GeneratorUserTest_326, GenerateDifferentTypes_326) {

    auto gen = generator_user.generateValues(Catch::Generators::as<std::string>(), "hello", "world");

    EXPECT_EQ(gen.get(), "hello");

    gen.next();

    EXPECT_EQ(gen.get(), "world");

}



TEST_F(GeneratorUserTest_326, GenerateBoundaryValues_326) {

    auto gen = generator_user.generateValues(Catch::Generators::as<int>(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    EXPECT_EQ(gen.get(), std::numeric_limits<int>::min());

    gen.next();

    EXPECT_EQ(gen.get(), std::numeric_limits<int>::max());

}

```



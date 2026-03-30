#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/generators/catch_generators.hpp"

#include "catch2/internal/catch_stringref.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"

#include "catch2/internal/catch_source_line_info.hpp"

#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"



using namespace Catch::Generators;

using namespace Catch::Detail;



class MockIGeneratorTracker : public IGeneratorTracker {

public:

    MOCK_METHOD(bool, hasGenerator, (), (override));

    MOCK_METHOD(const Generators::GeneratorBasePtr &, getGenerator, (), (override));

    MOCK_METHOD(void, setGenerator, (Generators::GeneratorBasePtr && generator), (override));

};



TEST_F(MockIGeneratorTrackerTest_327, HasGenerator_ReturnsFalse_327) {

    MockIGeneratorTracker mock;

    EXPECT_CALL(mock, hasGenerator()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(mock.hasGenerator());

}



TEST_F(MockIGeneratorTrackerTest_327, HasGenerator_ReturnsTrue_327) {

    MockIGeneratorTracker mock;

    EXPECT_CALL(mock, hasGenerator()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(mock.hasGenerator());

}



TEST_F(MockIGeneratorTrackerTest_327, GetGenerator_ReturnsValidPointer_327) {

    MockIGeneratorTracker mock;

    auto generator = std::make_unique<Generators::GeneratorBase>();

    EXPECT_CALL(mock, getGenerator()).WillOnce(::testing::ReturnRef(*generator));

    EXPECT_EQ(&mock.getGenerator(), generator.get());

}



TEST_F(MockIGeneratorTrackerTest_327, SetGenerator_SetsCorrectly_327) {

    MockIGeneratorTracker mock;

    auto new_generator = std::make_unique<Generators::GeneratorBase>();

    EXPECT_CALL(mock, setGenerator(::testing::_));

    mock.setGenerator(std::move(new_generator));

}



TEST_F(MockIGeneratorTrackerTest_327, Generate_CallsCorrectMethods_327) {

    MockIGeneratorTracker* tracker_mock = new MockIGeneratorTracker;

    SourceLineInfo line_info("test_file.cpp", 42);

    StringRef generator_name("test_generator");



    EXPECT_CALL(*tracker_mock, getGenerator()).WillOnce(::testing::Return(Generators::GeneratorBasePtr()));



    auto generated_value = generate(generator_name, line_info, []{ return 42; });

    EXPECT_EQ(generated_value, 42);



    delete tracker_mock;

}



TEST_F(MockIGeneratorTrackerTest_327, Generate_HandlesExistingTracker_327) {

    MockIGeneratorTracker* tracker_mock = new MockIGeneratorTracker;

    SourceLineInfo line_info("test_file.cpp", 42);

    StringRef generator_name("test_generator");



    EXPECT_CALL(*tracker_mock, getGenerator()).WillOnce(::testing::Return(Generators::GeneratorBasePtr(new Generators::Generator<int>())));



    auto generated_value = generate(generator_name, line_info, []{ return 42; });

    EXPECT_EQ(generated_value, 42);



    delete tracker_mock;

}

```



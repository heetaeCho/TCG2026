#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators.cpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch::Generators;

using namespace testing;



class MockIResultCapture : public Catch::IResultCapture {

public:

    MOCK_METHOD3(createGeneratorTracker, IGeneratorTracker*(StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr&& generator));

};



TEST_F(MockIResultCaptureTest_355, CreateGeneratorTracker_NormalOperation_355) {

    MockIResultCapture mock;

    StringRef generatorName("test_generator");

    SourceLineInfo lineInfo(__FILE__, __LINE__);

    auto generator = std::make_unique<Generators::GeneratorBase>();



    EXPECT_CALL(mock, createGeneratorTracker(generatorName, lineInfo, _)).Times(1);

    mock.createGeneratorTracker(generatorName, lineInfo, std::move(generator));

}



TEST_F(MockIResultCaptureTest_355, CreateGeneratorTracker_BoundaryCondition_EmptyString_355) {

    MockIResultCapture mock;

    StringRef generatorName("");

    SourceLineInfo lineInfo(__FILE__, __LINE__);

    auto generator = std::make_unique<Generators::GeneratorBase>();



    EXPECT_CALL(mock, createGeneratorTracker(generatorName, lineInfo, _)).Times(1);

    mock.createGeneratorTracker(generatorName, lineInfo, std::move(generator));

}



TEST_F(MockIResultCaptureTest_355, CreateGeneratorTracker_ExceptionalCase_NullptrGenerator_355) {

    MockIResultCapture mock;

    StringRef generatorName("test_generator");

    SourceLineInfo lineInfo(__FILE__, __LINE__);

    Generators::GeneratorBasePtr generator = nullptr;



    EXPECT_CALL(mock, createGeneratorTracker(generatorName, lineInfo, _)).Times(1);

    mock.createGeneratorTracker(generatorName, lineInfo, std::move(generator));

}

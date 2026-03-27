#include <gtest/gtest.h>

#include "catch_interfaces_generatortracker.hpp"

#include <gmock/gmock.h>



using namespace Catch;

using namespace Catch::Generators;



class MockGeneratorUntypedBase : public GeneratorUntypedBase {

public:

    MOCK_CONST_METHOD0(next, bool());

    MOCK_CONST_METHOD0(stringifyImpl, std::string());

};



TEST_F(GeneratorUntypedBaseTest_59, CurrentElementAsString_CacheEmpty_ReturnsStringifiedValue_59) {

    MockGeneratorUntypedBase mockGenerator;

    EXPECT_CALL(mockGenerator, stringifyImpl()).WillOnce(testing::Return("test_string"));

    StringRef result = mockGenerator.currentElementAsString();

    EXPECT_EQ(result.toString(), "test_string");

}



TEST_F(GeneratorUntypedBaseTest_59, CurrentElementAsString_CacheNotEmpty_ReturnsCachedValue_59) {

    MockGeneratorUntypedBase mockGenerator;

    mockGenerator.m_stringReprCache = "cached_string";

    StringRef result = mockGenerator.currentElementAsString();

    EXPECT_EQ(result.toString(), "cached_string");

}



TEST_F(GeneratorUntypedBaseTest_59, CurrentElementAsString_CallTwice_CachesFirstResult_59) {

    MockGeneratorUntypedBase mockGenerator;

    EXPECT_CALL(mockGenerator, stringifyImpl()).WillOnce(testing::Return("test_string"));

    StringRef result1 = mockGenerator.currentElementAsString();

    StringRef result2 = mockGenerator.currentElementAsString();

    EXPECT_EQ(result1.toString(), "test_string");

    EXPECT_EQ(result2.toString(), "test_string");

}

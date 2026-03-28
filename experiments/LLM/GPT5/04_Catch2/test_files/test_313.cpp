// File: generator_wrapper_next_tests_313.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the real header under test.
// Adjust the include path if your project layout differs.
#include "Catch2/src/catch2/generators/catch_generators.hpp"

using ::testing::Return;
using ::testing::InSequence;
using ::testing::StrictMock;

namespace Catch { namespace Generators {

// Minimal declaration of IGenerator<T> just for mocking in tests if it's not visible
// through the included header. If the real IGenerator<T> is visible, this block
// should be skipped by the compiler due to ODR; otherwise it provides only what's
// needed for black-box interaction (countedNext()) without re-implementing logic.
#ifndef CATCH_TEST_IGENERATOR_FWD_313
#define CATCH_TEST_IGENERATOR_FWD_313
template <typename T>
struct IGenerator {
    virtual ~IGenerator() = default;
    virtual bool countedNext() = 0;
    // NOTE: We do NOT declare or use any other members; tests only observe next()->countedNext().
};
#endif

}} // namespace Catch::Generators

namespace {

// Mock that satisfies just the collaborator surface used by GeneratorWrapper::next()
template <typename T>
class MockIGenerator : public Catch::Generators::IGenerator<T> {
public:
    MOCK_METHOD(bool, countedNext, (), (override));
};

// We assume the real class template is Catch::Generators::GeneratorWrapper<T>,
// as hinted by the Known Dependencies. If your codebase provides a non-templated
// alias or wrapper, specialize/adjust the using below accordingly.
using Catch::Generators::GeneratorWrapper;

class GeneratorWrapperTest_313 : public ::testing::Test {
protected:
    using T = int;
    StrictMock<MockIGenerator<T>> mock_;
};

TEST_F(GeneratorWrapperTest_313, NextReturnsTrueWhenUnderlyingCountedNextIsTrue_313) {
    EXPECT_CALL(mock_, countedNext())
        .Times(1)
        .WillOnce(Return(true));

    // Construct wrapper with the collaborator pointer (interface contract).
    GeneratorWrapper<T> wrapper(&mock_);

    // Act & Assert
    EXPECT_TRUE(wrapper.next());
}

TEST_F(GeneratorWrapperTest_313, NextReturnsFalseWhenUnderlyingCountedNextIsFalse_313) {
    EXPECT_CALL(mock_, countedNext())
        .Times(1)
        .WillOnce(Return(false));

    GeneratorWrapper<T> wrapper(&mock_);
    EXPECT_FALSE(wrapper.next());
}

TEST_F(GeneratorWrapperTest_313, NextCallsCountedNextExactlyOncePerInvocation_313) {
    // Verify single call count precisely.
    EXPECT_CALL(mock_, countedNext())
        .Times(1)
        .WillOnce(Return(true));

    GeneratorWrapper<T> wrapper(&mock_);
    (void)wrapper.next(); // ignore return, focus on interaction count
}

TEST_F(GeneratorWrapperTest_313, MultipleSequentialCallsPropagateUnderlyingResultsInOrder_313) {
    InSequence seq; // enforce order of expectations

    EXPECT_CALL(mock_, countedNext()).WillOnce(Return(true));
    EXPECT_CALL(mock_, countedNext()).WillOnce(Return(false));

    GeneratorWrapper<T> wrapper(&mock_);

    EXPECT_TRUE(wrapper.next());   // first result forwarded
    EXPECT_FALSE(wrapper.next());  // second result forwarded
}


// File: basic_result_tests_369.cpp

#include <gtest/gtest.h>

// Include the header under test
#include "catch2/internal/catch_clara.hpp"

namespace cc = Catch::Clara::Detail;

TEST(BasicResultTest_369, OkVoid_HasOkType_IsTrue_EmptyMessage_369) {
    // Arrange + Act
    auto r = cc::BasicResult<void>::ok();

    // Assert
    EXPECT_EQ(r.type(), cc::ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(r));
    EXPECT_TRUE(r.errorMessage().empty());
}

TEST(BasicResultTest_369, OkWithValue_HasOkType_IsTrue_EmptyMessage_369) {
    // Arrange + Act
    auto r = cc::BasicResult<int>::ok(42);

    // Assert
    EXPECT_EQ(r.type(), cc::ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(r));
    EXPECT_TRUE(r.errorMessage().empty());
    // Note: We intentionally do NOT inspect any stored value to avoid relying on internal state.
}

TEST(BasicResultTest_369, LogicError_HasLogicErrorType_IsFalse_PreservesMessage_369) {
    // Arrange
    std::string msg = "invalid flag combination";

    // Act
    auto r = cc::BasicResult<void>::logicError(std::string(msg));

    // Assert
    EXPECT_EQ(r.type(), cc::ResultType::LogicError);
    EXPECT_FALSE(static_cast<bool>(r));
    EXPECT_EQ(r.errorMessage(), msg);
}

TEST(BasicResultTest_369, RuntimeError_HasRuntimeErrorType_IsFalse_PreservesMessage_369) {
    // Arrange
    std::string msg = "I/O failure";

    // Act
    auto r = cc::BasicResult<int>::runtimeError(std::string(msg));

    // Assert
    EXPECT_EQ(r.type(), cc::ResultType::RuntimeError);
    EXPECT_FALSE(static_cast<bool>(r));
    EXPECT_EQ(r.errorMessage(), msg);
}

TEST(BasicResultTest_369, LogicError_AllowsEmptyMessage_369) {
    // Arrange
    std::string msg;

    // Act
    auto r = cc::BasicResult<void>::logicError(std::string(msg));

    // Assert
    EXPECT_EQ(r.type(), cc::ResultType::LogicError);
    EXPECT_FALSE(static_cast<bool>(r));
    EXPECT_TRUE(r.errorMessage().empty());
}

TEST(BasicResultTest_369, CrossTypeCopyCtor_PreservesTypeAndMessage_369) {
    // Arrange: create a source error result with a message
    std::string msg = "bad parse";
    auto src = cc::BasicResult<int>::logicError(std::string(msg));

    // Act: copy-construct a BasicResult with a different value type from the source
    cc::BasicResult<double> dst(src);

    // Assert: observable properties preserved
    EXPECT_EQ(dst.type(), cc::ResultType::LogicError);
    EXPECT_FALSE(static_cast<bool>(dst));
    EXPECT_EQ(dst.errorMessage(), msg);
}

TEST(BasicResultTest_369, OkCopyAcrossTypes_PreservesOkAndEmptyMessage_369) {
    // Arrange
    auto src = cc::BasicResult<long>::ok(123L);

    // Act
    cc::BasicResult<unsigned> dst(src);

    // Assert
    EXPECT_EQ(dst.type(), cc::ResultType::Ok);
    EXPECT_TRUE(static_cast<bool>(dst));
    EXPECT_TRUE(dst.errorMessage().empty());
}

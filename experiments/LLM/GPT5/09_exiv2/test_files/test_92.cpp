#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "exiv2/matroskavideo.hpp"

using namespace Exiv2::Internal;

class MatroskaTagTest_92 : public ::testing::Test {
protected:
    // Setup any necessary resources for the test here.
};

TEST_F(MatroskaTagTest_92, IsCompositeReturnsTrueForCompositeProcess_92) {
    // Arrange
    MatroskaTag tag(1, "CompositeTag", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Composite);

    // Act
    bool result = tag.isComposite();

    // Assert
    ASSERT_TRUE(result);
}

TEST_F(MatroskaTagTest_92, IsCompositeReturnsFalseForNonCompositeProcess_92) {
    // Arrange
    MatroskaTag tag(1, "NonCompositeTag", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Process);

    // Act
    bool result = tag.isComposite();

    // Assert
    ASSERT_FALSE(result);
}

TEST_F(MatroskaTagTest_92, IsCompositeReturnsFalseForSkipProcess_92) {
    // Arrange
    MatroskaTag tag(2, "SkipTag", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Skip);

    // Act
    bool result = tag.isComposite();

    // Assert
    ASSERT_FALSE(result);
}

TEST_F(MatroskaTagTest_92, IsCompositeReturnsFalseForUndefinedProcess_92) {
    // Arrange
    MatroskaTag tag(3, "UndefinedTag", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

    // Act
    bool result = tag.isComposite();

    // Assert
    ASSERT_FALSE(result);
}

TEST_F(MatroskaTagTest_92, IsCompositeReturnsFalseForDefaultMatroskaTag_92) {
    // Arrange
    MatroskaTag tag(4, "DefaultTag");

    // Act
    bool result = tag.isComposite();

    // Assert
    ASSERT_FALSE(result);
}
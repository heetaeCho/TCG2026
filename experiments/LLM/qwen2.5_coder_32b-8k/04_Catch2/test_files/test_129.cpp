#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_decomposer.hpp"



using namespace Catch;

using namespace testing;



// Mock class to simulate external collaborators if needed

class MockExternalCollaborator {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



TEST_F(CatchDecomposerTest_129, NormalOperation_129) {

    // Arrange

    int value = 42;

    Decomposer decomposer;



    // Act

    auto result = std::move(decomposer) <= value;



    // Assert

    EXPECT_EQ(&result.m_lhs, &value);

}



TEST_F(CatchDecomposerTest_129, BoundaryCondition_ZeroValue_129) {

    // Arrange

    int value = 0;

    Decomposer decomposer;



    // Act

    auto result = std::move(decomposer) <= value;



    // Assert

    EXPECT_EQ(&result.m_lhs, &value);

}



TEST_F(CatchDecomposerTest_129, BoundaryCondition_MaxIntValue_129) {

    // Arrange

    int value = std::numeric_limits<int>::max();

    Decomposer decomposer;



    // Act

    auto result = std::move(decomposer) <= value;



    // Assert

    EXPECT_EQ(&result.m_lhs, &value);

}



TEST_F(CatchDecomposerTest_129, BoundaryCondition_MinIntValue_129) {

    // Arrange

    int value = std::numeric_limits<int>::min();

    Decomposer decomposer;



    // Act

    auto result = std::move(decomposer) <= value;



    // Assert

    EXPECT_EQ(&result.m_lhs, &value);

}



TEST_F(CatchDecomposerTest_129, ExternalInteraction_MockHandlerCall_129) {

    // Arrange

    MockExternalCollaborator mockCollaborator;

    int value = 42;

    Decomposer decomposer;



    EXPECT_CALL(mockCollaborator, someMethod()).Times(1);



    // Act

    auto result = std::move(decomposer) <= value;

    mockCollaborator.someMethod();



    // Assert

    EXPECT_EQ(&result.m_lhs, &value);

}

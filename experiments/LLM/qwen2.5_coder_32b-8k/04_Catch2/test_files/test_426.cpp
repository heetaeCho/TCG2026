#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include "./TestProjects/Catch2/src/catch2/internal/catch_console_colour.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class MockColourImpl : public ColourImpl {

public:

    MOCK_METHOD(void, engageImpl, (std::ostream&), (override));

};



TEST_F(ColourGuardTest_426, EngageCallsEngageImpl_426) {

    MockColourImpl mockColourImpl;

    ColourGuard guard{Colour::Code{}, &mockColourImpl};

    std::ostringstream oss;



    EXPECT_CALL(mockColourImpl, engageImpl(Ref(oss)));

    guard.engage(oss);

}



TEST_F(ColourGuardTest_426, MoveConstructorPreservesState_426) {

    MockColourImpl mockColourImpl;

    ColourGuard original{Colour::Code{}, &mockColourImpl};

    std::ostringstream oss;



    EXPECT_CALL(mockColourImpl, engageImpl(Ref(oss)));

    ColourGuard moved = std::move(original);

    moved.engage(oss);

}



TEST_F(ColourGuardTest_426, EngageReturnsReferenceToSelf_426) {

    MockColourImpl mockColourImpl;

    ColourGuard guard{Colour::Code{}, &mockColourImpl};

    std::ostringstream oss;



    EXPECT_CALL(mockColourImpl, engageImpl(Ref(oss)));

    auto& result = guard.engage(oss);

    EXPECT_EQ(&guard, &result);

}



TEST_F(ColourGuardTest_426, OperatorLeftShiftCallsEngageImpl_426) {

    MockColourImpl mockColourImpl;

    ColourGuard guard{Colour::Code{}, &mockColourImpl};

    std::ostringstream oss;



    EXPECT_CALL(mockColourImpl, engageImpl(Ref(oss)));

    oss << std::move(guard);

}



TEST_F(ColourGuardTest_426, DeletedCopyConstructorAndAssignment_426) {

    MockColourImpl mockColourImpl;

    ColourGuard original{Colour::Code{}, &mockColourImpl};



    static_assert(!std::is_copy_constructible<ColourGuard>::value, "ColourGuard should not be copy constructible");

    static_assert(!std::is_copy_assignable<ColourGuard>::value, "ColourGuard should not be copy assignable");



    ColourGuard moved = std::move(original);

    EXPECT_NO_THROW(moved = std::move(moved)); // Self-move is okay

}

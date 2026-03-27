#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_console_colour.hpp"



using namespace Catch;

using namespace testing;



class MockIStream : public IStream {

public:

    MOCK_METHOD(void, write, (const std::string&), (override));

};



TEST_F(ColourImplTest_631, GuardColourCreatesGuardWithCorrectCodeAndImpl_631) {

    MockIStream mockStream;

    ColourImpl colourImpl(&mockStream);

    auto guard = colourImpl.guardColour(Colour::Red);



    EXPECT_EQ(guard.m_code, Colour::Red);

    EXPECT_EQ(guard.m_colourImpl, &colourImpl);

}



TEST_F(ColourImplTest_631, GuardGuardDtorResetsToNoneIfEngaged_631) {

    MockIStream mockStream;

    EXPECT_CALL(mockStream, write).WillRepeatedly(Return());

    ColourImpl colourImpl(&mockStream);

    auto guard = colourImpl.guardColour(Colour::Red);



    testing::InSequence seq;

    EXPECT_CALL(mockStream, write("RedCode")); // Assuming some code is written when engaging

    EXPECT_CALL(mockStream, write("NoneCode")); // Assuming "None" is written on destruction



    guard.engage(mockStream);

}



TEST_F(ColourImplTest_631, GuardGuardMoveConstructorTransfersState_631) {

    MockIStream mockStream;

    ColourImpl colourImpl(&mockStream);

    auto originalGuard = colourImpl.guardColour(Colour::Green).engage(mockStream);



    ColourGuard movedGuard(std::move(originalGuard));



    EXPECT_EQ(movedGuard.m_code, Colour::Green);

    EXPECT_EQ(movedGuard.m_colourImpl, &colourImpl);

    EXPECT_TRUE(movedGuard.m_engaged);

}



TEST_F(ColourImplTest_631, GuardGuardMoveAssignmentTransfersState_631) {

    MockIStream mockStream;

    ColourImpl colourImpl(&mockStream);

    auto originalGuard = colourImpl.guardColour(Colour::Blue).engage(mockStream);



    ColourGuard movedGuard(Colour::None, &colourImpl);

    movedGuard = std::move(originalGuard);



    EXPECT_EQ(movedGuard.m_code, Colour::Blue);

    EXPECT_EQ(movedGuard.m_colourImpl, &colourImpl);

    EXPECT_TRUE(movedGuard.m_engaged);

}



TEST_F(ColourImplTest_631, GuardGuardDeletedCopyConstructorAndAssignment_631) {

    MockIStream mockStream;

    ColourImpl colourImpl(&mockStream);

    auto guard = colourImpl.guardColour(Colour::Yellow);



    EXPECT_FALSE(std::is_copy_constructible<ColourGuard>::value);

    EXPECT_FALSE(std::is_copy_assignable<ColourGuard>::value);

}



TEST_F(ColourImplTest_631, GuardEngageSetsEngagedFlagAndCallsUse_631) {

    MockIStream mockStream;

    EXPECT_CALL(mockStream, write("YellowCode")); // Assuming some code is written when engaging



    ColourImpl colourImpl(&mockStream);

    auto guard = colourImpl.guardColour(Colour::Yellow).engage(mockStream);



    EXPECT_TRUE(guard.m_engaged);

}



TEST_F(ColourImplTest_631, GuardGuardDtorDoesNothingIfNotEngaged_631) {

    MockIStream mockStream;

    ColourImpl colourImpl(&mockStream);

    auto guard = colourImpl.guardColour(Colour::Cyan);



    EXPECT_CALL(mockStream, write).Times(0); // Expect no writes



    // Guard goes out of scope without engaging

}



TEST_F(ColourImplTest_631, GuardGuardCanEngageMultipleTimes_631) {

    MockIStream mockStream;

    EXPECT_CALL(mockStream, write("WhiteCode")).Times(2); // Assuming some code is written when engaging



    ColourImpl colourImpl(&mockStream);

    auto guard = colourImpl.guardColour(Colour::White);



    guard.engage(mockStream).engage(mockStream);

}

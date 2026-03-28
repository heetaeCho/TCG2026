#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch2/internal/catch_console_colour.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockStream : public std::ostream {

public:

    using std::ostream::ostream;

    MOCK_METHOD0(flush, std::ostream&());

};



TEST_F(ColourGuardTest_632, EngageDoesNotThrowOnValidStream_632) {

    ColourImpl colourImpl;

    Colour::Code code = {}; // Assuming default constructor is valid

    ColourGuard guard(code, &colourImpl);

    MockStream mockStream;



    EXPECT_NO_THROW(guard.engage(mockStream));

}



TEST_F(ColourGuardTest_632, EngageReturnsReferenceToSelf_632) {

    ColourImpl colourImpl;

    Colour::Code code = {};

    ColourGuard guard(code, &colourImpl);

    std::ostream stream;



    EXPECT_EQ(&guard, &(guard.engage(stream)));

}



TEST_F(ColourGuardTest_632, EngageCallsEngageImplOnce_632) {

    class MockColourImpl : public ColourImpl {

    public:

        MOCK_METHOD1(engageImpl, void(std::ostream&));

    };



    MockColourImpl mockColourImpl;

    Colour::Code code = {};

    ColourGuard guard(code, &mockColourImpl);

    std::ostream stream;



    EXPECT_CALL(mockColourImpl, engageImpl(_)).Times(1);

    guard.engage(stream);

}



TEST_F(ColourGuardTest_632, MoveConstructorSetsCorrectValues_632) {

    ColourImpl colourImpl;

    Colour::Code code = {};

    ColourGuard original(code, &colourImpl);

    std::ostream stream;



    // Engage the original to set m_engaged

    original.engage(stream);



    ColourGuard moved(std::move(original));



    EXPECT_EQ(moved.m_colourImpl, &colourImpl);

    EXPECT_EQ(moved.m_code, code);

    EXPECT_TRUE(moved.m_engaged);

}



TEST_F(ColourGuardTest_632, DeletedCopyConstructorDoesNotCompile_632) {

    // This test is conceptual as the compiler will prevent usage.

    // The deleted copy constructor should be tested by ensuring compilation fails if used.

    // Since we cannot directly write a failing compile-time test in gtest,

    // this serves as a reminder that such a check is necessary.

}



TEST_F(ColourGuardTest_632, DeletedCopyAssignmentDoesNotCompile_632) {

    // Similar to the above, this is more of a conceptual test.

    // The deleted copy assignment should be tested by ensuring compilation fails if used.

}

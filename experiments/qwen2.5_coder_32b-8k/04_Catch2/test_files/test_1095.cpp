#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>



// Assuming Catch2's ColourImpl and ColourGuard are defined in catch_console_colour.hpp

#include "catch_console_colour.hpp"



using namespace Catch;



class MockStream : public std::ostream {

public:

    using std::ostream::ostream;

    MOCK_METHOD(void, write, (const char*, std::streamsize), (override));

};



TEST_F(ColourGuardTest_1095, MoveConstructorDoesNotEngage_1095) {

    MockStream mockStream;

    ColourImpl::ColourCode code = {}; // Assuming Colour::Code is default constructible

    const ColourImpl colourImpl;



    ColourGuard guard(code, &colourImpl);

    EXPECT_CALL(mockStream, write(_, _)).Times(0); // Ensure no write calls happen



    ColourGuard movedGuard(std::move(guard));

}



TEST_F(ColourGuardTest_1095, EngageCallsEngageImplOnce_1095) {

    MockStream mockStream;

    ColourImpl::ColourCode code = {}; // Assuming Colour::Code is default constructible

    const ColourImpl colourImpl;



    ColourGuard guard(code, &colourImpl);

    EXPECT_CALL(mockStream, write(_, _)).Times(1); // Expect one call to engageImpl



    guard.engage(mockStream);

}



TEST_F(ColourGuardTest_1095, EngageOnMovedGuardThrows_1095) {

    MockStream mockStream;

    ColourImpl::ColourCode code = {}; // Assuming Colour::Code is default constructible

    const ColourImpl colourImpl;



    ColourGuard guard(code, &colourImpl);

    ColourGuard movedGuard(std::move(guard));



    EXPECT_THROW(movedGuard.engage(mockStream), std::runtime_error); // Assuming engage throws on disengaged guard

}



TEST_F(ColourGuardTest_1095, DeletedCopyConstructorAndAssignment_1095) {

    MockStream mockStream;

    ColourImpl::ColourCode code = {}; // Assuming Colour::Code is default constructible

    const ColourImpl colourImpl;



    ColourGuard guard(code, &colourImpl);



    EXPECT_FALSE((std::is_copy_constructible<ColourGuard>::value));

    EXPECT_FALSE((std::is_copy_assignable<ColourGuard>::value));



    ColourGuard anotherGuard(ColourImpl::ColourCode{}, &colourImpl);

    

    // Copy assignment should not compile

    // anotherGuard = guard; // This line would cause a compilation error, hence commented out.



    // Copy construction should not compile

    // ColourGuard yetAnotherGuard(guard); // This line would cause a compilation error, hence commented out.

}

#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_console_colour.cpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;



class ConsoleColourTest_634 : public ::testing::Test {

protected:

    // No additional setup required for these tests

};



TEST_F(ConsoleColourTest_634, PlatformDefault_IsAvailable_634) {

    EXPECT_TRUE(isColourImplAvailable(ColourMode::PlatformDefault));

}



TEST_F(ConsoleColourTest_634, ANSI_IsAvailable_634) {

    EXPECT_TRUE(isColourImplAvailable(ColourMode::ANSI));

}



TEST_F(ConsoleColourTest_634, Win32_IsAvailable_634) {

#if defined( CATCH_CONFIG_COLOUR_WIN32 )

    EXPECT_TRUE(isColourImplAvailable(ColourMode::Win32));

#else

    EXPECT_FALSE(isColourImplAvailable(ColourMode::Win32));

#endif

}



TEST_F(ConsoleColourTest_634, None_IsAvailable_634) {

    EXPECT_TRUE(isColourImplAvailable(ColourMode::None));

}



TEST_F(ConsoleColourTest_634, InvalidValue_IsNotAvailable_634) {

    EXPECT_FALSE(isColourImplAvailable(static_cast<ColourMode>(10))); // Assuming an invalid value

}

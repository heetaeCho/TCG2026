#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_console_colour.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using namespace ::testing;



class MockIStream : public IStream {

public:

    MOCK_METHOD(std::ostream&, stream, (), (override));

    MOCK_CONST_METHOD0(isConsole, bool(), (override));

};



TEST(makeColourImplTest_633, CreateANSIColourImplForANSIMode_633) {

    MockIStream mockStream;

    EXPECT_CALL(mockStream, isConsole()).WillOnce(Return(true));



    auto colourImpl = makeColourImpl(ColourMode::ANSI, &mockStream);

    ASSERT_NE(colourImpl.get(), nullptr);

    EXPECT_TRUE(dynamic_cast<ANSIColourImpl*>(colourImpl.get()) != nullptr);

}



TEST(makeColourImplTest_633, CreateWin32ColourImplForWin32Mode_633) {

#ifdef CATCH_CONFIG_COLOUR_WIN32

    MockIStream mockStream;

    EXPECT_CALL(mockStream, isConsole()).WillOnce(Return(true));



    auto colourImpl = makeColourImpl(ColourMode::Win32, &mockStream);

    ASSERT_NE(colourImpl.get(), nullptr);

    EXPECT_TRUE(dynamic_cast<Win32ColourImpl*>(colourImpl.get()) != nullptr);

#endif

}



TEST(makeColourImplTest_633, CreateNoColourImplForNoneMode_633) {

    MockIStream mockStream;

    auto colourImpl = makeColourImpl(ColourMode::None, &mockStream);

    ASSERT_NE(colourImpl.get(), nullptr);

    EXPECT_TRUE(dynamic_cast<NoColourImpl*>(colourImpl.get()) != nullptr);

}



TEST(makeColourImplTest_633, CreateANSIColourImplForPlatformDefaultWithANSISupport_633) {

    MockIStream mockStream;

    ON_CALL(mockStream, isConsole()).WillByDefault(Return(true));

    EXPECT_CALL(ANSIColourImpl, useImplementationForStream(_)).WillOnce(Return(true));



    auto colourImpl = makeColourImpl(ColourMode::PlatformDefault, &mockStream);

    ASSERT_NE(colourImpl.get(), nullptr);

    EXPECT_TRUE(dynamic_cast<ANSIColourImpl*>(colourImpl.get()) != nullptr);

}



#ifdef CATCH_CONFIG_COLOUR_WIN32

TEST(makeColourImplTest_633, CreateWin32ColourImplForPlatformDefaultWithWin32Support_633) {

    MockIStream mockStream;

    ON_CALL(mockStream, isConsole()).WillByDefault(Return(true));

    EXPECT_CALL(Win32ColourImpl, useImplementationForStream(_)).WillOnce(Return(true));

    EXPECT_CALL(ANSIColourImpl, useImplementationForStream(_)).WillOnce(Return(false));



    auto colourImpl = makeColourImpl(ColourMode::PlatformDefault, &mockStream);

    ASSERT_NE(colourImpl.get(), nullptr);

    EXPECT_TRUE(dynamic_cast<Win32ColourImpl*>(colourImpl.get()) != nullptr);

}

#endif



TEST(makeColourImplTest_633, CreateNoColourImplForPlatformDefaultWithoutSupport_633) {

    MockIStream mockStream;

    ON_CALL(mockStream, isConsole()).WillByDefault(Return(true));

    EXPECT_CALL(Win32ColourImpl, useImplementationForStream(_)).WillOnce(Return(false));

    EXPECT_CALL(ANSIColourImpl, useImplementationForStream(_)).WillOnce(Return(false));



    auto colourImpl = makeColourImpl(ColourMode::PlatformDefault, &mockStream);

    ASSERT_NE(colourImpl.get(), nullptr);

    EXPECT_TRUE(dynamic_cast<NoColourImpl*>(colourImpl.get()) != nullptr);

}



TEST(makeColourImplTest_633, ThrowsForUnknownColourMode_633) {

    MockIStream mockStream;

    EXPECT_THROW({

        makeColourImpl(static_cast<ColourMode>(42), &mockStream);

    }, std::runtime_error);

}

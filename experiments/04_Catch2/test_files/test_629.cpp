#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_console_colour.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockIStream : public IStream {

public:

    MOCK_METHOD(void, use, (Colour::Code colourCode), (override));

};



class ColourImplTest_629 : public ::testing::Test {

protected:

    std::unique_ptr<MockIStream> mock_stream;

    std::unique_ptr<ColourImpl> colour_impl;



    void SetUp() override {

        mock_stream = std::make_unique<MockIStream>();

        colour_impl = std::make_unique<ColourImpl>(mock_stream.get());

    }

};



TEST_F(ColourImplTest_629, GuardColourCallsUseWithNormalOperation_629) {

    EXPECT_CALL(*mock_stream, use(_)).Times(1);

    colour_impl->guardColour(Colour::Code::White);

}



TEST_F(ColourImplTest_629, GuardColourDoesNotThrowForValidColours_629) {

    ASSERT_NO_THROW(colour_impl->guardColour(Colour::Code::Red));

    ASSERT_NO_THROW(colour_impl->guardColour(Colour::Code::Green));

    ASSERT_NO_THROW(colour_impl->guardColour(Colour::Code::Blue));

}



TEST_F(ColourImplTest_629, GuardColourVerifiesExternalInteractionWithMock_629) {

    EXPECT_CALL(*mock_stream, use(Colour::Code::Yellow)).Times(1);

    colour_impl->guardColour(Colour::Code::Yellow);

}

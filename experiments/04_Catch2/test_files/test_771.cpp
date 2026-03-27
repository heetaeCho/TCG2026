#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_console.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"

#include "catch2/internal/catch_console_colour.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class MockStream : public IStream {

public:

    MOCK_METHOD(void, write, (std::string const&), (override));

};



class MockColourImpl : public ColourImpl {

public:

    using ColourImpl::ColourImpl;

    MOCK_METHOD(ColourGuard, guardColour, (struct Colour::Code colourCode), (override));

};



class ConsoleReporterTest : public ::testing::Test {

protected:

    void SetUp() override {

        auto mockStream = std::make_unique<MockStream>();

        m_streamPtr = mockStream.get();

        auto mockColourImpl = std::make_unique<MockColourImpl>(m_streamPtr);

        m_colourImplPtr = mockColourImpl.get();



        ReporterConfig config{nullptr, nullptr, false, {}, "", nullptr};

        config.stream = CATCH_MOVE(mockStream);

        config.colourMode_ = Colour::None;

        config.m_colourImpl = CATCH_MOVE(mockColourImpl);



        reporter = std::make_unique<ConsoleReporter>(CATCH_MOVE(config));

    }



    MockStream* m_streamPtr;

    MockColourImpl* m_colourImplPtr;

    std::unique_ptr<ConsoleReporter> reporter;

};



TEST_F(ConsoleReporterTest_771, BenchmarkFailed_NonEmptyError_771) {

    EXPECT_CALL(*m_colourImplPtr, guardColour(Colour::Red)).WillOnce(testing::Return(ByMove(MockColourImpl::ColourGuard{Colour::Red, m_colourImplPtr})));

    EXPECT_CALL(*m_streamPtr, write("Benchmark failed (error message)" + std::string(1, ColumnBreak()) + std::string(1, RowBreak())));



    reporter->benchmarkFailed(StringRef{"error message"});

}



TEST_F(ConsoleReporterTest_771, BenchmarkFailed_EmptyError_771) {

    EXPECT_CALL(*m_colourImplPtr, guardColour(Colour::Red)).WillOnce(testing::Return(ByMove(MockColourImpl::ColourGuard{Colour::Red, m_colourImplPtr})));

    EXPECT_CALL(*m_streamPtr, write("Benchmark failed ()" + std::string(1, ColumnBreak()) + std::string(1, RowBreak())));



    reporter->benchmarkFailed(StringRef{""});

}

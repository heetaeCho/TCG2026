#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_interfaces_reporter.hpp"



using namespace Catch;



class MockIStream : public IStream {

public:

    MOCK_METHOD(void, write, (const std::string&), (override));

};



TEST_F(ReporterConfigTest_111, TakeStream_ReturnsNonNullPointer_111) {

    auto mockStream = Detail::unique_ptr<IStream>(new MockIStream());

    ReporterConfig config(nullptr, CATCH_MOVE(mockStream), ColourMode::None, {});

    EXPECT_NE(config.takeStream().get(), nullptr);

}



TEST_F(ReporterConfigTest_111, TakeStream_MovesOwnership_StreamIsNull_111) {

    auto mockStream = Detail::unique_ptr<IStream>(new MockIStream());

    ReporterConfig config(nullptr, CATCH_MOVE(mockStream), ColourMode::None, {});

    config.takeStream();

    EXPECT_EQ(config.m_stream.get(), nullptr);

}



TEST_F(ReporterConfigTest_111, FullConfig_ReturnsCorrectPointer_111) {

    const IConfig* mockConfig = new IConfig();

    ReporterConfig config(mockConfig, {}, ColourMode::None, {});

    EXPECT_EQ(config.fullConfig(), mockConfig);

}



TEST_F(ReporterConfigTest_111, ColourMode_ReturnsSetColourMode_111) {

    ReporterConfig config(nullptr, {}, ColourMode::Ansi, {});

    EXPECT_EQ(config.colourMode(), ColourMode::Ansi);

}



TEST_F(ReporterConfigTest_111, CustomOptions_ReturnsCorrectMap_111) {

    std::map<std::string, std::string> customOpts = {{"key", "value"}};

    ReporterConfig config(nullptr, {}, ColourMode::None, CATCH_MOVE(customOpts));

    EXPECT_EQ(config.customOptions(), customOpts);

}



TEST_F(ReporterConfigTest_111, MoveConstructor_TransfersStreamOwnership_111) {

    auto mockStream = Detail::unique_ptr<IStream>(new MockIStream());

    ReporterConfig original(nullptr, CATCH_MOVE(mockStream), ColourMode::None, {});

    ReporterConfig moved(CATCH_MOVE(original));

    EXPECT_NE(moved.m_stream.get(), nullptr);

    EXPECT_EQ(original.m_stream.get(), nullptr);

}



TEST_F(ReporterConfigTest_111, MoveAssignment_TransfersStreamOwnership_111) {

    auto mockStream = Detail::unique_ptr<IStream>(new MockIStream());

    ReporterConfig original(nullptr, CATCH_MOVE(mockStream), ColourMode::None, {});

    ReporterConfig moved;

    moved = CATCH_MOVE(original);

    EXPECT_NE(moved.m_stream.get(), nullptr);

    EXPECT_EQ(original.m_stream.get(), nullptr);

}

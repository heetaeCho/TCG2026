#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "build.h"

// Mock class for CommandRunner to test virtual interface
class MockCommandRunner : public CommandRunner {
public:
    MOCK_METHOD(const size_t, CanRunMore, (), (override));
    MOCK_METHOD(bool, StartCommand, (Edge* edge), (override));
    MOCK_METHOD(bool, WaitForCommand, (Result* result), (override));
    MOCK_METHOD(std::vector<Edge*>, GetActiveEdges, (), (override));
    MOCK_METHOD(void, Abort, (), (override));
    ~MockCommandRunner() override = default;
};

// Test fixture
class CommandRunnerTest_89 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that default GetActiveEdges returns an empty vector
TEST_F(CommandRunnerTest_89, DefaultGetActiveEdgesReturnsEmptyVector_89) {
    // Create a minimal concrete subclass that uses default GetActiveEdges
    struct MinimalCommandRunner : public CommandRunner {
        const size_t CanRunMore() override { return 0; }
        bool StartCommand(Edge* edge) override { return false; }
        bool WaitForCommand(Result* result) override { return false; }
        void Abort() override {}
    };

    MinimalCommandRunner runner;
    std::vector<Edge*> edges = runner.GetActiveEdges();
    EXPECT_TRUE(edges.empty());
    EXPECT_EQ(edges.size(), 0u);
}

// Test that mock GetActiveEdges can return edges
TEST_F(CommandRunnerTest_89, MockGetActiveEdgesReturnsEdges_89) {
    MockCommandRunner runner;
    Edge* fakeEdge1 = reinterpret_cast<Edge*>(0x1);
    Edge* fakeEdge2 = reinterpret_cast<Edge*>(0x2);
    std::vector<Edge*> expected = {fakeEdge1, fakeEdge2};

    EXPECT_CALL(runner, GetActiveEdges())
        .WillOnce(::testing::Return(expected));

    std::vector<Edge*> result = runner.GetActiveEdges();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], fakeEdge1);
    EXPECT_EQ(result[1], fakeEdge2);
}

// Test that CanRunMore can be called via mock
TEST_F(CommandRunnerTest_89, CanRunMoreReturnsExpectedValue_89) {
    MockCommandRunner runner;

    EXPECT_CALL(runner, CanRunMore())
        .WillOnce(::testing::Return(5));

    EXPECT_EQ(runner.CanRunMore(), 5u);
}

// Test CanRunMore returns zero (boundary)
TEST_F(CommandRunnerTest_89, CanRunMoreReturnsZero_89) {
    MockCommandRunner runner;

    EXPECT_CALL(runner, CanRunMore())
        .WillOnce(::testing::Return(0));

    EXPECT_EQ(runner.CanRunMore(), 0u);
}

// Test StartCommand returns true
TEST_F(CommandRunnerTest_89, StartCommandReturnsTrue_89) {
    MockCommandRunner runner;
    Edge* fakeEdge = reinterpret_cast<Edge*>(0x1);

    EXPECT_CALL(runner, StartCommand(fakeEdge))
        .WillOnce(::testing::Return(true));

    EXPECT_TRUE(runner.StartCommand(fakeEdge));
}

// Test StartCommand returns false
TEST_F(CommandRunnerTest_89, StartCommandReturnsFalse_89) {
    MockCommandRunner runner;
    Edge* fakeEdge = reinterpret_cast<Edge*>(0x1);

    EXPECT_CALL(runner, StartCommand(fakeEdge))
        .WillOnce(::testing::Return(false));

    EXPECT_FALSE(runner.StartCommand(fakeEdge));
}

// Test StartCommand with nullptr edge
TEST_F(CommandRunnerTest_89, StartCommandWithNullEdge_89) {
    MockCommandRunner runner;

    EXPECT_CALL(runner, StartCommand(nullptr))
        .WillOnce(::testing::Return(false));

    EXPECT_FALSE(runner.StartCommand(nullptr));
}

// Test WaitForCommand returns true
TEST_F(CommandRunnerTest_89, WaitForCommandReturnsTrue_89) {
    MockCommandRunner runner;

    EXPECT_CALL(runner, WaitForCommand(::testing::_))
        .WillOnce(::testing::Return(true));

    EXPECT_TRUE(runner.WaitForCommand(nullptr));
}

// Test WaitForCommand returns false
TEST_F(CommandRunnerTest_89, WaitForCommandReturnsFalse_89) {
    MockCommandRunner runner;

    EXPECT_CALL(runner, WaitForCommand(::testing::_))
        .WillOnce(::testing::Return(false));

    EXPECT_FALSE(runner.WaitForCommand(nullptr));
}

// Test Abort is called
TEST_F(CommandRunnerTest_89, AbortIsCalled_89) {
    MockCommandRunner runner;

    EXPECT_CALL(runner, Abort())
        .Times(1);

    runner.Abort();
}

// Test GetActiveEdges returns empty vector from mock
TEST_F(CommandRunnerTest_89, MockGetActiveEdgesReturnsEmpty_89) {
    MockCommandRunner runner;

    EXPECT_CALL(runner, GetActiveEdges())
        .WillOnce(::testing::Return(std::vector<Edge*>()));

    std::vector<Edge*> result = runner.GetActiveEdges();
    EXPECT_TRUE(result.empty());
}

// Test multiple calls to GetActiveEdges
TEST_F(CommandRunnerTest_89, MultipleGetActiveEdgesCalls_89) {
    MockCommandRunner runner;
    Edge* fakeEdge = reinterpret_cast<Edge*>(0x1);

    EXPECT_CALL(runner, GetActiveEdges())
        .WillOnce(::testing::Return(std::vector<Edge*>()))
        .WillOnce(::testing::Return(std::vector<Edge*>{fakeEdge}))
        .WillOnce(::testing::Return(std::vector<Edge*>()));

    EXPECT_EQ(runner.GetActiveEdges().size(), 0u);
    EXPECT_EQ(runner.GetActiveEdges().size(), 1u);
    EXPECT_EQ(runner.GetActiveEdges().size(), 0u);
}

// Test that CommandRunner can be destroyed via base pointer (virtual destructor)
TEST_F(CommandRunnerTest_89, VirtualDestructorWorks_89) {
    CommandRunner* runner = new MockCommandRunner();
    // Should not leak or crash
    delete runner;
}

// Test CanRunMore with large value (boundary)
TEST_F(CommandRunnerTest_89, CanRunMoreLargeValue_89) {
    MockCommandRunner runner;
    size_t largeVal = static_cast<size_t>(-1); // max size_t

    EXPECT_CALL(runner, CanRunMore())
        .WillOnce(::testing::Return(largeVal));

    EXPECT_EQ(runner.CanRunMore(), largeVal);
}

// Test sequence of StartCommand and GetActiveEdges
TEST_F(CommandRunnerTest_89, StartThenGetActiveEdges_89) {
    MockCommandRunner runner;
    Edge* fakeEdge = reinterpret_cast<Edge*>(0x42);

    {
        ::testing::InSequence seq;

        EXPECT_CALL(runner, StartCommand(fakeEdge))
            .WillOnce(::testing::Return(true));

        EXPECT_CALL(runner, GetActiveEdges())
            .WillOnce(::testing::Return(std::vector<Edge*>{fakeEdge}));

        EXPECT_CALL(runner, WaitForCommand(::testing::_))
            .WillOnce(::testing::Return(true));

        EXPECT_CALL(runner, GetActiveEdges())
            .WillOnce(::testing::Return(std::vector<Edge*>()));
    }

    EXPECT_TRUE(runner.StartCommand(fakeEdge));
    EXPECT_EQ(runner.GetActiveEdges().size(), 1u);
    EXPECT_TRUE(runner.WaitForCommand(nullptr));
    EXPECT_EQ(runner.GetActiveEdges().size(), 0u);
}

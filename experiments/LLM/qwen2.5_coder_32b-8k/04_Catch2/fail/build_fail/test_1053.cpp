#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_message.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_reusable_string_stream.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_message_info.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_message.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo& message), (override));

};



class ScopedMessageTest_1053 : public ::testing::Test {

protected:

    NiceMock<MockIResultCapture> mockResultCapture;

    SourceLineInfo lineInfo{"test_file.cpp", 42};

    StringRef macroName{"TEST"};

    ResultWas::OfType type{ResultWas::Ok};



    void SetUp() override {

        Catch::getResultCapture = [&]() -> IResultCapture& { return mockResultCapture; };

    }

};



TEST_F(ScopedMessageTest_1053, ConstructorPushesMessage_1053) {

    MessageBuilder builder(macroName, lineInfo, type);

    builder << "Test message";



    EXPECT_CALL(mockResultCapture, pushScopedMessage(_)).Times(1);



    ScopedMessage scopedMessage(std::move(builder));

}



TEST_F(ScopedMessageTest_1053, MoveConstructorTransfersOwnership_1053) {

    MessageBuilder builder(macroName, lineInfo, type);

    builder << "Test message";



    EXPECT_CALL(mockResultCapture, pushScopedMessage(_)).Times(1);



    ScopedMessage original(std::move(builder));

    ScopedMessage moved(std::move(original));



    // No additional calls to pushScopedMessage expected after move

}



TEST_F(ScopedMessageTest_1053, DeletedCopyConstructorPreventsCopying_1053) {

    MessageBuilder builder(macroName, lineInfo, type);

    builder << "Test message";



    EXPECT_CALL(mockResultCapture, pushScopedMessage(_)).Times(1);



    ScopedMessage original(std::move(builder));



    // This should not compile

    // ScopedMessage copied(original);  // Uncommenting this line would cause a compilation error



    SUCCEED();

}



TEST_F(ScopedMessageTest_1053, EmptyStreamDoesNotPushMessage_1053) {

    MessageBuilder builder(macroName, lineInfo, type);

    // No stream operations to simulate empty message



    EXPECT_CALL(mockResultCapture, pushScopedMessage(_)).Times(0);



    ScopedMessage scopedMessage(std::move(builder));

}

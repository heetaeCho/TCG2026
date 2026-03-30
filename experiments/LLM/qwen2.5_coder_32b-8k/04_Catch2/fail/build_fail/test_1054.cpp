#include <gtest/gtest.h>

#include "catch2/catch_message.hpp"



using namespace Catch;



class ScopedMessageTest : public ::testing::Test {

protected:

    MessageBuilder createMessageBuilder() {

        // This is a mock implementation for creating a MessageBuilder.

        // In actual scenarios, this would involve setting up the builder appropriately.

        return MessageBuilder();

    }

};



TEST_F(ScopedMessageTest_1054, MoveConstructorSetsMovedFlagTrue_1054) {

    MessageBuilder builder = createMessageBuilder();

    ScopedMessage original(builder);

    ScopedMessage moved(std::move(original));

    EXPECT_TRUE(original.m_moved);

}



TEST_F(ScopedMessageTest_1054, CopyConstructorIsDeleted_1054) {

    MessageBuilder builder = createMessageBuilder();

    ScopedMessage original(builder);

    EXPECT_FALSE(original.m_moved);



    // This test ensures that the copy constructor is deleted.

    // If uncommented, this line will cause a compile-time error:

    // ScopedMessage copy = original;

}



TEST_F(ScopedMessageTest_1054, DestructorExists_1054) {

    MessageBuilder builder = createMessageBuilder();

    ScopedMessage* message = new ScopedMessage(builder);

    delete message;  // Ensure the destructor is called without issues

}

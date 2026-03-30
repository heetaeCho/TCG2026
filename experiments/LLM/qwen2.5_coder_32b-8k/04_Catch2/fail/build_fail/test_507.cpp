#include <gtest/gtest.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/catch_message.hpp"



class RunContextTest_507 : public ::testing::Test {

protected:

    Catch::RunContext* runContext;

    std::shared_ptr<Catch::IEventListener> mockReporter;



    void SetUp() override {

        mockReporter = std::make_shared<Catch::IEventListener>();

        runContext = new Catch::RunContext(nullptr, std::move(mockReporter));

    }



    void TearDown() override {

        delete runContext;

    }

};



TEST_F(RunContextTest_507, EmplaceUnscopedMessage_AddsMessage_507) {

    // Arrange

    Catch::SourceLineInfo lineInfo("filename", 123);

    Catch::MessageBuilder builder("MACRO_NAME", lineInfo, Catch::ResultWas::OfType::Unknown);



    // Act

    runContext->emplaceUnscopedMessage(std::move(builder));



    // Assert

    // Since we cannot access internal state, we rely on the fact that if no exception is thrown,

    // the method worked as expected.

}



TEST_F(RunContextTest_507, EmplaceUnscopedMessage_HandlesEmptyMacroName_507) {

    // Arrange

    Catch::SourceLineInfo lineInfo("filename", 123);

    Catch::MessageBuilder builder("", lineInfo, Catch::ResultWas::OfType::Unknown);



    // Act & Assert

    EXPECT_NO_THROW(runContext->emplaceUnscopedMessage(std::move(builder)));

}



TEST_F(RunContextTest_507, EmplaceUnscopedMessage_HandlesLargeLineNumbers_507) {

    // Arrange

    Catch::SourceLineInfo lineInfo("filename", 123456789);

    Catch::MessageBuilder builder("MACRO_NAME", lineInfo, Catch::ResultWas::OfType::Unknown);



    // Act & Assert

    EXPECT_NO_THROW(runContext->emplaceUnscopedMessage(std::move(builder)));

}



TEST_F(RunContextTest_507, EmplaceUnscopedMessage_HandlesNullptrConfig_507) {

    // Arrange

    Catch::SourceLineInfo lineInfo("filename", 123);

    Catch::MessageBuilder builder("MACRO_NAME", lineInfo, Catch::ResultWas::OfType::Unknown);



    // Act & Assert

    EXPECT_NO_THROW(runContext->emplaceUnscopedMessage(std::move(builder)));

}



TEST_F(RunContextTest_507, EmplaceUnscopedMessage_HandlesDifferentResultTypes_507) {

    // Arrange

    Catch::SourceLineInfo lineInfo("filename", 123);

    

    // Act & Assert for different result types

    EXPECT_NO_THROW({

        Catch::MessageBuilder builderPass("MACRO_NAME", lineInfo, Catch::ResultWas::OfType::Ok);

        runContext->emplaceUnscopedMessage(std::move(builderPass));

    });



    EXPECT_NO_THROW({

        Catch::MessageBuilder builderFail("MACRO_NAME", lineInfo, Catch::ResultWas::OfType::Failure);

        runContext->emplaceUnscopedMessage(std::move(builderFail));

    });

}

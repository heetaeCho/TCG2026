#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_exception_translator_registry.hpp"



using namespace Catch;



class ExceptionTranslatorRegistryTest_687 : public ::testing::Test {

protected:

    ExceptionTranslatorRegistry registry;

};



TEST_F(ExceptionTranslatorRegistryTest_687, TranslateActiveException_NoException_687) {

    EXPECT_EQ(registry.translateActiveException(), "Non C++ exception. Possibly a CLR exception.");

}



TEST_F(ExceptionTranslatorRegistryTest_687, TranslateActiveException_StdException_687) {

    try {

        throw std::runtime_error("Standard Exception");

        FAIL() << "Expected an exception to be thrown";

    } catch (...) {

        EXPECT_EQ(registry.translateActiveException(), "Standard Exception");

    }

}



TEST_F(ExceptionTranslatorRegistryTest_687, TranslateActiveException_StringLiteral_687) {

    try {

        throw "String Literal Exception";

        FAIL() << "Expected an exception to be thrown";

    } catch (...) {

        EXPECT_EQ(registry.translateActiveException(), "String Literal Exception");

    }

}



TEST_F(ExceptionTranslatorRegistryTest_687, TranslateActiveException_StringObject_687) {

    try {

        throw std::string("String Object Exception");

        FAIL() << "Expected an exception to be thrown";

    } catch (...) {

        EXPECT_EQ(registry.translateActiveException(), "String Object Exception");

    }

}



TEST_F(ExceptionTranslatorRegistryTest_687, TranslateActiveException_UnhandledException_687) {

    try {

        throw 42; // int type exception which is not handled

        FAIL() << "Expected an exception to be thrown";

    } catch (...) {

        EXPECT_EQ(registry.translateActiveException(), "Unknown exception");

    }

}



TEST_F(ExceptionTranslatorRegistryTest_687, TranslateActiveException_TestFailureException_Rethrow_687) {

    try {

        throw TestFailureException();

        FAIL() << "Expected an exception to be thrown";

    } catch (const TestFailureException& e) {

        EXPECT_THROW(registry.translateActiveException(), TestFailureException);

    }

}



TEST_F(ExceptionTranslatorRegistryTest_687, TranslateActiveException_TestSkipException_Rethrow_687) {

    try {

        throw TestSkipException();

        FAIL() << "Expected an exception to be thrown";

    } catch (const TestSkipException& e) {

        EXPECT_THROW(registry.translateActiveException(), TestSkipException);

    }

}

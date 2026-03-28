#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_registrars.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace testing;



class ListenerRegistrarTest : public Test {

protected:

    // Setup and teardown can be done here if needed

};



TEST_F(ListenerRegistrarTest_1084, ConstructorWithEmptyStringRef_1084) {

    StringRef emptyStringRef("");

    EXPECT_NO_THROW({

        ListenerRegistrar<Mock> registrar(emptyStringRef);

    });

}



TEST_F(ListenerRegistrarTest_1084, ConstructorWithNonNullCStr_1084) {

    const char* listenerName = "MyListener";

    EXPECT_NO_THROW({

        ListenerRegistrar<Mock> registrar(StringRef(listenerName));

    });

}



TEST_F(ListenerRegistrarTest_1084, ConstructorWithStringLiteral_1084) {

    EXPECT_NO_THROW({

        ListenerRegistrar<Mock> registrar("LiteralListener");

    });

}



TEST_F(ListenerRegistrarTest_1084, ConstructorWithStdString_1084) {

    std::string listenerName = "StdStringListener";

    EXPECT_NO_THROW({

        ListenerRegistrar<Mock> registrar(StringRef(listenerName));

    });

}

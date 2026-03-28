// TEST_ID: 1084

#include <gtest/gtest.h>
#include <string>

// Headers from the provided partials
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_stringref.hpp"

using Catch::ListenerRegistrar;
using Catch::StringRef;

class ListenerRegistrarTest_1084 : public ::testing::Test { };

// Normal operation: construct with C-string
TEST_F(ListenerRegistrarTest_1084, ConstructWithCString_1084) {
    EXPECT_NO_THROW({
        ListenerRegistrar reg(StringRef("my-listener"));
        (void)reg;
    });
}

// Normal operation: construct with std::string (via StringRef)
TEST_F(ListenerRegistrarTest_1084, ConstructWithStdString_1084) {
    std::string name = "std-string-listener";
    EXPECT_NO_THROW({
        ListenerRegistrar reg(StringRef(name));
        (void)reg;
    });
}

// Boundary: empty listener name
TEST_F(ListenerRegistrarTest_1084, ConstructWithEmptyName_1084) {
    EXPECT_NO_THROW({
        ListenerRegistrar reg(StringRef(""));
        (void)reg;
    });
}

// Special characters / non-ASCII and long name
TEST_F(ListenerRegistrarTest_1084, ConstructWithUnicodeAndLongName_1084) {
    // Mix of Unicode and a long suffix to exercise size handling through the public interface
    std::string longUnicode =
        u8"리스너-테스트-ユニコード-🙂-" + std::string(1024, 'x');
    EXPECT_NO_THROW({
        ListenerRegistrar reg(StringRef(longUnicode));
        (void)reg;
    });
}

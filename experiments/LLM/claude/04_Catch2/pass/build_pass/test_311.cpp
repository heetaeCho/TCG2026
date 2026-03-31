#include <gtest/gtest.h>
#include <stdexcept>

// Based on the provided interface, reconstruct the minimal header needed
namespace Catch {

class GeneratorException : public std::exception {
private:
    const char* const m_msg = "";

public:
    GeneratorException(const char* msg) : m_msg(msg) {}

    const char* what() const noexcept override {
        return m_msg;
    }
};

} // namespace Catch

// Test fixture
class GeneratorExceptionTest_311 : public ::testing::Test {
protected:
};

TEST_F(GeneratorExceptionTest_311, WhatReturnsProvidedMessage_311) {
    const char* msg = "Test error message";
    Catch::GeneratorException ex(msg);
    EXPECT_STREQ(ex.what(), "Test error message");
}

TEST_F(GeneratorExceptionTest_311, WhatReturnsExactPointer_311) {
    const char* msg = "Exact pointer test";
    Catch::GeneratorException ex(msg);
    EXPECT_EQ(ex.what(), msg);
}

TEST_F(GeneratorExceptionTest_311, WhatReturnsEmptyStringForEmptyMessage_311) {
    const char* msg = "";
    Catch::GeneratorException ex(msg);
    EXPECT_STREQ(ex.what(), "");
}

TEST_F(GeneratorExceptionTest_311, WhatIsNoexcept_311) {
    Catch::GeneratorException ex("noexcept test");
    EXPECT_TRUE(noexcept(ex.what()));
}

TEST_F(GeneratorExceptionTest_311, InheritsFromStdException_311) {
    Catch::GeneratorException ex("inheritance test");
    const std::exception& base_ref = ex;
    EXPECT_STREQ(base_ref.what(), "inheritance test");
}

TEST_F(GeneratorExceptionTest_311, CatchAsStdException_311) {
    bool caught = false;
    try {
        throw Catch::GeneratorException("catch test");
    } catch (const std::exception& e) {
        caught = true;
        EXPECT_STREQ(e.what(), "catch test");
    }
    EXPECT_TRUE(caught);
}

TEST_F(GeneratorExceptionTest_311, CatchAsGeneratorException_311) {
    bool caught = false;
    try {
        throw Catch::GeneratorException("specific catch");
    } catch (const Catch::GeneratorException& e) {
        caught = true;
        EXPECT_STREQ(e.what(), "specific catch");
    }
    EXPECT_TRUE(caught);
}

TEST_F(GeneratorExceptionTest_311, WhatWithLongMessage_311) {
    const char* long_msg = "This is a very long error message that contains a lot of detail about what went wrong in the generator. It includes information about the state and context.";
    Catch::GeneratorException ex(long_msg);
    EXPECT_STREQ(ex.what(), long_msg);
}

TEST_F(GeneratorExceptionTest_311, WhatWithSpecialCharacters_311) {
    const char* special_msg = "Error: unexpected value!\n\tDetails: x < 0 && y > 100";
    Catch::GeneratorException ex(special_msg);
    EXPECT_STREQ(ex.what(), special_msg);
}

TEST_F(GeneratorExceptionTest_311, MultipleInstancesIndependent_311) {
    Catch::GeneratorException ex1("first");
    Catch::GeneratorException ex2("second");
    EXPECT_STREQ(ex1.what(), "first");
    EXPECT_STREQ(ex2.what(), "second");
}

TEST_F(GeneratorExceptionTest_311, WhatCalledMultipleTimes_311) {
    Catch::GeneratorException ex("consistent");
    EXPECT_STREQ(ex.what(), "consistent");
    EXPECT_STREQ(ex.what(), "consistent");
    EXPECT_STREQ(ex.what(), "consistent");
}

TEST_F(GeneratorExceptionTest_311, WhatWithSingleCharMessage_311) {
    const char* msg = "X";
    Catch::GeneratorException ex(msg);
    EXPECT_STREQ(ex.what(), "X");
}

TEST_F(GeneratorExceptionTest_311, CopyBehavior_311) {
    Catch::GeneratorException ex1("copy test");
    Catch::GeneratorException ex2(ex1);
    EXPECT_STREQ(ex2.what(), "copy test");
}

TEST_F(GeneratorExceptionTest_311, PolymorphicWhatCall_311) {
    Catch::GeneratorException ex("polymorphic");
    std::exception* ptr = &ex;
    EXPECT_STREQ(ptr->what(), "polymorphic");
}

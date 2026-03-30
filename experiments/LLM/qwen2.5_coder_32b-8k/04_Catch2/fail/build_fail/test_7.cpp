#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <string>



// Assuming Catch::StringRef is in the same namespace as provided

namespace Catch {

class StringRef { 

private:

    const char * m_start = nullptr;

    size_type m_size = 0;



public:  

    constexpr StringRef() noexcept = default;

    constexpr StringRef(char const* rawChars, size_type size) noexcept : m_start(rawChars), m_size(size) {};

    StringRef(std::string const& stdString) noexcept : m_start(stdString.c_str()), m_size(stdString.size()) {};

    StringRef(char const* rawChars) noexcept : StringRef(rawChars, std::strlen(rawChars)) {};



    constexpr auto empty() const noexcept -> bool { return m_size == 0; }

    constexpr auto size() const noexcept -> size_type { return m_size; }

    constexpr StringRef substr(size_type start, size_type length) const noexcept;

    constexpr char const* data() const noexcept { return m_start; }

    explicit operator std::string() const;



    bool operator<(StringRef rhs) const noexcept;

    int compare(StringRef rhs) const;

    auto operator==(StringRef other) const noexcept -> bool;

    auto operator!=(StringRef other) const noexcept -> bool;

    constexpr auto operator[](size_type index) const noexcept -> char;

};

}



using namespace Catch;



// Test Fixture

class StringRefTest_7 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }

};



// Normal operation tests

TEST_F(StringRefTest_7, DefaultConstructorCreatesEmptyString_7) {

    StringRef ref;

    EXPECT_TRUE(ref.empty());

}



TEST_F(StringRefTest_7, CStrConstructorCreatesCorrectStringRef_7) {

    const char* str = "Hello";

    StringRef ref(str);

    EXPECT_EQ(ref.size(), strlen(str));

    EXPECT_STREQ(ref.data(), str);

}



TEST_F(StringRefTest_7, StdStringConstructorCreatesCorrectStringRef_7) {

    std::string str = "World";

    StringRef ref(str);

    EXPECT_EQ(ref.size(), str.size());

    EXPECT_STREQ(ref.data(), str.c_str());

}



// Boundary conditions tests

TEST_F(StringRefTest_7, EmptyCStringCreatesEmptyStringRef_7) {

    const char* str = "";

    StringRef ref(str);

    EXPECT_TRUE(ref.empty());

}



TEST_F(StringRefTest_7, EmptyStdStringCreatesEmptyStringRef_7) {

    std::string str;

    StringRef ref(str);

    EXPECT_TRUE(ref.empty());

}



TEST_F(StringRefTest_7, SubstrFromBeginning_7) {

    const char* str = "Hello";

    StringRef ref(str);

    auto substrRef = ref.substr(0, 2);

    EXPECT_STREQ(substrRef.data(), "He");

}



TEST_F(StringRefTest_7, SubstrFromMiddle_7) {

    const char* str = "Hello";

    StringRef ref(str);

    auto substrRef = ref.substr(1, 3);

    EXPECT_STREQ(substrRef.data(), "ell");

}



TEST_F(StringRefTest_7, SubstrToEnd_7) {

    const char* str = "Hello";

    StringRef ref(str);

    auto substrRef = ref.substr(2);

    EXPECT_STREQ(substrRef.data(), "llo");

}



// Exceptional or error cases tests

// Note: There are no observable exceptions based on the provided interface



// Verification of external interactions (no mocks needed for this class)



TEST_F(StringRefTest_7, OperatorEqualOnSameString_7) {

    StringRef ref1("Hello");

    StringRef ref2("Hello");

    EXPECT_TRUE(ref1 == ref2);

}



TEST_F(StringRefTest_7, OperatorNotEqualOnDifferentStrings_7) {

    StringRef ref1("Hello");

    StringRef ref2("World");

    EXPECT_FALSE(ref1 == ref2);

}



TEST_F(StringRefTest_7, LessThanOperator_7) {

    StringRef ref1("Apple");

    StringRef ref2("Banana");

    EXPECT_TRUE(ref1 < ref2);

}



TEST_F(StringRefTest_7, CompareFunction_7) {

    StringRef ref1("Hello");

    StringRef ref2("World");

    EXPECT_GT(ref2.compare(ref1), 0);

    EXPECT_EQ(ref1.compare(ref1), 0);

}

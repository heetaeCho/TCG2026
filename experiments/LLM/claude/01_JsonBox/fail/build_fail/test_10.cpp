#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <streambuf>
#include <string>
#include <functional>

// Include the header under test
#include "JsonBox/OutputFilter.h"

// A simple inserter functor for testing purposes
struct IdentityInserter {
    typedef char char_type;
    char operator()(char c) const { return c; }
};

struct UpperCaseInserter {
    typedef char char_type;
    char operator()(char c) const {
        if (c >= 'a' && c <= 'z') {
            return c - 'a' + 'A';
        }
        return c;
    }
};

// Test fixture
class OutputFilterTest_10 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Constructor with destination, inserter, and default deleteWhenFinished
TEST_F(OutputFilterTest_10, ConstructorWithDestinationAndInserter_10) {
    std::stringbuf sbuf;
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> filter(&sbuf, inserter);
    
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

// Test: Constructor with destination only (no inserter)
TEST_F(OutputFilterTest_10, ConstructorWithDestinationOnly_10) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<IdentityInserter> filter(&sbuf);
    
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

// Test: getDestination returns correct pointer
TEST_F(OutputFilterTest_10, GetDestinationReturnsCorrectPointer_10) {
    std::stringbuf sbuf1;
    std::stringbuf sbuf2;
    
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> filter1(&sbuf1, inserter);
    JsonBox::OutputFilter<IdentityInserter> filter2(&sbuf2, inserter);
    
    EXPECT_EQ(filter1.getDestination(), &sbuf1);
    EXPECT_EQ(filter2.getDestination(), &sbuf2);
    EXPECT_NE(filter1.getDestination(), filter2.getDestination());
}

// Test: getDestination with nullptr destination
TEST_F(OutputFilterTest_10, GetDestinationWithNullptr_10) {
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> filter(nullptr, inserter);
    
    EXPECT_EQ(filter.getDestination(), nullptr);
}

// Test: getInserter returns a reference to the inserter
TEST_F(OutputFilterTest_10, GetInserterReturnsReference_10) {
    std::stringbuf sbuf;
    UpperCaseInserter inserter;
    JsonBox::OutputFilter<UpperCaseInserter> filter(&sbuf, inserter);
    
    UpperCaseInserter &ref = filter.getInserter();
    // Verify the inserter works correctly
    EXPECT_EQ(ref('a'), 'A');
    EXPECT_EQ(ref('z'), 'Z');
    EXPECT_EQ(ref('A'), 'A');
    EXPECT_EQ(ref('1'), '1');
}

// Test: Constructor with deleteWhenFinished set to true
TEST_F(OutputFilterTest_10, ConstructorWithDeleteWhenFinishedTrue_10) {
    std::stringbuf *sbuf = new std::stringbuf();
    IdentityInserter inserter;
    // When deleteWhenFinished is true, the destructor should delete the destination
    JsonBox::OutputFilter<IdentityInserter> *filter = 
        new JsonBox::OutputFilter<IdentityInserter>(sbuf, inserter, true);
    
    EXPECT_EQ(filter->getDestination(), sbuf);
    
    // Destructor should handle deletion of sbuf
    delete filter;
    // If we get here without crash, the test passes
}

// Test: Constructor with deleteWhenFinished set to false (default)
TEST_F(OutputFilterTest_10, ConstructorWithDeleteWhenFinishedFalse_10) {
    std::stringbuf sbuf;
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> *filter = 
        new JsonBox::OutputFilter<IdentityInserter>(&sbuf, inserter, false);
    
    EXPECT_EQ(filter->getDestination(), &sbuf);
    
    delete filter;
    // sbuf should still be valid on the stack
}

// Test: overflow writes character to destination via inserter
TEST_F(OutputFilterTest_10, OverflowWritesToDestination_10) {
    std::stringbuf sbuf;
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> filter(&sbuf, inserter);
    
    auto result = filter.overflow('H');
    // The character should have been written (not EOF)
    EXPECT_NE(result, std::char_traits<char>::eof());
}

// Test: overflow with EOF returns EOF
TEST_F(OutputFilterTest_10, OverflowWithEOF_10) {
    std::stringbuf sbuf;
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> filter(&sbuf, inserter);
    
    auto result = filter.overflow(std::char_traits<char>::eof());
    // Typically, passing EOF to overflow should return EOF or not_eof
    // We just verify it doesn't crash; exact behavior depends on implementation
    (void)result;
}

// Test: underflow behavior (should return EOF as this is an output filter)
TEST_F(OutputFilterTest_10, UnderflowReturnsEOF_10) {
    std::stringbuf sbuf;
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> filter(&sbuf, inserter);
    
    auto result = filter.underflow();
    EXPECT_EQ(result, std::char_traits<char>::eof());
}

// Test: Multiple overflows write all characters
TEST_F(OutputFilterTest_10, MultipleOverflowsWriteAllCharacters_10) {
    std::stringbuf sbuf;
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> filter(&sbuf, inserter);
    
    std::string testStr = "Hello";
    for (char c : testStr) {
        auto result = filter.overflow(c);
        EXPECT_NE(result, std::char_traits<char>::eof());
    }
    
    // Verify what was written to the destination
    std::string output = sbuf.str();
    EXPECT_EQ(output.length(), testStr.length());
}

// Test: OutputFilter with UpperCaseInserter transforms characters
TEST_F(OutputFilterTest_10, OverflowWithUpperCaseInserterTransforms_10) {
    std::stringbuf sbuf;
    UpperCaseInserter inserter;
    JsonBox::OutputFilter<UpperCaseInserter> filter(&sbuf, inserter);
    
    filter.overflow('h');
    filter.overflow('i');
    
    std::string output = sbuf.str();
    // The inserter should transform 'h' to 'H' and 'i' to 'I'
    EXPECT_EQ(output, "HI");
}

// Test: OutputFilter is a streambuf
TEST_F(OutputFilterTest_10, IsStreambuf_10) {
    std::stringbuf sbuf;
    IdentityInserter inserter;
    JsonBox::OutputFilter<IdentityInserter> filter(&sbuf, inserter);
    
    // Verify it can be used as a std::streambuf pointer
    std::streambuf *base = &filter;
    EXPECT_NE(base, nullptr);
}

// Test: Two-argument constructor with deleteWhenFinished
TEST_F(OutputFilterTest_10, TwoArgConstructorWithDeleteWhenFinished_10) {
    std::stringbuf *sbuf = new std::stringbuf();
    JsonBox::OutputFilter<IdentityInserter> *filter = 
        new JsonBox::OutputFilter<IdentityInserter>(sbuf, true);
    
    EXPECT_EQ(filter->getDestination(), sbuf);
    
    // Destructor should handle deletion
    delete filter;
}

// Test: Two-argument constructor with default deleteWhenFinished (false)
TEST_F(OutputFilterTest_10, TwoArgConstructorDefaultDeleteFalse_10) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<IdentityInserter> filter(&sbuf, false);
    
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

// Test: getDestination is const-correct
TEST_F(OutputFilterTest_10, GetDestinationConstCorrectness_10) {
    std::stringbuf sbuf;
    IdentityInserter inserter;
    const JsonBox::OutputFilter<IdentityInserter> filter(&sbuf, inserter);
    
    // getDestination should be callable on const object
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

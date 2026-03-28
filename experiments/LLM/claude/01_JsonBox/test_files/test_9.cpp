#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <streambuf>
#include <string>
#include <functional>

// Include the actual header
#include "JsonBox/OutputFilter.h"

// A simple inserter functor for testing purposes
struct TestInserter {
    int callCount = 0;
    
    std::streambuf::int_type operator()(std::streambuf *destination, std::streambuf::int_type ch) {
        callCount++;
        if (destination && ch != std::streambuf::traits_type::eof()) {
            return destination->sputc(static_cast<char>(ch));
        }
        return ch;
    }
};

// An inserter that transforms characters (e.g., uppercase)
struct UpperCaseInserter {
    std::streambuf::int_type operator()(std::streambuf *destination, std::streambuf::int_type ch) {
        if (destination && ch != std::streambuf::traits_type::eof()) {
            char c = static_cast<char>(ch);
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';
            }
            return destination->sputc(c);
        }
        return ch;
    }
};

// A pass-through inserter
struct PassThroughInserter {
    std::streambuf::int_type operator()(std::streambuf *destination, std::streambuf::int_type ch) {
        if (destination && ch != std::streambuf::traits_type::eof()) {
            return destination->sputc(static_cast<char>(ch));
        }
        return ch;
    }
};

// Default constructible inserter
struct DefaultInserter {
    int value = 42;
    std::streambuf::int_type operator()(std::streambuf *destination, std::streambuf::int_type ch) {
        if (destination && ch != std::streambuf::traits_type::eof()) {
            return destination->sputc(static_cast<char>(ch));
        }
        return ch;
    }
};

class OutputFilterTest_9 : public ::testing::Test {
protected:
    std::stringbuf destBuffer;
};

// Test: Constructor with destination and inserter
TEST_F(OutputFilterTest_9, ConstructorWithInserter_9) {
    TestInserter inserter;
    JsonBox::OutputFilter<TestInserter> filter(&destBuffer, inserter);
    
    // Should not crash and destination should be accessible
    EXPECT_EQ(filter.getDestination(), &destBuffer);
}

// Test: Constructor with destination only (default inserter)
TEST_F(OutputFilterTest_9, ConstructorWithoutInserter_9) {
    JsonBox::OutputFilter<DefaultInserter> filter(&destBuffer);
    
    EXPECT_EQ(filter.getDestination(), &destBuffer);
}

// Test: Constructor with deleteWhenFinished set to false
TEST_F(OutputFilterTest_9, ConstructorDeleteWhenFinishedFalse_9) {
    TestInserter inserter;
    JsonBox::OutputFilter<TestInserter> filter(&destBuffer, inserter, false);
    
    EXPECT_EQ(filter.getDestination(), &destBuffer);
}

// Test: Constructor with deleteWhenFinished set to true (uses heap-allocated buffer)
TEST_F(OutputFilterTest_9, ConstructorDeleteWhenFinishedTrue_9) {
    std::stringbuf *heapBuffer = new std::stringbuf();
    TestInserter inserter;
    // When deleteWhenFinished is true, the filter should delete the destination in destructor
    JsonBox::OutputFilter<TestInserter> *filter = new JsonBox::OutputFilter<TestInserter>(heapBuffer, inserter, true);
    
    EXPECT_EQ(filter->getDestination(), heapBuffer);
    
    // Destructor should delete heapBuffer; no crash expected
    delete filter;
}

// Test: getDestination returns correct destination
TEST_F(OutputFilterTest_9, GetDestinationReturnsCorrectPointer_9) {
    TestInserter inserter;
    JsonBox::OutputFilter<TestInserter> filter(&destBuffer, inserter);
    
    const std::streambuf *dest = filter.getDestination();
    EXPECT_EQ(dest, &destBuffer);
}

// Test: getInserter returns a reference to the inserter
TEST_F(OutputFilterTest_9, GetInserterReturnsReference_9) {
    TestInserter inserter;
    inserter.callCount = 5;
    JsonBox::OutputFilter<TestInserter> filter(&destBuffer, inserter);
    
    TestInserter &ref = filter.getInserter();
    // The inserter should have been copied, so we check it's accessible
    // (The initial callCount may or may not be 5 depending on copy semantics, 
    //  but we can verify the reference is valid)
    EXPECT_GE(ref.callCount, 0);
}

// Test: getInserter returns modifiable reference
TEST_F(OutputFilterTest_9, GetInserterIsModifiable_9) {
    DefaultInserter inserter;
    inserter.value = 100;
    JsonBox::OutputFilter<DefaultInserter> filter(&destBuffer, inserter);
    
    DefaultInserter &ref = filter.getInserter();
    ref.value = 200;
    
    EXPECT_EQ(filter.getInserter().value, 200);
}

// Test: overflow writes character through inserter to destination
TEST_F(OutputFilterTest_9, OverflowWritesCharacter_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    auto result = filter.overflow('A');
    
    EXPECT_NE(result, std::streambuf::traits_type::eof());
    EXPECT_EQ(destBuffer.str(), "A");
}

// Test: overflow with multiple characters
TEST_F(OutputFilterTest_9, OverflowMultipleCharacters_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    filter.overflow('H');
    filter.overflow('i');
    filter.overflow('!');
    
    EXPECT_EQ(destBuffer.str(), "Hi!");
}

// Test: overflow with EOF character
TEST_F(OutputFilterTest_9, OverflowWithEOF_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    auto result = filter.overflow(std::streambuf::traits_type::eof());
    
    // EOF handling - the destination should remain unchanged
    EXPECT_EQ(destBuffer.str(), "");
}

// Test: underflow returns EOF (since this is an output filter)
TEST_F(OutputFilterTest_9, UnderflowReturnsEOF_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    auto result = filter.underflow();
    
    EXPECT_EQ(result, std::streambuf::traits_type::eof());
}

// Test: Using OutputFilter with ostream
TEST_F(OutputFilterTest_9, UseWithOstream_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    std::ostream os(&filter);
    os << "Hello";
    os.flush();
    
    EXPECT_EQ(destBuffer.str(), "Hello");
}

// Test: UpperCase inserter transforms characters
TEST_F(OutputFilterTest_9, UpperCaseInserterTransforms_9) {
    UpperCaseInserter inserter;
    JsonBox::OutputFilter<UpperCaseInserter> filter(&destBuffer, inserter);
    
    std::ostream os(&filter);
    os << "hello";
    os.flush();
    
    EXPECT_EQ(destBuffer.str(), "HELLO");
}

// Test: overflow with special characters
TEST_F(OutputFilterTest_9, OverflowWithSpecialCharacters_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    filter.overflow('\n');
    filter.overflow('\t');
    filter.overflow(' ');
    
    EXPECT_EQ(destBuffer.str(), "\n\t ");
}

// Test: overflow with null character
TEST_F(OutputFilterTest_9, OverflowWithNullChar_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    auto result = filter.overflow('\0');
    
    EXPECT_NE(result, std::streambuf::traits_type::eof());
    std::string expected(1, '\0');
    EXPECT_EQ(destBuffer.str(), expected);
}

// Test: Constructor with two-argument form and deleteWhenFinished
TEST_F(OutputFilterTest_9, TwoArgConstructorWithDelete_9) {
    std::stringbuf *heapBuffer = new std::stringbuf();
    JsonBox::OutputFilter<DefaultInserter> *filter = new JsonBox::OutputFilter<DefaultInserter>(heapBuffer, true);
    
    EXPECT_EQ(filter->getDestination(), heapBuffer);
    
    // Should safely delete heapBuffer
    delete filter;
}

// Test: Two-argument constructor default deleteWhenFinished is false
TEST_F(OutputFilterTest_9, TwoArgConstructorDefaultDelete_9) {
    JsonBox::OutputFilter<DefaultInserter> filter(&destBuffer);
    
    EXPECT_EQ(filter.getDestination(), &destBuffer);
    // Destructor should NOT delete destBuffer (stack allocated)
}

// Test: Empty string through ostream
TEST_F(OutputFilterTest_9, EmptyStringThroughOstream_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    std::ostream os(&filter);
    os << "";
    os.flush();
    
    EXPECT_EQ(destBuffer.str(), "");
}

// Test: Large output through filter
TEST_F(OutputFilterTest_9, LargeOutputThroughFilter_9) {
    PassThroughInserter inserter;
    JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    std::ostream os(&filter);
    std::string largeStr(10000, 'X');
    os << largeStr;
    os.flush();
    
    EXPECT_EQ(destBuffer.str(), largeStr);
}

// Test: getDestination is const-correct
TEST_F(OutputFilterTest_9, GetDestinationConstCorrectness_9) {
    PassThroughInserter inserter;
    const JsonBox::OutputFilter<PassThroughInserter> filter(&destBuffer, inserter);
    
    // getDestination is const, should work on const object
    const std::streambuf *dest = filter.getDestination();
    EXPECT_EQ(dest, &destBuffer);
}

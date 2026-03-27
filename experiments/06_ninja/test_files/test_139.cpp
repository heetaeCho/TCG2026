#include <gtest/gtest.h>

#include <string>



using namespace std;



// Assuming StringNeedsWin32Escaping is part of a class or namespace

// For this example, we'll assume it's in a namespace called 'util'

namespace util {

    static inline bool StringNeedsWin32Escaping(const string& input) { 

        for (size_t i = 0; i < input.size(); ++i) { 

            if (!IsKnownWin32SafeCharacter(input[i])) return true; 

        } 

        return false; 

    }

}



// Mock function to simulate IsKnownWin32SafeCharacter

bool IsKnownWin32SafeCharacter(char c);



class StringNeedsWin32EscapingTest_139 : public ::testing::Test {

protected:

    // Setup and teardown can be used if needed in the future

};



TEST_F(StringNeedsWin32EscapingTest_139, EmptyStringDoesNotNeedEscaping_139) {

    EXPECT_FALSE(util::StringNeedsWin32Escaping(""));

}



TEST_F(StringNeedsWin32EscapingTest_139, SafeCharactersDoNotNeedEscaping_139) {

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('a')).WillOnce(::testing::Return(true));

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('b')).WillOnce(::testing::Return(true));

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('c')).WillOnce(::testing::Return(true));



    EXPECT_FALSE(util::StringNeedsWin32Escaping("abc"));

}



TEST_F(StringNeedsWin32EscapingTest_139, UnsafeCharacterNeedsEscaping_139) {

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('a')).WillOnce(::testing::Return(true));

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('<')).WillOnce(::testing::Return(false));



    EXPECT_TRUE(util::StringNeedsWin32Escaping("a<"));

}



TEST_F(StringNeedsWin32EscapingTest_139, AllUnsafeCharactersNeedEscaping_139) {

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('<')).WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('>')).WillOnce(::testing::Return(false));



    EXPECT_TRUE(util::StringNeedsWin32Escaping("<>"));

}



TEST_F(StringNeedsWin32EscapingTest_139, MixedCharactersWithUnsafeNeedEscaping_139) {

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('a')).WillOnce(::testing::Return(true));

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('<')).WillOnce(::testing::Return(false));



    EXPECT_TRUE(util::StringNeedsWin32Escaping("a<"));

}



TEST_F(StringNeedsWin32EscapingTest_139, LongStringWithSingleUnsafeCharacterNeedsEscaping_139) {

    string longSafeString(1000, 'a');

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('a')).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(::testing::MockFunction<bool(char)>(), Call('<')).WillOnce(::testing::Return(false));



    EXPECT_TRUE(util::StringNeedsWin32Escaping(longSafeString + "<"));

}

```



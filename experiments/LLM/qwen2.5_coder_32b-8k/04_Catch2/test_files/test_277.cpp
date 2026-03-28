#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



namespace Catch {

    template <> struct StringMaker<unsigned char> {

        public: static std::string convert(unsigned char value);

    };

}



TEST(StringMakerUnsignedCharTests_277, ConvertNormalValue_277) {

    unsigned char normal_value = 'A';

    EXPECT_EQ(Catch::StringMaker<unsigned char>::convert(normal_value), "A");

}



TEST(StringMakerUnsignedCharTests_277, ConvertNullCharacter_277) {

    unsigned char null_char = '\0';

    EXPECT_EQ(Catch::StringMaker<unsigned char>::convert(null_char), "\0");

}



TEST(StringMakerUnsignedCharTests_277, ConvertMaxValue_277) {

    unsigned char max_value = std::numeric_limits<unsigned char>::max();

    EXPECT_EQ(Catch::StringMaker<unsigned char>::convert(max_value), "\xFF");

}

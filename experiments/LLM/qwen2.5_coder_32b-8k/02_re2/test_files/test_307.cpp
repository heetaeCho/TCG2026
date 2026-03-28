#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/compile.h"

#include "re2/prog.h"



namespace re2 {



class CompilerTest_307 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_307, IsCachedRuneByteSuffix_Cached_ReturnsTrue_307) {

    // Arrange

    int id = 1;

    uint8_t lo = 97; // 'a'

    uint8_t hi = 97; // 'a'

    bool foldcase = false;

    int next = 2;

    uint64_t key = compiler.MakeRuneCacheKey(lo, hi, foldcase, next);

    compiler.rune_cache_.insert({key, id});



    // Act

    bool result = compiler.IsCachedRuneByteSuffix(id);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(CompilerTest_307, IsCachedRuneByteSuffix_NotCached_ReturnsFalse_307) {

    // Arrange

    int id = 1;



    // Act

    bool result = compiler.IsCachedRuneByteSuffix(id);



    // Assert

    EXPECT_FALSE(result);

}



TEST_F(CompilerTest_307, IsCachedRuneByteSuffix_IdOutOfRange_ReturnsFalse_307) {

    // Arrange

    int id = -1; // Out of range ID



    // Act & Assert

    EXPECT_FALSE(compiler.IsCachedRuneByteSuffix(id));

}



TEST_F(CompilerTest_307, IsCachedRuneByteSuffix_EmptyCache_ReturnsFalse_307) {

    // Arrange

    int id = 1;



    // Act

    bool result = compiler.IsCachedRuneByteSuffix(id);



    // Assert

    EXPECT_FALSE(result);

}



}  // namespace re2

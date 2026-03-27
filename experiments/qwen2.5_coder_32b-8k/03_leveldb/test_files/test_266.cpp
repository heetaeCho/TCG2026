#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/options.h"



class LevelDBOptionsTest_266 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_options_create();

    }



    void TearDown() override {

        leveldb_options_destroy(options);

    }



    leveldb_options_t* options;

};



TEST_F(LevelDBOptionsTest_266, SetCompressionDefault_266) {

    // Test setting compression to default value

    leveldb_options_set_compression(options, kSnappyCompression);

    EXPECT_EQ(options->rep.compression, static_cast<CompressionType>(kSnappyCompression));

}



TEST_F(LevelDBOptionsTest_266, SetCompressionNoCompression_266) {

    // Test setting compression to no compression

    leveldb_options_set_compression(options, kNoCompression);

    EXPECT_EQ(options->rep.compression, static_cast<CompressionType>(kNoCompression));

}



TEST_F(LevelDBOptionsTest_266, SetCompressionZlibCompression_266) {

    // Test setting compression to zlib compression

    leveldb_options_set_compression(options, kZlibCompression);

    EXPECT_EQ(options->rep.compression, static_cast<CompressionType>(kZlibCompression));

}



TEST_F(LevelDBOptionsTest_266, SetCompressionBzip2Compression_266) {

    // Test setting compression to bzip2 compression

    leveldb_options_set_compression(options, kBzip2Compression);

    EXPECT_EQ(options->rep.compression, static_cast<CompressionType>(kBzip2Compression));

}



TEST_F(LevelDBOptionsTest_266, SetCompressionLZ4Compression_266) {

    // Test setting compression to lz4 compression

    leveldb_options_set_compression(options, kLZ4Compression);

    EXPECT_EQ(options->rep.compression, static_cast<CompressionType>(kLZ4Compression));

}



TEST_F(LevelDBOptionsTest_266, SetCompressionLZ4HCCompression_266) {

    // Test setting compression to lz4hc compression

    leveldb_options_set_compression(options, kLZ4HCCompression);

    EXPECT_EQ(options->rep.compression, static_cast<CompressionType>(kLZ4HCCompression));

}



TEST_F(LevelDBOptionsTest_266, SetCompressionXpressCompression_266) {

    // Test setting compression to xpress compression

    leveldb_options_set_compression(options, kXpressCompression);

    EXPECT_EQ(options->rep.compression, static_cast<CompressionType>(kXpressCompression));

}



TEST_F(LevelDBOptionsTest_266, SetCompressionZSTDCompression_266) {

    // Test setting compression to zstd compression

    leveldb_options_set_compression(options, kZSTD);

    EXPECT_EQ(options->rep.compression, static_cast<CompressionType>(kZSTD));

}



TEST_F(LevelDBOptionsTest_266, SetCompressionInvalidValue_266) {

    // Test setting compression to an invalid value

    leveldb_options_set_compression(options, 999);

    EXPECT_NE(options->rep.compression, static_cast<CompressionType>(999));

}

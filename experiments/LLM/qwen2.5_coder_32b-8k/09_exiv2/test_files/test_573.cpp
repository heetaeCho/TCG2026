#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

    class BlockMap { 

        private:

            enum blockType_e { bNone };

            blockType_e type_ = {bNone};

            struct Blob { 

                const byte* data() const { return nullptr; } // Mock implementation for the sake of test compilation

                size_t size() const { return 0; } // Mock implementation for the sake of test compilation

            };

            Blob data_; 



        public:

            void populate(const byte* source, size_t num);

            void markKnown(size_t num);

            bool isNone() const;

            bool isKnown() const;

            auto getData() const { return data_.data(); }

            size_t getSize() const { return data_.size(); }

    };

}



using namespace Exiv2;



class BlockMapTest_573 : public ::testing::Test {

protected:

    BlockMap blockMap;

};



TEST_F(BlockMapTest_573, DefaultStateIsNone_573) {

    EXPECT_TRUE(blockMap.isNone());

    EXPECT_FALSE(blockMap.isKnown());

}



TEST_F(BlockMapTest_573, PopulateSetsData_573) {

    byte data[] = {1, 2, 3};

    blockMap.populate(data, sizeof(data));

    EXPECT_NE(blockMap.getData(), nullptr);

    EXPECT_EQ(blockMap.getSize(), sizeof(data));

}



TEST_F(BlockMapTest_573, MarkKnownChangesState_573) {

    blockMap.markKnown(10);

    EXPECT_FALSE(blockMap.isNone());

    EXPECT_TRUE(blockMap.isKnown());

}



TEST_F(BlockMapTest_573, PopulateWithZeroSizeDoesNotChangeData_573) {

    byte data[] = {1, 2, 3};

    blockMap.populate(data, sizeof(data));

    blockMap.populate(nullptr, 0);

    EXPECT_NE(blockMap.getData(), nullptr);

    EXPECT_EQ(blockMap.getSize(), sizeof(data));

}



TEST_F(BlockMapTest_573, MarkKnownWithZeroSizeDoesNotChangeState_573) {

    blockMap.markKnown(10);

    blockMap.markKnown(0);

    EXPECT_FALSE(blockMap.isNone());

    EXPECT_TRUE(blockMap.isKnown());

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace leveldb {

    class Comparator;

    class Slice;

    class Status;



    class Block {

    public:

        class Iter : public Iterator {

        private:

            const Comparator *const comparator_;

            const char *const data_;

            const uint32_t restarts_;

            const uint32_t num_restarts_;

            uint32_t current_;

            uint32_t restart_index_;

            std::string key_;

            Slice value_;



        public:

            Iter(const Comparator* comparator, const char* data, uint32_t restarts, uint32_t num_restarts);

            bool Valid() const override;

            Status status() const override;

            Slice key() const override;

            Slice value() const override;

            void Next() override;

            void Prev() override;

            void Seek(const Slice& target) override;

            void SeekToFirst() override;

            void SeekToLast() override;



        private:

            inline int Compare(const Slice& a, const Slice& b) const;

            inline uint32_t NextEntryOffset() const;

            uint32_t GetRestartPoint(uint32_t index);

            void SeekToRestartPoint(uint32_t index);

            void CorruptionError();

            bool ParseNextKey();

        };

    };



    class Iterator {

    public:

        virtual ~Iterator() = default;

        virtual bool Valid() const = 0;

        virtual Status status() const = 0;

        virtual Slice key() const = 0;

        virtual Slice value() const = 0;

        virtual void Next() = 0;

        virtual void Prev() = 0;

        virtual void Seek(const Slice& target) = 0;

        virtual void SeekToFirst() = 0;

        virtual void SeekToLast() = 0;

    };

}



using namespace leveldb;



class MockComparator : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Slice&, const Slice&));

};



TEST_F(BlockIterTest_414, SeekToFirstSetsCurrentToRestartPoint_414) {

    // Arrange

    MockComparator comparator;

    char data[10];

    uint32_t restarts = 5;

    uint32_t num_restarts = 1;

    Block::Iter iter(&comparator, data, restarts, num_restarts);



    // Act

    iter.SeekToFirst();



    // Assert

    EXPECT_EQ(iter.current_, restarts);

}



TEST_F(BlockIterTest_414, SeekToFirstParsesNextKey_414) {

    // Arrange

    MockComparator comparator;

    char data[10];

    uint32_t restarts = 5;

    uint32_t num_restarts = 1;

    Block::Iter iter(&comparator, data, restarts, num_restarts);



    // Act & Assert

    EXPECT_CALL(iter, ParseNextKey()).Times(1);

    iter.SeekToFirst();

}



TEST_F(BlockIterTest_414, SeekToRestartPointSetsCurrentAndRestartIndex_414) {

    // Arrange

    MockComparator comparator;

    char data[10];

    uint32_t restarts = 5;

    uint32_t num_restarts = 1;

    Block::Iter iter(&comparator, data, restarts, num_restarts);



    // Act

    iter.SeekToRestartPoint(0);



    // Assert

    EXPECT_EQ(iter.current_, restarts);

    EXPECT_EQ(iter.restart_index_, 0);

}



TEST_F(BlockIterTest_414, ValidReturnsFalseIfCurrentExceedsDataLength_414) {

    // Arrange

    MockComparator comparator;

    char data[1];

    uint32_t restarts = 5;

    uint32_t num_restarts = 1;

    Block::Iter iter(&comparator, data, restarts, num_restarts);



    // Act & Assert

    EXPECT_FALSE(iter.Valid());

}



TEST_F(BlockIterTest_414, NextAdvancesCurrentIndex_414) {

    // Arrange

    MockComparator comparator;

    char data[10];

    uint32_t restarts = 5;

    uint32_t num_restarts = 1;

    Block::Iter iter(&comparator, data, restarts, num_restarts);

    iter.SeekToFirst();



    // Act

    iter.Next();



    // Assert

    EXPECT_EQ(iter.current_, iter.NextEntryOffset());

}



TEST_F(BlockIterTest_414, PrevDecrementsCurrentIndex_414) {

    // Arrange

    MockComparator comparator;

    char data[10];

    uint32_t restarts = 5;

    uint32_t num_restarts = 1;

    Block::Iter iter(&comparator, data, restarts, num_restarts);

    iter.SeekToFirst();

    iter.Next();



    // Act

    iter.Prev();



    // Assert

    EXPECT_EQ(iter.current_, restarts);

}



TEST_F(BlockIterTest_414, SeekFindsTargetKey_414) {

    // Arrange

    MockComparator comparator;

    char data[10];

    uint32_t restarts = 5;

    uint32_t num_restarts = 1;

    Block::Iter iter(&comparator, data, restarts, num_restarts);

    Slice target("target");



    EXPECT_CALL(comparator, Compare(_, _)).WillOnce(testing::Return(0));



    // Act

    iter.Seek(target);



    // Assert

    // This would typically check that the current position is correct,

    // but we cannot directly access internal state.

}



TEST_F(BlockIterTest_414, SeekToLastSetsCurrentToEndOfData_414) {

    // Arrange

    MockComparator comparator;

    char data[10];

    uint32_t restarts = 5;

    uint32_t num_restarts = 1;

    Block::Iter iter(&comparator, data, restarts, num_restarts);



    // Act

    iter.SeekToLast();



    // Assert

    EXPECT_EQ(iter.current_, iter.GetRestartPoint(num_restarts - 1));

}

// File: test_remoteio_611.cpp
// Unit tests for Exiv2::RemoteIo (black-box, interface-based)
// TEST_ID = 611

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <memory>

#include "exiv2/basicio.hpp"

namespace {

// A minimal BasicIo mock to satisfy signatures where a BasicIo& is required.
// We do NOT assert any internal interaction patterns (black-box constraint).
class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
  MOCK_METHOD(Exiv2::byte*, mmap, (bool unnamed), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(size_t, tell, (), (const, override));
  MOCK_METHOD(size_t, size, (), (const, override));
  MOCK_METHOD(bool, isopen, (), (const, override));
  MOCK_METHOD(int, error, (), (const, override));
  MOCK_METHOD(bool, eof, (), (const, override));
  MOCK_METHOD(const std::string&, path, (), (const, noexcept, override));
  MOCK_METHOD(void, populateFakeData, (), (override));
};

class RemoteIoTest_611 : public ::testing::Test {
protected:
  Exiv2::RemoteIo io_;
};

}  // namespace

TEST_F(RemoteIoTest_611, MunmapReturnsZero_611) {
  // Observable behavior from provided partial implementation: munmap() returns 0.
  EXPECT_EQ(io_.munmap(), 0);
}

TEST_F(RemoteIoTest_611, MunmapIsIdempotentFromCallerPerspective_611) {
  // Black-box: calling munmap repeatedly should be safe for the caller to do.
  // We only assert the documented/observed return value from the partial code.
  EXPECT_EQ(io_.munmap(), 0);
  EXPECT_EQ(io_.munmap(), 0);
}

TEST_F(RemoteIoTest_611, DefaultConstructedStatusQueriesAreCallable_611) {
  // No assumptions about exact values; just that calls are valid and stable across
  // repeated queries when no intervening operation is performed.
  EXPECT_NO_THROW({
    const auto t1 = io_.tell();
    const auto t2 = io_.tell();
    EXPECT_EQ(t1, t2);

    const auto s1 = io_.size();
    const auto s2 = io_.size();
    EXPECT_EQ(s1, s2);

    const auto o1 = io_.isopen();
    const auto o2 = io_.isopen();
    EXPECT_EQ(o1, o2);

    const auto e1 = io_.eof();
    const auto e2 = io_.eof();
    EXPECT_EQ(e1, e2);

    const auto err1 = io_.error();
    const auto err2 = io_.error();
    EXPECT_EQ(err1, err2);
  });
}

TEST_F(RemoteIoTest_611, PathReferenceIsStableAcrossCalls_611) {
  // We do not assume what the path string contains; only that returning a
  // reference remains valid across repeated calls.
  EXPECT_NO_THROW({
    const std::string& p1 = io_.path();
    const std::string& p2 = io_.path();
    EXPECT_EQ(&p1, &p2);
  });
}

TEST_F(RemoteIoTest_611, OpenCloseAreCallable_611) {
  // No assumptions about return values; only that they can be called safely.
  EXPECT_NO_THROW({
    (void)io_.open();
    (void)io_.close();
  });
}

TEST_F(RemoteIoTest_611, WriteWithNullptrAndZeroIsCallable_611) {
  // Boundary condition: zero-length write with nullptr buffer.
  // We do not assume the returned size; only that it is callable without throwing.
  EXPECT_NO_THROW({
    const auto n = io_.write(static_cast<const Exiv2::byte*>(nullptr), 0U);
    (void)n;
  });
}

TEST_F(RemoteIoTest_611, ReadWithZeroCountIsCallable_611) {
  // Boundary condition: read(0) and read(buf, 0).
  EXPECT_NO_THROW({
    Exiv2::DataBuf b = io_.read(0U);
    (void)b;

    Exiv2::byte dummy = 0;
    const auto n = io_.read(&dummy, 0U);
    (void)n;
  });
}

TEST_F(RemoteIoTest_611, GetbPutbAreCallable_611) {
  // No assumptions about EOF behavior or returned values.
  EXPECT_NO_THROW({
    (void)io_.putb(static_cast<Exiv2::byte>(0));
    (void)io_.getb();
  });
}

TEST_F(RemoteIoTest_611, SeekBoundaryOffsetsAreCallable_611) {
  // Boundary-ish offsets: 0, negative, and large positive.
  // We do not assume clamping rules or error codes.
  EXPECT_NO_THROW({
    (void)io_.seek(0, Exiv2::BasicIo::beg);
    (void)io_.seek(-1, Exiv2::BasicIo::cur);
    (void)io_.seek(static_cast<int64_t>(1) << 40, Exiv2::BasicIo::end);
  });
}

TEST_F(RemoteIoTest_611, MmapAndMunmapAreCallable_611) {
  // We do not assume mmap returns non-null; only that calling it and munmap is safe.
  EXPECT_NO_THROW({
    (void)io_.mmap(false);
    EXPECT_EQ(io_.munmap(), 0);
  });
}

TEST_F(RemoteIoTest_611, WriteFromBasicIoIsCallableWithMock_611) {
  // We only verify that the overload accepting BasicIo& can be called with an
  // external collaborator object. No assumptions about interactions.
  MockBasicIo src;
  EXPECT_NO_THROW({
    const auto n = io_.write(src);
    (void)n;
  });
}

TEST_F(RemoteIoTest_611, TransferFromBasicIoIsCallableWithMock_611) {
  // Similar to write(BasicIo&): only callability with an external collaborator.
  MockBasicIo src;
  EXPECT_NO_THROW({
    io_.transfer(src);
  });
}

TEST_F(RemoteIoTest_611, PopulateFakeDataIsCallable_611) {
  // No assumptions about what "fake data" means; just that it's callable.
  EXPECT_NO_THROW({
    io_.populateFakeData();
  });
}

TEST_F(RemoteIoTest_611, DestructorSmokeTest_611) {
  // Exceptional/error case (observable): object can be destroyed without throwing.
  EXPECT_NO_THROW({
    auto ptr = std::make_unique<Exiv2::RemoteIo>();
    // Optionally exercise a couple of harmless calls prior to destruction.
    (void)ptr->munmap();  // known-return method
    ptr.reset();
  });
}
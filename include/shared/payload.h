#pragma once

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>
#include <wasm.h>

class Payload {
public:
    Payload() : start_(nullptr), end_(nullptr), ptr_(nullptr), size_(0) {}
    Payload(const char *start, size_t size) : start_((char *)start), end_((char *)start + size), ptr_(start), size_(size) {}

    // Copy
    Payload(const Payload &payload) : start_(payload.start_), end_(payload.end_), ptr_(payload.ptr_), size_(payload.size_) {}

    // Move
    Payload(Payload &&payload) noexcept
    : start_(std::exchange(payload.start_, nullptr)), end_(std::exchange(payload.end_, nullptr)),
    ptr_(std::exchange(payload.ptr_, nullptr)), size_(std::exchange(payload.size_, 0)) {}

    // Move/Copy Assign
    Payload&operator=(Payload payload) noexcept {
        std::swap(start_, payload.start_);
        std::swap(end_, payload.end_);
        std::swap(ptr_, payload.ptr_);
        std::swap(size_, payload.size_);

        return *this;
    }

    // Overloaded (de)serialisation functions
//    template <typename Packer>
//    void msgpack_pack(Packer& pk) const {
//        pk.pack_bin(size_);
//        pk.pack_bin_body(start_, size_);
//    }
//
//    void msgpack_unpack(clmdep_msgpack::object const& o) {
//        start_ = o.via.bin.ptr;
//        ptr_ = start_;
//
//        size_ = o.via.bin.size;
//        end_ = start_ + size_;
//    }

    void reset() { ptr_ = start_; }
    bool eob() const { return ptr_ >= end_; }
    const char *at() const { return ptr_; }

    const char *data_start() const { return start_; }
    const char *data_end() const { return end_; }
    size_t size() const { return size_; }

    char peek() const { return *ptr_; }
    char consume() { return *ptr_++; }
    void skip(unsigned int length) { ptr_ += length; }

    unsigned char read_u8() { return consume(); }

    // Read one number encoded in unsigned little endian base
    template <typename T = unsigned int> T read_uleb128(enum VaruintN limit) {
        T result = 0;
        T shift = 0;
        T length = 0;

        while (true) {
            char c = consume();

            // Ignore the msb using & 0x7f
            result |= (c & 0x7f) << shift;
            shift += 7;
            length += 7;

            // If the msb is clear, we have read the last byte
            if (!(c & 0x80) || length >= limit) { // The limit is at most ceil(limit / 7) bytes
                break;
            }
        }

        return result;
    }

    // The parameter "limit" refers to the maximum length of the
    // LEB128 variable-length integer "size" (e.g. 1, 7 or 32 bits),
    // which in turn, defines the length of the name string itself
    std::string read_name(enum VaruintN limit) {
        unsigned int size = read_uleb128(limit);

        char buffer[size + 1];
        for (unsigned int i = 0; i < size; i++) {
            buffer[i] = consume();
        }
        buffer[size] = 0;

        return std::string(buffer);
    }

private:
    const char *start_, *end_;
    const char *ptr_;
    size_t size_;
};
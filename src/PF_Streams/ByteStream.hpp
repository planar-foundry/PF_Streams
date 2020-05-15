#pragma once

#include <PF_Streams/Detail/Export.hpp>

#include <cstddef>
#include <stdint.h>
#include <utility>

namespace pf::streams
{

class ByteStream
{
public:
    enum class Mode
    {
        Read,
        Write
    };

    PFSTREAMS_API ByteStream(Mode mode, std::byte* buff, int len);

    PFSTREAMS_API Mode mode() const;
    PFSTREAMS_API std::byte* buffer() const;
    PFSTREAMS_API int len() const;
    PFSTREAMS_API int len_remaining() const;
    PFSTREAMS_API int head() const;
    PFSTREAMS_API bool overflow() const;
    PFSTREAMS_API void seek(int at);

    PFSTREAMS_API bool do_u8(uint8_t* address);
    PFSTREAMS_API bool do_u16(uint16_t* address);
    PFSTREAMS_API bool do_u32(uint32_t* address);
    PFSTREAMS_API bool do_u64(uint64_t* address);
    PFSTREAMS_API bool do_uvar(uint64_t* address, uint8_t size);

    PFSTREAMS_API bool do_i8(int8_t* address);
    PFSTREAMS_API bool do_i16(int16_t* address);
    PFSTREAMS_API bool do_i32(int32_t* address);
    PFSTREAMS_API bool do_i64(int64_t* address);

    PFSTREAMS_API bool do_f32(float* address);
    PFSTREAMS_API bool do_f64(double* address);

    PFSTREAMS_API bool do_bytes(int len, std::byte* address);

private:
    Mode m_mode;
    std::byte* m_buff;
    int m_len;
    int m_head;

    bool read_bytes(void* dst, int bytes);
    bool write_bytes(void* data, int bytes);
};

}

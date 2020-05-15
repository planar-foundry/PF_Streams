PF_Streams
==========

Exposes a library which can be used to read and write data to arbitrary memory.

## Headline features

* Read and write regular primitives, binary data, and variable-sized unsigned ints,
* The read- or write-ness of the stream is determined in the constructor, so the same code path can be used for serializing and deserializing,
* Primitives are endian swapped on read and write. Little endian by default - swap with -DPFSTREAMS_BIG_ENDIAN=1.

## Instructions

Refer to `tests/` for a minimal example.

1. Typically, it is expected that your serialziation and deserialization code should look something like this:

```cpp
void serialize(ByteStream* stream, Body_Payload_Acks32* header)
{
    stream->do_u16(&header->sequence);
    stream->do_u16(&header->ack);
    stream->do_u32(&header->ack32);
}

void read(Body_Payload_Acks32* header, const std::byte* data, int len)
{
    ByteStream stream(ByteStream::Mode::Read, const_cast<std::byte*>(data), len);
    serialize(&stream, header);
    PFDEBUG_ASSERT(!stream.overflow());
}

void write(const Body_Payload_Acks32* header, std::byte* data, int len)
{
    ByteStream stream(ByteStream::Mode::Write, data, len);
    serialize(&stream, const_cast<Body_Payload_Acks32*>(header));
    PFDEBUG_ASSERT(!stream.overflow());
}
```

Note the `const_cast`, which allow you to maintain a const-correct interface while avoiding the need for duplicate read/write functions.

2. It is possible to check what mode a stream is in, and in some cases, optimize code for read/writing, for example:

```cpp
void serialize_payload(ByteStream* stream, std::byte** payload, uint16_t len)
{
    if (stream->mode() == ByteStream::Mode::Read)
    {
        // This is an optimization. There's no point copying it out of the buffer - let's leave that up to the user.
        // Instead, we grab a raw pointer from inside the stream and return it.
        *payload = stream->buffer() + stream->head();
        stream->seek(stream->head() + len);
    }
    else
    {
        stream->do_bytes(len, *payload);
    }
}
```

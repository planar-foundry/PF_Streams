#pragma once

#if defined(WIN32) && defined(PF_Streams_EXPORTS)
    #define PFSTREAMS_API __declspec(dllexport)
#else
    #define PFSTREAMS_API
#endif

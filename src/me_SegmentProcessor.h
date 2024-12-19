// Segment processor interface

/*
  Author: Martin Eden
  Last mod.: 2024-12-19
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_SegmentProcessor
{
  /*
    Copy stream

    Function fails when input or output stream fails.
  */
  TBool CopyFrom(
    me_MemorySegment::TMemorySegment Src,
    me_MemorySegment::TMemorySegment Dest,
    TOperation Getter,
    TOperation Setter
  );
}

/*
  2024-12-13
  2024-12-18
*/

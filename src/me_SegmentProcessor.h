// Segment processor interface

/*
  Author: Martin Eden
  Last mod.: 2025-08-24
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_SegmentProcessor
{
  // Copy data
  TBool CopyFrom(
    me_MemorySegment::TMemorySegment Src_Seg,
    me_MemorySegment::TMemorySegment Dest_Seg,
    TOperation Src_Getter,
    TOperation Dest_Setter
  );

  // Compare data
  TBool AreEqual(
    me_MemorySegment::TMemorySegment A_Seg,
    me_MemorySegment::TMemorySegment B_Seg,
    TOperation A_Getter,
    TOperation B_Getter
  );
}

/*
  2024-12-13
  2024-12-18
  2025-08-24
*/

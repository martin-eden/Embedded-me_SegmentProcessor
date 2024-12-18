// Segment processor interface

/*
  Author: Martin Eden
  Last mod.: 2024-12-13
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
    TResponsiveMethod Getter,
    TResponsiveMethod Setter
  )
  {
    me_MemorySegment::TSegmentIterator SrcRator;
    me_MemorySegment::TSegmentIterator DestRator;
    TAddress ReadAddr;
    TAddress WriteAddr;
    TUnit Unit;
    TAddress UnitAddr = (TAddress) &Unit;

    if (!SrcRator.Init(Src))
      return false;

    if (!DestRator.Init(Dest))
      return false;

    while (true)
    {
      if (!SrcRator.GetNext(&ReadAddr))
        break;

      if (!DestRator.GetNext(&WriteAddr))
        break;

      if (!Getter(UnitAddr, ReadAddr))
        return false;

      if (!Setter(UnitAddr, ReadAddr))
        return false;
    }

    return true;
  };
}

/*
  2024-12-13
  2024-12-18
*/

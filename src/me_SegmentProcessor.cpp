// Segment processor

/*
  Author: Martin Eden
  Last mod.: 2024-12-19
*/

#include <me_SegmentProcessor.h>

using namespace me_SegmentProcessor;

using
  me_MemorySegment::TMemorySegment,
  me_MemorySegment::TSegmentIterator;

TBool me_SegmentProcessor::CopyFrom(
  TMemorySegment Src,
  TMemorySegment Dest,
  TOperation Getter,
  TOperation Setter
)
{
  TSegmentIterator SrcRator;
  TSegmentIterator DestRator;
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

    if (!Setter(UnitAddr, WriteAddr))
      return false;
  }

  return true;
}

/*
  2024-12-19
*/

// Segment processor

/*
  Author: Martin Eden
  Last mod.: 2025-08-25
*/

#include <me_SegmentProcessor.h>

using namespace me_SegmentProcessor;

using
  me_MemorySegment::TMemorySegment,
  me_MemorySegment::TSegmentIterator;

/*
  Copy data between segments
*/
TBool me_SegmentProcessor::CopyFrom(
  TMemorySegment Src_Seg,
  TMemorySegment Dest_Seg,
  TOperation Src_Getter,
  TOperation Dest_Setter
)
{
  TSegmentIterator Src_Rator;
  TSegmentIterator Dest_Rator;

  TAddress ReadAddr;
  TAddress WriteAddr;

  TUnit Unit;
  TAddress UnitAddr = (TAddress) &Unit;

  if (!Src_Rator.Init(Src_Seg))
    return false;

  if (!Dest_Rator.Init(Dest_Seg))
    return false;

  while (Src_Rator.GetNextAddr(&ReadAddr))
  {
    if (!Src_Getter(UnitAddr, ReadAddr))
      return false;

    if (!Dest_Rator.GetNextAddr(&WriteAddr))
      return false;

    if (!Dest_Setter(UnitAddr, WriteAddr))
      return false;
  }

  return true;
}

/*
  Compare segment's data
*/
TBool me_SegmentProcessor::AreEqual(
  me_MemorySegment::TMemorySegment A_Seg,
  me_MemorySegment::TMemorySegment B_Seg,
  TOperation A_Getter,
  TOperation B_Getter
)
{
  TSegmentIterator A_Rator;
  TSegmentIterator B_Rator;

  TUnit A_Unit;
  TUnit B_Unit;

  TAddress A_Unit_Addr = (TAddress) &A_Unit;
  TAddress B_Unit_Addr = (TAddress) &B_Unit;

  TAddress A_ReadAddr;
  TAddress B_ReadAddr;

  if (!A_Rator.Init(A_Seg))
    return false;

  if (!B_Rator.Init(B_Seg))
    return false;

  while (A_Rator.GetNextAddr(&A_ReadAddr))
  {
    if (!A_Getter(A_Unit_Addr, A_ReadAddr))
      return false;

    if (!B_Rator.GetNextAddr(&B_ReadAddr))
      return false;

    if (!B_Getter(B_Unit_Addr, B_ReadAddr))
      return false;

    if (A_Unit != B_Unit)
      return false;
  }

  return true;
}

/*
  2024-12-19
*/

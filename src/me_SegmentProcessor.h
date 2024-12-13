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
  // Getter as a class
  class TInputStream
  {
    public:
      virtual TBool Read(TUnit * Unit) = 0;
  };

  // Setter as a class
  class TOutputStream
  {
    public:
      virtual TBool Write(TUnit Unit) = 0;
  };

  /*
    Reader with range margins inside 1-d segment.

    Just masqueraded segment iterator for the sake
    of accessing "GetNext()" method under name "Read()".
  */
  class TMemsegStreamReader : public TInputStream
  {
    private:
      me_MemorySegment::TSegmentIterator Rator;

    public:
      void Init(
        me_MemorySegment::TMemorySegment Segment,
        TResponsiveMethod Getter
      )
      {
        Rator.Init(Segment, Getter);
      };

      TBool Read(TUnit * Unit) override
      {
        return Rator.GetNext(Unit);
      };
  };

  // Writer with range margins inside 1-d segment
  class TMemsegStreamWriter : public TOutputStream
  {
    private:
      me_MemorySegment::TSegmentIterator Rator;

    public:
      void Init(
        me_MemorySegment::TMemorySegment Segment,
        TResponsiveMethod Setter
      )
      {
        Rator.Init(Segment, Setter);
      };

      TBool Write(TUnit Unit) override
      {
        return Rator.GetNext(&Unit);
      };
  };

  /*
    Copy stream

    Function fails when input or output stream fails.
  */
  TBool Copy(
    TInputStream * Reader,
    TOutputStream * Writer
  )
  {
    TUnit Unit;

    while (true)
    {
      if (!Reader->Read(&Unit))
        return false;

      if (!Writer->Write(Unit))
        return false;
    }

    return true;
  };
}

/*
  2024-12-13
*/

// Segment processor in-growth test

/*
  Author: Martin Eden
  Last mod.: 2024-12-13
*/

/*
  In this test we want to check stream processing by reading
  data from memory and writing it to serial.

  Yes, for this case we're just printing string but mechanics
  are more universal than that.
*/

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_SegmentProcessor.h>
#include <me_Uart.h>
#include <me_UartSpeeds.h>
#include <me_Console.h>
#include <me_FlashMemory.h>

// Wrapping me_Uart::SendByte() as TResponsiveMethod
TBool WriteUnit(
  TAddress Data,
  TAddress Instance [[gnu::unused]]
)
{
  TUnit Unit;

  Unit = *(TUnit *) Data;

  me_Uart::SendByte(Unit);

  return true;
}

void RunTest()
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::UnitGetter,
    me_SegmentProcessor::TMemsegStreamReader,
    me_SegmentProcessor::TMemsegStreamWriter,
    me_MemorySegment::Freetown::FromAddrSize,
    me_SegmentProcessor::Copy;

  TMemorySegment TestData = FromAsciiz("ABC\n");
  TMemorySegment FakeSegment = FromAddrSize(0, 2000);
  TMemsegStreamReader InputStream;
  TMemsegStreamWriter OutputStream;
  TResponsiveMethod MemGetter = UnitGetter;
  TResponsiveMethod UartWriter = WriteUnit;

  InputStream.Init(TestData, MemGetter);
  OutputStream.Init(FakeSegment, UartWriter);

  Copy(&InputStream, &OutputStream);

  /*
    Okay, we printed some text from memory to serial

    .. In some weird way. Serial.print() and Console.Write()
    are doing this much more naturally.

    "What's the point of that abstractions?" -- they ask.
  */

  // ( How about printing Flash memory guys?

  static const char FlashTestData[] [[gnu::progmem]] = "DEF\n";
  TMemorySegment FlashDataSeg =
    FromAddrSize((TAddress) FlashTestData, sizeof(FlashTestData) - 1);

  TResponsiveMethod FlashGetter = me_FlashMemory::UnitGetter;

  InputStream.Init(FlashDataSeg, FlashGetter);
  OutputStream.Init(FakeSegment, UartWriter);

  Copy(&InputStream, &OutputStream);

  // ) Yes, we've just printed flash data to serial

  // We can demonstrate copying memory but we won't
}

void setup()
{
  me_Uart::Init(me_UartSpeeds::Bps_115k);
  Console.Print("Hello there!"); // yes, Console can print memory without us
  RunTest();
  Console.Print("Done.");
}

void loop()
{
}

/*
  2024-12-13
*/

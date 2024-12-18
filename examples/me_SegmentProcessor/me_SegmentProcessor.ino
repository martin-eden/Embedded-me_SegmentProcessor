// Segment processor in-growth test

/*
  Author: Martin Eden
  Last mod.: 2024-12-18
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
#include <me_ProgramMemory.h>
#include <me_WorkMemory.h>

void RunTest()
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::FromAddrSize,
    me_SegmentProcessor::CopyFrom;

  TMemorySegment TestData = FromAsciiz("ABC\n");
  TMemorySegment FakeSegment = FromAddrSize(0, 2000);
  TOperation Mem_GetByte = me_WorkMemory::Op_GetByte;
  TOperation Flash_GetByte = me_ProgramMemory::Op_GetByte;
  TOperation Uart_SendByte = me_Uart::Op_PutByte;

  CopyFrom(TestData, FakeSegment, Mem_GetByte, Uart_SendByte);

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

  CopyFrom(FlashDataSeg, FakeSegment, Flash_GetByte, Uart_SendByte);

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

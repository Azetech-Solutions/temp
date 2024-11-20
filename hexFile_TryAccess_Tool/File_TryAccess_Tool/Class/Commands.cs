using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;

namespace File_TryAccess_Tool
{
    public static class Commands
    {
        public static UInt32 AppmajorVer = 0;
        public static UInt32 AppminorVer = 0;
        public static UInt32 AppBuildVer = 0;
        public static UInt32 AppReleaseVer = 0;

        public const byte Flashstart = 0xF5;
        public const byte Flasherase = 0xFE;
        public const byte FlashData = 0xFD;
        public const byte Flashcomplete = 0xFC;
        public const byte ChooseFlashMode = 0xFB;

        public const byte Responce_OK = 0x00;
        public const byte Responce_NOTOK = 0x01;

        public const UInt32 APP1_Pattern = 0xA1A1A1A1;
        public const UInt32 APP2_Pattern = 0xA2A2A2A2;

        public const byte NVMGetAlldata = 0xE1;
        public const byte NVMUpdate = 0xE2;
        public const byte NVMClear = 0xE3;
        public const byte NVMUpdateAlldata = 0xE4;
        public const byte NVMReOrg = 0xE5;

        public const byte GETAPPVERSIONCMD = 0xD0;
        public const byte GETNVSLASTADDRESSCMD = 0xD1;
        public const byte NVSstartCMD = 0xFA; // used to update the NVS Data
        public static uint NVS_Pattern = 0xC1C1C1C1;

        public const byte FCSingleFrame = 0;
        public const byte FCFirstFrame = 1;
        public const byte FCConsecutiveFrame = 2;
        public const byte FCFlowcontrolFrame = 3;

        public static bool FCrxCbkFlag = false;

        public const byte FCSendstatus = 0;
        public const byte FCWaitstatus = 1;
        public const byte FCAbortstatus = 2;
        public const byte FCRepeatstatus = 3;

        public const byte MAXTransmitSize = 240;

    }
}

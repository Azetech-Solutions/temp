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

        public static byte Flashstart = 0xF5;
        public static byte Flasherase = 0xFE;
        public static byte FlashData = 0xFD;
        public static byte Flashcomplete = 0xFC;
        public static byte ChooseFlashMode = 0xFB;
        public static byte ChooseNVSMode = 0xFA;

        public static byte Responce_OK = 0x00;
        public static byte Responce_NOTOK = 0x01;

        public static UInt32 APP1_Pattern = 0xA1A1A1A1;
        public static UInt32 APP2_Pattern = 0xA2A2A2A2;

        public static byte NVMGetAlldata = 0xE1;
        public static byte NVMUpdate = 0xE2;
        public static byte NVMClear = 0xE3;
        public static byte NVMUpdateAlldata = 0xE4;
        public static byte NVMReOrg = 0xE5;



    }
}

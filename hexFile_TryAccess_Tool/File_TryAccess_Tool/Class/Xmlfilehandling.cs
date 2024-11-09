using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace File_TryAccess_Tool
{
    public static class Xmlfilehandling
    {
        static XmlDocument settingDoc;

        public static XmlNodeList setType;
        public static XmlNodeList setSector;
        public static XmlNodeList setSectorLength;
        public static XmlNodeList setBank;
        public static XmlNodeList setStartAddress;
        public static XmlNodeList setEndAddress;
        public static XmlNodeList setDataBlock;
        public static XmlNodeList setVerinfo;
        public static XmlNodeList setComport;
        public static XmlNodeList setComiflist;

        public static void XMLRegister(XmlDocument x)
        { 
            settingDoc = x;

            setType = x.GetElementsByTagName("type");
            setSector = x.GetElementsByTagName("sector");
            setSectorLength = x.GetElementsByTagName("sectorlength");
            setBank = x.GetElementsByTagName("bank");
            setStartAddress = x.GetElementsByTagName("startaddress");
            setEndAddress = x.GetElementsByTagName("endaddress");
            setDataBlock = x.GetElementsByTagName("datablock");
            setVerinfo = x.GetElementsByTagName("versioninfo");
            setComport = x.GetElementsByTagName("comport");
            setComiflist = x.GetElementsByTagName("comif");
            //string path = Directory.GetCurrentDirectory() + @"Toolsetting.xml";
        }
        
    }
}

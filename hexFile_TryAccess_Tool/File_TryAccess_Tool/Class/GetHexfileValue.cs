using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace File_TryAccess_Tool
{
    public class GetHexfileValue
    {

        public byte ReadByte_Hexfile(string line, int index = 0)
        {
            return (byte) Convert.ToByte(line.Substring(index, 2),16);
        }

        public ushort ReadWord_Hexfile(string line, int index = 0, int size = 2)
        {
            byte[] readword = new byte[2];

            int i = 0;
            while (size > 0)
            {
                readword[i] = ReadByte_Hexfile(line, index);

                i++;
                size--;
                index += 2;
            }

            return (ushort)((readword[0] << 8) | readword[1]);
        }

        public byte[] ReadData_Hexfile(String line, int index = 0, int size = 0 )
        {
            List<byte> data = new List<byte>();

            while(size > 0) 
            {
                data.Add( ReadByte_Hexfile(line, index) );
                size--;
                index += 2;
            }

            return data.ToArray();
        }

        public uint CalculateCKsum_Hexfile(byte[] hex)
        {
            uint[] hexval = new uint[hex.Length/4];
            uint retval = 0;

            if ((hex.Length / 4) == 1)
            {
                hexval[0] = (uint)( (hex[3] << 24) | (hex[2] << 16) | (hex[1] << 8) | (hex[0]) );

                retval = (uint) hexval[0];
            }
            else if ((hex.Length / 4) == 2)
            {
                hexval[0] = (uint)((hex[3] << 24) | (hex[2] << 16) | (hex[1] << 8) | (hex[0]) );
                hexval[1] = (uint)((hex[7] << 24) | (hex[6] << 16) | (hex[5] << 8) | (hex[4]) );

                retval = (uint)(hexval[0] + hexval[1]);
            }
            else if ((hex.Length / 4) == 3)
            {
                hexval[0] = (uint)((hex[3] << 24) | (hex[2] << 16) | (hex[1] << 8) | (hex[0]) );
                hexval[1] = (uint)((hex[7] << 24) | (hex[6] << 16) | (hex[5] << 8) | (hex[4]) );
                hexval[2] = (uint)((hex[11] << 24) | (hex[10] << 16) | (hex[9] << 8) | (hex[8]) );

                retval = (uint)(hexval[0] + hexval[1] + hexval[2]);
            }
            else if ((hex.Length / 4) == 4)
            {
                hexval[0] = (uint)((hex[3] << 24) | (hex[2] << 16) | (hex[1] << 8) | (hex[0]) );
                hexval[1] = (uint)((hex[7] << 24) | (hex[6] << 16) | (hex[5] << 8) | (hex[4]) );
                hexval[2] = (uint)((hex[11] << 24) | (hex[10] << 16) | (hex[9] << 8) | (hex[8]) );
                hexval[3] = (uint)((hex[15] << 24)  | (hex[14] << 16) | (hex[13] << 8) | (hex[12]) );

                retval = (uint)(hexval[0] + hexval[1] + hexval[2] + hexval[3]);
            }

            return retval;
        }

        public byte[] Changeformat_HexDatas(byte cmd, int add, byte[] data)
        {
            List<byte> list = new List<byte>();

            list.Add(cmd);
            list.Add((byte)(add >> 24));
            list.Add((byte)(add >> 16));
            list.Add((byte)(add >> 8));
            list.Add((byte)(add));

            for(int i = 0;i < data.Length; i++)
            {
                list.Add(data[i]);
            }

            if(data.Length < 16)
            {
                for( int i = data.Length - 1; i < 21; i++) 
                {
                    list.Add(0xFF);
                }
            }
            return list.ToArray();
        }

    }
}

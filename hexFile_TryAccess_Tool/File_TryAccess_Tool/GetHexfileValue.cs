using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace File_TryAccess_Tool
{
    public class GetHexfileValue
    {

        public string HexfileReadByte(string line, int index = 0)
        {
            return line.Substring(index, 2);
        }

        public string HexfileReadword(string line, int index = 0)
        {
            return line.Substring(index, 4);
        }

        public string HexfileReadDatas(String line, int index = 0, int size = 0)
        {
            return line.Substring(index, (size * 2));
        }

        public uint HexfileSumOfLine(string hex)
        {
            uint[] hexval = new uint[hex.Length / 2];

            // Convert hexadecimal string to byte array
            byte[] byteArray = new byte[hex.Length / 2];

            for (int i = 0; i < byteArray.Length; i++)
            {
                byteArray[i] = Convert.ToByte(hex.Substring(i * 2, 2), 16);
            }

            if ((byteArray.Length / 4) == 1)
            {
                hexval[0] = (uint)(byteArray[3] << 24 | byteArray[2] << 16 | byteArray[1] << 8 | byteArray[0]);
            }
            else if ((byteArray.Length / 4) == 2)
            {
                hexval[0] = (uint)(byteArray[3] << 24 | byteArray[2] << 16 | byteArray[1] << 8 | byteArray[0]);
                hexval[1] = (uint)(byteArray[7] << 24 | byteArray[6] << 16 | byteArray[5] << 8 | byteArray[4]);
            }
            else if ((byteArray.Length / 4) == 3)
            {
                hexval[0] = (uint)(byteArray[3] << 24 | byteArray[2] << 16 | byteArray[1] << 8 | byteArray[0]);
                hexval[1] = (uint)(byteArray[7] << 24 | byteArray[6] << 16 | byteArray[5] << 8 | byteArray[4]);
                hexval[2] = (uint)(byteArray[11] << 24 | byteArray[10] << 16 | byteArray[9] << 8 | byteArray[8]);
            }
            else if ((byteArray.Length / 4) == 4)
            {
                hexval[0] = (uint)(byteArray[3] << 24 | byteArray[2] << 16 | byteArray[1] << 8 | byteArray[0]);
                hexval[1] = (uint)(byteArray[7] << 24 | byteArray[6] << 16 | byteArray[5] << 8 | byteArray[4]);
                hexval[2] = (uint)(byteArray[11] << 24 | byteArray[10] << 16 | byteArray[9] << 8 | byteArray[8]);
                hexval[3] = (uint)(byteArray[15] << 24 | byteArray[14] << 16 | byteArray[13] << 8 | byteArray[12]);
            }


            uint sum = hexval[0] + hexval[1] + hexval[2] + hexval[3];

            return sum;
        }
    }
}

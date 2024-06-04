using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace File_TryAccess_Tool
{
    public static class Log
    {
        static RichTextBox richTextBox = null;
        public static void logRegister(RichTextBox r) 
        {
            richTextBox = r; 
        }

        public static void Clear()
        {
            if (richTextBox != null)
            {
                richTextBox.Text = "";
                richTextBox.ScrollToCaret();
            }
        }

        public static void Write(string Message, Color color, bool prefixTimeStamp = true)
        {
            if (richTextBox != null)
            {
                if (prefixTimeStamp)
                {
                    Message = "[" + DateTime.Now.ToShortTimeString() + "]" + Message;
                }

                try
                {
                    if (richTextBox.InvokeRequired)
                    {
                        richTextBox.Invoke(new MethodInvoker(() =>
                        {
                            richTextBox.AppendText(Message);
                            richTextBox.Select((richTextBox.TextLength - (Message.Length - 1)), Message.Length);
                            richTextBox.SelectionColor = color;
                            richTextBox.Select(richTextBox.TextLength, 0);
                            richTextBox.ScrollToCaret();
                        }));
                    }
                    else
                    {
                        richTextBox.AppendText(Message);
                        richTextBox.Select((richTextBox.TextLength - (Message.Length - 1)), Message.Length);
                        richTextBox.SelectionColor = color;
                        richTextBox.Select(richTextBox.TextLength, 0);
                        richTextBox.ScrollToCaret();
                    }
                }
                catch
                {
                    // Do nothing
                }
            }
        }

        public static void WriteLine(string Message, Color color, bool prefixTimeStamp = true)
        {
            Write(Message + Environment.NewLine, color, prefixTimeStamp);
        }

        public static void Message(string Message)
        {
                WriteLine(" " + Message, Color.Black);
        }

        public static void Info(string Message)
        {
                WriteLine("[I] " + Message, Color.Black);
        }

        public static void Warning(string Message)
        {
                WriteLine("[W] " + Message, Color.OrangeRed);
        }

        public static void Error(string Message)
        {
                WriteLine("[E] " + Message, Color.Red);
        }
    }
}

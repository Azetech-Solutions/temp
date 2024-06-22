using System;
using System.ComponentModel;
using static File_TryAccess_Tool.Log;
using static File_TryAccess_Tool.Hexfilehandling;
using static File_TryAccess_Tool.GetHexfileValue;
using System.Threading;
using System.Data;


namespace File_TryAccess_Tool
{
    public static class BackgroundworkerFile
    {
        public static string findApp = null;
        public static BackgroundWorker Worker;

        public static Hexfilehandling hexfile;
        public static void RegisterBackgroundworkerFile()
        {
            Worker = new BackgroundWorker();
            Worker.DoWork += new System.ComponentModel.DoWorkEventHandler(Method_DoWork);
            Worker.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(Method_runComplete);
            hexfile = new Hexfilehandling();
        }

        public enum Backworkerjobtype
        {
            unkown = 0,
            MainForm = 1,
            NvsForm = 2,
            NvmForm = 3,
        }
        

        public static bool JobSchedule(Backworkerjobtype jobtype)
        {            
            bool retval = false;
            Worker.RunWorkerAsync(jobtype);
            

            return retval;
        }

        private static void Method_runComplete(object sender, RunWorkerCompletedEventArgs e)
        {
            
        }


        private static  Backworkerjobtype jobtype = Backworkerjobtype.unkown;

        private static void Method_DoWork(object sender, DoWorkEventArgs e)
        {
            jobtype = (Backworkerjobtype)e.Argument;
            switch (jobtype)
            {
                case Backworkerjobtype.MainForm:
                    {
                        bool Modestatus = false;

                        if (hexfile.Flashstartcommands(Convert.ToUInt32(Xmlfilehandling.setStartAddress[2].InnerText)))  // based on xml app1 start address
                        {
                            Modestatus = true;
                        }

                        if (Modestatus == true)
                        {
                            bool Flh_CompleteStatus = false;

                            Log.Message("Flash transmit start");
                            if (hexfile.FlashDatatransmit())
                            {
                                Log.Message("Flash transmit start end");
                                Flh_CompleteStatus = true; // to confirm all data's are transmit to uC
                            }

                            if (Flh_CompleteStatus == true)
                            {
                                if (findApp == "App1")
                                {
                                    Log.Message("Flash update start");
                                    if (hexfile.UpdateflashappHeader(Convert.ToUInt32(Xmlfilehandling.setStartAddress[2].InnerText)))   // based on xml app1 start address
                                    {
                                        Log.Message("Flash update start end");
                                        Log.Message("Flash Complete start");
                                        hexfile.flashcompletecommand(Convert.ToUInt32(Xmlfilehandling.setStartAddress[2].InnerText));   // based on xml app1 start address
                                        Log.Message("Flash Complete start end");
                                    }
                                }
                                else
                                {
                                    if (hexfile.UpdateflashappHeader(Convert.ToUInt32(Xmlfilehandling.setStartAddress[3].InnerText)))   // based on xml app2 start address
                                    {
                                        hexfile.flashcompletecommand(Convert.ToUInt32(Xmlfilehandling.setStartAddress[3].InnerText));    // based on xml app2 start address
                                    }
                                }
                            }// end 
                        }
                       
                    }
                    break;
                case Backworkerjobtype.NvsForm:
                    {

                    }
                    break;
                case Backworkerjobtype.NvmForm:
                    {

                    }
                    break;
                default:
                    break;
            }

            Worker.CancelAsync();
        }
    }
}

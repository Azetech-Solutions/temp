using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
using System.Xml;
using System.Windows.Forms;
using static File_TryAccess_Tool.Tooltransmit;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using File_TryAccess_Tool.Class;
using System.Linq;
using System.Threading;

namespace File_TryAccess_Tool
{
    public class NvmDataHandling
    {
        System.Windows.Forms.TreeView tView;
        private FlowControlHandling fctxhandle = new FlowControlHandling();

        public NvmDataHandling(System.Windows.Forms.TreeView t) { tView = t; }

        public void NvmClearCmD()
        {
            List<byte> clearCMD = new List<byte>();

            clearCMD.Add(Commands.NVMClear);

            Log.Message("NvmClear Start");

            FCDatabytesupdate(clearCMD.ToArray());
            FCTransmit.Length = (byte)clearCMD.Count;
            MCUTransmitFunction.Transmit(FCTransmit);
            
            while(true)
            {
                if (MCUStatusRxData[0] == 0x00)
                {
                    MCUStatusRxData[0] = 0xFF;
                    break;
                }
                else if (MCUStatusRxData[0] == 0x01)
                {
                    MCUStatusRxData[0] = 0xFF;

                    MCUTransmitFunction.Transmit(FCTransmit);
                }
            }

            Log.Message("NvmClear End ");
        } // clear end

        public void NvmReOrgCMD()
        {
            List<byte> ReorgCMD = new List<byte>();

            ReorgCMD.Add(Commands.NVMReOrg);

            FCDatabytesupdate(ReorgCMD.ToArray());
            FCTransmit.Length =(byte)ReorgCMD.Count;
            MCUTransmitFunction.Transmit(FCTransmit);

            Log.Message("NvmReOrg Start");
            while (true)
            {
                if (MCUStatusRxData[0] == 0x00)
                {
                    MCUStatusRxData[0] = 0xFF;
                    break;
                }
                else if (MCUStatusRxData[0] == 0x01)
                {
                    MCUStatusRxData[0] = 0xFF;

                    MCUTransmitFunction.Transmit(FCTransmit);
                }
            }

            Log.Message("NvmReOrg End ");
        } // reorg end

        public void NvmExportXML(string tbxdata,string xmlfilePath)
        {
            int togetvalidData = 0;

            XmlTextWriter xwriter = new XmlTextWriter(xmlfilePath, System.Text.Encoding.UTF8);
            xwriter.Formatting = Formatting.Indented;
            xwriter.WriteStartDocument();

            xwriter.WriteStartElement("nvmblocks");

            while(togetvalidData < tbxdata.Length)
            {
                xwriter.WriteStartElement("nvmblock");
                xwriter.WriteElementString("pattern", tbxdata.Substring(togetvalidData, 8));
                togetvalidData += 8;
                xwriter.WriteElementString("len", tbxdata.Substring(togetvalidData, 4));
                togetvalidData += 4;
                xwriter.WriteElementString("id", tbxdata.Substring(togetvalidData, 4));
                togetvalidData += 4;
                xwriter.WriteElementString("nvmversion", tbxdata.Substring(togetvalidData, 8));
                togetvalidData += 8;
                xwriter.WriteElementString("nvmdatacksum", tbxdata.Substring(togetvalidData, 8));
                togetvalidData += 8;
                xwriter.WriteElementString("data0", tbxdata.Substring(togetvalidData, 8));
                togetvalidData += 8;
                xwriter.WriteElementString("data1", tbxdata.Substring(togetvalidData, 8));
                togetvalidData += 8;
                xwriter.WriteElementString("data2", tbxdata.Substring(togetvalidData, 8));
                togetvalidData += 8;
                xwriter.WriteElementString("data3", tbxdata.Substring(togetvalidData, 8));
                togetvalidData += 8;
                xwriter.WriteEndElement();
            }

            xwriter.WriteEndElement();
            xwriter.WriteEndDocument();
            xwriter.Flush();
            xwriter.Close();
        } // export end
 
        public void NvmImportXML(string filepath)
        {
            if(filepath != null)
            {
                LoadXmlToTreeView(filepath);
            }            
        } // import end

        private void LoadXmlToTreeView(string filePath)
        {
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load(filePath);
            TreeNode rootNode = new TreeNode(xmlDoc.DocumentElement.Name);
            tView.Nodes.Add(rootNode);
            AddTreeNode(xmlDoc.DocumentElement, rootNode);
        } // end

        private void AddTreeNode(XmlNode xmlNode, TreeNode treeNode)
        {
            XmlNode childNode;
            TreeNode childTreeNode;
            XmlNodeList nodeList;

            if (xmlNode.HasChildNodes)
            {
                nodeList = xmlNode.ChildNodes;
                for (ushort i = 0; i <= nodeList.Count - 1; i++)
                {
                    childNode = xmlNode.ChildNodes[i];
                    treeNode.Nodes.Add(new TreeNode(childNode.Name));
                    childTreeNode = treeNode.Nodes[i];
                    AddTreeNode(childNode, childTreeNode);
                }
            }
            else
            {
                treeNode.Text = xmlNode.OuterXml.Trim();
            }
        } // end        


        public void UpdateAllCMD(string Totaldata, byte[] uptcmd)
        {
            XmlDocument uptxml = new XmlDocument();
            uptxml.Load(Totaldata);
            byte[] validNvmUpdatealldata = fctxhandle.ConvertHexStringToByteArray(uptxml.InnerText);

            Log.Message("UpdateAllCMD Start");
            // cmd transmit // to initiate the update the all NVM data's            
            FCDatabytesupdate(uptcmd);
            FCTransmit.Length = (byte)uptcmd.Length;
            MCUTransmitFunction.Transmit(FCTransmit);

            while (true)
            {
                if (MCUStatusRxData[0] == 0x00)
                {
                    MCUStatusRxData[0] = 0xFF;                    
                    break;
                }
                else if (MCUStatusRxData[0] == 0x01)
                {
                    MCUStatusRxData[0] = 0xFF;

                    MCUTransmitFunction.Transmit(FCTransmit);
                }
            }

            fctxhandle.FCDataTransmit(validNvmUpdatealldata);

            Log.Message("UpdateAllCMD End");
        }



        public void NvmUpdateCMD(string strdata)
        {
            List<byte> data = new List<byte>();            
            byte[] UptDatainbytes = fctxhandle.ConvertHexStringToByteArray(strdata);

            data.Add(Commands.NVMUpdate);
            data.Add((byte)UptDatainbytes.Length);
            data.Add(0x00);

            Log.Message("UpdateCMD Start");
            for (int i = 0; i< UptDatainbytes.Length; i++)
            {
                data.Add(UptDatainbytes[i]);
            }

            FCDatabytesupdate(data.ToArray());
            FCTransmit.Length = (byte)data.Count;
            MCUTransmitFunction.Transmit(FCTransmit);

            while (true)
            {
                if (MCUStatusRxData[0] == 0x00)
                {
                    MCUStatusRxData[0] = 0xFF;
                    break;
                }
                else if (MCUStatusRxData[0] == 0x01)
                {
                    MCUStatusRxData[0] = 0xFF;

                    MCUTransmitFunction.Transmit(FCTransmit);
                }
            }

            Log.Message("UpdateCMD End");
        }
    }
}

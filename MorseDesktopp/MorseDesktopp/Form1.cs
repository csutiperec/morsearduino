using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MorseDesktopp
{
    public partial class Form1 : Form
    {
        SerialPort serialPort = new SerialPort("COM3", 9600);
        public Form1()
        {
            InitializeComponent();
        }

        private void openPort()
        {
            if (!serialPort.IsOpen)
                try
                {
                    serialPort.DtrEnable = true;
                    serialPort.Open();
                }
                catch (Exception e)
                {
                    //textBox1.Text = "An error has occured! \r\nAre you sure the device is plugged in to the COM3 port of your desktop?";
                    textBox1.Text = e.ToString();
                }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openPort();
            serialPort.Write(textBox1.Text);
            serialPort.Close();
        }

        private void serialPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string msg = serialPort.ReadLine();
            this.BeginInvoke(new LineReceivedEvent(LineReceived), msg);
        }

        private delegate void LineReceivedEvent(string msg);
        private void LineReceived(string msg)
        {
            string decodedMsg = decodeMsg(msg);
            textBox1.Text = decodedMsg;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
            openPort();
            serialPort.DataReceived += serialPort_DataReceived;
        }
        private string decodeMsg(string message)
        {
            for (int j = message.Length - 1; j < 0; j++)
            {
                if (message[j].ToString() != "b")
                    message.Remove(j, 1);
            }
            string msg = "";
            int i = 1;
            while (i < message.Length)
            {
                string charcode = "";
                while (message[i - 1] != 'b')
                {
                    charcode = charcode + message[i - 1];
                    i++;
                }
                msg = msg + decodeCharacter(charcode);
                i++;
            }
            return msg;
        }
        private string decodeCharacter(string charcode)
        {
            switch (charcode)
            {
                case "sl":
                    return "a";
                case "lsss":
                    return "b";
                case "lsls":
                    return "c";
                case "lss":
                    return "d";
                case "s":
                    return "e";
                case "ssls":
                    return "f";
                case "lls":
                    return "g";
                case "ssss":
                    return "h";
                case "ss":
                    return "i";
                case "slll":
                    return "j";
                case "lsl":
                    return "k";
                case "slss":
                    return "l";
                case "ll":
                    return "m";
                case "ls":
                    return "n";
                case "lll":
                    return "o";
                case "slls":
                    return "p";
                case "llsl":
                    return "q";
                case "sls":
                    return "r";
                case "sss":
                    return "s";
                case "l":
                    return "t";
                case "ssl":
                    return "u";
                case "sssl":
                    return "v";
                case "sll":
                    return "w";
                case "lssl":
                    return "x";
                case "lsll":
                    return "y";
                case "llss":
                    return "z";
                case "sllll":
                    return "1";
                case "sslll":
                    return "2";
                case "sssll":
                    return "3";
                case "ssssl":
                    return "4";
                case "sssss":
                    return "5";
                case "lssss":
                    return "6";
                case "llsss":
                    return "7";
                case "lllss":
                    return "8";
                case "lllls":
                    return "9";
                case "lllll":
                    return "0";
            }
            return "";
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            SerialPort serialPort = new SerialPort("COM3", 9600);
            try
            {
                serialPort.Open();
                string msg = serialPort.ReadExisting();
                textBox1.Text = msg;
            }
            catch (Exception)
            {
                Console.WriteLine("No device found on port COM3");
                textBox1.Text = "An error has occured! \r\nAre you sure the device is plugged in to the COM3 port of your desktop?";
            }
        }
    }
}

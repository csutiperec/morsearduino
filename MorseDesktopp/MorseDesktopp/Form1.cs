using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MorseDesktopp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SerialPort serialPort = new SerialPort("COM3", 9600);
            try
            {
                serialPort.Open();
                serialPort.Write(textBox1.Text);
                serialPort.Close();
            }
            catch (Exception)
            {
                Console.WriteLine("No device found on port COM3");
                textBox1.Text = "An error has occured! \r\nAre you sure the device is plugged in to the COM3 port of your desktop?";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SerialPort serialPort = new SerialPort("COM3", 9600);
            try
            {
                serialPort.Open();
                string msg = serialPort.ReadLine();
                serialPort.Close();
                textBox1.Text = decodeMsg(msg);
            }
            catch (Exception)
            {
                Console.WriteLine("No device found on port COM3");
                textBox1.Text = "An error has occured! \r\nAre you sure the device is plugged in to the COM3 port of your desktop?";
            }
        }

        private string decodeMsg(string message)
        {
            string msg = "";
            int i = 0;
            while (i<message.Length)
            {
                string charcode = "";
                while (message[i] != 'b')
                {
                    charcode = charcode + message[i];
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
    }
}

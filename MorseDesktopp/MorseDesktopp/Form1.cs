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

            }
        }
    }
}

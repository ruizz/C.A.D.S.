using System;
using System.Linq;
using System.Text;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;
using System.Threading;
using System.ComponentModel;
using System.Collections.Generic;



namespace WinFormCharpWebCam
{
    //Design by Pongsakorn Poosankam
    public partial class mainWinForm : Form
    {
        SerialPort port;
        Thread thread;

        public mainWinForm()
        {
            InitializeComponent();
        }
        WebCam webcam;
        private void mainWinForm_Load(object sender, EventArgs e)
        {
            webcam = new WebCam();
            webcam.InitializeWebCam(ref imgVideo);
            webcam.Start();

            thread = new Thread(new ThreadStart(captureMovement));
            thread.Start();
        }

        private void bntStart_Click(object sender, EventArgs e)
        {
            
        }

        private void bntStop_Click(object sender, EventArgs e)
        {
            thread.Abort();
            webcam.Stop();
        }

        private void bntContinue_Click(object sender, EventArgs e)
        {
            webcam.Continue();
        }

        private void bntCapture_Click(object sender, EventArgs e)
        {
            imgCapture.Image = imgVideo.Image;
        }

        // Not needed.
        private void bntSave_Click(object sender, EventArgs e)
        {
            //Helper.SaveImageCapture(imgCapture.Image);
            
        }

        private void bntVideoFormat_Click(object sender, EventArgs e)
        {
            webcam.ResolutionSetting();
        }

        private void bntVideoSource_Click(object sender, EventArgs e)
        {
            webcam.AdvanceSetting();
        }

        public void captureMovement() {
            while (true)
            {
                port = new SerialPort("COM3", 9600);
                port.Open();
                String s = port.ReadLine();
                Thread.Sleep(1200);
                imgCapture.Image = imgVideo.Image;
                port.Close();
            }
        }

        private void imgVideo_Click(object sender, EventArgs e)
        {

        }
    }
}

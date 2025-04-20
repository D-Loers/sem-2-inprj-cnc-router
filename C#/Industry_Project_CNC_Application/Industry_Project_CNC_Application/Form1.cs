using System;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Industry_Project_CNC_Application
{
    public partial class Form1 : Form
    {
        public bool EStop = false;
        TcpClient clientsock;
        NetworkStream stream;
        string uploadedFileContent;

        private string[] gCodeLines;
        private PointF currentPosition;
        private Bitmap canvas;
        private Graphics graphics;
        private float scaleFactor = 0.5f;
        private int currentLineIndex = 0;
        private System.Windows.Forms.Timer timer;
        private float currentTemperature;

        public Form1()
        {
            InitializeComponent();
            InitializeCanvas();
            InitializeTimer();
        }

        private void InitializeTimer()
        {
            timer = new Timer();
            timer.Interval = 500;
            timer.Tick += new EventHandler(OnTimedEvent);
        }

        private void OnTimedEvent(object sender, EventArgs e)
        {
            if (gCodeLines != null && currentLineIndex < gCodeLines.Length)
            {
                ProcessGCodeLine(gCodeLines[currentLineIndex]);
                currentLineIndex++;
                ProgressCanvasBox.Invalidate();
            }
            else
            {
                timer.Stop();
            }
        }

        private void InitializeCanvas()
        {
            canvas = new Bitmap(ProgressCanvasBox.Width, ProgressCanvasBox.Height);
            graphics = Graphics.FromImage(canvas);
            graphics.Clear(Color.White);
            ProgressCanvasBox.Image = canvas;
        }

        private void ConnectButton_Click(object sender, EventArgs e)
        {
            try
            {
                string serverIP = IPBox.Text;
                const int port = 8888;
                clientsock = new TcpClient();
                ConnectionBox.Items.Add("Connecting to server...\n");
                clientsock.Connect(IPAddress.Parse(serverIP), port);
                stream = clientsock.GetStream();
                ConnectionBox.Items.Add("Connected to server.\n");
                tabControl1.SelectedTab = fileSelection;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }

        private async void SendNextGCodeLine()
        {
            if (!EStop)
            {
                if (currentLineIndex < gCodeLines.Length)
                {
                    string line = gCodeLines[currentLineIndex];
                    await SendMessage(line);

                    bool ackReceived = await WaitForAck();
                    if (ackReceived)
                    {
                        currentLineIndex++;
                        SendNextGCodeLine();
                    }
                    else
                    {
                        MessageBox.Show("Error: Ack not received");
                        QuitConnection();
                    }
                }
                else
                {
                    MessageBox.Show("G-Code Execution Completed");
                    graphics.Clear(Color.White);
                    ProgressCanvasBox.Invalidate();
                }
            }
        }

        private async Task<bool> WaitForAck()
        {
            byte[] responseData = new byte[1024];
            int bytesRead = await stream.ReadAsync(responseData, 0, responseData.Length);
            string responseMessage = Encoding.ASCII.GetString(responseData, 0, bytesRead);

            ConnectionBox.Items.Add("Server Response: " + responseMessage + "\n");

            return responseMessage.Trim().Equals("ACK", StringComparison.OrdinalIgnoreCase);
        }

        private void QuitConnectionButton_Click(object sender, EventArgs e)
        {
            SendMessage("$START;");
        }



        private void StartAppButton_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = fileSelection;
        }

        private void ConnectTabButton_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = connection;
        }

        private void QuitButton_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void ChooseFileButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "Text files (*.ngc)|*.ngc|All files (*.*)|*.*"
            };
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                uploadedFileContent = File.ReadAllText(filePath);
                gCodeLines = uploadedFileContent.Split('\n');
                FileBox.Items.Clear();
                foreach (string line in gCodeLines)
                {
                    FileBox.Items.Add(line);
                }
            }
        }

        private async Task SendMessage(string message)
        {
            if (!EStop)
            {
                if (clientsock == null || !clientsock.Connected || stream == null)
                {
                    MessageBox.Show("Not connected to the server. Please connect first.");
                    return;
                }

                try
                {
                    byte[] data = Encoding.ASCII.GetBytes(message);
                    stream.WriteAsync(data, 0, data.Length);

                    byte[] responseData = new byte[1024];
                    int bytesRead = await stream.ReadAsync(responseData, 0, responseData.Length);
                    string responseMessage = Encoding.ASCII.GetString(responseData, 0, bytesRead);
                    ConnectionBox.Items.Add("Server response: " + responseMessage + "\n");

                    string[] splitMsg = responseMessage.Split(';');

                    foreach (string line in splitMsg)
                    {
                        ConnectionBox.Items.Add($"{line}");
                    }

                    //if(responseMessage.StartsWith("$"))
                    //{
                    //    string tempString = responseMessage.Substring(4).Trim();
                    //    if(float.TryParse(tempString, out float temp)) 
                    //    {
                    //        currentTemperature = temp;
                    //        Invoke(new Action(UpdateTemperatureDisplay));
                    //    }
                    //}
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }
        }

        private void UpdateTemperatureDisplay() 
        {
            TemperatureLabel.Text = $"Temperature: {currentTemperature} C";
        }

        private void QuitConnection()
        {
            if (clientsock != null && clientsock.Connected)
            {
                clientsock.Close();
            }
        }
        private void ProcessGCodeLine(string line)
        {
            if (!EStop)
            {
                string trimmedLine = line.Trim();
                if (trimmedLine.StartsWith("G0") || trimmedLine.StartsWith("G1"))
                {
                    var newPosition = ParseCoordinates(trimmedLine);
                    if (newPosition != PointF.Empty)
                    {
                        if (trimmedLine.StartsWith("G1"))
                        {
                            graphics.DrawLine(Pens.Black, currentPosition, newPosition);
                        }
                        currentPosition = newPosition;
                    }
                }
            }
        }

        private PointF ParseCoordinates(string line)
        {
            string[] parts = line.Split(' ');
            float x = float.NaN;
            float y = float.NaN;

            foreach (var part in parts)
            {
                if (part.StartsWith("X"))
                {
                    x = float.Parse(part.Substring(1), CultureInfo.InvariantCulture) * scaleFactor;
                }
                else if (part.StartsWith("Y"))
                {
                    y = float.Parse(part.Substring(1), CultureInfo.InvariantCulture) * scaleFactor;
                }
            }
            if (!float.IsNaN(x) && !float.IsNaN(y))
            {
                x = (float)(x + ProgressCanvasBox.Width / 2);
                y = (float)(ProgressCanvasBox.Height / 2 - y);

                return new PointF(x, y);
            }
            else if (!float.IsNaN(x))
            {
                x = x + ProgressCanvasBox.Width / 2;
                return new PointF(x, currentPosition.Y);
            }
            else if (!float.IsNaN(y))
            {
                y = ProgressCanvasBox.Height / 2 - y;
                return new PointF(currentPosition.X, y);
            }

            return PointF.Empty;
        }

        private void EStopButton_Click(object sender, EventArgs e)
        {
            EStop = true;
            MessageBox.Show("Emergency stop has been activated.");
        }

        private void PauseButton_Click(object sender, EventArgs e)
        {
            //UNUSED
        }

        private void ResumeButton_Click(object sender, EventArgs e)
        {
            //UNUSED
        }

        private async void StartButton_Click(object sender, EventArgs e)
        {
            if (clientsock == null || !clientsock.Connected || stream == null)
            {
                MessageBox.Show("Not connected to the server. Please connect first.");
                return;
            }
            if (gCodeLines == null || gCodeLines.Length == 0)
            {
                MessageBox.Show("Upload a file first");
                return;
            }

            await SendMessage("$START;");
            currentLineIndex = 0;
            tabControl1.SelectedTab = CncProgress;
            SendNextGCodeLine();
            timer.Start();
        }
    }
}
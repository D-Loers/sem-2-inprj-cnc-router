namespace Industry_Project_CNC_Application
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.connection = new System.Windows.Forms.TabPage();
            this.ConnectionBox = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.IPBox = new System.Windows.Forms.TextBox();
            this.QuitConnectionButton = new System.Windows.Forms.Button();
            this.ConnectButton = new System.Windows.Forms.Button();
            this.CncProgress = new System.Windows.Forms.TabPage();
            this.ProgressCanvasBox = new System.Windows.Forms.PictureBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.EStopButton = new System.Windows.Forms.Button();
            this.ResumeButton = new System.Windows.Forms.Button();
            this.PauseButton = new System.Windows.Forms.Button();
            this.fileSelection = new System.Windows.Forms.TabPage();
            this.StartButton = new System.Windows.Forms.Button();
            this.FileBox = new System.Windows.Forms.ListBox();
            this.ChooseFileButton = new System.Windows.Forms.Button();
            this.navigationMenu = new System.Windows.Forms.TabPage();
            this.QuitButton = new System.Windows.Forms.Button();
            this.ConnectTabButton = new System.Windows.Forms.Button();
            this.StartAppButton = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.TemperatureLabel = new System.Windows.Forms.Label();
            this.connection.SuspendLayout();
            this.CncProgress.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ProgressCanvasBox)).BeginInit();
            this.fileSelection.SuspendLayout();
            this.navigationMenu.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // connection
            // 
            this.connection.Controls.Add(this.ConnectionBox);
            this.connection.Controls.Add(this.label1);
            this.connection.Controls.Add(this.IPBox);
            this.connection.Controls.Add(this.QuitConnectionButton);
            this.connection.Controls.Add(this.ConnectButton);
            this.connection.Location = new System.Drawing.Point(8, 39);
            this.connection.Margin = new System.Windows.Forms.Padding(6);
            this.connection.Name = "connection";
            this.connection.Padding = new System.Windows.Forms.Padding(6);
            this.connection.Size = new System.Drawing.Size(1188, 664);
            this.connection.TabIndex = 4;
            this.connection.Text = "connection";
            this.connection.UseVisualStyleBackColor = true;
            // 
            // ConnectionBox
            // 
            this.ConnectionBox.FormattingEnabled = true;
            this.ConnectionBox.ItemHeight = 25;
            this.ConnectionBox.Location = new System.Drawing.Point(460, 69);
            this.ConnectionBox.Margin = new System.Windows.Forms.Padding(6);
            this.ConnectionBox.Name = "ConnectionBox";
            this.ConnectionBox.Size = new System.Drawing.Size(358, 179);
            this.ConnectionBox.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(292, 286);
            this.label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(156, 25);
            this.label1.TabIndex = 4;
            this.label1.Text = "please enter IP";
            // 
            // IPBox
            // 
            this.IPBox.Location = new System.Drawing.Point(460, 281);
            this.IPBox.Margin = new System.Windows.Forms.Padding(6);
            this.IPBox.Name = "IPBox";
            this.IPBox.Size = new System.Drawing.Size(196, 31);
            this.IPBox.TabIndex = 3;
            // 
            // QuitConnectionButton
            // 
            this.QuitConnectionButton.Location = new System.Drawing.Point(460, 473);
            this.QuitConnectionButton.Margin = new System.Windows.Forms.Padding(6);
            this.QuitConnectionButton.Name = "QuitConnectionButton";
            this.QuitConnectionButton.Size = new System.Drawing.Size(200, 72);
            this.QuitConnectionButton.TabIndex = 2;
            this.QuitConnectionButton.Text = "stop connection";
            this.QuitConnectionButton.UseVisualStyleBackColor = true;
            this.QuitConnectionButton.Click += new System.EventHandler(this.QuitConnectionButton_Click);
            // 
            // ConnectButton
            // 
            this.ConnectButton.Location = new System.Drawing.Point(460, 374);
            this.ConnectButton.Margin = new System.Windows.Forms.Padding(6);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(200, 72);
            this.ConnectButton.TabIndex = 0;
            this.ConnectButton.Text = "connect";
            this.ConnectButton.UseVisualStyleBackColor = true;
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // CncProgress
            // 
            this.CncProgress.Controls.Add(this.TemperatureLabel);
            this.CncProgress.Controls.Add(this.ProgressCanvasBox);
            this.CncProgress.Controls.Add(this.progressBar1);
            this.CncProgress.Controls.Add(this.EStopButton);
            this.CncProgress.Controls.Add(this.ResumeButton);
            this.CncProgress.Controls.Add(this.PauseButton);
            this.CncProgress.Location = new System.Drawing.Point(8, 39);
            this.CncProgress.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.CncProgress.Name = "CncProgress";
            this.CncProgress.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.CncProgress.Size = new System.Drawing.Size(1188, 664);
            this.CncProgress.TabIndex = 2;
            this.CncProgress.Text = "CNC progress";
            this.CncProgress.UseVisualStyleBackColor = true;
            // 
            // ProgressCanvasBox
            // 
            this.ProgressCanvasBox.Location = new System.Drawing.Point(0, 0);
            this.ProgressCanvasBox.Name = "ProgressCanvasBox";
            this.ProgressCanvasBox.Size = new System.Drawing.Size(539, 497);
            this.ProgressCanvasBox.TabIndex = 6;
            this.ProgressCanvasBox.TabStop = false;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(24, 517);
            this.progressBar1.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(150, 36);
            this.progressBar1.TabIndex = 5;
            // 
            // EStopButton
            // 
            this.EStopButton.Location = new System.Drawing.Point(546, 222);
            this.EStopButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.EStopButton.Name = "EStopButton";
            this.EStopButton.Size = new System.Drawing.Size(182, 50);
            this.EStopButton.TabIndex = 4;
            this.EStopButton.Text = "emergency stop";
            this.EStopButton.UseVisualStyleBackColor = true;
            this.EStopButton.Click += new System.EventHandler(this.EStopButton_Click);
            // 
            // ResumeButton
            // 
            this.ResumeButton.Location = new System.Drawing.Point(546, 123);
            this.ResumeButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.ResumeButton.Name = "ResumeButton";
            this.ResumeButton.Size = new System.Drawing.Size(112, 48);
            this.ResumeButton.TabIndex = 2;
            this.ResumeButton.Text = "resume";
            this.ResumeButton.UseVisualStyleBackColor = true;
            this.ResumeButton.Click += new System.EventHandler(this.ResumeButton_Click);
            // 
            // PauseButton
            // 
            this.PauseButton.Location = new System.Drawing.Point(546, 27);
            this.PauseButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.PauseButton.Name = "PauseButton";
            this.PauseButton.Size = new System.Drawing.Size(112, 50);
            this.PauseButton.TabIndex = 1;
            this.PauseButton.Text = "pause";
            this.PauseButton.UseVisualStyleBackColor = true;
            this.PauseButton.Click += new System.EventHandler(this.PauseButton_Click);
            // 
            // fileSelection
            // 
            this.fileSelection.Controls.Add(this.StartButton);
            this.fileSelection.Controls.Add(this.FileBox);
            this.fileSelection.Controls.Add(this.ChooseFileButton);
            this.fileSelection.Location = new System.Drawing.Point(8, 39);
            this.fileSelection.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.fileSelection.Name = "fileSelection";
            this.fileSelection.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.fileSelection.Size = new System.Drawing.Size(1188, 664);
            this.fileSelection.TabIndex = 1;
            this.fileSelection.Text = "file selection";
            this.fileSelection.UseVisualStyleBackColor = true;
            // 
            // StartButton
            // 
            this.StartButton.Location = new System.Drawing.Point(458, 419);
            this.StartButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(182, 48);
            this.StartButton.TabIndex = 8;
            this.StartButton.Text = "start machining";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // FileBox
            // 
            this.FileBox.FormattingEnabled = true;
            this.FileBox.ItemHeight = 25;
            this.FileBox.Location = new System.Drawing.Point(290, 73);
            this.FileBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.FileBox.Name = "FileBox";
            this.FileBox.Size = new System.Drawing.Size(499, 254);
            this.FileBox.TabIndex = 4;
            // 
            // ChooseFileButton
            // 
            this.ChooseFileButton.Location = new System.Drawing.Point(458, 361);
            this.ChooseFileButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.ChooseFileButton.Name = "ChooseFileButton";
            this.ChooseFileButton.Size = new System.Drawing.Size(182, 36);
            this.ChooseFileButton.TabIndex = 0;
            this.ChooseFileButton.Text = "choose file";
            this.ChooseFileButton.UseVisualStyleBackColor = true;
            this.ChooseFileButton.Click += new System.EventHandler(this.ChooseFileButton_Click);
            // 
            // navigationMenu
            // 
            this.navigationMenu.Controls.Add(this.QuitButton);
            this.navigationMenu.Controls.Add(this.ConnectTabButton);
            this.navigationMenu.Controls.Add(this.StartAppButton);
            this.navigationMenu.Location = new System.Drawing.Point(8, 39);
            this.navigationMenu.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.navigationMenu.Name = "navigationMenu";
            this.navigationMenu.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.navigationMenu.Size = new System.Drawing.Size(1188, 664);
            this.navigationMenu.TabIndex = 0;
            this.navigationMenu.Text = "navigation menu";
            this.navigationMenu.UseVisualStyleBackColor = true;
            // 
            // QuitButton
            // 
            this.QuitButton.Location = new System.Drawing.Point(450, 347);
            this.QuitButton.Margin = new System.Windows.Forms.Padding(6);
            this.QuitButton.Name = "QuitButton";
            this.QuitButton.Size = new System.Drawing.Size(208, 69);
            this.QuitButton.TabIndex = 3;
            this.QuitButton.Text = "quit application";
            this.QuitButton.UseVisualStyleBackColor = true;
            this.QuitButton.Click += new System.EventHandler(this.QuitButton_Click);
            // 
            // ConnectTabButton
            // 
            this.ConnectTabButton.Location = new System.Drawing.Point(450, 273);
            this.ConnectTabButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.ConnectTabButton.Name = "ConnectTabButton";
            this.ConnectTabButton.Size = new System.Drawing.Size(208, 64);
            this.ConnectTabButton.TabIndex = 2;
            this.ConnectTabButton.Text = "connect to device";
            this.ConnectTabButton.UseVisualStyleBackColor = true;
            this.ConnectTabButton.Click += new System.EventHandler(this.ConnectTabButton_Click);
            // 
            // StartAppButton
            // 
            this.StartAppButton.Location = new System.Drawing.Point(450, 206);
            this.StartAppButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.StartAppButton.Name = "StartAppButton";
            this.StartAppButton.Size = new System.Drawing.Size(208, 59);
            this.StartAppButton.TabIndex = 0;
            this.StartAppButton.Text = "start";
            this.StartAppButton.UseVisualStyleBackColor = true;
            this.StartAppButton.Click += new System.EventHandler(this.StartAppButton_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.navigationMenu);
            this.tabControl1.Controls.Add(this.fileSelection);
            this.tabControl1.Controls.Add(this.CncProgress);
            this.tabControl1.Controls.Add(this.connection);
            this.tabControl1.Location = new System.Drawing.Point(-4, -6);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1204, 711);
            this.tabControl1.TabIndex = 0;
            // 
            // TemperatureLabel
            // 
            this.TemperatureLabel.AutoSize = true;
            this.TemperatureLabel.Location = new System.Drawing.Point(212, 517);
            this.TemperatureLabel.Name = "TemperatureLabel";
            this.TemperatureLabel.Size = new System.Drawing.Size(134, 25);
            this.TemperatureLabel.TabIndex = 7;
            this.TemperatureLabel.Text = "Temperature";
            this.CncProgress.Controls.Add(this.TemperatureLabel);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1200, 703);
            this.Controls.Add(this.tabControl1);
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.Name = "Form1";
            this.Text = " ";
            this.connection.ResumeLayout(false);
            this.connection.PerformLayout();
            this.CncProgress.ResumeLayout(false);
            this.CncProgress.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ProgressCanvasBox)).EndInit();
            this.fileSelection.ResumeLayout(false);
            this.navigationMenu.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);


        }

        #endregion

        private System.Windows.Forms.TabPage connection;
        private System.Windows.Forms.ListBox ConnectionBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox IPBox;
        private System.Windows.Forms.Button QuitConnectionButton;
        private System.Windows.Forms.Button ConnectButton;
        private System.Windows.Forms.TabPage CncProgress;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Button EStopButton;
        private System.Windows.Forms.Button ResumeButton;
        private System.Windows.Forms.Button PauseButton;
        private System.Windows.Forms.TabPage fileSelection;
        private System.Windows.Forms.Button ChooseFileButton;
        private System.Windows.Forms.TabPage navigationMenu;
        private System.Windows.Forms.Button QuitButton;
        private System.Windows.Forms.Button ConnectTabButton;
        private System.Windows.Forms.Button StartAppButton;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.ListBox FileBox;
        private System.Windows.Forms.PictureBox ProgressCanvasBox;
        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Label TemperatureLabel;
    }
}


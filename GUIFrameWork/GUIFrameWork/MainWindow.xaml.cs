using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;
using System.Threading;
using System.Windows.Threading;

namespace GUIFrameWork
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool stopthread = false;
        string _path;
        Thread t;
        Intermediate.Mapper m;
        public MainWindow()
        {
            InitializeComponent();
            m = new Intermediate.Mapper();
        }
        #region events
        private void btnChooseImage_Click_1(object sender, RoutedEventArgs e)
        {
            string imagepath = GetSelectedFile();

            _path = imagepath;

            byte[] arrayofbytes = File.ReadAllBytes(imagepath);
            SetImageData(arrayofbytes);
        }

        private void btnProcessImage_Click_1(object sender, RoutedEventArgs e)
        {
            this.processedworkingImage.Source = Intermediate.Mapper.ProcessImage(_path);
        }
        #endregion

        #region methods
        public string GetSelectedFile()
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Image Files | *.jpg;*.bmp;*.png";
            string selectedFile = null;
            Nullable<bool> result = ofd.ShowDialog();
            if (result.HasValue == true && result.Value == true)
            {
                selectedFile = ofd.FileName;
            }
            return selectedFile;
        }

        public void SetImageData(byte[] data)
        {
            var source = new BitmapImage();
            source.BeginInit();
            source.StreamSource = new MemoryStream(data);
            source.EndInit();
            this.workingImage.Source = source;
        }

        #endregion
        public delegate void CallThread();
        private void btnStartVideo_Click_1(object sender, RoutedEventArgs e)
        {
            CallThread delegat = new CallThread(ThreadFunction);
            ThreadStart ts = new ThreadStart(delegat);
            if (t != null)
                t.Abort();
            t = new Thread(ts);
            t.Start();
            
        }
        void ThreadFunction()
        {
            while (!stopthread)
            {
                Dispatcher.Invoke(new Action(() => {
                    this.processedworkingImage.Source = Intermediate.Mapper.ProcessVideoFrame();
                }), DispatcherPriority.ContextIdle);
                
            }
        }
        private void btnStopVideo_Click_1(object sender, RoutedEventArgs e)
        {
            
            stopthread = true;
            if (t != null)
                t.Abort();
        }

        private void Window_Closing_1(object sender, System.ComponentModel.CancelEventArgs e)
        {
            stopthread = true;
            if (t != null)
                t.Abort();
            t = null;
        }

    }
}

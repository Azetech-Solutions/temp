using File_TryAccess_Tool.Forms;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace File_TryAccess_Tool.Class
{
    public class preloadHandling
    {
        Preloadform wait;
        Thread loadPreloadform;

        public void showWaitState()
        {
            loadPreloadform = new Thread(new ThreadStart(loadingprocess));
            loadPreloadform.Start();
        }

        public void showWaitState(Form parent)
        {            
            loadPreloadform = new Thread(new ParameterizedThreadStart(loadingprocess));
            loadPreloadform.Start(parent);
        }

        public void closeWaitState()
        {
            if(wait  != null)
            {
                wait.BeginInvoke(new System.Threading.ThreadStart(wait.closePreloadform));
                wait = null;
                loadPreloadform = null;
            }
        }

        private void loadingprocess()
        {
            wait = new Preloadform();
            wait.ShowDialog();
        }

        private void loadingprocess(Object parent)
        {
            Form parent1 = parent as Form;
            wait = new Preloadform(parent1);
            wait.ShowDialog();
        }
             
    }
}

using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace GtaVOptimizer.Tray
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            ApplicationConfiguration.Initialize();
            var menu = new ContextMenuStrip();
            menu.Items.Add("Attach to GTA5.exe", null, (_, __) => Attach());
            menu.Items.Add("Open log", null, (_, __) =>
                Process.Start("notepad.exe", "gta5-fps-unlocker.log"));
            menu.Items.Add("Exit", null, (_, __) => Application.Exit());

            var tray = new NotifyIcon
            {
                Icon = SystemIcons.Application,
                Text = "GtaV-Optimizer",
                ContextMenuStrip = menu,
                Visible = true
            };
            Application.Run();
        }

        static void Attach()
        {
            var psi = new ProcessStartInfo("gta5-optimizer.exe")
            {
                UseShellExecute = true,
                Verb = "runas"
            };
            Process.Start(psi);
        }
    }
}
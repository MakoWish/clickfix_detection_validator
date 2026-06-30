using System;
using System.Diagnostics;
using System.IO;
using System.Text;

internal static class Program
{
    private static int Main(string[] args)
    {
        string docs = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
        string workDir = Path.Combine(docs, "928252966059280400");
        Directory.CreateDirectory(workDir);

        string marker = Path.Combine(workDir, "clickfix-sim-payload.txt");
        string exePath = Process.GetCurrentProcess().MainModule?.FileName ?? "(unknown)";

        var sb = new StringBuilder();
        sb.AppendLine("Benign ClickFix validation payload executed.");
        sb.AppendLine("TimestampUtc=" + DateTimeOffset.UtcNow.ToString("O"));
        sb.AppendLine("User=" + Environment.UserDomainName + "\\" + Environment.UserName);
        sb.AppendLine("Host=" + Environment.MachineName);
        sb.AppendLine("ExecutablePath=" + exePath);
        sb.AppendLine("Arguments=" + string.Join(" ", args));
        sb.AppendLine();

        File.AppendAllText(marker, sb.ToString());

        Console.WriteLine("Benign ClickFix validation payload executed.");
        Console.WriteLine("Marker: " + marker);

        return 0;
    }
}

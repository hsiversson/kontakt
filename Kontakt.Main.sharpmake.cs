using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading.Tasks;
using Sharpmake;
using Sharpmake.Generators.FastBuild;

namespace Kontakt
{
    public static class Main
    {
        private static void ConfigureRootDirectory()
        {
            FileInfo fileInfo = Util.GetCurrentSharpmakeFileInfo();
            string rootDirectory = Path.Combine(fileInfo.DirectoryName, Globals.RelativeRootPath);
            Globals.RootDirectory = Util.SimplifyPath(rootDirectory);
        }

        private static void ConfigureAutoCleanup()
        {
            Util.FilesAutoCleanupActive = true;
            Util.FilesAutoCleanupDBPath = Path.Combine(Globals.TmpDirectory, "sharpmake");

            if (!Directory.Exists(Util.FilesAutoCleanupDBPath))
                Directory.CreateDirectory(Util.FilesAutoCleanupDBPath);
        }

        [Sharpmake.Main]
        public static void SharpmakeMain(Sharpmake.Arguments arguments)
        {
            ConfigureRootDirectory();
            ConfigureAutoCleanup();

            FastBuildSettings.FastBuildWait = true;
            FastBuildSettings.FastBuildSummary = false;
            FastBuildSettings.FastBuildNoSummaryOnError = true;
            FastBuildSettings.FastBuildDistribution = false;
            FastBuildSettings.FastBuildMonitor = true;
            FastBuildSettings.FastBuildAllowDBMigration = true;

            // for the purpose of this sample, we'll reuse the FastBuild executables that live in the sharpmake source repo
            string sharpmakeFastBuildDir = Util.PathGetAbsolute(Globals.RootDirectory, @"..\..\..\tools\FastBuild");
            switch (Util.GetExecutingPlatform())
            {
                case Platform.linux:
                    FastBuildSettings.FastBuildMakeCommand = Path.Combine(sharpmakeFastBuildDir, "Linux-x64", "fbuild");
                    break;
                case Platform.mac:
                    FastBuildSettings.FastBuildMakeCommand = Path.Combine(sharpmakeFastBuildDir, "OSX-x64", "FBuild");
                    break;
                case Platform.win64:
                default:
                    FastBuildSettings.FastBuildMakeCommand = Path.Combine(sharpmakeFastBuildDir, "Windows-x64", "FBuild.exe");
                    break;
            }

            Bff.UnityResolver = new Bff.FragmentUnityResolver();

            foreach (Type solutionType in Assembly.GetExecutingAssembly().GetTypes().Where(t => !t.IsAbstract && t.IsSubclassOf(typeof(CommonSolution))))
                arguments.Generate(solutionType);
        }
    }
}
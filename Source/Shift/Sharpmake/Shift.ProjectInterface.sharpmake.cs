using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using Sharpmake;

namespace Shift
{
    public class ProjectInterface : Project
    {
        public string SourceFolderPath        = @"[project.RootPath]\" + Globals.ProjectSourceFolderPath;
        public string ShiftSourceFolderPath   = @"[project.RootPath]\" + Globals.ShiftSourceFolderPath;
        public string DataFolderPath          = @"[project.RootPath]\Data";
        public string ExternalFolderPath      = @"[project.SourceFolderPath]\External";
        public string ShiftExternalFolderPath = @"[project.ShiftSourceFolderPath]\External";
        public string ProjectsFolderPath      = "[project.SourceRootPath]";
        public string OutputFolderPath        = @"[project.SourceFolderPath]\" + Globals.OutputFolderName;
        public string IntermediateFolderPath  = @"[project.SourceFolderPath]\" + Globals.IntermediateFolderName;
        public string TempFolderPath          = @"[project.SourceFolderPath]\" + Globals.TempFolderName;

        public bool EnableVersionStampingPostBuild = false;
        public bool EnableStandardPlatformExcludes = true;

        public ProjectInterface()
            : base(typeof(Target))
        {
            RootPath = Globals.AbsoluteRootPath;

            SourceRootPath = string.Empty;
            IsFileNameToLower = false;
            IsTargetFileNameToLower = false;

            DependenciesOrder = DependenciesOrderFirst;

            ResourceFilesExtensions.Add(".ico", ".rc");
        }

        [Configure]
        [ConfigurePriority(-100)]
        public virtual void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            aConfig.Name = "[target.Name]";
            aConfig.ProjectFileName = "[project.Name]";
            aConfig.ProjectPath = "[project.ProjectsFolderPath]";
            aConfig.TargetPath = @"[project.OutputFolderPath]\[target.DirectoryName]";
            aConfig.IntermediatePath = @"[project.IntermediateFolderPath]\[target.DirectoryName]\[project.Name]";
            aConfig.TargetLibraryPath = aConfig.IntermediatePath;

            //aConfig.CreateTargetCopyCommand = Utilities.CreateCopyCommandWithRobocopy;

            string platformString = aTarget.PlatformString.ToLowerInvariant();
            string blobPlatformString = platformString;
            aConfig.BlobPath = $@"[project.TempFolderPath]\blob\[project.Name]_{blobPlatformString}_[target.DevEnvironment]";
            
            if (aTarget.OutputType == OutputType.Dll)
                aConfig.Output = Configuration.OutputType.Dll;
            else
                aConfig.Output = Configuration.OutputType.Lib;

            aConfig.TargetFileSuffix = "[target.TargetSuffix]";

            aConfig.Options.Add(Options.Vc.General.PreferredToolArchitecture.x64);
            aConfig.Options.Add(Options.Vc.Compiler.FloatingPointModel.Fast);
            aConfig.Options.Add(Options.Vc.Compiler.RTTI.Enable);
            aConfig.Options.Add(Options.Vc.Compiler.CppLanguageStandard.Latest);
            aConfig.Options.Add(Options.Vc.General.WarningLevel.Level4);
            aConfig.Options.Add(Options.Vc.General.DebugInformation.ProgramDatabase);
            aConfig.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);
            aConfig.Options.Add(Options.Vc.Linker.GenerateDebugInformation.Enable);
            aConfig.Options.Add(Options.Vc.Linker.LargeAddress.Default);
            aConfig.Options.Add(Options.Vc.Compiler.Exceptions.Enable);
        }

        [Configure(Platform.win32 | Platform.win64)]
        [ConfigurePriority(5)]
        public virtual void ConfigureMicrosoft(Configuration aConfig, Target aTarget)
        {
            var disabledWarnings = new Options.Vc.Compiler.DisableSpecificWarnings();
            disabledWarnings.Add(
                "4201",     // Nonstandard extension used: nameless struct/union.
                "26495",    // Variable <var> is uninitialized. Always initializea member variable.
                "26812"    // Prefer 'enum class' over 'enum'.
                );

            aConfig.Options.Add(disabledWarnings);

            aConfig.Options.Add(Options.Vc.Librarian.TreatLibWarningAsErrors.Enable);
            aConfig.Options.Add(Options.Vc.Linker.TreatLinkerWarningAsErrors.Enable);
            aConfig.Options.Add(
                new Options.Vc.Linker.DisableSpecificWarnings(
                "4211",     // LNK4211: This object file does not define any previously undefined public symbols.
                "4099"      // LNK4099: PDB not found.
                )
            );
            aConfig.Options.Add(
                new Options.Vc.Librarian.DisableSpecificWarnings(
                "4211",     // LNK4211: This object file does not define any previously undefined public symbols.
                "4099"      // LNK4099: PDB not found.
                )
            );
        }

        [Configure(Platform.win64)]
        public virtual void ConfigureWin64(Configuration aConfig, Target aTarget)
        {
            aConfig.Defines.Add(
                "WIN64",
                "_WINDOWS"
            );
        }

        [Configure]
        [ConfigurePriority(100)]
        public virtual void PostConfigAll(Configuration aConfig, Target aTarget)
        {

        }

        private static string ProjectFilter = @"^\s*/[/|\*]\s*ProjectFilter\(([^\)]+)\)";
        private string ParseProjectFilterEntry(string aFilePath)
        {
            StreamReader fileReader = new StreamReader(aFilePath);
            string line = fileReader.ReadLine();
            if (line == null)
                return null;

            Match match = Regex.Match(line, ProjectFilter, RegexOptions.IgnoreCase);
            if (!match.Success || match.Groups.Count != 2)
                return null;

            string filter = match.Groups[1].ToString();
            return filter.Replace('/', '\\');
        }
        
        private Dictionary<string, string> FilterPathCache = new Dictionary<string, string>();
        public override bool ResolveFilterPathForFile(string aRelativeFilePath, out string aFilterPath)
        {
            aFilterPath = null;

            bool result = false;
            lock (FilterPathCache)
            {
                result = FilterPathCache.TryGetValue(aRelativeFilePath, out aFilterPath);
            }

            if (!result)
            {
                string absolutePath = Path.Combine(SourceRootPath, aRelativeFilePath);
                if (File.Exists(absolutePath))
                    aFilterPath = ParseProjectFilterEntry(absolutePath);

                lock (FilterPathCache)
                {
                    FilterPathCache[aRelativeFilePath] = aFilterPath;
                }
            }

            return aFilterPath != null;
        }
    }
}
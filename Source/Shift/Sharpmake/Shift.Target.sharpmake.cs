using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using Sharpmake;

[module: Sharpmake.Reference("Sharpmake.CommonPlatforms.dll")]

namespace Shift
{

    [Fragment, Flags]
    public enum BuildConfiguration
    {
        Debug = 1 << 0,
        Release = 1 << 1,
        Shipping = 1 << 2
    }

    [Fragment, Flags]
    public enum Compiler
    {
        MSVC = 1 << 0,
        Clang = 1 << 1
    }

    [Fragment, Flags]
    public enum TargetType
    {
        Default = 1 << 0,
        Server = 1 << 1
    }

    [Fragment, Flags]
    public enum IncludeWhatYouUse
    {
        Disabled = 1 << 0,
        Enabled = 1 << 1
    }

    [Fragment, Flags]
    public enum OutputType
    {
        Lib = 1 << 0,
        Dll = 1 << 1
    }

    public static class Extensions
    {
        public static string ToPlatformString(this Platform aPlatform)
        {
            return aPlatform.ToString();
        }
    }

    [DebuggerDisplay("\"{Platform}_{DevEnv}\" {Name}")]
    public class Target : Sharpmake.ITarget
    {
        public Platform Platform;
        public BuildConfiguration BuildConfig;
        public Compiler Compiler;
        public TargetType TargetType;
        public DevEnv DevEnvironment;
        public IncludeWhatYouUse IncludeWhatYouUse;
        public BuildSystem BuildSystem;
        public OutputType OutputType;

        private static readonly bool IsVisualStudio22Available = !string.IsNullOrEmpty(Util.GetVisualStudioInstallPathFromQuery(DevEnv.vs2022, allowPrereleaseVersions: true));
        
        private string _PlatformString;
        public string PlatformString
        {
            get { return _PlatformString ?? (_PlatformString = Platform.ToPlatformString()); }
        }

        public string NameForSolution
        {
            get
            {
                string name = BuildConfig.ToString();
                if (BuildSystem == BuildSystem.FastBuild)
                {
                    name += "_" + BuildSystem.FastBuild;
                    // if (BlobType == BlobType.NoBlob)
                    //      name += "_NoBlob";
                }

                if (TargetType != TargetType.Default)
                    name += "_" + TargetType;

                if (IncludeWhatYouUse == IncludeWhatYouUse.Enabled)
                    name += "_IWYU";

                return name;
            }
        }

        public string DirectoryName
        {
            get
            {
                var dirNameParts = new List<string>();
                dirNameParts.Add(BuildConfig.ToString());
                if (BuildSystem == BuildSystem.FastBuild)
                    dirNameParts.Add(BuildSystem.ToString());

                if (TargetType != TargetType.Default)
                    dirNameParts.Add(TargetType.ToString());

                if (IncludeWhatYouUse == IncludeWhatYouUse.Enabled)
                    dirNameParts.Add(IncludeWhatYouUse.ToString());

                dirNameParts.Add(DevEnvironment.ToString());

                return string.Join("_", dirNameParts);
            }
        }

        public string TargetSuffix
        {
            get
            {
                StringBuilder result = new StringBuilder();
                if (Platform == Platform.linux)
                {
                    result.Append("_linux");
                }
                else
                    result.Append("_" + PlatformString);

                return result.ToString().ToLower();
            }
        }

        public Target() {}

        public Target(
            Platform aPlatform,
            BuildConfiguration aBuildConfig,
            Compiler aCompiler,
            TargetType aTargetType,
            DevEnv aDevEnvironment,
            IncludeWhatYouUse aIncludeWhatYouUse = IncludeWhatYouUse.Disabled,
            BuildSystem aBuildSystem = BuildSystem.MSBuild,
            OutputType aOutputType = OutputType.Lib
        )
        {
            Platform = aPlatform;
            BuildConfig = aBuildConfig;
            Compiler = aCompiler;
            TargetType = aTargetType;
            DevEnvironment = aDevEnvironment;
            IncludeWhatYouUse = aIncludeWhatYouUse;
            BuildSystem = aBuildSystem;
            OutputType = aOutputType;

            if (IsVisualStudio22Available)
                DevEnvironment |= DevEnv.vs2022;
            else
                DevEnvironment = DevEnvironment.RemoveFlag(DevEnv.vs2022);
        }

        public static DevEnv GetDefaultDevEnvironment()
        {
            return DevEnv.vs2022;
        }

        public static BuildConfiguration GetDefaultBuildConfiguration()
        {
            return BuildConfiguration.Debug | BuildConfiguration.Release | BuildConfiguration.Shipping;
        }

        public static Target[] GetDefaultTargets(bool aUseFastBuild = false, BuildConfiguration? aBuildConfig = null)
        {
            List<Target> targets = new List<Target>();
            targets.AddRange(GetWin64Targets(aUseFastBuild, aBuildConfig));

            return targets.ToArray();
        }

        public static Target[] GetWin64Targets(bool aUseFastBuild = false, BuildConfiguration? aBuildConfig = null)
        {
            List<Target> targets = new List<Target>();
            BuildConfiguration buildConfig = aBuildConfig.HasValue ? aBuildConfig.Value : GetDefaultBuildConfiguration();

            IncludeWhatYouUse iwyuMask = IncludeWhatYouUse.Disabled;
            if (Globals.CustomArgs.GenerateIWYUSolution)
                iwyuMask |= IncludeWhatYouUse.Enabled;

            targets.Add(
                new Target(
                    Platform.win64,
                    buildConfig,
                    GetWin64Compiler(),
                    TargetType.Default,
                    GetDefaultDevEnvironment(),
                    iwyuMask,
                    BuildSystem.MSBuild
                )
            );

            if (Globals.CustomArgs.EnableFastBuild && aUseFastBuild)
            {
                targets.Add(
                    new Target(
                        Platform.win64,
                        buildConfig,
                        GetWin64Compiler(),
                        TargetType.Default,
                        GetDefaultDevEnvironment(),
                        iwyuMask,
                        BuildSystem.FastBuild
                    )
                );
            }

            if (Globals.TargetDelegate != null)
                targets.AddRange(Globals.TargetDelegate(aUseFastBuild, aBuildConfig));

            return targets.ToArray();
        }

        public static Compiler GetWin64Compiler()
        {
            return Compiler.MSVC;
        }
    }

}
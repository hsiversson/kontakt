using System;
using System.Collections.Generic;
using Sharpmake;

namespace Shift
{
    public static class Globals
    {
        public static string RelativeRootPath = @"..\";
        public static string AbsoluteRootPath = string.Empty;

        public static string Username = Environment.GetEnvironmentVariable("USERNAME") ?? Environment.GetEnvironmentVariable("USER");

        public static string ProjectSourceFolderPath = @"Source";
        public static string ShiftSourceFolderPath = @"Source\Shift";

        public static string OutputFolderName = "Build_Output";
        public static string IntermediateFolderName = "Build_Intermediate";
        public static string TempFolderName = "Build_Temp";

        public static ShiftArguments CustomArgs = new ShiftArguments();

        public delegate Target[] CustomTargetDelegate(bool aUseFastBuild, BuildConfiguration? aBuildConfig);
        public static CustomTargetDelegate TargetDelegate;
    }
}
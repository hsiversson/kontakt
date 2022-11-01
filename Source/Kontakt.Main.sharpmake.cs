using System;
using System.Collections.Generic;
using System.IO;
using Sharpmake;
using Shift;

[module: Sharpmake.Include("Kontakt/Kontakt.sharpmake.cs")]
[module: Sharpmake.Include("Shift/Sharpmake/Shift.sharpmake.cs")]

namespace Kontakt
{
    public static class Main
    {
        static void ConfigureProject(Project.Configuration aConfiguration, Shift.Target aTarget)
        {
            //aConfiguration.Defines.Add();
        }

        [Sharpmake.Main]
        public static void SharpmakeMain(Sharpmake.Arguments aArguments)
        {

            FileInfo sharpmakeFileInfo = Util.GetCurrentSharpmakeFileInfo();
            string sharpmakeFileDir = Util.PathMakeStandard(sharpmakeFileInfo.DirectoryName);
            Shift.Globals.AbsoluteRootPath = Util.PathGetAbsolute(sharpmakeFileDir, Shift.Globals.RelativeRootPath);
            //Shift.Globals.ProjectName = "Kontakt";

            aArguments.Generate<KontaktSolution>();
        }
    }
}
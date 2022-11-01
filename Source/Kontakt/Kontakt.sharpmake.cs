using System.Collections.Generic;
using Shift;

[module: Sharpmake.Include("KClient/KClient.sharpmake.cs")]
[module: Sharpmake.Include("KClientExe/KClientExe.sharpmake.cs")]
[module: Sharpmake.Include("KShared/KShared.sharpmake.cs")]

namespace Kontakt
{
    [Sharpmake.Generate]
    public class KontaktProject : ProjectInterface
    {
        public KontaktProject()
        {
            SourceRootPath = @"[project.SourceFolderPath]\Kontakt\[project.Name]";
            EnableVersionStampingPostBuild = true;
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);
            aConfig.SolutionFolder = "3. Kontakt";
            //aConfig.AddPrivateDependency<Shift.Core.CommonProject>(aTarget);
        }
    }

    [Sharpmake.Generate]
    public class KontaktSolution : SolutionInterface
    {
        public KontaktSolution()
        {
            Name = "Kontakt";

            AddTargets(Target.GetWin64Targets());
            //AddTargets(Target.GetWin64ServerTargets());
        }

        public override void ConfigureWin64(Configuration aConfig, Target aTarget)
        {
            base.ConfigureWin64(aConfig, aTarget);

            if (aTarget.TargetType == TargetType.Default)
                aConfig.AddProject<Kontakt.KClientExeProject>(aTarget);
        }
    }
}
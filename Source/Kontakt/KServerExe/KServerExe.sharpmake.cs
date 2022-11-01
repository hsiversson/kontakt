using System.Collections.Generic;
using Shift;

namespace Kontakt
{
    [Sharpmake.Generate]
    public class KontaktProject : ProjectInterface
    {
        public KontaktProject()
        {
            SourceRootPath= @"[project.CodeFolderPath]\Kontakt\[project.name]";
            EnableVersionStampingPostBuild = true;
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.AddPrivateDependency<Shift.Core.CommonProject>(aTarget);
        }

        [Sharpmake.Generate]
        public class KontaktSolution : SolutionInterface
        {
            public KontaktSolution()
            {
                Name = "Kontakt";

                AddTargets(Target.GetWin64Targets());
                AddTargets(Target.GetWin64ServerTargets());
            }

            public override void ConfigureWin64(Configuration aConfig, Target aTarget)
            {
                base.ConfigureWin64(aConfig, aTarget);

                if (target.Usage == Usage.Common)
                    aConfig.AddProject<Kontakt.KClientExeProject>(target);
            }
        }
    }
}
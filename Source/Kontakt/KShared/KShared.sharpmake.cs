using System.Collections.Generic;
using System.Collections.Concurrent;
using System.IO;
using Shift;

namespace Kontakt
{
    [Sharpmake.Generate]
    public class KSharedProject : KontaktProject
    {
        public KSharedProject()
        {
            Name = "KShared";
            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);
            
            aConfig.PrecompHeader = "KShared_Precompiled.h";
            aConfig.PrecompSource = "KShared_Precompiled.cpp";

            aConfig.IncludePaths.Add("[project.SourceRootPath]");
        }

        public override void ConfigureWin64(Configuration aConfig, Target aTarget)
        {
            base.ConfigureWin64(aConfig, aTarget);
        }
    }
}
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.IO;
using Shift;

namespace Kontakt
{
    [Sharpmake.Generate]
    public class KServerProject : KontaktProject
    {
        public KServerProject()
        {
            Name = "KServer";
            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "KServer_Precompiled.h";
            aConfig.PrecompSource = "KServer_Precompiled.cpp";

            aConfig.IncludePaths.Add("[project.SourceRootPath]");

            aConfig.AddPrivateDependency<Kontakt.KSharedProject>(aTarget);
            //aConfig.AddPrivateDependency<Shift.Core.AppFrameworkProject>();
            //aConfig.AddPrivateDependency<Shift.Core.RenderProject>();
        }

        public override void ConfigureWin64(Configuration aConfig, Target aTarget)
        {
            base.ConfigureWin64(aConfig, aTarget);
        }
    }
}
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.IO;
using Shift;

namespace Kontakt
{
    [Sharpmake.Generate]
    public class KClientProject : KontaktProject
    {
        public KClientProject()
        {
            Name = "KClient";
            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "KClient_Precompiled.h";
            aConfig.PrecompSource = "KClient_Precompiled.cpp";

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
using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class AppFrameworkProject : CoreProject
    {
        public AppFrameworkProject()
        {
            Name = "AppFramework";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "AppFramework_Precompiled.h";
            aConfig.PrecompSource = "AppFramework_Precompiled.cpp";

            aConfig.AddPublicDependency<Shift.Core.CommonProject>(aTarget);
            aConfig.AddPublicDependency<Shift.Core.FacadeProject>(aTarget);
        }
    }
}
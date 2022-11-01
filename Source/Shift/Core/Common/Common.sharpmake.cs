using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class CommonProject : CoreProject
    {
        public CommonProject()
        {
            Name = "Common";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Common_Precompiled.h";
            aConfig.PrecompSource = "Common_Precompiled.cpp";

            aConfig.AddPublicDependency<Core.PlatformProject>(aTarget);
            aConfig.AddPublicDependency<Core.EngineTypesProject>(aTarget);
        }
    }
}
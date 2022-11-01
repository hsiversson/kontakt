using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class EngineTypesProject : CoreProject
    {
        public EngineTypesProject()
        {
            Name = "EngineTypes";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "EngineTypes_Precompiled.h";
            aConfig.PrecompSource = "EngineTypes_Precompiled.cpp";

            aConfig.AddPublicDependency<Core.PlatformProject>(aTarget);
        }
    }
}
using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class PlatformProject : CoreProject
    {
        public PlatformProject()
        {
            Name = "Platform";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Platform_Precompiled.h";
            aConfig.PrecompSource = "Platform_Precompiled.cpp";

            aConfig.Defines.Add("_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING");
        }
    }
}
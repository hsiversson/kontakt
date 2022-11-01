using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class AudioProject : CoreProject
    {
        public AudioProject()
        {
            Name = "Audio";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Audio_Precompiled.h";
            aConfig.PrecompSource = "Audio_Precompiled.cpp";
        }
    }
}
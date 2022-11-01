using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class NetworkProject : CoreProject
    {
        public NetworkProject()
        {
            Name = "Network";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Network_Precompiled.h";
            aConfig.PrecompSource = "Network_Precompiled.cpp";
        }
    }
}
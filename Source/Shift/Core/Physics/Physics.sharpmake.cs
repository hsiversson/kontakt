using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class PhysicsProject : CoreProject
    {
        public PhysicsProject()
        {
            Name = "Physics";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Physics_Precompiled.h";
            aConfig.PrecompSource = "Physics_Precompiled.cpp";
        }
    }
}
using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class InputOutputProject : CoreProject
    {
        public InputOutputProject()
        {
            Name = "InputOutput";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "InputOutput_Precompiled.h";
            aConfig.PrecompSource = "InputOutput_Precompiled.cpp";
        }
    }
}
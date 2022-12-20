using System;
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class FacadeProject : CoreProject
    {
        public FacadeProject()
        {
            Name = "Facade";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Facade_Precompiled.h";
            aConfig.PrecompSource = "Facade_Precompiled.cpp";

            aConfig.AddPrivateDependency<Shift.Core.CommonProject>(aTarget);
            aConfig.AddPublicDependency<Shift.Core.RenderProject>(aTarget);
        }
    }
}
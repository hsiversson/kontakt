
using Sharpmake;

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class RenderProject : CoreProject
    {
        public RenderProject()
        {
            Name = "Render";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Render_Precompiled.h";
            aConfig.PrecompSource = "Render_Precompiled.cpp";

            aConfig.AddPrivateDependency<Core.CommonProject>(aTarget);
        }

        public override void ConfigureWin64(Configuration aConfig, Target aTarget)
        {
            base.ConfigureWin64(aConfig, aTarget);


        }
    }
}
namespace Shift.Submodules
{
    [Sharpmake.Generate]
    public class GraphicsProject : SubmodulesProject
    {
        public GraphicsProject()
        {
            Name = "Graphics";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Graphics_Precompiled.h";
            aConfig.PrecompSource = "Graphics_Precompiled.cpp";

            aConfig.AddPublicDependency<Core.RenderProject>(aTarget);
        }
    }
}
namespace Shift.Submodules
{
    [Sharpmake.Generate]
    public class EditorProject : SubmodulesProject
    {
        public EditorProject()
        {
            Name = "Editor";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "Editor_Precompiled.h";
            aConfig.PrecompSource = "Editor_Precompiled.cpp";

            aConfig.AddPrivateDependency<GraphicsProject>(aTarget);
            aConfig.AddPrivateDependency<GameEntityProject>(aTarget);
            aConfig.AddPrivateDependency<Core.AppFrameworkProject>(aTarget);
        }
    }
}
namespace Shift.Submodules
{
    [Sharpmake.Generate]
    public class GameEntityProject : SubmodulesProject
    {
        public GameEntityProject()
        {
            Name = "GameEntity";

            AddTargets(Target.GetDefaultTargets());
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.PrecompHeader = "GameEntity_Precompiled.h";
            aConfig.PrecompSource = "GameEntity_Precompiled.cpp";
        }
    }
}
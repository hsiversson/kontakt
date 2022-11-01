[module: Sharpmake.Include("GameEntity/GameEntity.sharpmake.cs")]
[module: Sharpmake.Include("Graphics/Graphics.sharpmake.cs")]

namespace Shift.Submodules
{
    [Sharpmake.Generate]
    public class SubmodulesProject : ProjectInterface
    {
        public SubmodulesProject()
        {
            SourceRootPath = @"[project.SharpmakeCsPath]";
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.SolutionFolder = "2. Submodules";
            aConfig.IncludePaths.Add("[project.SourceRootPath]");

            aConfig.AddPrivateDependency<Core.CommonProject>(aTarget);
        }
    }
}
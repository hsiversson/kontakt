[module: Sharpmake.Include("AppFramework/AppFramework.sharpmake.cs")]
[module: Sharpmake.Include("Audio/Audio.sharpmake.cs")]
[module: Sharpmake.Include("Common/Common.sharpmake.cs")]
[module: Sharpmake.Include("EngineTypes/EngineTypes.sharpmake.cs")]
[module: Sharpmake.Include("Facade/Facade.sharpmake.cs")]
[module: Sharpmake.Include("InputOutput/InputOutput.sharpmake.cs")]
[module: Sharpmake.Include("Network/Network.sharpmake.cs")]
[module: Sharpmake.Include("Physics/Physics.sharpmake.cs")]
[module: Sharpmake.Include("Platform/Platform.sharpmake.cs")]
[module: Sharpmake.Include("Render/Render.sharpmake.cs")]

namespace Shift.Core
{
    [Sharpmake.Generate]
    public class CoreProject : ProjectInterface
    {
        public CoreProject()
        {
            SourceRootPath = @"[project.ShiftSourceFolderPath]\Core\[project.Name]";
        }

        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.SolutionFolder = "1. Core";
            aConfig.IncludePaths.Add("[project.SourceRootPath]");
        }
    }
}
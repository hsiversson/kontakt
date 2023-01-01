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

        public override void ConfigureWin64(Configuration aConfig, Target aTarget)
        {
            base.ConfigureWin64(aConfig, aTarget);

            // assimp
            aConfig.IncludePaths.Add(@"[project.ShiftExternalFolderPath]\Assimp\include");
            aConfig.LibraryPaths.Add(@"[project.ShiftExternalFolderPath]\Assimp\lib");
            aConfig.LibraryFiles.Add("assimp-vc143-mt");
			aConfig.TargetCopyFiles.Add(@"[project.ShiftExternalFolderPath]\Assimp\bin\assimp-vc143-mt.dll");

            // msdfgen
            aConfig.IncludePaths.Add(@"[project.ShiftExternalFolderPath]\MSDFGen\include");
            aConfig.LibraryPaths.Add(@"[project.ShiftExternalFolderPath]\MSDFGen\lib");
            aConfig.LibraryFiles.Add("msdfgen-core");
            aConfig.LibraryFiles.Add("msdfgen-ext");
        }
    }
}
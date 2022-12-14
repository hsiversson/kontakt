
using System;
using System.IO;
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

            // DirectX Agility SDK
			aConfig.IncludePaths.Add(@"[project.ShiftExternalFolderPath]\D3D12\include");
			aConfig.TargetCopyFiles.Add(
				@"[project.ShiftExternalFolderPath]\D3D12\bin\d3d12core.dll",
				@"[project.ShiftExternalFolderPath]\D3D12\bin\d3d12sdklayers.dll"
			);

            // DirectX shader compiler
            aConfig.IncludePaths.Add(@"[project.ShiftExternalFolderPath]\DirectXShaderCompiler\include");
            aConfig.TargetCopyFiles.Add(
                @"[project.ShiftExternalFolderPath]\DirectXShaderCompiler\bin\dxcompiler.dll",
                @"[project.ShiftExternalFolderPath]\DirectXShaderCompiler\bin\dxil.dll"
            );

            // NvAPI
            aConfig.IncludePaths.Add(@"[project.ShiftExternalFolderPath]\Nvidia\nvapi\include");
            aConfig.LibraryPaths.Add(@"[project.ShiftExternalFolderPath]\Nvidia\nvapi\lib");
            aConfig.LibraryFiles.Add("nvapi64");
            
            // AGS
            aConfig.IncludePaths.Add(@"[project.ShiftExternalFolderPath]\AMD\ags\ags_lib\inc");
            aConfig.LibraryPaths.Add(@"[project.ShiftExternalFolderPath]\AMD\ags\ags_lib\lib");
            aConfig.LibraryFiles.Add("amd_ags_x64");
            aConfig.TargetCopyFiles.Add(@"[project.ShiftExternalFolderPath]\AMD\ags\ags_lib\lib\amd_ags_x64.dll");
        }
    }
}
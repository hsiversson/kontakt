using System.Collections.Generic;
using System.IO;
using Sharpmake;
using Shift;

namespace Kontakt
{
    [Sharpmake.Generate]
    public class KServerExeProject : KontaktProject
    {
        public KServerExeProject()
        {
            Name = "KServerExe";

            AddTargets(Shift.Target.GetWin64Targets());

            DeployProject = true;

            //XResourcesImg.Add(
            //    "kontakt-exe-icon.ico",
            //    "icon.ico"
            //);
        }

        public override void ConfigureAll(Configuration aConfig, Shift.Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);

            aConfig.SolutionFolder = "4. Executables";
            aConfig.Output = Configuration.OutputType.Exe;

            aConfig.TargetFileName = "KontaktClient_" + Util.GetSimplePlatformString(aTarget.Platform) + "_[target.BuildConfig]";
            aConfig.TargetFileSuffix = string.Empty;

            // No precompiled header
            aConfig.PrecompHeader = null;
            aConfig.PrecompSource = null;

            aConfig.Options.Add(Options.Vc.Linker.SubSystem.Windows);
            aConfig.Options.Add(Options.Vc.ManifestTool.EnableDpiAwareness.Yes);

            aConfig.AddPrivateDependency<Kontakt.KServerProject>(aTarget);
            aConfig.AddPrivateDependency<Shift.Core.AppFrameworkProject>(aTarget);
            aConfig.AddPrivateDependency<Shift.Core.RenderProject>(aTarget);
            aConfig.AddPrivateDependency<Shift.Submodules.GameEntityProject>(aTarget);
            aConfig.AddPrivateDependency<Shift.Submodules.GraphicsProject>(aTarget);

            //if (aTarget.Optimization != Shift.Optimization.Shipping)
            //{
            //    aConfig.AddPrivateDependency<Shift.EditorProject>(aTarget);
            //}
        }
    }
}
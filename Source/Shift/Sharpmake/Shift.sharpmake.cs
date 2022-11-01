[module: Sharpmake.Include("Shift.CommandLine.sharpmake.cs")]
[module: Sharpmake.Include("Shift.Globals.sharpmake.cs")]
[module: Sharpmake.Include("Shift.ProjectInterface.sharpmake.cs")]
[module: Sharpmake.Include("Shift.SolutionInterface.sharpmake.cs")]
[module: Sharpmake.Include("Shift.Target.sharpmake.cs")]
[module: Sharpmake.Include("Shift.Utilities.sharpmake.cs")]
[module: Sharpmake.Include("../Core/Core.sharpmake.cs")]
//[module: Sharpmake.Include("../External/External.sharpmake.cs")]
[module: Sharpmake.Include("../Submodules/Submodules.sharpmake.cs")]

namespace Shift
{
    public abstract class ShiftProject : ProjectInterface
    {
        public override void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            base.ConfigureAll(aConfig, aTarget);
            aConfig.SolutionFolder += "Shift/";
        }
    }
}
using Sharpmake;

namespace Shift
{
    public class SolutionInterface : Sharpmake.Solution
    {
        public string RootPath = Globals.AbsoluteRootPath;

        public SolutionInterface()
            : base(typeof(Target)) 
        {

        }

        [Configure]
        public virtual void ConfigureAll(Configuration aConfig, Target aTarget)
        {
            aConfig.SolutionPath = @"[solution.RootPath]\";
            
            string platformString = aTarget.PlatformString.ToLowerInvariant();

            aConfig.SolutionFileName = $"[solution.Name]_{platformString}_[target.DevEnvironment]";
            if (aTarget.IncludeWhatYouUse == IncludeWhatYouUse.Enabled)
                aConfig.SolutionFileName += "_IWYU";

            aConfig.Name = aTarget.NameForSolution;
            aConfig.IncludeOnlyNeededFastBuildProjects = false;

        }

        [Configure(Platform.win64)]
        public virtual void ConfigureWin64(Configuration aConfig, Target aTarget)
        {
            aConfig.PlatformName = "win64";
        }
    }
}
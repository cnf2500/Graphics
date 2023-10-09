//Name: Christopher Forte
//Date: 21/08/2023
//Email: cnf2500@gmail.com

using UnrealBuildTool;
using System.IO;

public class FirstLaurel : ModuleRules
{
    public FirstLaurel(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty/");

        // Add libcurl and OpenSSL include paths
        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ThirdPartyPath, "libcurl", "7.83.1", "include"),
                Path.Combine(ThirdPartyPath, "OpenSSL", "1.1.1n", "include", "Mac", "openssl")
            }
        );

        // Add libraries
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "libcurl", "7.83.1", "lib", "Mac", "Release", "libcurl.a"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "OpenSSL", "1.1.1n", "lib", "Mac", "libcrypto.a"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "OpenSSL", "1.1.1n", "lib", "Mac", "libssl.a"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "nghttp2", "1.47.0", "lib", "Mac", "Release", "libnghttp2.a"));

        // Link with SystemConfiguration and CoreLocation frameworks for macOS
        if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicFrameworks.AddRange(new string[] { "SystemConfiguration", "CoreLocation" });
        }

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Json", "JsonUtilities" });
    }
}


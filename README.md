# Core2 SDK
Core2 SDK is a rebuilding of FLCoreSDK. The original FLCoreSDK was very useful but suffered from some major drawbacks:

* Most virtual functions unusable due to incorrect position
* No determination of class inheritance hierarchy
* No reversal of non-exported classes
* No determination of member fields

The Core2 SDK Project aims to fix or at least alleviate these limitations by undertaking a more thorough analysis of FL's binaries, and in addition, take reversal "beyond" just the exported engine pieces to make even more advanced plugins and modifications possible.

Obviously a 100% accurate recreation of FL's source is impossible, but *most* functionality can still be determined or deduced. If you wish to contribute your own work to this project, feel free to submit a pull request.

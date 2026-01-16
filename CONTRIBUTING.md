# Contributing
## Before You Start
Decompilation is quite a hard skill for beginners, so we suggest exploring and learning how to use ghidra and understand C++/assembly. 
Contributions are generally taken in the form of pull requests, be it creation of stubs for a class or a complete implementation of a function.

## Ghidra Server
Since decompilation is a harder skill that takes a while to learn, write access to the ghidra server is limited to those who gain permission from us in the discord. 
In order to signup for the ghidra server, head to the [panel website](https://panel.bananapizzuh.dev/) and login with discord.

## General Decompilation Process
This section is not necessarily applicable to all cases, but it does apply to most. 
Since we are using the debug symbols from the Mac OS port of the game, we ideally cross reference everything we can. 
There are some significant differences in the logic of some functions between the target windows binary and the Mac OS binary. 
Despite these differences, most of the skeleton structure of the game can be taken with the symbols and then implemented to match the target.

### Function Matching
As previously mentioned, the structure is generally the same between the binaries so it quite trivial to match functions that both feature. 
This can usually be done by searching for a string used in the specific function you are looking at or by tracing the call path of the function to a common point.

### ModVals
SexyAppFramework has a feature called `ModVal`s which allow for hot reloading of variables to make development easier. 
For whatever reason, PopCap did not remove these from the final game. 
The intended way to use these is through the `M()` macro defined in ModVal.h. 
Since we are focusing on accuracy we will have to implement them as calling the actual `ModVal()` function to preserve the string (e.g. `ModVal(0, "SEXY_SEXYMODVALc:\\gamesrc\\cpp\\thunderball\\LoadingScreen.cpp383,66", 228)`).

### Reccmp
Since the project is set up to check accuracy with reccmp, we must add annotations to our functions and data. More details can be found [here.](https://github.com/isledecomp/reccmp/blob/master/docs/annotations.md)
We aim for a high percentage match with the functions, but ultimately as long as the logic is accurate to the original game is the priority.

## Questions
If you have any questions, you can ask them in our [discord server.](https://discord.gg/83D3CSVxsj)

# Peggle Deluxe Decompilation  
[Discord](https://discord.gg/83D3CSVxsj) | [Contributing](https://github.com/bananapizzuh/deluxe/blob/main/CONTRIBUTING.md) | [License](https://github.com/bananapizzuh/deluxe/blob/main/LICENSE.md)  

This project aims to decompile the English 1.01 executable of Peggle Deluxe from the steam release. Many variable and function names have been taken from the Mac OS port, as PopCap generously built those executables with debug symbols.

<p align="center">
 <img src="https://github.com/bananapizzuh/deluxe/raw/refs/heads/gh-pages/progress.svg" alt="Progress" />
</p>

## Building
Requirements:
 - CMake 3.18 or higher
 - Microsoft Visual C++ 14. A portable version can be obtained can be obtained [here.](https://github.com/bananapizzuh/msvc80-sp1)

Run `cmake -B build/ -G "NMake Makefiles"` then `cmake --build build` to build.

## Accuracy
For accuracy checking, we are using a tool derived from the Lego Island decompilation, [reccmp](github.com/isledecomp/reccmp). To install reccmp, install it through pip: `pip install git+https://github.com/isledecomp/reccmp`

## Acknowledgements
- Alula for their [Zuma Deluxe Decompilation](https://github.com/alula/CircleShootApp/) that this project is initially based on
- PopCap for making this wonderful game

## Legal
- This repository does not contain any game assets; you will need to get them from your own copy of the game. If you don't already own it, the Steam version is easily available to purchase: https://store.steampowered.com/app/3480/Peggle_Deluxe/






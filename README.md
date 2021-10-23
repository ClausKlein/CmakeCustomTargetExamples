# Howto generating files at build Time with CMake

Thanks to [Craig Scott](https://crascit.com/author/crascit/) for his Blog!


## A modified example from https://crascit.com/2017/04/18/generated-sources-in-cmake-builds/

Instead of using [https://cmake.org/cmake/help/latest/command/add_custom_target.html](add_custom_target)
to generate the sources manually, you should define custom `OUTPUTS <files>` with `DEPENDS <files>` using
[https://cmake.org/cmake/help/latest/command/add_custom_command.html](add_custom_command).

CMake can then automatically work out dependencies when those outputs are used as inputs to another target.


Sam Thursfield has
[https://samthursfield.wordpress.com/2015/11/21/cmake-dependencies-between-targets-and-files-and-custom-commands/](more
CMake tips) if you are interesed.


## CMake and Ninja can generate graphviz files showing the dependencies between the targets in a project

see [CMake generated](MyProj.svg)

and [Ninja generated](deps.svg)


This dependency trees [DAG](https://en.wikipedia.org/wiki/Directed_acyclic_graph) are generated with this
[CMakeLists.txt](CMakeLists.txt) and **dot**, a tool from [graphviz](https://graphviz.org/Gallery/directed/ninja.html)


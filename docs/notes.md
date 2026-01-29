# Notes

## Mechanics

### Failure Conditions:
1. **Total Erasure *(failure)***
    - population eliminated
    - culture extinguished
    - institutions destroyed
    - no successor identity

  ```
  population -> 0
  culture persistence -> 0
  institutional continuity -> 0
  ```
    true terminal failure, no trace of the society left

2. **Political loss, civilizational survival *(not failure)***
    - Conquered states that are absorbed into empires
    - Language, Technology, and Religion survive
    - Administrative Systems persist in some cases

    - civ A should be absorbed into civ B
    - A's traits partially overwrite B
    - Hybrid successor emerges

3. **Fragmentation under pressure *(soft failure)***
    - Core civilization remains alive but border regions defect
    - successor states form
    - civilization transforms instead of dying

    
  
## commands

### Windows

---

powershell command to build. run from project dir then open visual studio solution from build dir

This is if you have a global install of anaconda, you can replace this with your python environment. I personally found anaconda to be the easiest route to get this working on windows.

```ps
mkdir build # if doesn't exist already

cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DPython_EXECUTABLE=C:/ProgramData/anaconda3/envs/pybind/python.exe -DPython_INCLUDE_DIR=C:/ProgramData/anaconda3/envs/pybind/include -DPython_LIBRARY=C:/ProgramData/anaconda3/envs/pybind/libs/python314.lib
```
---

### Linux

bash command for linux users

``` bash
mkdir build # if doesn't exist already
cd build
cmake -S .. -B .
cmake --build . --config Debug
```
---
## sources
[pybind11 reference](https://pybind11.readthedocs.io/en/stable/index.html)
[cmake article on glob](https://www.w3tutorials.net/blog/how-to-use-all-c-files-in-a-directory-with-the-cmake-build-system/)

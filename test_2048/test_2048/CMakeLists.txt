# CMakeList.txt: Projekt CMake pro test_2048, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (test_2048 "test_2048.cpp" "test_2048.h" "praceSeSoubory.h" "praceSeSoubory.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test_2048 PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.

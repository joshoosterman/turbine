clang-format-3.3 -style=Google -i */*.h */*.cc
python cpplint.py */*.h */*.cc

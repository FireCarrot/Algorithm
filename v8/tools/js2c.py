import os, re, sys, string

def JS2C(source, target, env):
  ids = []
  delay_ids = []
  modules = []
  # Locate the macros file name.
  consts = {}
  macros = {}
  for s in source:
    if 'macros.py' == (os.path.split(str(s))[1]:
      (consts, macros) = ReadMacros(ReadLines(str(s)))
    else:
      modules.append(s)

  # Build source code lines
  source_lines = [ ]
  source_lines_empty = [ ]
  for s in modules:
    delay = str(s).endswith('-delay.js')
    lines = ReadFile(str(s))

def main():
  output = sys.argv[1]
  input = sys.argv[2:]
  JS2C(input, [output], None)

if __name__ == "__main__":
  main()

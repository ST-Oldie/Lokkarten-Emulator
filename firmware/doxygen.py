Import("env")

# Single action/command per 1 target
env.AddCustomTarget("doxygen", None, 'rm -r docs/doxygen/* ; doxygen Doxyfile')
